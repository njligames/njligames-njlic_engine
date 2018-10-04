#include "android_file.h"

 #if defined(__ANDROID__)

 AAssetManager *asset_manager = NULL;

 static int android_read(void *cookie, char *buf, int size)
 {
   return AAsset_read((AAsset *)cookie, buf, size);
 }

 static int android_write(void *cookie, const char *buf, int size)
 {
   return EACCES; // can't provide write access to the apk
 }

 static fpos_t android_seek(void *cookie, fpos_t offset, int whence)
 {
   return AAsset_seek((AAsset *)cookie, offset, whence);
 }

 static int android_close(void *cookie)
 {
   AAsset_close((AAsset *)cookie);
   return 0;
 }

 void initAssetManager(AAssetManager *assetManager)
 {
   asset_manager = assetManager;
   assert(asset_manager != NULL && "Android Asset Manager is null");
 }

 FILE *android_fopen(const char *fname, const char *mode)
 {
   assert(asset_manager != NULL && "Android Asset Manager is null");
 
   AAsset *asset = AAssetManager_open(asset_manager, fname, 0);
 
   if (!asset)
     return NULL;
 
   return funopen(asset, android_read, android_write, android_seek,
                  android_close);
 }

 void Java_org_libsdl_app_SDLActivity_initAssetManager(
     JNIEnv *env, jclass jclazz, jobject java_asset_manager)
 {
   initAssetManager(AAssetManager_fromJava(env, java_asset_manager));
 }

 #endif
