#ifndef __NJLIGameEngine__
#define __NJLIGameEngine__

namespace njli
{
  class NJLIGameEngine
  {
  public:
    static bool isIOS();
    static bool isANDROID();
    static bool isEMSCRIPTEN();
    static bool isMACOSX();
    static bool isTVOS();

    static bool create(const char *deviceName, bool initLua = true);
    //    static bool create(int x, int y, int width, int height, int
    //    orientation, const char* deviceName, bool initLua = true);
    static void resize(int x, int y, int width, int height, int orientation);
    static int width();
    static int height();
    static int orientation();

    static bool start(int argc, char **argv);
    static void update(float step);
    static void render();
    static void destroy();

    //    static void setTouch(const void* touch, const int index, const
    //    unsigned long num_touches);
    ////    static void setTouch(int deviceIndex, int touchIndex, int
    /// num_touches);
    //    static void setTouch(const int x, const int y);
    //    static void setTouch(int touchDevId, int pointerFingerId, int
    //    eventType, float x, float y, float dx, float dy, float pressure);
    static void handleFinger(int touchDevId, int pointerFingerId, int eventType,
                             float x, float y, float dx, float dy,
                             float pressure);
    static void handleFingers();
    //    static void startHandleFingers();

    static void mouse(int button, int eventType, float x, float y, int clicks);

    static void keyUp(const char *keycodeName, bool withCapsLock,
                      bool withControl, bool withShift, bool withAlt,
                      bool withGui);

    static void keyDown(const char *keycodeName, bool withCapsLock,
                        bool withControl, bool withShift, bool withAlt,
                        bool withGui);

    static void handleEvent(void *event);

    //    static void clearNodeTouches();
    //
    //    static void touchDown();
    //    static void touchUp();
    //    static void touchMove();
    //    static void touchCancelled();

    static void willResignActive();
    static void didBecomeActive();
    static void didEnterBackground();
    static void willEnterForeground();
    static void willTerminate();
    static void interrupt();
    static void resumeInterrupt();

    //    static void pauseGame();
    //    static void unpauseGame();
    //
    //    static void pauseSound();
    //    static void unpauseSound();

    static void keyboardShow();
    static void keyboardCancel();
    static void keyboardReturn(const char *text);

    static void receivedMemoryWarning();

    enum PlatformID
    {
      PlatformID_iOS = 0,
      PlatformID_Android,
      PlatformID_Emscripten,
      PlatformID_MacOSx,
      PlatformID_tvOS,
      PlatformID_Linux
    };

    static PlatformID platformID();

  protected:
  private:
  };
}

#endif
