//
//  NJLIInterface.cpp
//  macOS
//
//  Created by James Folk on 4/27/17.
//
//

#include "NJLIInterface.h"
#include "Game.h"
#include <map>
#include <string>
#include <vector>

std::vector<SDL_Joystick *> gGameJoysticks;
typedef std::map<int, SDL_Joystick *> JoystickMap;
typedef std::pair<int, SDL_Joystick *> JoystickPair;

JoystickMap gGameJoystickMap;

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_GLContext gGlContext;
SDL_DisplayMode gDisplayMode;
SDL_MouseMotionEvent gLastEvent;
int gDone = 0;
int gXOffset = 0;
int gYOffset = 0;
int gNumTouches = 1;

void NJLI_HandleUpdate(double timeStep)
{
  njli::NJLIGameEngine::update(timeStep);
}

void NJLI_HandleRender() { njli::NJLIGameEngine::render(); }

void NJLI_HandleLowMemory() { njli::NJLIGameEngine::receivedMemoryWarning(); }

void NJLI_HandleQuit() { gDone = 1; }

void NJLI_HandlePause() {}

void NJLI_HandleResume() {}

void NJLI_HandleDropFile(const char *filename) { SDL_Log("%s", filename); }

void NJLI_HandleResize(int width, int height, int sdlFormat, float refreshRate)
{
#if defined(__EMSCRIPTEN__)
  gDisplayMode.h = 725.0f;
  float div = gDisplayMode.h / 9.0;
  gDisplayMode.w = div * 16.0f;
  //      gDisplayMode.h = 600.0f;
  gDisplayMode.refresh_rate = 60.0f;
#else

  gDisplayMode.w = width;
  gDisplayMode.h = height;
  gDisplayMode.refresh_rate = refreshRate;
#endif

  njli::NJLIGameEngine::resize(gXOffset, gYOffset, gDisplayMode.w,
                               gDisplayMode.h, 0);
}

int NJLI_HandlePadDown(int device_id, int keycode) { return 0; }

int NJLI_HandlePadUp(int device_id, int keycode) { return 0; }

void NJLI_HandleJoy(int device_id, int axis, float value) {}

void NJLI_HandleHat(int device_id, int hat_id, int x, int y) {}

void NJLI_HandleKeyDown(const std::string &keycodeName, bool withCapsLock,
                        bool withControl, bool withShift, bool withAlt,
                        bool withGui)
{
  njli::NJLIGameEngine::keyDown(keycodeName.c_str(), withCapsLock, withControl,
                                withShift, withAlt, withGui);
}

void NJLI_HandleKeyUp(const std::string &keycodeName, bool withCapsLock,
                      bool withControl, bool withShift, bool withAlt,
                      bool withGui)
{
  njli::NJLIGameEngine::keyUp(keycodeName.c_str(), withCapsLock, withControl,
                              withShift, withAlt, withGui);
}

void NJLI_HandleKeyboardFocusLost()
{
  //    SDL_Log("NJLI_HandleKeyboardFocusLost: %d", keycode);
}

void NJLI_HandleKeyboardFinish(const unsigned char *state, int numStates)
{
  /*
   *  const Uint8 *state = SDL_GetKeyboardState(NULL);
   *  if ( state[SDL_SCANCODE_RETURN] )   {
   *      printf("<RETURN> is pressed.\n");
   *  }
   */
}

void NJLI_HandleMouse(int button, int eventType, float x, float y, int clicks)
{
  int w, h;
  SDL_GetWindowSize(gWindow, &w, &h);
  int dw, dh;
  SDL_GL_GetDrawableSize(gWindow, &dw, &dh);

  float sw, sh;
  SDL_RenderGetScale(gRenderer, &sw, &sh);

  float pointSizeScale = (float)dw / (float)w;

  njli::NJLIGameEngine::mouse(button, eventType, x * pointSizeScale,
                              gDisplayMode.h - (y * pointSizeScale), clicks);
}

void NJLI_HandleTouch(int touchDevId, int pointerFingerId, int eventType,
                      float x, float y, float dx, float dy, float pressure)
{
  int action = eventType;
  switch (eventType)
    {
    case SDL_FINGERDOWN:
      action = 0;
      break;
    case SDL_FINGERUP:
      action = 1;
      break;
    case SDL_FINGERMOTION:
      action = 2;
      break;
    default:
      break;
    }

  int w, h;
  SDL_GetWindowSize(gWindow, &w, &h);

  int dw, dh;
  SDL_GL_GetDrawableSize(gWindow, &dw, &dh);

  float _x = x * dw;
  float _y = (1.0 - y) * dh;

  float _dx = dx;
  float _dy = dy;
  njli::NJLIGameEngine::handleFinger(touchDevId, pointerFingerId, action, _x,
                                     _y, _dx, _dy, pressure);
}

void NJLI_HandleFinishTouches() { njli::NJLIGameEngine::handleFingers(); }

void NJLI_HandleAccel(float x, float y, float z) {}

void NJLI_HandleSurfaceChanged() {}

void NJLI_HandleSurfaceDestroyed()
{
  njli::NJLIGameEngine::destroy();

  for (JoystickMap::iterator i = gGameJoystickMap.begin();
       i != gGameJoystickMap.end();)
    {
      SDL_Joystick *joystick = i->second;

      SDL_JoystickClose(joystick);
      i = gGameJoystickMap.erase(i);
    }

  SDL_GL_DeleteContext(gGlContext);
  SDL_DestroyWindow(gWindow);
  SDL_Quit();
}

int NJLI_HandleAddJoystick(int device_id, const char *name,
                           int is_accelerometer, int nbuttons, int naxes,
                           int nhats, int nballs)
{
  return 0;
}

int NJLI_HandleRemoveJoystick(int device_id) { return 0; }

const char *NJLI_HandleGetHint(const char *name) { return ""; }

void NJLI_HandleCommitText(const char *text, int newCursorPosition) {}

void NJLI_HandleSetComposingText(const char *text, int newCursorPosition) {}

void NJLI_HandleVRCameraRotation(float m11, float m12, float m13, float m21,
                                 float m22, float m23, float m31, float m32,
                                 float m33)
{
  njli::NJLIGameEngine::setVRCameraRotation(m11, m12, m13, m21, m22, m23, m31,
                                            m32, m33);
}

void NJLI_HandleVRCameraRotationYPR(float yaw, float pitch, float roll)
{
  njli::NJLIGameEngine::setVRCameraRotation(yaw, pitch, roll);
}

void NJLI_HandleVRCameraLocation(float x, float y, float z)
{
  njli::NJLIGameEngine::setVRCameraLocation(x, y, z);
}
