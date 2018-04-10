
#include "Log.h"
#define TAG "Game.cpp"
#include "AbstractRender.h"
#include "Game.h"
#include "GraphicsPlatform.h"
#include "World.h"
#include <string>

#ifdef __ANDROID__
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

    //    printGLInfo();
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
    njli::World::getInstance()->getWorldClock()->reset();

    std::string source = R"(
Runtime = {
    Create = {},
    Destroy = {},
    Update = {},
    Render = {},
    Resize = {},
    TouchesDown = {},
    TouchesUp = {},
    TouchesMove = {},
    TouchesCancelled = {},
    TouchDown = {},
    TouchUp = {},
    TouchMove = {},
    TouchCancelled = {},
    MouseDown = {},
    MouseUp = {},
    MouseMove = {},
    KeyDown = {},
    KeyUp = {},
    WorldEnterState = {},
    WorldUpdateState = {},
    WorldExitState = {},
    WorldOnMessage = {},
    WorldKeyboardShow = {},
    WorldKeyboardCancel = {},
    WorldKeyboardReturn = {},
    WorldReceivedMemoryWarning = {},
    WorldGamePause = {},
    WorldGameUnPause = {},
    WorldRenderHUD = {},
    WorldTouchesDown = {},
    WorldTouchesUp = {},
    WorldTouchesMove = {},
    WorldTouchesCancelled = {},
    WorldTouchDown = {},
    WorldTouchUp = {},
    WorldTouchMove = {},
    WorldTouchCancelled = {},
    WorldMouseDown = {},
    WorldMouseUp = {},
    WorldMouseMove = {},
    WorldKeyDown = {},
    WorldKeyUp = {},
    WorldWillResignActive = {},
    WorldDidBecomeActive = {},
    WorldDidEnterBackground = {},
    WorldWillEnterForeground = {},
    WorldWillTerminate = {},
    WorldInterrupt = {},
    WorldResumeInterrupt = {},
    SceneEnterState = {},
    SceneUpdateState = {},
    SceneExitState = {},
    SceneOnMessage = {},
    SceneKeyboardShow = {},
    SceneKeyboardCancel = {},
    SceneKeyboardReturn = {},
    SceneRenderHUD = {},
    SceneGamePause = {},
    SceneGameUnPause = {},
    SceneTouchesDown = {},
    SceneTouchesUp = {},
    SceneTouchesMove = {},
    SceneTouchesCancelled = {},
    SceneTouchDown = {},
    SceneTouchUp = {},
    SceneTouchMove = {},
    SceneTouchCancelled = {},
    SceneMouseDown = {},
    SceneMouseUp = {},
    SceneMouseMove = {},
    SceneKeyDown = {},
    SceneKeyUp = {},
    SceneReceivedMemoryWarning = {},
    SceneWillResignActive = {},
    SceneDidBecomeActive = {},
    SceneDidEnterBackground = {},
    SceneWillEnterForeground = {},
    SceneWillTerminate = {},
    SceneInterrupt = {},
    SceneResumeInterrupt = {},
    NodeEnterState = {},
    NodeUpdateState = {},
    NodeExitState = {},
    NodeOnMessage = {},
    NodeCollide = {},
    NodeNear = {},
    NodeActionUpdate = {},
    NodeActionComplete = {},
    NodeRayTouchesDown = {},
    NodeRayTouchesUp = {},
    NodeRayTouchesMove = {},
    NodeRayTouchesCancelled = {},
    NodeRayTouchesMissed = {},
    NodeRayTouchDown = {},
    NodeRayTouchUp = {},
    NodeRayTouchMove = {},
    NodeRayTouchCancelled = {},
    NodeRayMouseDown = {},
    NodeRayMouseUp = {},
    NodeRayMouseMove = {},
    NodeRayTouchMissed = {},
    NodeRayMouseMissed = {},
    NodeKeyboardShow = {},
    NodeKeyboardCancel = {},
    NodeKeyboardReturn = {},
    NodeRenderHUD = {},
    NodeGamePause = {},
    NodeGameUnPause = {},
    NodeTouchesDown = {},
    NodeTouchesUp = {},
    NodeTouchesMove = {},
    NodeTouchesCancelled = {},
    NodeTouchDown = {},
    NodeTouchUp = {},
    NodeTouchMove = {},
    NodeTouchCancelled = {},
    NodeMouseDown = {},
    NodeMouseUp = {},
    NodeMouseMove = {},
    NodeKeyDown = {},
    NodeKeyUp = {},
}

function RegisterCreate(name, func)
    Runtime.Create[name] = func
end

function RegisterDestroy(name, func)
    Runtime.Destroy[name] = func
end

function RegisterUpdate(name, func)
    Runtime.Update[name] = func
end

function RegisterRender(name, func)
    Runtime.Render[name] = func
end

function RegisterResize(name, func)
    Runtime.Resize[name] = func
end

function RegisterTouchesDown(name, func)
    Runtime.TouchesDown[name] = func
end

function RegisterTouchesUp(name, func)
    Runtime.TouchesUp[name] = func
end

function RegisterTouchesMove(name, func)
    Runtime.TouchesMove[name] = func
end

function RegisterTouchesCancelled(name, func)
    Runtime.TouchesCancelled[name] = func
end

function RegisterTouchDown(name, func)
    Runtime.TouchDown[name] = func
end

function RegisterTouchUp(name, func)
    Runtime.TouchUp[name] = func
end

function RegisterTouchMove(name, func)
    Runtime.TouchMove[name] = func
end

function RegisterTouchCancelled(name, func)
    Runtime.TouchCancelled[name] = func
end

function RegisterMouseDown(name, func)
    Runtime.MouseDown[name] = func
end

function RegisterMouseUp(name, func)
    Runtime.MouseUp[name] = func
end

function RegisterMouseMove(name, func)
    Runtime.MouseMove[name] = func
end
      
function RegisterKeyDown(name, func)
    Runtime.KeyDown[name] = func
end
      
function RegisterKeyUp(name, func)
    Runtime.KeyUp[name] = func
end
      
function RegisterWorldEnterState(name, func)
    Runtime.WorldEnterState[name] = func
end

function RegisterWorldUpdateState(name, func)
    Runtime.WorldUpdateState[name] = func
end

function RegisterWorldExitState(name, func)
    Runtime.WorldExitState[name] = func
end

function RegisterWorldOnMessage(name, func)
    Runtime.WorldOnMessage[name] = func
end

function RegisterWorldKeyboardShow(name, func)
    Runtime.WorldKeyboardShow[name] = func
end

function RegisterWorldKeyboardCancel(name, func)
    Runtime.WorldKeyboardCancel[name] = func
end

function RegisterWorldKeyboardReturn(name, func)
    Runtime.WorldKeyboardReturn[name] = func
end

function RegisterWorldReceivedMemoryWarning(name, func)
    Runtime.WorldReceivedMemoryWarning[name] = func
end

function RegisterWorldGamePause(name, func)
    Runtime.WorldGamePause[name] = func
end

function RegisterWorldGameUnPause(name, func)
    Runtime.WorldGameUnPause[name] = func
end

function RegisterWorldRenderHUD(name, func)
    Runtime.WorldRenderHUD[name] = func
end

function RegisterWorldTouchesDown(name, func)
    Runtime.WorldTouchesDown[name] = func
end

function RegisterWorldTouchesUp(name, func)
    Runtime.WorldTouchesUp[name] = func
end

function RegisterWorldTouchesMove(name, func)
    Runtime.WorldTouchesMove[name] = func
end

function RegisterWorldTouchesCancelled(name, func)
    Runtime.WorldTouchesCancelled[name] = func
end

function RegisterWorldTouchDown(name, func)
    Runtime.WorldTouchDown[name] = func
end

function RegisterWorldTouchUp(name, func)
    Runtime.WorldTouchUp[name] = func
end

function RegisterWorldTouchMove(name, func)
    Runtime.WorldTouchMove[name] = func
end

function RegisterWorldTouchCancelled(name, func)
    Runtime.WorldTouchCancelled[name] = func
end

function RegisterWorldMouseDown(name, func)
    Runtime.WorldMouseDown[name] = func
end

function RegisterWorldMouseUp(name, func)
    Runtime.WorldMouseUp[name] = func
end

function RegisterWorldMouseMove(name, func)
    Runtime.WorldMouseMove[name] = func
end
      
      
      
      
function RegisterWorldKeyDown(name, func)
    Runtime.WorldKeyDown[name] = func
end

function RegisterWorldKeyUp(name, func)
    Runtime.WorldKeyUp[name] = func
end
      

function RegisterWorldWillResignActive(name, func)
    Runtime.WorldWillResignActive[name] = func
end

function RegisterWorldDidBecomeActive(name, func)
    Runtime.WorldDidBecomeActive[name] = func
end

function RegisterWorldDidEnterBackground(name, func)
    Runtime.WorldDidEnterBackground[name] = func
end

function RegisterWorldWillEnterForeground(name, func)
    Runtime.WorldWillEnterForeground[name] = func
end

function RegisterWorldWillTerminate(name, func)
    Runtime.WorldWillTerminate[name] = func
end

function RegisterWorldInterrupt(name, func)
    Runtime.WorldInterrupt[name] = func
end

function RegisterWorldResumeInterrupt(name, func)
    Runtime.WorldResumeInterrupt[name] = func
end

function RegisterSceneEnterState(name, func)
    Runtime.SceneEnterState[name] = func
end

function RegisterSceneUpdateState(name, func)
    Runtime.SceneUpdateState[name] = func
end

function RegisterSceneExitState(name, func)
    Runtime.SceneExitState[name] = func
end

function RegisterSceneOnMessage(name, func)
    Runtime.SceneOnMessage[name] = func
end

function RegisterSceneKeyboardShow(name, func)
    Runtime.SceneKeyboardShow[name] = func
end

function RegisterSceneKeyboardCancel(name, func)
    Runtime.SceneKeyboardCancel[name] = func
end

function RegisterSceneKeyboardReturn(name, func)
    Runtime.SceneKeyboardReturn[name] = func
end

function RegisterSceneRenderHUD(name, func)
    Runtime.SceneRenderHUD[name] = func
end

function RegisterSceneGamePause(name, func)
    Runtime.SceneGamePause[name] = func
end

function RegisterSceneGameUnPause(name, func)
    Runtime.SceneGameUnPause[name] = func
end

function RegisterSceneTouchesDown(name, func)
    Runtime.SceneTouchesDown[name] = func
end

function RegisterSceneTouchesUp(name, func)
    Runtime.SceneTouchesUp[name] = func
end

function RegisterSceneTouchesMove(name, func)
    Runtime.SceneTouchesMove[name] = func
end

function RegisterSceneTouchesCancelled(name, func)
    Runtime.SceneTouchesCancelled[name] = func
end

function RegisterSceneTouchDown(name, func)
    Runtime.SceneTouchDown[name] = func
end

function RegisterSceneTouchUp(name, func)
    Runtime.SceneTouchUp[name] = func
end

function RegisterSceneTouchMove(name, func)
    Runtime.SceneTouchMove[name] = func
end

function RegisterSceneTouchCancelled(name, func)
    Runtime.SceneTouchCancelled[name] = func
end

function RegisterSceneMouseDown(name, func)
    Runtime.SceneMouseDown[name] = func
end

function RegisterSceneMouseUp(name, func)
    Runtime.SceneMouseUp[name] = func
end

function RegisterSceneMouseMove(name, func)
    Runtime.SceneMouseMove[name] = func
end
      
      
      
function RegisterSceneKeyDown(name, func)
    Runtime.SceneKeyDown[name] = func
end

function RegisterSceneKeyUp(name, func)
    Runtime.SceneKeyUp[name] = func
end

function RegisterSceneReceivedMemoryWarning(name, func)
    Runtime.SceneReceivedMemoryWarning[name] = func
end

function RegisterSceneWillResignActive(name, func)
    Runtime.SceneWillResignActive[name] = func
end

function RegisterSceneDidBecomeActive(name, func)
    Runtime.SceneDidBecomeActive[name] = func
end

function RegisterSceneDidEnterBackground(name, func)
    Runtime.SceneDidEnterBackground[name] = func
end

function RegisterSceneWillEnterForeground(name, func)
    Runtime.SceneWillEnterForeground[name] = func
end

function RegisterSceneWillTerminate(name, func)
    Runtime.SceneWillTerminate[name] = func
end

function RegisterSceneInterrupt(name, func)
    Runtime.SceneInterrupt[name] = func
end

function RegisterSceneResumeInterrupt(name, func)
    Runtime.SceneResumeInterrupt[name] = func
end

function RegisterNodeEnterState(name, func)
    Runtime.NodeEnterState[name] = func
end

function RegisterNodeUpdateState(name, func)
    Runtime.NodeUpdateState[name] = func
end

function RegisterNodeExitState(name, func)
    Runtime.NodeExitState[name] = func
end

function RegisterNodeOnMessage(name, func)
    Runtime.NodeOnMessage[name] = func
end

function RegisterNodeCollide(name, func)
    Runtime.NodeCollide[name] = func
end

function RegisterNodeNear(name, func)
    Runtime.NodeNear[name] = func
end

function RegisterNodeActionUpdate(name, func)
    Runtime.NodeActionUpdate[name] = func
end

function RegisterNodeActionComplete(name, func)
    Runtime.NodeActionComplete[name] = func
end

function RegisterNodeRayTouchesDown(name, func)
    Runtime.NodeRayTouchesDown[name] = func
end

function RegisterNodeRayTouchesUp(name, func)
    Runtime.NodeRayTouchesUp[name] = func
end

function RegisterNodeRayTouchesMove(name, func)
    Runtime.NodeRayTouchesMove[name] = func
end

function RegisterNodeRayTouchesCancelled(name, func)
    Runtime.NodeRayTouchesCancelled[name] = func
end

function RegisterNodeRayTouchesMissed(name, func)
    Runtime.NodeRayTouchesMissed[name] = func
end

function RegisterNodeRayTouchDown(name, func)
    Runtime.NodeRayTouchDown[name] = func
end

function RegisterNodeRayTouchUp(name, func)
    Runtime.NodeRayTouchUp[name] = func
end

function RegisterNodeRayTouchMove(name, func)
    Runtime.NodeRayTouchMove[name] = func
end

function RegisterNodeRayTouchCancelled(name, func)
    Runtime.NodeRayTouchCancelled[name] = func
end

function RegisterNodeRayMouseDown(name, func)
    Runtime.NodeRayMouseDown[name] = func
end

function RegisterNodeRayMouseUp(name, func)
    Runtime.NodeRayMouseUp[name] = func
end

function RegisterNodeRayMouseMove(name, func)
    Runtime.NodeRayMouseMove[name] = func
end

function RegisterNodeRayTouchMissed(name, func)
    Runtime.NodeRayTouchMissed[name] = func
end

function RegisterNodeRayMouseMissed(name, func)
    Runtime.NodeRayMouseMissed[name] = func
end

function RegisterNodeKeyboardShow(name, func)
    Runtime.NodeKeyboardShow[name] = func
end

function RegisterNodeKeyboardCancel(name, func)
    Runtime.NodeKeyboardCancel[name] = func
end

function RegisterNodeKeyboardReturn(name, func)
    Runtime.NodeKeyboardReturn[name] = func
end

function RegisterNodeRenderHUD(name, func)
    Runtime.NodeRenderHUD[name] = func
end

function RegisterNodeGamePause(name, func)
    Runtime.NodeGamePause[name] = func
end

function RegisterNodeGameUnPause(name, func)
    Runtime.NodeGameUnPause[name] = func
end

function RegisterNodeTouchesDown(name, func)
    Runtime.NodeTouchesDown[name] = func
end

function RegisterNodeTouchesUp(name, func)
    Runtime.NodeTouchesUp[name] = func
end

function RegisterNodeTouchesMove(name, func)
    Runtime.NodeTouchesMove[name] = func
end

function RegisterNodeTouchesCancelled(name, func)
    Runtime.NodeTouchesCancelled[name] = func
end

function RegisterNodeTouchDown(name, func)
    Runtime.NodeTouchDown[name] = func
end

function RegisterNodeTouchUp(name, func)
    Runtime.NodeTouchUp[name] = func
end

function RegisterNodeTouchMove(name, func)
    Runtime.NodeTouchMove[name] = func
end

function RegisterNodeTouchCancelled(name, func)
    Runtime.NodeTouchCancelled[name] = func
end

function RegisterNodeMouseDown(name, func)
    Runtime.NodeMouseDown[name] = func
end

function RegisterNodeMouseUp(name, func)
    Runtime.NodeMouseUp[name] = func
end

function RegisterNodeMouseMove(name, func)
    Runtime.NodeMouseMove[name] = func
end
      
      
      

      

function RegisterNodeKeyDown(name, func)
    Runtime.NodeKeyDown[name] = func
end

function RegisterNodeKeyUp(name, func)
    Runtime.NodeKeyUp[name] = func
end



function __NJLICreate()
    for k, v in pairs(Runtime.Create) do v() end
end

function __NJLIDestroy()
    for k, v in pairs(Runtime.Destroy) do v() end
end

function __NJLIUpdate(timeStep)
    for k, v in pairs(Runtime.Update) do v(timeStep) end
end

function __NJLIRender()
    for k, v in pairs(Runtime.Render) do v() end
end

function __NJLIResize(width, height, orientation)
    for k, v in pairs(Runtime.Resize) do v(width, height, orientation) end
end

function __NJLITouchesDown(touches)
    for k, v in pairs(Runtime.TouchesDown) do v(touches) end
end

function __NJLITouchesUp(touches)
    for k, v in pairs(Runtime.TouchesUp) do v(touches) end
end

function __NJLITouchesMove(touches)
    for k, v in pairs(Runtime.TouchesMove) do v(touches) end
end

function __NJLITouchesCancelled(touches)
    for k, v in pairs(Runtime.TouchesCancelled) do v(touches) end
end

function __NJLITouchDown(touch)
    for k, v in pairs(Runtime.TouchDown) do v(touch) end
end

function __NJLITouchUp(touch)
    for k, v in pairs(Runtime.TouchUp) do v(touch) end
end

function __NJLITouchMove(touch)
    for k, v in pairs(Runtime.TouchMove) do v(touch) end
end

function __NJLITouchCancelled(touch)
    for k, v in pairs(Runtime.TouchCancelled) do v(touch) end
end

function __NJLIMouseDown(mouse)
        print("__NJLIMouseDown")
    for k, v in pairs(Runtime.MouseDown) do v(mouse) end
end

function __NJLIMouseUp(mouse)
    for k, v in pairs(Runtime.MouseUp) do v(mouse) end
end

function __NJLIMouseMove(mouse)
    for k, v in pairs(Runtime.MouseMove) do v(mouse) end
end

function __NJLIKeyDown(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.KeyDown) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end

function __NJLIKeyUp(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.KeyUp) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end
                
                
                
                
                
                

function __NJLIWorldEnterState()
    for k, v in pairs(Runtime.WorldEnterState) do v() end
end

function __NJLIWorldUpdateState(timeStep)
    for k, v in pairs(Runtime.WorldUpdateState) do v(timeStep) end
end

function __NJLIWorldExitState()
    for k, v in pairs(Runtime.WorldExitState) do v() end
end

function __NJLIWorldOnMessage(message)
    for k, v in pairs(Runtime.WorldOnMessage) do v(message) end
end

function __NJLIWorldKeyboardShow()
    for k, v in pairs(Runtime.WorldKeyboardShow) do v() end
end

function __NJLIWorldKeyboardCancel()
    for k, v in pairs(Runtime.WorldKeyboardCancel) do v() end
end

function __NJLIWorldKeyboardReturn(text)
    for k, v in pairs(Runtime.WorldKeyboardReturn) do v(text) end
end

function __NJLIWorldReceivedMemoryWarning()
    for k, v in pairs(Runtime.WorldReceivedMemoryWarning) do v() end
end

function __NJLIWorldGamePause()
    for k, v in pairs(Runtime.WorldGamePause) do v() end 
end

function __NJLIWorldGameUnPause()
    for k, v in pairs(Runtime.WorldGameUnPause) do v() end 
end

function __NJLIWorldRenderHUD()
    for k, v in pairs(Runtime.WorldRenderHUD) do v() end 
end

function __NJLIWorldTouchesDown(touches)
    for k, v in pairs(Runtime.WorldTouchesDown) do v(touches) end 
end

function __NJLIWorldTouchesUp(touches)
    for k, v in pairs(Runtime.WorldTouchesUp) do v(touches) end 
end

function __NJLIWorldTouchesMove(touches)
    for k, v in pairs(Runtime.WorldTouchesMove) do v(touches) end 
end

function __NJLIWorldTouchesCancelled(touches)
    for k, v in pairs(Runtime.WorldTouchesCancelled) do v(touches) end 
end

function __NJLIWorldTouchDown(touches)
    for k, v in pairs(Runtime.WorldTouchDown) do v(touches) end 
end

function __NJLIWorldTouchUp(touches)
    for k, v in pairs(Runtime.WorldTouchUp) do v(touches) end 
end

function __NJLIWorldTouchMove(touches)
    for k, v in pairs(Runtime.WorldTouchMove) do v(touches) end 
end

function __NJLIWorldTouchCancelled(touches)
    for k, v in pairs(Runtime.WorldTouchCancelled) do v(touches) end 
end

function __NJLIWorldMouseDown(mouse)
    for k, v in pairs(Runtime.WorldMouseDown) do v(mouse) end 
end

function __NJLIWorldMouseUp(mouse)
    for k, v in pairs(Runtime.WorldMouseUp) do v(mouse) end 
end

function __NJLIWorldMouseMove(mouse)
    for k, v in pairs(Runtime.WorldMouseMove) do v(mouse) end 
end
        
        
        
        
        
        
        
        
        
        
        
        
function __NJLIWorldKeyDown(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.WorldKeyDown) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end

function __NJLIWorldKeyUp(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.WorldKeyUp) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end
                
                

function __NJLIWorldWillResignActive()
    for k, v in pairs(Runtime.WorldWillResignActive) do v() end 
end

function __NJLIWorldDidBecomeActive()
    for k, v in pairs(Runtime.WorldDidBecomeActive) do v() end 
end

function __NJLIWorldDidEnterBackground()
    for k, v in pairs(Runtime.WorldDidEnterBackground) do v() end 
end

function __NJLIWorldWillEnterForeground()
    for k, v in pairs(Runtime.WorldWillEnterForeground) do v() end 
end

function __NJLIWorldWillTerminate()
    for k, v in pairs(Runtime.WorldWillTerminate) do v() end 
end

function __NJLIWorldInterrupt()
    for k, v in pairs(Runtime.WorldInterrupt) do v() end 
end

function __NJLIWorldResumeInterrupt()
    for k, v in pairs(Runtime.WorldResumeInterrupt) do v() end 
end

function __NJLISceneEnterState(scene)
    for k, v in pairs(Runtime.SceneEnterState) do v(scene) end 
end

function __NJLISceneUpdateState(scene, timeStep)
    for k, v in pairs(Runtime.SceneUpdateState) do v(scene, timeStep) end 
end

function __NJLISceneExitState(scene)
    for k, v in pairs(Runtime.SceneExitState) do v(scene) end 
end

function __NJLISceneOnMessage(scene, message)
    for k, v in pairs(Runtime.SceneOnMessage) do v(scene, message) end 
end

function __NJLISceneKeyboardShow(scene)
    for k, v in pairs(Runtime.SceneKeyboardShow) do v(scene) end 
end

function __NJLISceneKeyboardCancel(scene)
    for k, v in pairs(Runtime.SceneKeyboardCancel) do v(scene) end 
end

function __NJLISceneKeyboardReturn(scene, text)
    for k, v in pairs(Runtime.SceneKeyboardReturn) do v(scene, text) end 
end

function __NJLISceneRenderHUD(scene)
    for k, v in pairs(Runtime.SceneRenderHUD) do v(scene) end 
end

function __NJLISceneGamePause(scene)
    for k, v in pairs(Runtime.SceneGamePause) do v(scene) end 
end

function __NJLISceneGameUnPause(scene)
    for k, v in pairs(Runtime.SceneGameUnPause) do v(scene) end 
end

function __NJLISceneTouchesDown(scene, touches)
    for k, v in pairs(Runtime.SceneTouchesDown) do v(scene, touches) end 
end

function __NJLISceneTouchesUp(scene, touches)
    for k, v in pairs(Runtime.SceneTouchesUp) do v(scene, touches) end 
end

function __NJLISceneTouchesMove(scene, touches)
    for k, v in pairs(Runtime.SceneTouchesMove) do v(scene, touches) end 
end

function __NJLISceneTouchesCancelled(scene, touches)
    for k, v in pairs(Runtime.SceneTouchesCancelled) do v(scene, touches) end 
end

function __NJLISceneTouchDown(scene, touches)
    for k, v in pairs(Runtime.SceneTouchDown) do v(scene, touches) end 
end

function __NJLISceneTouchUp(scene, touches)
    for k, v in pairs(Runtime.SceneTouchUp) do v(scene, touches) end 
end

function __NJLISceneTouchMove(scene, touches)
    for k, v in pairs(Runtime.SceneTouchMove) do v(scene, touches) end 
end

function __NJLISceneTouchCancelled(scene, touches)
    for k, v in pairs(Runtime.SceneTouchCancelled) do v(scene, touches) end 
end

function __NJLISceneMouseDown(scene, mouse)
    for k, v in pairs(Runtime.SceneMouseDown) do v(scene, mouse) end 
end

function __NJLISceneMouseUp(scene, mouse)
    for k, v in pairs(Runtime.SceneMouseUp) do v(scene, mouse) end 
end

function __NJLISceneMouseMove(scene, mouse)
    for k, v in pairs(Runtime.SceneMouseMove) do v(scene, mouse) end 
end
        
        
        
        
function __NJLISceneKeyDown(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.SceneKeyDown) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end

function __NJLISceneKeyUp(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.SceneKeyUp) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end
        
        
        
        
        
        

function __NJLISceneReceivedMemoryWarning(scene)
    for k, v in pairs(Runtime.SceneReceivedMemoryWarning) do v(scene) end 
end

function __NJLISceneWillResignActive(scene)
    for k, v in pairs(Runtime.SceneWillResignActive) do v(scene) end 
end

function __NJLISceneDidBecomeActive(scene)
    for k, v in pairs(Runtime.SceneDidBecomeActive) do v(scene) end 
end

function __NJLISceneDidEnterBackground(scene)
    for k, v in pairs(Runtime.SceneDidEnterBackground) do v(scene) end 
end

function __NJLISceneWillEnterForeground(scene)
    for k, v in pairs(Runtime.SceneWillEnterForeground) do v(scene) end 
end

function __NJLISceneWillTerminate(scene)
    for k, v in pairs(Runtime.SceneWillTerminate) do v(scene) end 
end

function __NJLISceneInterrupt(scene)
    for k, v in pairs(Runtime.SceneInterrupt) do v(scene) end 
end

function __NJLISceneResumeInterrupt(scene)
    for k, v in pairs(Runtime.SceneResumeInterrupt) do v(scene) end 
end

function __NJLINodeEnterState(node)
    for k, v in pairs(Runtime.NodeEnterState) do v(node) end 
end

function __NJLINodeUpdateState(node, timeStep)
    for k, v in pairs(Runtime.NodeUpdateState) do v(node, timeStep) end 
end

function __NJLINodeExitState(node)
    for k, v in pairs(Runtime.NodeExitState) do v(node) end 
end

function __NJLINodeOnMessage(node, message)
    for k, v in pairs(Runtime.NodeOnMessage) do v(node, message) end 
end

function __NJLINodeCollide(node, otherNode, collisionPoint)
    for k, v in pairs(Runtime.NodeCollide) do v(node, otherNode, collisionPoint) end 
end

function __NJLINodeNear(node, otherNode)
    for k, v in pairs(Runtime.NodeNear) do v(node, otherNode) end 
end

function __NJLINodeActionUpdate(action, timeStep)
    for k, v in pairs(Runtime.NodeActionUpdate) do v(action, timeStep) end 
end

function __NJLINodeActionComplete(action)
    for k, v in pairs(Runtime.NodeActionComplete) do v(action) end 
end

function __NJLINodeRayTouchesDown(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchesDown) do v(rayContact) end 
end

function __NJLINodeRayTouchesUp(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchesUp) do v(rayContact) end 
end

function __NJLINodeRayTouchesMove(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchesMove) do v(rayContact) end 
end

function __NJLINodeRayTouchesCancelled(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchesCancelled) do v(rayContact) end 
end

function __NJLINodeRayTouchesMissed(node)
    for k, v in pairs(Runtime.NodeRayTouchesMissed) do v(node) end 
end

function __NJLINodeRayTouchDown(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchDown) do v(rayContact) end 
end

function __NJLINodeRayTouchUp(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchUp) do v(rayContact) end 
end

function __NJLINodeRayTouchMove(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchMove) do v(rayContact) end 
end

function __NJLINodeRayTouchCancelled(rayContact)
    for k, v in pairs(Runtime.NodeRayTouchCancelled) do v(rayContact) end 
end

function __NJLINodeRayMouseDown(rayContact)
    for k, v in pairs(Runtime.NodeRayMouseDown) do v(rayContact) end 
end

function __NJLINodeRayMouseUp(rayContact)
    for k, v in pairs(Runtime.NodeRayMouseUp) do v(rayContact) end 
end

function __NJLINodeRayMouseMove(rayContact)
    for k, v in pairs(Runtime.NodeRayMouseMove) do v(rayContact) end 
end

function __NJLINodeRayTouchMissed(node)
    for k, v in pairs(Runtime.NodeRayTouchMissed) do v(node) end 
end

function __NJLINodeRayMouseMissed(node)
    for k, v in pairs(Runtime.NodeRayMouseMissed) do v(node) end 
end

function __NJLINodeKeyboardShow(node)
    for k, v in pairs(Runtime.NodeKeyboardShow) do v(node) end 
end

function __NJLINodeKeyboardCancel(node)
    for k, v in pairs(Runtime.NodeKeyboardCancel) do v(node) end 
end

function __NJLINodeKeyboardReturn(node)
    for k, v in pairs(Runtime.NodeKeyboardReturn) do v(node) end 
end

function __NJLINodeRenderHUD(node)
    for k, v in pairs(Runtime.NodeRenderHUD) do v(node) end 
end

function __NJLINodeGamePause(node)
    for k, v in pairs(Runtime.NodeGamePause) do v(node) end 
end

function __NJLINodeGameUnPause(node)
    for k, v in pairs(Runtime.NodeGameUnPause) do v(node) end 
end

function __NJLINodeTouchesDown(node, touches)
    for k, v in pairs(Runtime.NodeTouchesDown) do v(node, touches) end 
end

function __NJLINodeTouchesUp(node, touches)
    for k, v in pairs(Runtime.NodeTouchesUp) do v(node, touches) end 
end

function __NJLINodeTouchesMove(node, touches)
    for k, v in pairs(Runtime.NodeTouchesMove) do v(node, touches) end 
end

function __NJLINodeTouchesCancelled(node, touches)
    for k, v in pairs(Runtime.NodeTouchesCancelled) do v(node, touches) end 
end

function __NJLINodeTouchDown(node, touches)
    for k, v in pairs(Runtime.NodeTouchDown) do v(node, touches) end 
end

function __NJLINodeTouchUp(node, touches)
    for k, v in pairs(Runtime.NodeTouchUp) do v(node, touches) end 
end

function __NJLINodeTouchMove(node, touches)
    for k, v in pairs(Runtime.NodeTouchMove) do v(node, touches) end 
end

function __NJLINodeTouchCancelled(node, touches)
    for k, v in pairs(Runtime.NodeTouchCancelled) do v(node, touches) end 
end

function __NJLINodeMouseDown(node, mouse)
    for k, v in pairs(Runtime.NodeMouseDown) do v(node, mouse) end 
end

function __NJLINodeMouseUp(node, mouse)
    for k, v in pairs(Runtime.NodeMouseUp) do v(node, mouse) end 
end

function __NJLINodeMouseMove(node, mouse)
    for k, v in pairs(Runtime.NodeMouseMove) do v(node, mouse) end 
end
        
        
        
        
        
function __NJLINodeKeyDown(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.NodeKeyDown) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end

function __NJLINodeKeyUp(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui)
    for k, v in pairs(Runtime.NodeKeyUp) do v(keycodeName, withCapsLock, withControl, withShift, withAlt, withGui) end
end
        )";

    bool ret = false;
    if (World::getInstance()->getWorldLuaVirtualMachine()->compileString(
            source.c_str()))
      {
        ret = World::getInstance()->getWorldLuaVirtualMachine()->compileFile(
            "scripts/main.lua");
        njli::World::getInstance()->createScript();
      }
    return ret;
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
    njli::World::getInstance()->getDebugDrawer()->processSdlEvent(
        (SDL_Event *)event);
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
}
