#include "WorldEvent.h"

#include "JLIFactoryTypes.h"

#import <UIKit/UIKit.h>

//#include "firebase/admob.h"
//#include "firebase/admob/types.h"
//#include "firebase/app.h"
//#include "firebase/future.h"
//
//#include "firebase/admob/banner_view.h"
//#include "firebase/admob/interstitial_ad.h"
//
//#include "firebase/analytics.h"

namespace njli
{
  // A simple listener that logs changes to an InterstitialAd.
//  class LoggingInterstitialAdListener
//      : public firebase::admob::InterstitialAd::Listener
//  {
//  public:
//    LoggingInterstitialAdListener();
//    void OnPresentationStateChanged(
//        firebase::admob::InterstitialAd *interstitial_ad,
//        firebase::admob::InterstitialAd::PresentationState state) override;
//  };
//
//  LoggingInterstitialAdListener::LoggingInterstitialAdListener() {}
//  void LoggingInterstitialAdListener::OnPresentationStateChanged(
//      firebase::admob::InterstitialAd *interstitial_ad,
//      firebase::admob::InterstitialAd::PresentationState state)
//  {
//    //    ::LogMessage("InterstitialAd PresentationState has changed to %d.",
//    //    state);
//    printf("InterstitialAd PresentationState has changed to %d.", state);
//  }
//
//  class AdUnit;
//  class LoadingInterstitialAdListener
//      : public firebase::admob::InterstitialAd::Listener
//  {
//  public:
//    LoadingInterstitialAdListener(AdUnit *ad);
//    void OnPresentationStateChanged(
//        firebase::admob::InterstitialAd *interstitial_ad,
//        firebase::admob::InterstitialAd::PresentationState state) override;
//
//  private:
//    AdUnit *mAdUnit;
//  };

  class AdUnit
  {
    friend class LoadingInterstitialAdListener;

//    firebase::admob::InterstitialAd *interstitial_ad;
//    LoadingInterstitialAdListener *interstitial_listener;
    bool mIsLoadedCalled;
    bool mShouldShow;
    bool mIsDone;

  public:
    AdUnit();
    virtual ~AdUnit();
    void update();

    void show();
    bool isDone();
    inline void reset();

  protected:
    inline void setDone();
    void init();
    void load();
    void show_internal();

    bool isInitialized() const;
    bool isLoaded() const;

    bool isShown() const;
  };

  AdUnit::AdUnit()
      : //interstitial_ad(nullptr), interstitial_listener(nullptr),
        mIsLoadedCalled(false), mShouldShow(false), mIsDone(false)
  {
  }
  AdUnit::~AdUnit()
  {
//    if (interstitial_ad)
//      {
//        delete interstitial_ad;
//      }
//    if (interstitial_listener)
//      {
//        delete interstitial_listener;
//      }
  }
  void AdUnit::update()
  {
    if (!isInitialized())
      {
        init();
      }
    else
      {
        if (!mIsLoadedCalled && !isLoaded())
          {
            load();
          }
      }
    if (!isDone() && mShouldShow)
      {
        show_internal();
        mShouldShow = false;
      }
  }

  void AdUnit::show()
  {
    if (!isDone())
      {
        mShouldShow = true;
      }
  }
  bool AdUnit::isDone() { return mIsDone; }
  void AdUnit::reset()
  {
    mIsDone = false;
//    if (interstitial_ad)
//      {
//        delete interstitial_ad;
//        interstitial_ad = nullptr;
//      }
//    if (interstitial_listener)
//      {
//        delete interstitial_listener;
//        interstitial_listener = nullptr;
//      }
  }

  void AdUnit::setDone() { mIsDone = true; }
  void AdUnit::init()
  {
#if defined(__ANDROID__)
    // Create the Firebase app.
    firebase::App *app = firebase::App::Create(
        firebase::AppOptions(), GetJniEnv(), GetActivity());
      
      

    // Your Android AdMob app ID.
    const char *kAdMobAppID = "ca-app-pub-XXXXXXXXXXXXXXXX~NNNNNNNNNN";
#else
    // Create the Firebase app.
//    firebase::App *app = firebase::App::Create(firebase::AppOptions());

    // Your iOS AdMob app ID.
    const char *kAdMobAppID = "ca-app-pub-7116197939810801~2607064730";
#endif // __ANDROID__

    // Initialize the AdMob library with your AdMob app ID.
//    firebase::admob::Initialize(*app, kAdMobAppID);
      
//      ::firebase::analytics::Initialize(*app);
      

    UIWindow *window = [[UIApplication sharedApplication] keyWindow];
    UIView *my_ad_parent = [window.subviews objectAtIndex:0];

#if defined(__ANDROID__)
    // Android ad unit IDs
    const char *kBannerAdUnit = "ca-app-pub-3940256099942544/6300978111";
    const char *kInterstitialAdUnit = "ca-app-pub-3940256099942544/1033173712";
#else
    // iOS ad unit IDs

#if defined(NDEBUG)
    const char *kBannerAdUnit = "ca-app-pub-7116197939810801/5324920939";
    const char *kInterstitialAdUnit = "ca-app-pub-7116197939810801/9087840469";
#else
    const char *kBannerAdUnit = "ca-app-pub-3940256099942544/2934735716";
    const char *kInterstitialAdUnit = "ca-app-pub-3940256099942544/4411468910";
#endif

#endif
      
      

    
      
//    interstitial_ad = new firebase::admob::InterstitialAd();

    // my_ad_parent is a reference to an iOS UIView or an Android Activity.
    // This is the parent UIView or Activity of the interstitial ad.
//    interstitial_ad->Initialize(
//        static_cast<firebase::admob::AdParent>(my_ad_parent),
//        kInterstitialAdUnit);

    //      interstitial_listener = new LoggingInterstitialAdListener();

//    interstitial_listener = new LoadingInterstitialAdListener(this);
//    interstitial_ad->SetListener(interstitial_listener);
  }
  void AdUnit::load()
  {
    if (isInitialized())
      {
//        firebase::admob::AdRequest my_ad_request = {};
//
//        // If the app is aware of the user's gender, it can be added to the
//        // targeting information. Otherwise, "unknown" should be used.
//        my_ad_request.gender = firebase::admob::kGenderUnknown;
//
//        // The user's birthday, if known. Note that months are indexed from one.
//        my_ad_request.birthday_day = 10;
//        my_ad_request.birthday_month = 11;
//        my_ad_request.birthday_year = 1976;
//
//        // Additional keywords to be used in targeting.
//        static const char *kKeywords[] = {"AdMob", "C++", "Fun"};
//        my_ad_request.keyword_count = sizeof(kKeywords) / sizeof(kKeywords[0]);
//        my_ad_request.keywords = kKeywords;
//
//        // "Extra" key value pairs can be added to the request as well.
//        static const firebase::admob::KeyValuePair kRequestExtras[] = {
//            {"the_name_of_an_extra", "the_value_for_that_extra"}};
//        my_ad_request.extras_count =
//            sizeof(kRequestExtras) / sizeof(kRequestExtras[0]);
//        my_ad_request.extras = kRequestExtras;
//
//        // Register the device IDs associated with any devices that will be used
//        // to test your app. Below are sample test device IDs used for making
//        // the ad request.
//        static const char *kTestDeviceIDs[] = {
//            "a537a2299ecd89b4cd83a7cecb6603dd"};
//        my_ad_request.test_device_id_count =
//            sizeof(kTestDeviceIDs) / sizeof(kTestDeviceIDs[0]);
//        my_ad_request.test_device_ids = kTestDeviceIDs;
//
//        interstitial_ad->LoadAd(my_ad_request);
        mIsLoadedCalled = true;
      }
  }
  void AdUnit::show_internal()
  {
    if (mIsLoadedCalled && isLoaded())
      {
//        interstitial_ad->Show();
        mIsLoadedCalled = false;
      }
  }

  bool AdUnit::isInitialized() const
  {
//    if (interstitial_ad)
//      {
//
//        return (interstitial_ad->InitializeLastResult().status() ==
//                    firebase::kFutureStatusComplete &&
//                interstitial_ad->InitializeLastResult().error() ==
//                    firebase::admob::kAdMobErrorNone);
//      }
    return false;
  }
  bool AdUnit::isLoaded() const
  {
//    auto s = interstitial_ad->LoadAdLastResult().status();
//    auto e = interstitial_ad->LoadAdLastResult().error();
//    return (s == firebase::kFutureStatusComplete &&
//            e == firebase::admob::kAdMobErrorNone);
  }

  bool AdUnit::isShown() const
  {
      return false;
//      (interstitial_ad->ShowLastResult().status() ==
//                firebase::kFutureStatusComplete &&
//            interstitial_ad->ShowLastResult().error() ==
//                firebase::admob::kAdMobErrorNone);
  }

//  LoadingInterstitialAdListener::LoadingInterstitialAdListener(AdUnit *ad)
//      : mAdUnit(ad)
//  {
//  }
//  void LoadingInterstitialAdListener::OnPresentationStateChanged(
//      firebase::admob::InterstitialAd *interstitial_ad,
//      firebase::admob::InterstitialAd::PresentationState state)
//  {
//
//    if (firebase::admob::InterstitialAd::PresentationState::
//            kPresentationStateHidden == state)
//      {
//        mAdUnit->setDone();
//      }
//    else if (firebase::admob::InterstitialAd::PresentationState::
//                 kPresentationStateCoveringUI == state)
//      {
//      }
//  }

  WorldEvent::WorldEvent()
      : mAdUnitQueue(new std::queue<AdUnit *>()) //: mAdData(new AdData())
  {
    mAdUnitQueue->push(new AdUnit());
    mAdUnitQueue->push(new AdUnit());

    mCurrenAdUnit = mAdUnitQueue->front();
  }

  WorldEvent::~WorldEvent()
  {
    while (!mAdUnitQueue->empty())
      {
        auto t = mAdUnitQueue->front();
        delete t;
        mAdUnitQueue->pop();
      }
    delete mAdUnitQueue;
  }

  const char *WorldEvent::getClassName() const { return "WorldEvent"; }

s32 WorldEvent::getType() const { return 0;}//JLI_OBJECT_TYPE_WorldEvent; }
  //  s32 WorldEvent::getType() const { return 0; }

  WorldEvent::operator std::string() const
  {
    return ""; // njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
  }

  void WorldEvent::show() { mShow = true; }

  void WorldEvent::update()
  {
    if (mShow)
      {
        if (!mCurrenAdUnit->isDone())
          {
            mCurrenAdUnit->show();
            mShow = false;
          }
      }

    if (mCurrenAdUnit->isDone())
      {
        mAdUnitQueue->pop();

        mCurrenAdUnit->reset();
        mAdUnitQueue->push(mCurrenAdUnit);
        mCurrenAdUnit = mAdUnitQueue->front();
      }
    mCurrenAdUnit->update();
  }
}
