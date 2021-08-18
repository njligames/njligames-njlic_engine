#include "File.h"
#include "Log.h"
#import <UIKit/UIKit.h>

#include <string>
#include <vector>

static char s_Buffer[4098];

const char *RESOURCE_PATH()
{
  NSString *resourcePath = [[NSBundle mainBundle] resourcePath];
  return [resourcePath cStringUsingEncoding:NSASCIIStringEncoding];
}

const char *ASSET_PATH(const char *file)
{
  NSString *filePath = [[NSString alloc]
      initWithFormat:@"%s%@%s", DOCUMENT_BASEPATH(), @"assets/", file];

  if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
      strcpy(s_Buffer, [filePath UTF8String]);
      return s_Buffer;
    }

  NSMutableString *adjusted_relative_path =
      [[NSMutableString alloc] initWithString:@"assets/"];
  [adjusted_relative_path
      appendString:[[NSString alloc] initWithCString:file
                                            encoding:NSASCIIStringEncoding]];

  NSString *obj = [[NSBundle mainBundle] pathForResource:adjusted_relative_path
                                                  ofType:nil];

  SDL_assertCheck(obj != nil, "The path `%s`, doesn't exist", file);

  strcpy(s_Buffer, [obj cStringUsingEncoding:NSASCIIStringEncoding]);
  return s_Buffer;
}

const char *BUNDLE_PATH()
{
  NSMutableString *path = [[NSMutableString alloc]
      initWithString:[[NSBundle mainBundle] resourcePath]];
  [path appendString:[[NSString alloc] initWithCString:"/assets/"
                                              encoding:NSASCIIStringEncoding]];

  return [path UTF8String];
}

const char *DOCUMENT_PATH(const char *file)
{
  NSString *documentDirectory =
      [NSString stringWithCString:DOCUMENT_BASEPATH()
                         encoding:NSASCIIStringEncoding];
  NSString *filename = [[NSString alloc] initWithCString:file
                                                encoding:NSASCIIStringEncoding];
  NSString *fullFilename =
      [documentDirectory stringByAppendingPathComponent:filename];

  return [fullFilename UTF8String];
}

void setRunningPath(const char *file) {}

void setScriptDir(const char *path) {}

void setAssetPath(const char *path) {}

const char *DOCUMENT_BASEPATH()
{
  NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                       NSUserDomainMask, YES);
  NSString *documentsDirectory =
      [paths objectAtIndex:0]; // Get documents folder
                               //  return [documentsDirectory UTF8String];

  return [[NSString stringWithFormat:@"%@/", documentsDirectory] UTF8String];
}

void sleepThread(float milliseconds)
{
  [NSThread sleepForTimeInterval:milliseconds];
}

// static int createFolder(NSString *folderName)
//{
//    NSString *filePath = [[NSString alloc]
//    initWithCString:DOCUMENT_PATH([folderName UTF8String])
//    encoding:NSASCIIStringEncoding];
//
//    if (![[NSFileManager defaultManager] fileExistsAtPath:filePath])
//    {
//         NSError *error;
//        [[NSFileManager defaultManager] createDirectoryAtPath:filePath
//        withIntermediateDirectories:NO attributes:nil error:&error]; //Create
//        folder if (error) {
//            SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s", [[error
//            localizedDescription] UTF8String]); return 0;
//        }
//        return 1;
//    }
//    SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Unable to create directory: %s ",
//    [filePath UTF8String]); return 0;
//}

static void createDirectoryStructure(const char *filename)
{
  static char temp[2048];

  //    DEBUG_LOG_ASSERT_WRITE(strlen(filename) < 2048, "TAG", "error");

  NSMutableArray *array = [[NSMutableArray alloc] init];

  strcpy(temp, filename);
  char *token = strtok(temp, "/");
  std::string path("");
  while (token != NULL)
    {
      path += token;
      path += "/";

      NSString *filePath =
          [[NSString alloc] initWithCString:DOCUMENT_PATH(path.c_str())
                                   encoding:NSASCIIStringEncoding];

      [array addObject:filePath];

      token = strtok(NULL, "/");
    }
  [array removeLastObject];

  for (NSString *filePath in array)
    {
      if (![[NSFileManager defaultManager] fileExistsAtPath:filePath])
        {
          NSError *error;
          [[NSFileManager defaultManager]
                    createDirectoryAtPath:filePath
              withIntermediateDirectories:NO
                               attributes:nil
                                    error:&error]; // Create folder
          if (error)
            {
              SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s",
                           [[error localizedDescription] UTF8String]);
            }
        }
    }

  //    NSMutableArray *array = [[NSMutableArray alloc] init];
  //
  //    char *temp = new char[strlen(filename)];
  //    strcpy(temp, filename);
  //    char *token = strtok(temp, "/");
  //    /* walk through other tokens */
  //    NSString *currentString;
  //    while( token != NULL )
  //    {
  //        currentString = [[NSString alloc] initWithCString:token
  //        encoding:NSASCIIStringEncoding]; [array addObject:currentString];
  //
  //        token = strtok(NULL, "/");
  //    }
  //
  //    [array removeObject:currentString];
  //
  //    NSMutableString *ss = [[NSMutableString alloc] init];
  //    [ss appendString: @"/"];
  //    for (NSString *s in array)
  //    {
  //        [ss appendString: s];
  //        [ss appendString: @"/"];
  //
  ////        createFolder(ss);
  //
  //    }
  //
  //    delete [] temp;
}

// static void createFolder(NSString *folderName)
//{
//    NSError *error;
//    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
//    NSUserDomainMask, YES); NSString *documentsDirectory = [paths
//    objectAtIndex:0]; // Get documents folder NSString *dataPath =
//    [documentsDirectory stringByAppendingPathComponent:folderName];
//
//    if (![[NSFileManager defaultManager] fileExistsAtPath:dataPath])
//        [[NSFileManager defaultManager] createDirectoryAtPath:dataPath
//        withIntermediateDirectories:NO attributes:nil error:&error]; //Create
//        folder
//}

// static NSString *getDocumentPath(const std::string &filename)
//{
//    return [[NSString alloc] initWithCString:DOCUMENT_PATH(filename.c_str())
//    encoding:NSASCIIStringEncoding];
//}

#pragma mark REFERENCE http://mobile.antonio081014.com/2013/06/create-rename-delete-read-and-write.html

int CRUD_create(const char *filename, const void *buffer, unsigned long len)
{
  createDirectoryStructure(filename);

  NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename)
                                                encoding:NSASCIIStringEncoding];
  NSData *data = [NSData dataWithBytes:buffer length:len];

  if (![[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
      if ([[NSFileManager defaultManager] createFileAtPath:filePath
                                                  contents:data
                                                attributes:nil])
        {
          //            SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Created File
          //            %s\n", [filePath UTF8String]);
          return 1;
        }

      SDL_LogError(SDL_LOG_CATEGORY_TEST, "Couldn't create file: %s - %d,%s\n",
                   filename, errno, strerror(errno));
      return 0;
    }

  SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "file exists %s\n", [filePath UTF8String]);
  return 0;
}
int CRUD_read(const char *filename, void **buffer, unsigned long *len)
{
  NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename)
                                                encoding:NSASCIIStringEncoding];

  if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
      NSData *data = [NSData dataWithContentsOfFile:filePath];

      *len = [data length];
      *buffer = new char[*len];

      memcpy(*buffer, [data bytes], *len);

      return 1;
    }

  SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "file does not exists %s",
              [filePath UTF8String]);

  return 0;
}
int CRUD_update(const char *filename, const void *buffer, unsigned long len)
{
  NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename)
                                                encoding:NSASCIIStringEncoding];

  if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
      NSError *error = nil;
      NSData *content = [[NSData alloc] initWithBytes:buffer length:len];

      [content writeToFile:filePath atomically:YES];
      // If error happens, log it.
      if (error)
        {
          SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s",
                       [[error localizedDescription] UTF8String]);
          return 0;
        }
      return 1;
    }
  // If the file doesn't exists, log it.
  SDL_LogError(SDL_LOG_CATEGORY_TEST, "File %s doesn't exists",
               [filePath UTF8String]);
  return 0;
}
int CRUD_delete(const char *filename)
{
  NSString *filePath = [[NSString alloc] initWithCString:DOCUMENT_PATH(filename)
                                                encoding:NSASCIIStringEncoding];

  if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
      NSError *error = nil;
      // This function also returnsYES if the item was removed successfully or
      // if path was nil. Returns NO if an error occurred.
      [[NSFileManager defaultManager] removeItemAtPath:filePath error:&error];
      if (error)
        {
          SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s",
                       [[error localizedDescription] UTF8String]);
          return 0;
        }
      return 1;
    }
  SDL_LogError(SDL_LOG_CATEGORY_TEST, "File %s doesn't exists",
               [filePath UTF8String]);
  return 0;
}

#pragma mark REFERENCE http://nshipster.com/nsfilemanager/

void setupFileSystem()
{
  NSFileManager *fileManager = [NSFileManager defaultManager];
  NSURL *bundleURL = [[NSBundle mainBundle] bundleURL];
  NSDirectoryEnumerator *enumerator =
      [fileManager enumeratorAtURL:bundleURL
          includingPropertiesForKeys:@[ NSURLNameKey, NSURLIsDirectoryKey ]
                             options:NSDirectoryEnumerationSkipsHiddenFiles
                        errorHandler:^BOOL(NSURL *url, NSError *error) {
                          if (error)
                            {
                              //                                                 NSLog(@"[Error] %@ (%@)", error, url);
                              return NO;
                            }

                          return YES;
                        }];

  NSMutableArray *mutableFileURLs = [NSMutableArray array];
  for (NSURL *fileURL in enumerator)
    {
      NSString *filename;
      [fileURL getResourceValue:&filename forKey:NSURLNameKey error:nil];

      NSNumber *isDirectory;
      [fileURL getResourceValue:&isDirectory
                         forKey:NSURLIsDirectoryKey
                          error:nil];

      // Skip directories with '_' prefix, for example
      if ([filename hasPrefix:@"_"] && [isDirectory boolValue])
        {
          [enumerator skipDescendants];
          continue;
        }

      if (![isDirectory boolValue])
        {
          [mutableFileURLs addObject:fileURL];
        }
    }
  for (NSURL *fileURL in mutableFileURLs)
    {
      std::string s([fileURL fileSystemRepresentation]);
      NSString *filePath =
          [[NSString alloc] initWithCString:s.c_str()
                                   encoding:NSASCIIStringEncoding];

      //        if([[filePath pathExtension] isEqualToString:@"lua"]) {
      NSData *data = [NSData dataWithContentsOfFile:filePath];

      NSDictionary *info = [[NSBundle mainBundle] infoDictionary];
      NSString *_bundleName = [NSString
          stringWithFormat:@"%@", [info objectForKey:@"CFBundleName"]];

      std::string bundleName([_bundleName UTF8String]);

      std::string _AssetPath(bundleName + std::string(".app/assets/"));

      size_t found = s.find(_AssetPath);
      size_t len = s.length();
      std::string str2 = s.substr(found + strlen(_AssetPath.c_str()), len);

      CRUD_create(str2.c_str(), [data bytes], [data length]);

      //        }
    }

  //    NSFileManager *fileMgr = [[NSFileManager alloc] init];
  //    NSError *error = nil;
  //    NSArray *paths =
  //    NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
  //    NSUserDomainMask, YES); NSString *documentsDirectory = [paths
  //    objectAtIndex:0]; NSArray *files = [fileMgr
  //    contentsOfDirectoryAtPath:documentsDirectory error:nil];
  //
  //    NSLog(@"%@", files);
}

//#include "firebase/admob/banner_view.h"

void initBanner()
{
//  UIWindow *window = [[UIApplication sharedApplication] keyWindow];
//  UIView *my_ad_parent = [window.subviews objectAtIndex:0];
//
//#if defined(__ANDROID__)
//  // Android ad unit IDs
//  const char *kBannerAdUnit = "ca-app-pub-3940256099942544/6300978111";
//  //        const char* kInterstitialAdUnit =
//  //        "ca-app-pub-3940256099942544/1033173712";
//#else
//  // iOS ad unit IDs
//  const char *kBannerAdUnit = "ca-app-pub-7116197939810801/5324920939";
//  //        const char* kInterstitialAdUnit =
//  //        "ca-app-pub-3940256099942544/4411468910";
//#endif
//
//  firebase::admob::BannerView *banner_view;
//  banner_view = new firebase::admob::BannerView();
//
//  firebase::admob::AdSize ad_size;
//  ad_size.ad_size_type = firebase::admob::kAdSizeStandard;
//  ad_size.width = 320;
//  ad_size.height = 50;
//  // my_ad_parent is a reference to an iOS UIView or an Android Activity.
//  // This is the parent UIView or Activity of the banner view.
//  banner_view->Initialize(static_cast<firebase::admob::AdParent>(my_ad_parent),
//                          kBannerAdUnit, ad_size);
//
//  //        if (banner_view->InitializeLastResult().status() ==
//  //            firebase::kFutureStatusComplete &&
//  //            banner_view->InitializeLastResult().error() ==
//  //            firebase::admob::kAdMobErrorNone) {
//  //
//  //            int i = 0;
//  ////          banner_view->Show();
//  //
//  //        }
//
//  //    if(banner_view->InitializeLastResult().status() ==
//  //       firebase::kFutureStatusComplete) {
//  //        bool complete = true;
//  //        if(banner_view->InitializeLastResult().error() ==
//  //           firebase::admob::kAdMobErrorNone) {
//  //            bool noerror = true;
//  //        }
//  //    }
//
//  // Initialize all the AdRequest struct member values to zero.
//  firebase::admob::AdRequest my_ad_request = {};
//
//  // If the app is aware of the user's gender, it can be added to the
//  // targeting information. Otherwise, "unknown" should be used.
//  my_ad_request.gender = firebase::admob::kGenderUnknown;
//
//  // The user's birthday, if known. Note that months are indexed from one.
//  my_ad_request.birthday_day = 10;
//  my_ad_request.birthday_month = 11;
//  my_ad_request.birthday_year = 1976;
//
//  // Additional keywords to be used in targeting.
//  static const char *kKeywords[] = {"AdMob", "C++", "Fun"};
//  my_ad_request.keyword_count = sizeof(kKeywords) / sizeof(kKeywords[0]);
//  my_ad_request.keywords = kKeywords;
//
//  // "Extra" key value pairs can be added to the request as well.
//  static const firebase::admob::KeyValuePair kRequestExtras[] = {
//      {"the_name_of_an_extra", "the_value_for_that_extra"}};
//  my_ad_request.extras_count =
//      sizeof(kRequestExtras) / sizeof(kRequestExtras[0]);
//  my_ad_request.extras = kRequestExtras;
//
//  //    // Register the device IDs associated with any devices that will be used
//  //    to
//  //    // test your app. Below are sample test device IDs used for making the
//  //    ad request. static const char* kTestDeviceIDs[] =
//  //        {"2077ef9a63d2b398840261c8221a0c9b",
//  //         "098fe087d987c9a878965454a65654d7"};
//  //    my_ad_request.test_device_id_count =
//  //        sizeof(kTestDeviceIDs) / sizeof(kTestDeviceIDs[0]);
//  //    my_ad_request.test_device_ids = kTestDeviceIDs;
//
//  banner_view->LoadAd(my_ad_request);
//
//  //    if (banner_view->InitializeLastResult().status() ==
//  //        firebase::kFutureStatusComplete &&
//  //        banner_view->InitializeLastResult().error() ==
//  //        firebase::admob::kAdMobErrorNone) {
//  //      banner_view->Show();
//  //    }
//
//  //    if (banner_view->ShowLastResult().status() ==
//  //        firebase::kFutureStatusComplete &&
//  //        banner_view->ShowLastResult().error() ==
//  //        firebase::admob::kAdMobErrorNone) {
//  //      banner_view->LoadAd(my_ad_request);
//  //    }
}
