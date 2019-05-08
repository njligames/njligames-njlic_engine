//
//  Engine.cpp
//
//  Created by James Folk on 9/7/17.
//
//

#include "Engine.h"

#if defined(__EMSCRIPTEN__)
#include "emscripten/emscripten.h"
//#include "emscripten.h"
#endif

#include "GraphicsPlatform.h"

#include <iostream>
#include <memory>
#include <string>
using namespace std;

#include "DeviceUtil.h"
#include "File.h"
#include "Game.h"
#include "NJLIInterface.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "World.h"
#include "btTransform.h"

namespace njli
{

  class Graphics
  {
  private:
    SDL_Window *_window;

  public:
    Graphics(SDL_Window *window) { _window = window; }

    void update()
    {
      njli::NJLIGameEngine::render();

      SDL_GL_SwapWindow(_window);
    }
  };

  static unique_ptr<Graphics> gGraphics;

  static const char *ControllerAxisName(const SDL_GameControllerAxis axis)
  {
    switch (axis)
      {
#define AXIS_CASE(ax)                                                          \
  case SDL_CONTROLLER_AXIS_##ax:                                               \
    return #ax
        AXIS_CASE(INVALID);
        AXIS_CASE(LEFTX);
        AXIS_CASE(LEFTY);
        AXIS_CASE(RIGHTX);
        AXIS_CASE(RIGHTY);
        AXIS_CASE(TRIGGERLEFT);
        AXIS_CASE(TRIGGERRIGHT);
#undef AXIS_CASE
      default:
        return "???";
      }
  }

  static const char *ControllerButtonName(const SDL_GameControllerButton button)
  {
    switch (button)
      {
#define BUTTON_CASE(btn)                                                       \
  case SDL_CONTROLLER_BUTTON_##btn:                                            \
    return #btn
        BUTTON_CASE(INVALID);
        BUTTON_CASE(A);
        BUTTON_CASE(B);
        BUTTON_CASE(X);
        BUTTON_CASE(Y);
        BUTTON_CASE(BACK);
        BUTTON_CASE(GUIDE);
        BUTTON_CASE(START);
        BUTTON_CASE(LEFTSTICK);
        BUTTON_CASE(RIGHTSTICK);
        BUTTON_CASE(LEFTSHOULDER);
        BUTTON_CASE(RIGHTSHOULDER);
        BUTTON_CASE(DPAD_UP);
        BUTTON_CASE(DPAD_DOWN);
        BUTTON_CASE(DPAD_LEFT);
        BUTTON_CASE(DPAD_RIGHT);
#undef BUTTON_CASE
      default:
        return "???";
      }
  }

  static void SDLTest_PrintEvent(SDL_Event *event)
  {
    if (event->type == SDL_FINGERMOTION)
      {
        /* Mouse and finger motion are really spammy */

        //        SDL_Log("SDL EVENT: Finger: %s touch=%ld, finger=%ld, x=%f,
        //        y=%f, dx=%f, dy=%f, pressure=%f",
        //                (event->type == SDL_FINGERDOWN) ? "down" : "up",
        //                (long) event->tfinger.touchId,
        //                (long) event->tfinger.fingerId,
        //                event->tfinger.x, event->tfinger.y,
        //                event->tfinger.dx, event->tfinger.dy,
        //                event->tfinger.pressure);

        return;
      }

    switch (event->type)
      {
      case SDL_JOYDEVICEMOTION:
        {
          SDL_Log("Joystick device %d motion. [%f, %f, %f, %f, %f, %f, %f, %f, "
                  "%f]\n",
                  (int)event->jmotion.which, event->jmotion.m11,
                  event->jmotion.m12, event->jmotion.m13, event->jmotion.m21,
                  event->jmotion.m22, event->jmotion.m23, event->jmotion.m31,
                  event->jmotion.m32, event->jmotion.m33);
          SDL_Log("Yaw, Pitch, Roll (%f, %f, %f)\n", event->jmotion.yaw,
                  event->jmotion.pitch, event->jmotion.roll);
        }
        break;
      case SDL_WINDOWEVENT:
        switch (event->window.event)
          {
          case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("SDL EVENT: Window %d shown", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("SDL EVENT: Window %d hidden", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("SDL EVENT: Window %d exposed", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_MOVED:
            SDL_Log("SDL EVENT: Window %d moved to %d,%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
          case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("SDL EVENT: Window %d resized to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
          case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("SDL EVENT: Window %d changed size to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
          case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("SDL EVENT: Window %d minimized", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("SDL EVENT: Window %d maximized", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("SDL EVENT: Window %d restored", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_ENTER:
            SDL_Log("SDL EVENT: Mouse entered window %d",
                    event->window.windowID);
            break;
          case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("SDL EVENT: Mouse left window %d", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("SDL EVENT: Window %d gained keyboard focus",
                    event->window.windowID);
            break;
          case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("SDL EVENT: Window %d lost keyboard focus",
                    event->window.windowID);
            break;
#if !defined(__LINUX__)
          case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("SDL EVENT: Window %d closed", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_TAKE_FOCUS:
            SDL_Log("SDL EVENT: Window %d take focus", event->window.windowID);
            break;
          case SDL_WINDOWEVENT_HIT_TEST:
            SDL_Log("SDL EVENT: Window %d hit test", event->window.windowID);
            break;
#endif
          default:
            SDL_Log("SDL EVENT: Window %d got unknown event %d",
                    event->window.windowID, event->window.event);
            break;
          }
        break;
      case SDL_KEYDOWN:
        SDL_Log("SDL EVENT: Keyboard: key pressed  in window %d: scancode "
                "0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID, event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
      case SDL_KEYUP:
        SDL_Log("SDL EVENT: Keyboard: key released in window %d: scancode "
                "0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID, event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
      case SDL_TEXTINPUT:
        SDL_Log("SDL EVENT: Keyboard: text input \"%s\" in window %d",
                event->text.text, event->text.windowID);
        break;
      case SDL_MOUSEMOTION:
        SDL_Log("SDL EVENT: Mouse: moved to %d,%d (%d,%d) in window %d",
                event->motion.x, event->motion.y, event->motion.xrel,
                event->motion.yrel, event->motion.windowID);
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_Log("SDL EVENT: Mouse: button %d pressed at %d,%d with click count "
                "%d in window %d",
                event->button.button, event->button.x, event->button.y,
                event->button.clicks, event->button.windowID);
        break;
      case SDL_MOUSEBUTTONUP:
        SDL_Log("SDL EVENT: Mouse: button %d released at %d,%d with click "
                "count %d in window %d",
                event->button.button, event->button.x, event->button.y,
                event->button.clicks, event->button.windowID);
        break;
      case SDL_MOUSEWHEEL:
        SDL_Log("SDL EVENT: Mouse: wheel scrolled %d in x and %d in y "
                "(reversed: %d) in window %d",
                event->wheel.x, event->wheel.y, event->wheel.direction,
                event->wheel.windowID);
        break;
      case SDL_JOYDEVICEADDED:
        {
          SDL_Log("SDL EVENT: Joystick index %d attached",
                  event->jdevice.which);

          // Load joystick
          SDL_Joystick *joystick = SDL_JoystickOpen(event->jdevice.which);

          if (joystick == NULL)
            {
              printf("Warning: Unable to open game controller! SDL Error: %s\n",
                     SDL_GetError());
            }
          else
            {
              gGameJoystickMap.insert(
                  JoystickPair(SDL_JoystickInstanceID(joystick), joystick));
            }
        }
        break;
      case SDL_JOYDEVICEREMOVED:
        {

          SDL_Log("SDL EVENT: Joystick %d removed", event->jdevice.which);

          JoystickMap::iterator iter =
              gGameJoystickMap.find(event->jdevice.which);
          if (iter != gGameJoystickMap.end())
            {
              SDL_Joystick *joystick = iter->second;
              SDL_JoystickClose(joystick);
            }
        }
        break;
      case SDL_JOYBALLMOTION:
        SDL_Log("SDL EVENT: Joystick %d: ball %d moved by %d,%d",
                event->jball.which, event->jball.ball, event->jball.xrel,
                event->jball.yrel);
        break;
      case SDL_JOYAXISMOTION:
        {
          SDL_Log("SDL EVENT: Joystick %d: axis %d, value %d",
                  event->jaxis.which, event->jaxis.axis, event->jaxis.value);
        }
        break;
      case SDL_JOYHATMOTION:
        {
          const char *position = "UNKNOWN";
          switch (event->jhat.value)
            {
            case SDL_HAT_CENTERED:
              position = "CENTER";
              break;
            case SDL_HAT_UP:
              position = "UP";
              break;
            case SDL_HAT_RIGHTUP:
              position = "RIGHTUP";
              break;
            case SDL_HAT_RIGHT:
              position = "RIGHT";
              break;
            case SDL_HAT_RIGHTDOWN:
              position = "RIGHTDOWN";
              break;
            case SDL_HAT_DOWN:
              position = "DOWN";
              break;
            case SDL_HAT_LEFTDOWN:
              position = "LEFTDOWN";
              break;
            case SDL_HAT_LEFT:
              position = "LEFT";
              break;
            case SDL_HAT_LEFTUP:
              position = "LEFTUP";
              break;
            }
          SDL_Log("SDL EVENT: Joystick %d: hat %d moved to %s",
                  event->jhat.which, event->jhat.hat, position);
        }
        break;
      case SDL_JOYBUTTONDOWN:
        SDL_Log("SDL EVENT: Joystick %d: button %d pressed",
                event->jbutton.which, event->jbutton.button);
        break;
      case SDL_JOYBUTTONUP:
        SDL_Log("SDL EVENT: Joystick %d: button %d released",
                event->jbutton.which, event->jbutton.button);
        break;
      case SDL_CONTROLLERDEVICEADDED:
        SDL_Log("SDL EVENT: Controller index %d attached",
                event->cdevice.which);
        break;
      case SDL_CONTROLLERDEVICEREMOVED:
        SDL_Log("SDL EVENT: Controller %d removed", event->cdevice.which);
        break;
      case SDL_CONTROLLERAXISMOTION:
        SDL_Log("SDL EVENT: Controller %d axis %d ('%s') value: %d",
                event->caxis.which, event->caxis.axis,
                ControllerAxisName((SDL_GameControllerAxis)event->caxis.axis),
                event->caxis.value);
        break;
      case SDL_CONTROLLERBUTTONDOWN:
        SDL_Log("SDL EVENT: Controller %d button %d ('%s') down",
                event->cbutton.which, event->cbutton.button,
                ControllerButtonName(
                    (SDL_GameControllerButton)event->cbutton.button));
        break;
      case SDL_CONTROLLERBUTTONUP:
        SDL_Log("SDL EVENT: Controller %d button %d ('%s') up",
                event->cbutton.which, event->cbutton.button,
                ControllerButtonName(
                    (SDL_GameControllerButton)event->cbutton.button));
        break;
      case SDL_CLIPBOARDUPDATE:
        SDL_Log("SDL EVENT: Clipboard updated");
        break;

      case SDL_FINGERDOWN:
      case SDL_FINGERUP:
        SDL_Log("SDL EVENT: Finger: %s touch=%ld, finger=%ld, x=%f, y=%f, "
                "dx=%f, dy=%f, pressure=%f",
                (event->type == SDL_FINGERDOWN) ? "down" : "up",
                (long)event->tfinger.touchId, (long)event->tfinger.fingerId,
                event->tfinger.x, event->tfinger.y, event->tfinger.dx,
                event->tfinger.dy, event->tfinger.pressure);
        break;
      case SDL_DOLLARGESTURE:
        SDL_Log("SDL_EVENT: Dollar gesture detect: %" SDL_PRIs64,
                (Sint64)event->dgesture.gestureId);
        break;
      case SDL_DOLLARRECORD:
        SDL_Log("SDL_EVENT: Dollar gesture record: %" SDL_PRIs64,
                (Sint64)event->dgesture.gestureId);
        break;
      case SDL_MULTIGESTURE:
        SDL_Log("SDL_EVENT: Multi gesture fingers: %d",
                event->mgesture.numFingers);
        break;

      case SDL_RENDER_DEVICE_RESET:
        SDL_Log("SDL EVENT: render device reset");
        break;
      case SDL_RENDER_TARGETS_RESET:
        SDL_Log("SDL EVENT: render targets reset");
        break;

      case SDL_QUIT:
        SDL_Log("SDL EVENT: Quit requested");
        break;
      case SDL_USEREVENT:
        SDL_Log("SDL EVENT: User event %d", event->user.code);
        break;
      default:
        SDL_Log("Unknown event %04x", event->type);
        break;
      }
  }

  static void UpdateFrame(void *param)
  {
    njli::NJLIGameEngine::update(1.0f / ((float)gDisplayMode.refresh_rate));

    Graphics *graphics = (Graphics *)param;
    graphics->update();
  }

#if (defined(__IPHONEOS__) && __IPHONEOS__)

  static int EventFilter(void *userdata, SDL_Event *event)
  {
    //#if ((defined(__IPHONEOS__) && __IPHONEOS__) || (defined(__ANDROID__) &&
    //__ANDROID__))
    //    NJLI_HandleStartTouches();
    //#endif

    njli::NJLIGameEngine::handleEvent(&event);
    //    SDLTest_PrintEvent(event);

    Uint32 eventType = event->type;

    switch (eventType)
      {
      case SDL_JOYDEVICEMOTION:
        {
          //              SDL_Log("Joystick device %d motion. [%f, %f, %f, %f,
          //              %f, %f, %f, %f, %f]\n", (int) event->jmotion.which,
          //              event->jmotion.m11, event->jmotion.m12,
          //              event->jmotion.m13, event->jmotion.m21,
          //              event->jmotion.m22, event->jmotion.m23,
          //              event->jmotion.m31, event->jmotion.m32,
          //              event->jmotion.m33); SDL_Log("Yaw, Pitch, Roll (%f,
          //              %f, %f)\n", event->jmotion.yaw, event->jmotion.pitch,
          //              event->jmotion.roll);

          //              float _transform[] =
          //              {static_cast<float>(event->jmotion.m11),
          //              static_cast<float>(event->jmotion.m12),
          //              static_cast<float>(event->jmotion.m13),
          //              static_cast<float>(event->jmotion.m21),
          //              static_cast<float>(event->jmotion.m22),
          //              static_cast<float>(event->jmotion.m23),
          //              static_cast<float>(event->jmotion.m31),
          //              static_cast<float>(event->jmotion.m32),
          //              static_cast<float>(event->jmotion.m33)};

          //              glm::mat4 transform = glm::make_mat4(_transform);
          //              NJLI_HandleVRCameraRotation(static_cast<float>(event->jmotion.m11),
          //              static_cast<float>(event->jmotion.m12),
          //              static_cast<float>(event->jmotion.m13),
          //              static_cast<float>(event->jmotion.m21),
          //              static_cast<float>(event->jmotion.m22),
          //              static_cast<float>(event->jmotion.m23),
          //              static_cast<float>(event->jmotion.m31),
          //              static_cast<float>(event->jmotion.m32),
          //              static_cast<float>(event->jmotion.m33));

          NJLI_HandleVRCameraRotationYPR(
              static_cast<float>(event->jmotion.yaw),
              static_cast<float>(event->jmotion.pitch),
              static_cast<float>(event->jmotion.roll));
          // = glm::mat4(event->jmotion.m11, event->jmotion.m12,
          // event->jmotion.m13, event->jmotion.m21, event->jmotion.m22,
          // event->jmotion.m23, event->jmotion.m31, event->jmotion.m32,
          // event->jmotion.m33);
        }
        break;
        //#if ((defined(__MACOSX__) && __MACOSX__) || (defined(__EMSCRIPTEN__)
        //&&
        //__EMSCRIPTEN__))
        //      case SDL_MOUSEMOTION:
        //      case SDL_MOUSEBUTTONDOWN:
        //      case SDL_MOUSEBUTTONUP:
        //
        //        NJLI_HandleMouse(event->button.button, event->type,
        //        event->button.x,
        //                         event->button.y, event->button.clicks);
        //        break;
        //#endif

      //#if ((defined(__IPHONEOS__) && __IPHONEOS__) || (defined(__ANDROID__) &&
      //__ANDROID__))
      case SDL_FINGERMOTION:
      case SDL_FINGERDOWN:
      case SDL_FINGERUP:
        NJLI_HandleTouch((int)event->tfinger.touchId,
                         (int)event->tfinger.fingerId, event->type,
                         event->tfinger.x, event->tfinger.y, event->tfinger.dx,
                         event->tfinger.dy, event->tfinger.pressure);
        break;
      //#endif
      default:
        break;
      }

#if ((defined(__IPHONEOS__) && __IPHONEOS__) ||                                \
     (defined(__ANDROID__) && __ANDROID__))
    NJLI_HandleFinishTouches();
#endif

    return 1;
  }
#endif

    static void saveScreenshotToFile(std::string filename, int windowWidth, int windowHeight) {
        const int numberOfPixels = windowWidth * windowHeight * 3;
        unsigned char pixels[numberOfPixels];
        
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadBuffer(GL_FRONT);
        glReadPixels(0, 0, windowWidth, windowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
        
        FILE *outputFile = fopen(filename.c_str(), "w");
        short header[] = {0, 2, 0, 0, 0, 0, (short) windowWidth, (short) windowHeight, 24};
        
        fwrite(&header, sizeof(header), 1, outputFile);
        fwrite(pixels, numberOfPixels, 1, outputFile);
        fclose(outputFile);
        
        printf("Finish writing to file.\n");
    }
    
  static void SDLTest_ScreenShot(SDL_Renderer *renderer)
  {
      SDL_Rect viewport;
      SDL_RenderGetViewport(renderer, &viewport);
      saveScreenshotToFile("screenshot.tga", viewport.w, viewport.h);
      
      
      
//      const Uint32 format = SDL_PIXELFORMAT_RGB888;
//
//      SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, viewport.w, viewport.h, 24, format);
//      SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
//      SDL_SaveBMP(surface, "screenshot.bmp");
//      SDL_FreeSurface(surface);
      
      
//      SDL_Surface *sshot = SDL_CreateRGBSurface(0, viewport.w, viewport.h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0x00000000);
//      SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
//      SDL_SaveBMP(sshot, "screenshot.bmp");
//      SDL_FreeSurface(sshot);
      
//    SDL_Rect viewport;
//    SDL_Surface *surface;

    if (!renderer)
      {
        return;
      }

//    SDL_RenderGetViewport(renderer, &viewport);
//    surface = SDL_CreateRGBSurface(0, viewport.w, viewport.h, 24,
//#if SDL_BYTEORDER == SDL_LIL_ENDIAN
//                                   0x00FF0000, 0x0000FF00, 0x000000FF,
//#else
//                                   0x000000FF, 0x0000FF00, 0x00FF0000,
//#endif
//                                   0x00000000);
//    if (!surface)
//      {
//        //        fprintf(stderr, "Couldn't create surface: %s\n",
//        //        SDL_GetError());
//        return;
//      }

//    if (SDL_RenderReadPixels(renderer, NULL, surface->format->format,
//                             surface->pixels, surface->pitch) < 0)
//      {
//        //        fprintf(stderr, "Couldn't read screen: %s\n", SDL_GetError());
//        SDL_free(surface);
//        return;
//      }

//    if (SDL_SaveBMP(surface, "screenshot.bmp") < 0)
//      {
//        //        fprintf(stderr, "Couldn't save screenshot.bmp: %s\n",
//        //        SDL_GetError());
//        SDL_free(surface);
//        return;
//      }
  }

  static void FullscreenTo(int index, int windowId)
  {
    Uint32 flags;
    struct SDL_Rect rect = {0, 0, 0, 0};
    SDL_Window *window = SDL_GetWindowFromID(windowId);
    if (!window)
      {
        return;
      }

    SDL_GetDisplayBounds(index, &rect);

    flags = SDL_GetWindowFlags(window);
    if (flags & SDL_WINDOW_FULLSCREEN)
      {
        SDL_SetWindowFullscreen(window, SDL_FALSE);
        SDL_Delay(15);
      }

    SDL_SetWindowPosition(window, rect.x, rect.y);
    SDL_SetWindowFullscreen(window, SDL_TRUE);
  }

  static void handleInput()
  {
    bool callFinishKeys = false;
    SDL_Event event;
    SDL_PumpEvents();
    while (SDL_PollEvent(&event))
      {
        njli::NJLIGameEngine::handleEvent(&event);
        //        SDLTest_PrintEvent(&event);
        switch (event.type)
          {

#if defined(__MACOSX__) || defined(__EMSCRIPTEN__) || defined(__ANDROID__)
          case SDL_MOUSEMOTION:
          case SDL_MOUSEBUTTONDOWN:
          case SDL_MOUSEBUTTONUP:

            NJLI_HandleMouse(event.button.button, event.type, event.button.x,
                             event.button.y, event.button.clicks);
            break;
#endif

#if (defined(__ANDROID__) && __ANDROID__)
          case SDL_FINGERMOTION:
          case SDL_FINGERDOWN:
          case SDL_FINGERUP:
            NJLI_HandleTouch((int)event.tfinger.touchId,
                             (int)event.tfinger.fingerId, event.type,
                             event.tfinger.x, event.tfinger.y, event.tfinger.dx,
                             event.tfinger.dy, event.tfinger.pressure);
            break;
#endif
          case SDL_APP_DIDENTERFOREGROUND:
            SDL_Log("SDL_APP_DIDENTERFOREGROUND");

#if (defined(__IPHONEOS__) && __IPHONEOS__)
            SDL_iPhoneSetAnimationCallback(gWindow, 1, UpdateFrame,
                                           gGraphics.get());
#endif
            NJLI_HandleResume();
            break;

          case SDL_APP_DIDENTERBACKGROUND:
            SDL_Log("SDL_APP_DIDENTERBACKGROUND");

            njli::NJLIGameEngine::didEnterBackground();
            break;

          case SDL_APP_LOWMEMORY:
            SDL_Log("SDL_APP_LOWMEMORY");
            NJLI_HandleLowMemory();

            break;

          case SDL_APP_TERMINATING:
            SDL_Log("SDL_APP_TERMINATING");
            njli::NJLIGameEngine::willTerminate();
            break;

          case SDL_APP_WILLENTERBACKGROUND:
            SDL_Log("SDL_APP_WILLENTERBACKGROUND");
#if (defined(__IPHONEOS__) && __IPHONEOS__)
            SDL_iPhoneSetAnimationCallback(gWindow, 1, NULL, gGraphics.get());
#endif
            NJLI_HandlePause();
            break;

          case SDL_APP_WILLENTERFOREGROUND:
            SDL_Log("SDL_APP_WILLENTERFOREGROUND");

            njli::NJLIGameEngine::willEnterForeground();
            break;

          case SDL_WINDOWEVENT:
            switch (event.window.event)
              {
              case SDL_WINDOWEVENT_RESTORED:
                NJLI_HandleResume();
                break;
              case SDL_WINDOWEVENT_MINIMIZED:
                NJLI_HandlePause();
                break;
              case SDL_WINDOWEVENT_RESIZED:
              case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                  int w, h;
#if defined(__MACOSX__)
                  SDL_GetWindowSize(gWindow, &w, &h);
#else
                  SDL_GL_GetDrawableSize(gWindow, &w, &h);
#endif
                  NJLI_HandleResize(w, h, gDisplayMode.format,
                                    gDisplayMode.refresh_rate);
                }
                break;
              case SDL_WINDOWEVENT_CLOSE:
                {
                  SDL_Window *window =
                      SDL_GetWindowFromID(event.window.windowID);
                  if (window)
                    {
                      if (window == gWindow)
                        {
                          SDL_DestroyWindow(gWindow);
                          gWindow = NULL;
                          break;
                        }
                    }
                }
                break;
              }
            break;
          case SDL_KEYUP:
            {
              callFinishKeys = true;
              int temp = SDL_GetModState();
              temp = temp & KMOD_CAPS;
              bool withCapsLock = (temp == KMOD_CAPS);

              bool withControl = !!(event.key.keysym.mod & KMOD_CTRL);
              bool withShift = !!(event.key.keysym.mod & KMOD_SHIFT);
              bool withAlt = !!(event.key.keysym.mod & KMOD_ALT);
              bool withGui = !!(event.key.keysym.mod & KMOD_GUI);

              NJLI_HandleKeyUp(SDL_GetScancodeName(event.key.keysym.scancode),
                               withCapsLock, withControl, withShift, withAlt,
                               withGui);
            }
            break;
          case SDL_KEYDOWN:
            {
              callFinishKeys = true;
              int temp = SDL_GetModState();
              temp = temp & KMOD_CAPS;
              bool withCapsLock = (temp == KMOD_CAPS);

              bool withControl = !!(event.key.keysym.mod & KMOD_CTRL);
              bool withShift = !!(event.key.keysym.mod & KMOD_SHIFT);
              bool withAlt = !!(event.key.keysym.mod & KMOD_ALT);
              bool withGui = !!(event.key.keysym.mod & KMOD_GUI);

              NJLI_HandleKeyDown(SDL_GetScancodeName(event.key.keysym.scancode),
                                 withCapsLock, withControl, withShift, withAlt,
                                 withGui);

              switch (event.key.keysym.sym)
                {
                /* Add hotkeys here */
//                    case SDLK_0:
                case SDLK_PRINTSCREEN:
                  {
                    SDL_Window *window =
                        SDL_GetWindowFromID(event.key.windowID);
                    if (window)
                      {
                        if (window == gWindow)
                          {
                            SDLTest_ScreenShot(gRenderer);
                          }
                      }
                  }
                  break;
                case SDLK_EQUALS:
                  if (withControl)
                    {
                      /* Ctrl-+ double the size of the window */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          int w, h;
                          SDL_GetWindowSize(window, &w, &h);
                          SDL_SetWindowSize(window, w * 2, h * 2);
                        }
                    }
                  break;
                case SDLK_MINUS:
                  if (withControl)
                    {
                      /* Ctrl-- half the size of the window */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          int w, h;
                          SDL_GetWindowSize(window, &w, &h);
                          SDL_SetWindowSize(window, w / 2, h / 2);
                        }
                    }
                  break;
                case SDLK_o:
                  if (withControl)
                    {
#if !defined(__LINUX__)
                      /* Ctrl-O (or Ctrl-Shift-O) changes window opacity. */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          float opacity;
                          if (SDL_GetWindowOpacity(window, &opacity) == 0)
                            {
                              if (withShift)
                                {
                                  opacity += 0.20f;
                                }
                              else
                                {
                                  opacity -= 0.20f;
                                }
                              SDL_SetWindowOpacity(window, opacity);
                            }
                        }
#endif
                    }
                  break;

                case SDLK_c:
                  if (withControl)
                    {
                      /* Ctrl-C copy awesome text! */
                      SDL_SetClipboardText("SDL rocks!\nYou know it!");
                      printf("Copied text to clipboard\n");
                    }
                  if (withAlt)
                    {
                      /* Alt-C toggle a render clip rectangle */
                      int w, h;
                      if (gRenderer)
                        {
                          SDL_Rect clip;
                          SDL_GetWindowSize(gWindow, &w, &h);
                          SDL_RenderGetClipRect(gRenderer, &clip);
                          if (SDL_RectEmpty(&clip))
                            {
                              clip.x = w / 4;
                              clip.y = h / 4;
                              clip.w = w / 2;
                              clip.h = h / 2;
                              SDL_RenderSetClipRect(gRenderer, &clip);
                            }
                          else
                            {
                              SDL_RenderSetClipRect(gRenderer, NULL);
                            }
                        }
                    }
                  if (withShift)
                    {
                      SDL_Window *current_win = SDL_GetKeyboardFocus();
                      if (current_win)
                        {
                          const bool shouldCapture =
                              (SDL_GetWindowFlags(current_win) &
                               SDL_WINDOW_MOUSE_CAPTURE) == 0;
                          const int rc =
                              SDL_CaptureMouse((SDL_bool)shouldCapture);
                          SDL_Log("%sapturing mouse %s!\n",
                                  shouldCapture ? "C" : "Unc",
                                  (rc == 0) ? "succeeded" : "failed");
                        }
                    }
                  break;
                case SDLK_v:
                  if (withControl)
                    {
                      /* Ctrl-V paste awesome text! */
                      char *text = SDL_GetClipboardText();
                      if (*text)
                        {
                          printf("Clipboard: %s\n", text);
                        }
                      else
                        {
                          printf("Clipboard is empty\n");
                        }
                      SDL_free(text);
                    }
                  break;
                case SDLK_g:
                  if (withControl)
                    {
                      /* Ctrl-G toggle grab */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          SDL_SetWindowGrab(window, !SDL_GetWindowGrab(window)
                                                        ? SDL_TRUE
                                                        : SDL_FALSE);
                        }
                    }
                  break;
                case SDLK_m:
                  if (withControl)
                    {
                      /* Ctrl-M maximize */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          Uint32 flags = SDL_GetWindowFlags(window);
                          if (flags & SDL_WINDOW_MAXIMIZED)
                            {
                              SDL_RestoreWindow(window);
                            }
                          else
                            {
                              SDL_MaximizeWindow(window);
                            }
                        }
                    }
                  break;
                case SDLK_r:
                  if (withControl)
                    {
                      /* Ctrl-R toggle mouse relative mode */
                      SDL_SetRelativeMouseMode(
                          !SDL_GetRelativeMouseMode() ? SDL_TRUE : SDL_FALSE);
                    }
                  break;
                case SDLK_z:
                  if (withControl)
                    {
                      /* Ctrl-Z minimize */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          SDL_MinimizeWindow(window);
                        }
                    }
                  break;
                case SDLK_RETURN:
                  if (withControl)
                    {
                      /* Ctrl-Enter toggle fullscreen */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          Uint32 flags = SDL_GetWindowFlags(window);
                          if (flags & SDL_WINDOW_FULLSCREEN)
                            {
                              SDL_SetWindowFullscreen(window, SDL_FALSE);
                            }
                          else
                            {
                              SDL_SetWindowFullscreen(window,
                                                      SDL_WINDOW_FULLSCREEN);
                            }
                        }
                    }
                  else if (withAlt)
                    {
                      /* Alt-Enter toggle fullscreen desktop */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          Uint32 flags = SDL_GetWindowFlags(window);
                          if (flags & SDL_WINDOW_FULLSCREEN)
                            {
                              SDL_SetWindowFullscreen(window, SDL_FALSE);
                            }
                          else
                            {
                              SDL_SetWindowFullscreen(
                                  window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                            }
                        }
                    }
                  else if (withShift)
                    {
                      /* Shift-Enter toggle fullscreen desktop / fullscreen */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          Uint32 flags = SDL_GetWindowFlags(window);
                          if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) ==
                              SDL_WINDOW_FULLSCREEN_DESKTOP)
                            {
                              SDL_SetWindowFullscreen(window,
                                                      SDL_WINDOW_FULLSCREEN);
                            }
                          else
                            {
                              SDL_SetWindowFullscreen(
                                  window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                            }
                        }
                    }

                  break;
                case SDLK_b:
                  if (withControl)
                    {
                      /* Ctrl-B toggle window border */
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      if (window)
                        {
                          const Uint32 flags = SDL_GetWindowFlags(window);
                          const SDL_bool b =
                              ((flags & SDL_WINDOW_BORDERLESS) != 0)
                                  ? SDL_TRUE
                                  : SDL_FALSE;
                          SDL_SetWindowBordered(window, b);
                        }
                    }
                  break;
                case SDLK_a:
                  if (withControl)
                    {
                      /* Ctrl-A reports absolute mouse position. */
                      int x, y;
                      const Uint32 mask = SDL_GetGlobalMouseState(&x, &y);
                      SDL_Log("ABSOLUTE MOUSE: (%d, %d)%s%s%s%s%s\n", x, y,
                              (mask & SDL_BUTTON_LMASK) ? " [LBUTTON]" : "",
                              (mask & SDL_BUTTON_MMASK) ? " [MBUTTON]" : "",
                              (mask & SDL_BUTTON_RMASK) ? " [RBUTTON]" : "",
                              (mask & SDL_BUTTON_X1MASK) ? " [X2BUTTON]" : "",
                              (mask & SDL_BUTTON_X2MASK) ? " [X2BUTTON]" : "");
                    }
                  break;
                case SDLK_0:
                    {
                        SDL_Window *window =
                        SDL_GetWindowFromID(event.key.windowID);
                        if (window)
                        {
                            if (window == gWindow)
                            {
                                SDLTest_ScreenShot(gRenderer);
                            }
                        }
                        
                        
                  if (withControl)
                    {
                      SDL_Window *window =
                          SDL_GetWindowFromID(event.key.windowID);
                      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                               "Test Message",
                                               "You're awesome!", window);
                    }
                    }
                  break;
                case SDLK_1:
                  if (withControl)
                    {
                      FullscreenTo(0, event.key.windowID);
                    }
                  break;
                case SDLK_2:
                  if (withControl)
                    {
                      FullscreenTo(1, event.key.windowID);
                    }
                  break;
                case SDLK_ESCAPE:
                  gDone = 1;
                  break;
                case SDLK_SPACE:
                  { /*
                     char message[256];
                     SDL_Window *window =
                         SDL_GetWindowFromID(event.key.windowID);

                     SDL_snprintf(message, sizeof(message),
                                  "(%i, %i), rel (%i, %i)\n", gLastEvent.x,
                                  gLastEvent.y, gLastEvent.xrel,
                                  gLastEvent.yrel);
                     SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                                              "Last mouse position", message,
                                              window);*/
                    break;
                  }
                default:
                  break;
                }
              break;
            }
          case SDL_QUIT:

            NJLI_HandleQuit();

            break;

          case SDL_MOUSEWHEEL:
            SDL_Log("SDL EVENT: Mouse: wheel scrolled %d in x and %d in y "
                    "(reversed: %d) in window %d",
                    event.wheel.x, event.wheel.y, event.wheel.direction,
                    event.wheel.windowID);
            //            gXOffset -= (event.wheel.x * 1);
            //            gYOffset -= (event.wheel.y * 1);
            //            NJLI_HandleResize(gDisplayMode.w, gDisplayMode.h,
            //                              gDisplayMode.format,
            //                              gDisplayMode.refresh_rate);
            // SDL_MouseWheelEvent wheel = event.wheel;

            break;
          case SDL_DROPFILE:
            {
              char *dropped_filedir = event.drop.file;
              NJLI_HandleDropFile(dropped_filedir);
              SDL_free(dropped_filedir);
            }
            break;
#if !defined(__LINUX__)
          case SDL_DROPTEXT:
            {
              char *dropped_filedir = event.drop.file;
              NJLI_HandleDropFile(dropped_filedir);
              SDL_free(dropped_filedir);
            }
            break;
          case SDL_DROPBEGIN:
            {
              printf("Dropped file begin: %u\n", event.drop.windowID);
            }
            break;
          case SDL_DROPCOMPLETE:
            {
              printf("Dropped file begin: %u\n", event.drop.windowID);
            }
#endif
            break;
          default:
            break;
          }
      }

    if (callFinishKeys)
      NJLI_HandleKeyboardFinish(SDL_GetKeyboardState(NULL), SDL_NUM_SCANCODES);

#if !(defined(__MACOSX__) && __MACOSX__)
#endif
  }

#if !(defined(__IPHONEOS__) && __IPHONEOS__)
  static void mainloop()
  {
#if !defined(NDEBUG) && 0
    // Declare display mode structure to be filled in.
    SDL_DisplayMode current;
    // Get current display mode of all displays.
    for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i)
      {

        int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

        if (should_be_zero != 0)
          // In case of error...
          SDL_Log("Could not get display mode for video display #%d: %s", i,
                  SDL_GetError());

        else
          // On success, print the current display mode.
          SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i,
                  current.w, current.h, current.refresh_rate);
      }
#endif

    handleInput();

    UpdateFrame(gGraphics.get());

    int w, h;
    SDL_GL_GetDrawableSize(gWindow, &w, &h);

    int w2, h2;
    SDL_GetWindowSize(gWindow, &w2, &h2);

#if defined(__EMSCRIPTEN__) || defined(__ANDROID__)

    NJLI_HandleResize(gDisplayMode.w, gDisplayMode.h, gDisplayMode.format,
                      gDisplayMode.refresh_rate);

#endif

#if defined(__EMSCRIPTEN__)

    if (gDone)
      {
        emscripten_cancel_main_loop();

        njli::NJLIGameEngine::destroy();

        SDL_GL_DeleteContext(gGlContext);

        while (!gGameJoysticks.empty())
          {
            SDL_Joystick *joystick = gGameJoysticks.back();
            gGameJoysticks.pop_back();
            SDL_JoystickClose(joystick);
          }

        SDL_DestroyWindow(gWindow);
        SDL_Quit();
      }

#endif
  }
#endif

#if defined(__MACOSX__)

  static void SDLTest_PrintRendererFlag(Uint32 flag)
  {
    switch (flag)
      {
      case SDL_RENDERER_PRESENTVSYNC:
        fprintf(stderr, "PresentVSync");
        break;
      case SDL_RENDERER_ACCELERATED:
        fprintf(stderr, "Accelerated");
        break;
      default:
        fprintf(stderr, "0x%8.8x", flag);
        break;
      }
  }

  static void SDLTest_PrintPixelFormat(Uint32 format)
  {
    switch (format)
      {
      case SDL_PIXELFORMAT_UNKNOWN:
        fprintf(stderr, "Unknwon");
        break;
      case SDL_PIXELFORMAT_INDEX1LSB:
        fprintf(stderr, "Index1LSB");
        break;
      case SDL_PIXELFORMAT_INDEX1MSB:
        fprintf(stderr, "Index1MSB");
        break;
      case SDL_PIXELFORMAT_INDEX4LSB:
        fprintf(stderr, "Index4LSB");
        break;
      case SDL_PIXELFORMAT_INDEX4MSB:
        fprintf(stderr, "Index4MSB");
        break;
      case SDL_PIXELFORMAT_INDEX8:
        fprintf(stderr, "Index8");
        break;
      case SDL_PIXELFORMAT_RGB332:
        fprintf(stderr, "RGB332");
        break;
      case SDL_PIXELFORMAT_RGB444:
        fprintf(stderr, "RGB444");
        break;
      case SDL_PIXELFORMAT_RGB555:
        fprintf(stderr, "RGB555");
        break;
      case SDL_PIXELFORMAT_BGR555:
        fprintf(stderr, "BGR555");
        break;
      case SDL_PIXELFORMAT_ARGB4444:
        fprintf(stderr, "ARGB4444");
        break;
      case SDL_PIXELFORMAT_ABGR4444:
        fprintf(stderr, "ABGR4444");
        break;
      case SDL_PIXELFORMAT_ARGB1555:
        fprintf(stderr, "ARGB1555");
        break;
      case SDL_PIXELFORMAT_ABGR1555:
        fprintf(stderr, "ABGR1555");
        break;
      case SDL_PIXELFORMAT_RGB565:
        fprintf(stderr, "RGB565");
        break;
      case SDL_PIXELFORMAT_BGR565:
        fprintf(stderr, "BGR565");
        break;
      case SDL_PIXELFORMAT_RGB24:
        fprintf(stderr, "RGB24");
        break;
      case SDL_PIXELFORMAT_BGR24:
        fprintf(stderr, "BGR24");
        break;
      case SDL_PIXELFORMAT_RGB888:
        fprintf(stderr, "RGB888");
        break;
      case SDL_PIXELFORMAT_BGR888:
        fprintf(stderr, "BGR888");
        break;
      case SDL_PIXELFORMAT_ARGB8888:
        fprintf(stderr, "ARGB8888");
        break;
      case SDL_PIXELFORMAT_RGBA8888:
        fprintf(stderr, "RGBA8888");
        break;
      case SDL_PIXELFORMAT_ABGR8888:
        fprintf(stderr, "ABGR8888");
        break;
      case SDL_PIXELFORMAT_BGRA8888:
        fprintf(stderr, "BGRA8888");
        break;
      case SDL_PIXELFORMAT_ARGB2101010:
        fprintf(stderr, "ARGB2101010");
        break;
      case SDL_PIXELFORMAT_YV12:
        fprintf(stderr, "YV12");
        break;
      case SDL_PIXELFORMAT_IYUV:
        fprintf(stderr, "IYUV");
        break;
      case SDL_PIXELFORMAT_YUY2:
        fprintf(stderr, "YUY2");
        break;
      case SDL_PIXELFORMAT_UYVY:
        fprintf(stderr, "UYVY");
        break;
      case SDL_PIXELFORMAT_YVYU:
        fprintf(stderr, "YVYU");
        break;
      case SDL_PIXELFORMAT_NV12:
        fprintf(stderr, "NV12");
        break;
      case SDL_PIXELFORMAT_NV21:
        fprintf(stderr, "NV21");
        break;
      default:
        fprintf(stderr, "0x%8.8x", format);
        break;
      }
  }

  static void SDLTest_PrintRenderer(SDL_RendererInfo *info)
  {
    int i, count;

    fprintf(stderr, "  Renderer %s:\n", info->name);

    fprintf(stderr, "    Flags: 0x%8.8X", info->flags);
    fprintf(stderr, " (");
    count = 0;
    for (i = 0; i < sizeof(info->flags) * 8; ++i)
      {
        Uint32 flag = (1 << i);
        if (info->flags & flag)
          {
            if (count > 0)
              {
                fprintf(stderr, " | ");
              }
            SDLTest_PrintRendererFlag(flag);
            ++count;
          }
      }
    fprintf(stderr, ")\n");

    fprintf(stderr, "    Texture formats (%d): ", info->num_texture_formats);
    for (i = 0; i < (int)info->num_texture_formats; ++i)
      {
        if (i > 0)
          {
            fprintf(stderr, ", ");
          }
        SDLTest_PrintPixelFormat(info->texture_formats[i]);
      }
    fprintf(stderr, "\n");

    if (info->max_texture_width || info->max_texture_height)
      {
        fprintf(stderr, "    Max Texture Size: %dx%d\n",
                info->max_texture_width, info->max_texture_height);
      }
  }

#endif

  static void createRenderer()
  {
    int n = SDL_GetNumRenderDrivers();
    SDL_RendererInfo info;

    for (int j = 0; j < n; ++j)
      {
        SDL_GetRenderDriverInfo(j, &info);
        //            SDLTest_PrintRenderer(&info);
        SDL_LogInfo(SDL_LOG_CATEGORY_TEST, "%s", info.name);
        if (SDL_strcasecmp(info.name, "opengl") == 0 ||
            SDL_strcasecmp(info.name, "opengles2") == 0)
          {
            gRenderer = SDL_CreateRenderer(gWindow, j, 0);
            return;
          }
      }
  }

  int run_main(int argc, char **argv)
  {

    std::string working_directory("");
    bool found_working_dir = false;
    for (int i = 0; i < argc; ++i)
      {
        std::string s(argv[i]);

        if (found_working_dir)
          {
            working_directory = std::string(argv[i]);
            working_directory += "/";
            found_working_dir = false;

            setAssetPath(working_directory.c_str());

            World::usingZeroBrane = true;
          }
        if (s == "-working_dir")
          {
            found_working_dir = true;
          }
      }

#if (defined(__MACOSX__) && __MACOSX__)
    if (argc > 1)
      {
        //        setRunningPath(argv[1]);
        //        setScriptDir(argv[1]);
      }
#endif

    SDL_SetHint(SDL_HINT_ACCELEROMETER_AS_JOYSTICK, "0");

    /* initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
      {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
      }

    const char *name, *type;
    int i;
    SDL_Joystick *joystick;

    /* Print information about the joysticks */
    SDL_Log("There are %d joysticks attached\n", SDL_NumJoysticks());
    for (i = 0; i < SDL_NumJoysticks(); ++i)
      {
        name = SDL_JoystickNameForIndex(i);
        SDL_Log("Joystick %d: %s\n", i, name ? name : "Unknown Joystick");
        joystick = SDL_JoystickOpen(i);
        if (joystick == NULL)
          {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "SDL_JoystickOpen(%d) failed: %s\n", i,
                         SDL_GetError());
          }
        else
          {
            char guid[64];
            SDL_assert(SDL_JoystickFromInstanceID(
                           SDL_JoystickInstanceID(joystick)) == joystick);
            SDL_JoystickGetGUIDString(SDL_JoystickGetGUID(joystick), guid,
                                      sizeof(guid));
            switch (SDL_JoystickGetType(joystick))
              {
              case SDL_JOYSTICK_TYPE_GAMECONTROLLER:
                type = "Game Controller";
                break;
              case SDL_JOYSTICK_TYPE_WHEEL:
                type = "Wheel";
                break;
              case SDL_JOYSTICK_TYPE_ARCADE_STICK:
                type = "Arcade Stick";
                break;
              case SDL_JOYSTICK_TYPE_FLIGHT_STICK:
                type = "Flight Stick";
                break;
              case SDL_JOYSTICK_TYPE_DANCE_PAD:
                type = "Dance Pad";
                break;
              case SDL_JOYSTICK_TYPE_GUITAR:
                type = "Guitar";
                break;
              case SDL_JOYSTICK_TYPE_DRUM_KIT:
                type = "Drum Kit";
                break;
              case SDL_JOYSTICK_TYPE_ARCADE_PAD:
                type = "Arcade Pad";
                break;
              case SDL_JOYSTICK_TYPE_THROTTLE:
                type = "Throttle";
                break;
              default:
                type = "Unknown";
                break;
              }
            SDL_Log("       type: %s\n", type);
            SDL_Log("       axes: %d\n", SDL_JoystickNumAxes(joystick));
            SDL_Log("      balls: %d\n", SDL_JoystickNumBalls(joystick));
            SDL_Log("       hats: %d\n", SDL_JoystickNumHats(joystick));
            SDL_Log("    buttons: %d\n", SDL_JoystickNumButtons(joystick));
            SDL_Log("instance id: %d\n", SDL_JoystickInstanceID(joystick));
            SDL_Log("       guid: %s\n", guid);
            SDL_Log("    VID/PID: 0x%.4x/0x%.4x\n",
                    SDL_JoystickGetVendor(joystick),
                    SDL_JoystickGetProduct(joystick));
            SDL_JoystickClose(joystick);
          }
      }

#if defined(__ANDROID__) || defined(__IPHONEOS__)
    if (SDL_NumJoysticks() > 0)
      {
#else
    if (argv[1])
      {
#endif
        SDL_bool reportederror = SDL_FALSE;
        SDL_bool keepGoing = SDL_TRUE;
        SDL_Event event;
        int device;
#if defined(__ANDROID__) || defined(__IPHONEOS__)
        device = 0;
#else
        device = atoi(argv[1]);
#endif
        joystick = SDL_JoystickOpen(device);
        if (joystick != NULL)
          {
            SDL_assert(SDL_JoystickFromInstanceID(
                           SDL_JoystickInstanceID(joystick)) == joystick);
          }

        //              while ( keepGoing ) {
        //                  if (joystick == NULL) {
        //                      if ( !reportederror ) {
        //                          SDL_Log("Couldn't open joystick %d: %s\n",
        //                          device, SDL_GetError()); keepGoing =
        //                          SDL_FALSE; reportederror = SDL_TRUE;
        //                      }
        //                  } else {
        //                      reportederror = SDL_FALSE;
        //                      keepGoing = WatchJoystick(joystick);
        //                      SDL_JoystickClose(joystick);
        //                  }
        //
        //                  joystick = NULL;
        //                  if (keepGoing) {
        //                      SDL_Log("Waiting for attach\n");
        //                  }
        //                  while (keepGoing) {
        //                      SDL_WaitEvent(&event);
        //                      if ((event.type == SDL_QUIT) || (event.type ==
        //                      SDL_FINGERDOWN)
        //                          || (event.type == SDL_MOUSEBUTTONDOWN)) {
        //                          keepGoing = SDL_FALSE;
        //                      } else if (event.type == SDL_JOYDEVICEADDED) {
        //                          device = event.jdevice.which;
        //                          joystick = SDL_JoystickOpen(device);
        //                          if (joystick != NULL) {
        //                              SDL_assert(SDL_JoystickFromInstanceID(SDL_JoystickInstanceID(joystick))
        //                              == joystick);
        //                          }
        //                          break;
        //                      }
        //                  }
        //              }
      }

#if !defined(__ANDROID__)
    SDL_GetDesktopDisplayMode(0, &gDisplayMode);
#endif

#if defined(__EMSCRIPTEN__)
    gDisplayMode.h = 725.0f;
    float div = gDisplayMode.h / 9.0;
    gDisplayMode.w = div * 16.0f;
    //      gDisplayMode.h = 600.0f;
    gDisplayMode.refresh_rate = 60.0f;
#endif

#if defined(__EMSCRIPTEN__) || defined(__ANDROID__) || defined(__IPHONEOS__)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

#if defined(__GL_ES2__)

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);

#elif defined(__GL_ES3__)

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);

#elif defined(__GL_2__)

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
#if defined(__MACOSX__)
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#endif

#elif defined(__GL_3__)

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
#if defined(__MACOSX__)
//      SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
//      SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,
//      SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
//      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
//

//      SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
//      SDL_GL_CONTEXT_PROFILE_CORE);
#endif

#endif

#if defined(__MACOSX__) || defined(__WINDOWS32__) || defined(__WINDOWS64__)
    SDL_EventState(SDL_DROPFILE, SDL_ENABLE);
#endif

    Uint32 flags = SDL_WINDOW_OPENGL;

#if defined(__MACOSX__)
    flags |= SDL_WINDOW_RESIZABLE;
    //      flags |= SDL_WINDOW_MAXIMIZED;
    flags |= SDL_WINDOW_ALWAYS_ON_TOP;
    flags |= SDL_WINDOW_UTILITY;
#endif

#if defined(__ANDROID__) || defined(__IPHONEOS__)
    flags |= SDL_WINDOW_FULLSCREEN;
#endif

#if defined(__ANDROID__) || defined(__IPHONEOS__) || defined(__MACOSX__)
    flags |= SDL_WINDOW_ALLOW_HIGHDPI;
#endif

    /* create window and renderer */
    gWindow = SDL_CreateWindow("NJLIGameEngine", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, gDisplayMode.w,
                               gDisplayMode.h, flags);

    createRenderer();
#if defined(__MACOSX__)

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto Width = DM.w;
    auto Height = (DM.w / 16) * 9;

    // 4:3
    //     SDL_SetWindowSize(gWindow, 800, 600);
    // 16:9
    //          SDL_SetWindowSize(gWindow, 800, 450);
    SDL_SetWindowSize(gWindow, Width, Height);
    // 8:5
    //          SDL_SetWindowSize(gWindow, 800, 500);
    // 3:2
    //          SDL_SetWindowSize(gWindow, 800, 533.333333333333333F);

#endif

    //    int w, h;
    //    SDL_GetWindowSize(gWindow, &w, &h);
    //    SDL_Log("SDL_GetWindowSize #%d: current display mode is %dx%dpx", 0,
    //    w, h);

    //#if defined(__MACOSX__)
    //#if !(defined(NDEBUG))
    //        SDL_SetWindowSize(gWindow, w * 0.25f, h * 0.25f);
    //#endif
    //#endif

    //    SDL_GL_GetDrawableSize(gWindow, &w, &h);
    //    SDL_Log("SDL_GL_GetDrawableSize #%d: current display mode is %dx%dpx",
    //    0, w, h);

    if (!gWindow)
      {
        printf("Could not initialize Window\n");
        return 1;
      }

#if (defined(__ANDROID__) && (__ANDROID__))
    SDL_SetWindowFullscreen(gWindow, SDL_TRUE);
#endif

    gGlContext = SDL_GL_CreateContext(gWindow);

#if defined(__WINDOWS32__)
    glewExperimental = true;
    GLenum e = GLEW_OK;
    e = glewInit();
    if (e != GLEW_OK)
      { // never fails
        printf("glewInit initialization failed. GLEW error %s\n",
               glewGetErrorString(e));
      }
#endif

    if (!njli::NJLIGameEngine::create(
            DeviceUtil::hardwareDescription().c_str()))
      {
        cerr << "Error initializing OpenGL" << endl;
        return 1;
      }

    gGraphics = unique_ptr<Graphics>(new Graphics(gWindow));

#if (defined(__IPHONEOS__) && __IPHONEOS__)
    SDL_AddEventWatch(EventFilter, NULL);
#endif

    //    int drawableW, drawableH;
    //    int screen_w, screen_h;
    //    float pointSizeScale;

    /* The window size and drawable size may be different when highdpi is
     * enabled,
     * due to the increased pixel density of the drawable. */
    SDL_GetWindowSize(gWindow, &gDisplayMode.w, &gDisplayMode.h);

//      SDL_GL_GetDrawableSize(gWindow, &w, &h);
#if !defined(__EMSCRIPTEN__)
    SDL_GL_GetDrawableSize(gWindow, &gDisplayMode.w, &gDisplayMode.h);
#endif
    //      gDisplayMode.w = drawableW;
    //      gDisplayMode.h = drawableH;

    /* In OpenGL, point sizes are always in pixels. We don't want them looking
     * tiny on a retina screen. */
    //    pointSizeScale = (float)gDisplayMode.w / (float)screen_h;

    //#if defined(__MACOSX__)
    //    SDL_GetWindowSize(gWindow, &w, &h);
    //#else
    //    SDL_GL_GetDrawableSize(gWindow, &w, &h);
    //#endif
    //#if defined(__EMSCRIPTEN__)

#if defined(__EMSCRIPTEN__)
    //           int fullScreen = 0;
    //           emscripten_get_canvas_size(&gDisplayMode.w, &gDisplayMode.h,
    //           &fullScreen);

    //           EMSCRIPTEN_RESULT r =
    //           emscripten_get_canvas_element_size("#gameCanvas",
    //           &gDisplayMode.w, &gDisplayMode.h); if (r !=
    //           EMSCRIPTEN_RESULT_SUCCESS) /* handle error */
    //               EmscriptenFullscreenChangeEvent e;
    //           r = emscripten_get_fullscreen_status(&e);
    //           if (r != EMSCRIPTEN_RESULT_SUCCESS) /* handle error */
    //               fullScreen = e.isFullscreen;

#endif
    //    gDisplayMode.w *= pointSizeScale;
    //    gDisplayMode.h *= pointSizeScale;

    NJLI_HandleResize(gDisplayMode.w, gDisplayMode.h, gDisplayMode.format,
                      gDisplayMode.refresh_rate);
    //#endif

    //      bool vsynch = true;
    //      if(vsynch)
    //      {
    //          SDL_GL_SetSwapInterval(1);
    //      }
    //      else
    //      {
    //          SDL_GL_SetSwapInterval(0);
    //      }

    gDone = (njli::NJLIGameEngine::start(argc, argv) == false) ? 1 : 0;

#if defined(__EMSCRIPTEN__)
    emscripten_set_main_loop(mainloop, 0, 0);
#else

    while (!gDone)
      {
#if defined(__IPHONEOS__) && __IPHONEOS__
        handleInput();
#else
        mainloop();
#endif
      }

    NJLI_HandleSurfaceDestroyed();

#endif

    return 0;
  } // namespace njli
} // namespace njli
