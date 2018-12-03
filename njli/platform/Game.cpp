
#include "Log.h"
#define TAG "Game.cpp"
#include "AbstractRender.h"
#include "Game.h"
#include "GraphicsPlatform.h"
#include "World.h"
#include <string>

#if defined( __ANDROID__) || defined(_WIN32)
#else
#include <sys/sysctl.h>
#include <sys/types.h>
#endif

namespace njli
{

  bool NJLIGameEngine::isIOS() { return platformID() == PlatformID_iOS; }

  bool NJLIGameEngine::isANDROID()
  {
    return platformID() == PlatformID_Android;
  }

  bool NJLIGameEngine::isEMSCRIPTEN()
  {
    return platformID() == PlatformID_Emscripten;
  }

  bool NJLIGameEngine::isMACOSX() { return platformID() == PlatformID_MacOSx; }

  bool NJLIGameEngine::isTVOS() { return platformID() == PlatformID_tvOS; }

  bool NJLIGameEngine::create(const char *deviceName, bool initLua)
  {
    njli::World::createInstance();
    if (initLua)
      njli::World::getInstance()->getWorldLuaVirtualMachine()->init();

    //    if (LOGGING_ON) {
    const char *platform =
        (isIOS()
             ? "iOS"
             : (isANDROID()
                    ? "Android"
                    : (isEMSCRIPTEN()
                           ? "Emscripten"
                           : ((isMACOSX() ? "MacOSx" : "UNKNOWN_PLATFORM")))));
    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Platform Name = `%s`\n", platform);
    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Device Name = `%s`\n", deviceName);

        printGLInfo();
    initGL();

    njli::World::getInstance()->setDeviceName(deviceName);

    //    njli::World::getInstance()->createScript();

    return true;
  }

  void NJLIGameEngine::resize(int x, int y, int width, int height,
                              int orientation)
  {
    if (njli::World::hasInstance())
      njli::World::getInstance()->resize(x, y, width, height, orientation);
  }
  int NJLIGameEngine::width()
  {
    return njli::World::getInstance()->getViewportDimensions().x();
  }

  int NJLIGameEngine::height()
  {
    return njli::World::getInstance()->getViewportDimensions().y();
  }

  int NJLIGameEngine::orientation()
  {
    return njli::World::getInstance()->getWorldInput()->getOrientation();
  }

  bool NJLIGameEngine::start(int argc, char **argv)
  {
      std::string main_file("scripts/main.lua");
      bool found_project_file = false;
      for(int i = 0; i < argc; ++i)
      {
          SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "arg # %d `%s`", i, argv[i]);

          std::string s(argv[i]);
          
          if(found_project_file)
          {
              main_file = std::string(argv[i]);
              found_project_file = false;
          }
          if(s == "-project")
          {
              found_project_file = true;
          }

      }
      
    njli::World::getInstance()->getWorldClock()->reset();

    //    std::string source = R"(
    //
    //        )";

    //    bool ret = false;
    //    if (World::getInstance()->getWorldLuaVirtualMachine()->compileString(
    //            source.c_str()))
    //      {
    //        ret =
    //        World::getInstance()->getWorldLuaVirtualMachine()->compileFile(
    //            "scripts/main.lua");
    //        njli::World::getInstance()->createScript();
    //      }
    //    return ret;
    bool ret = World::getInstance()->getWorldLuaVirtualMachine()->compileFile(
        main_file.c_str());
    if (!ret)
      {
      }
    njli::World::getInstance()->createScript();
    return true;
  }
  void NJLIGameEngine::update(float step)
  {
    BT_PROFILE("Game update");
    njli::World::getInstance()->update(step, 3);
  }

  void NJLIGameEngine::render() { njli::World::getInstance()->render(); }

  void NJLIGameEngine::destroy()
  {
    njli::World::getInstance()->destroyScript();
    njli::World::destroyInstance();
  }

  // void NJLIGameEngine::setTouch(const void* touch, const int index,
  //    const unsigned long num_touches)
  //{
  //    //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "set_touch(%s)\n", "?");
  //    njli::World::getInstance()->getWorldInput()->setTouch(touch,
  //                                                          index,
  //                                                          num_touches);
  //}
  //    void NJLIGameEngine::setTouch(int deviceIndex, int touchIndex, int
  //    num_touches)
  //    {
  //        njli::World::getInstance()->getWorldInput()->setTouch(deviceIndex,
  //        touchIndex, num_touches);
  //    }
  //    void NJLIGameEngine::setTouch(const int x, const int y)
  //    {
  //        njli::World::getInstance()->getWorldInput()->setTouch(x, y, 0, 1,
  //        1.0);
  //    }
  //
  //    void NJLIGameEngine::setTouch(int touchDevId, int pointerFingerId, int
  //    eventType, float x, float y, float dx, float dy, float pressure)
  //    {
  //
  //    }

  //    void NJLIGameEngine::finger(int touchDevId, int pointerFingerId, int
  //    eventType, float x, float y, float dx, float dy, float pressure)
  //    {
  //
  //    }
  //
  //    void NJLIGameEngine::fingers()
  //    {
  //
  //    }
  //
  //    void NJLIGameEngine::resetFingers()
  //    {
  //
  //    }

  void NJLIGameEngine::handleFinger(int touchDevId, int pointerFingerId,
                                    int eventType, float x, float y, float dx,
                                    float dy, float pressure)
  {
    njli::World::getInstance()->getWorldInput()->handleFinger(
        touchDevId, pointerFingerId, eventType, x, y, dx, dy, pressure);
  }

  void NJLIGameEngine::handleFingers()
  {
    njli::World::getInstance()->getWorldInput()->handleFingers();
  }

  //    void NJLIGameEngine::startHandleFingers()
  //    {
  //        njli::World::getInstance()->getWorldInput()->startHandleFingers();
  //    }

  void NJLIGameEngine::mouse(int button, int eventType, float x, float y,
                             int clicks)
  {
    njli::World::getInstance()->getWorldInput()->handleMouse(button, eventType,
                                                             x, y, clicks);
  }

  void NJLIGameEngine::keyUp(const char *keycodeName, bool withCapsLock,
                             bool withControl, bool withShift, bool withAlt,
                             bool withGui)
  {
    njli::World::getInstance()->getWorldInput()->handleKeyUp(
        keycodeName, withCapsLock, withControl, withShift, withAlt, withGui);
  }

  void NJLIGameEngine::keyDown(const char *keycodeName, bool withCapsLock,
                               bool withControl, bool withShift, bool withAlt,
                               bool withGui)
  {
    njli::World::getInstance()->getWorldInput()->handleKeyDown(
        keycodeName, withCapsLock, withControl, withShift, withAlt, withGui);
  }

  void NJLIGameEngine::handleEvent(void *event)
  {
//    njli::World::getInstance()->getDebugDrawer()->processSdlEvent((SDL_Event *)event);
  }

  // void NJLIGameEngine::setTouch(const int x, const int y, const int index,
  //    const unsigned long num_touches, float scaleFactor)
  //{
  //    //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "set_touch(%d, %d, %d, %d,
  //    %f)\n", x, y, index,
  //    //    num_touches, scaleFactor);
  //    int xx = (x < 0)
  //        ? 0
  //        : ((x > njli::World::getInstance()->getViewportDimensions().x())
  //                  ? njli::World::getInstance()->getViewportDimensions().x()
  //                  : x);
  //    int yy = (y < 0)
  //        ? 0
  //        : ((y > njli::World::getInstance()->getViewportDimensions().y())
  //                  ? njli::World::getInstance()->getViewportDimensions().y()
  //                  : y);
  //
  //    njli::World::getInstance()->getWorldInput()->setTouch(
  //        xx, yy, index, num_touches, scaleFactor);
  //}

  // void NJLIGameEngine::clearNodeTouches()
  //{
  //    njli::World::getInstance()->getWorldInput()->clearNodeTouches();
  //}
  //
  // void NJLIGameEngine::touchDown()
  //{
  //    //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "touch_down(%s)\n", "");
  //    njli::World::getInstance()->getWorldInput()->touchDown();
  //}
  // void NJLIGameEngine::touchUp()
  //{
  //    //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "touch_up(%s)\n", "");
  //    njli::World::getInstance()->getWorldInput()->touchUp();
  //}
  // void NJLIGameEngine::touchMove()
  //{
  //    //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "touch_move(%s)\n", "");
  //    njli::World::getInstance()->getWorldInput()->touchMove();
  //}
  // void NJLIGameEngine::touchCancelled()
  //{
  //    njli::World::getInstance()->getWorldInput()->touchCancelled();
  //}

  void NJLIGameEngine::willResignActive()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldWillResignActive");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->willResignActive();
  }
  void NJLIGameEngine::didBecomeActive()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldDidBecomeActive");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->didBecomeActive();
  }

  void NJLIGameEngine::didEnterBackground()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldDidEnterBackground");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->didEnterBackground();
  }

  void NJLIGameEngine::willEnterForeground()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldWillEnterForeground");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->willEnterForeground();
  }

  void NJLIGameEngine::willTerminate()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldWillTerminate");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->willTerminate();
  }

  void NJLIGameEngine::interrupt()
  {
    njli::World::getInstance()->getWorldSound()->enablePause();

    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldInterrupt");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->interrupt();
  }

  void NJLIGameEngine::resumeInterrupt()
  {
    njli::World::getInstance()->getWorldSound()->enablePause(false);

    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldResumeInterrupt");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->resumeInterrupt();
  }

  // void NJLIGameEngine::pauseGame()
  //{
  //    njli::World::getInstance()->enablePauseGame();
  //}
  //
  // void NJLIGameEngine::unpauseGame()
  //{
  //    njli::World::getInstance()->enablePauseGame(false);
  //}

  // void NJLIGameEngine::pauseSound()
  //{
  //    njli::World::getInstance()->getWorldSound()->enablePause();
  //}
  //
  // void NJLIGameEngine::unpauseSound()
  //{
  //    njli::World::getInstance()->getWorldSound()->enablePause(false);
  //}

  void NJLIGameEngine::keyboardShow()
  {
    njli::World::getInstance()->getWorldInput()->keyboardShow();
    //    char buffer[256];
    //    sprintf(buffer, "%s", "__NJLIWorldKeyboardShow");
    //    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
  }

  void NJLIGameEngine::keyboardCancel()
  {
    njli::World::getInstance()->getWorldInput()->keyboardCancel();
    //    char buffer[256];
    //    sprintf(buffer, "%s", "__NJLIWorldKeyboardCancel");
    //    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
  }

  void NJLIGameEngine::keyboardReturn(const char *text)
  {
    njli::World::getInstance()->getWorldInput()->keyboardReturn(text);
    //    char buffer[256];
    //    sprintf(buffer, "%s", "__NJLIWorldKeyboardReturn");
    //
    //    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
    //    text);
  }

  void NJLIGameEngine::receivedMemoryWarning()
  {
    //    njli::World::getInstance()->getWorldResourceLoader()->unLoadAll();
    //    njli::World::getInstance()->getWorldFactory()->collectGarbage();
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
        "__NJLIWorldReceivedMemoryWarning");

    if (njli::World::getInstance()->getScene())
      njli::World::getInstance()->getScene()->receivedMemoryWarning();
  }
    
    void NJLIGameEngine::setVRCameraRotation(float m11, float m12, float m13,
                                             float m21, float m22, float m23,
                                             float m31, float m32, float m33)
    {
        btMatrix3x3 m(m11, m12, m13,
                      m21, m22, m23,
                      m31, m32, m33);
        btTransform transform(m);
        
        if (njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->setVRCameraRotation(transform);
    }
    
    void NJLIGameEngine::setVRCameraRotation(float yaw, float pitch, float roll)
    {
        //pitch is left to right
        // roll is up and down
        // yaw is clockwise and counter-clockwise
        yaw *= -1.0f;
        roll *= -1.0f;
//        SDL_Log("%f, %f, %f\n", yaw, pitch, roll);
        
        btMatrix3x3 m(btMatrix3x3::getIdentity());
        m.setEulerYPR(yaw, pitch, roll);
        btTransform transform(m);
        
        if (njli::World::getInstance()->getScene())
            njli::World::getInstance()->getScene()->setVRCameraRotation(transform);
    }
} // namespace njli
