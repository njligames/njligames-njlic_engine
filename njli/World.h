//
//  World.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__World__
#define __JLIGameEngineTest__World__

#include "Util.h"
#include <cstddef>

//#include "btAlignedObjectArray.h"
#include "WorldFactory.h"
#include "WorldLuaVirtualMachine.h"
//#include "WorldSQLite.h"
#include "WorldSound.h"
//#include "WorldPythonVirtualMachine.h"
#include "Camera.h"
#include "WorldClock.h"
#include "WorldDebugDrawer.h"
//#include "WorldHUD.h"
#include "WorldInput.h"
#include "WorldResourceLoader.h"
#include "WorldSocket.h"
#include "WorldSound.h"
#include "WorldState.h"
#include "WorldStateMachine.h"
#include <string>
//#include "WorldFacebook.h"

namespace njli
{
  class WorldHUD;
  /// <#Description#>
  class World : public AbstractObject
  {
  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    static void createInstance();
    static void destroyInstance();
    static World *getInstance();
    static bool hasInstance();

  private:
    World();
    virtual ~World();

  public:
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldFactory *getWorldFactory();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldFactory *getWorldFactory() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldResourceLoader *getWorldResourceLoader();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldResourceLoader *getWorldResourceLoader() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldClock *getWorldClock();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldClock *getWorldClock() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldLuaVirtualMachine *getWorldLuaVirtualMachine();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldLuaVirtualMachine *getWorldLuaVirtualMachine() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //        WorldPythonVirtualMachine *getWorldPythonVirtualMachine();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //        const WorldPythonVirtualMachine *getWorldPythonVirtualMachine()
    //        const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldSocket *getWorldSocket();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldSocket *getWorldSocket() const;

/**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
// WorldFacebook *getWorldFacebook();
/**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
// const WorldFacebook *getWorldFacebook() const;

#if defined(USE_NANOVG_LIBRARY)
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldHUD *getWorldHUD();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldHUD *getWorldHUD() const;
#endif

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldInput *getWorldInput();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldInput *getWorldInput() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldSound *getWorldSound();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldSound *getWorldSound() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldStateMachine *getStateMachine();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldStateMachine *getStateMachine() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    WorldDebugDrawer *getDebugDrawer();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const WorldDebugDrawer *getDebugDrawer() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    // WorldSQLite* getWorldSQLite();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    // const WorldSQLite* getWorldSQLite() const;

    /**
         *  <#Description#>
         *
         *  @param touches <#touches description#>
         */
    void touchDown(DeviceTouch **touches);
    /**
         *  <#Description#>
         *
         *  @param touches <#touches description#>
         */
    void touchUp(DeviceTouch **touches);
    /**
         *  <#Description#>
         *
         *  @param touches <#touches description#>
         */
    void touchMove(DeviceTouch **touches);
    /**
         *  <#Description#>
         *
         *  @param touches <#touches description#>
         */
    void touchCancelled(DeviceTouch **touches);

    void touchDown(const DeviceTouch &touch);
    void touchUp(const DeviceTouch &touch);
    void touchMove(const DeviceTouch &touch);

    void mouseDown(const DeviceMouse &touch);
    void mouseUp(const DeviceMouse &touch);
    void mouseMove(const DeviceMouse &touch);

    void keyUp(const char *keycodeName, bool withCapsLock, bool withControl,
               bool withShift, bool withAlt, bool withGui);

    void keyDown(const char *keycodeName, bool withCapsLock, bool withControl,
                 bool withShift, bool withAlt, bool withGui);

    void keyboardShow();
    void keyboardCancel();
    void keyboardReturn(const char *text);

    /**
         *  <#Description#>
         *
         *  @param camera <#camera description#>
         */
    //    void setTouchCamera(Camera* camera);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //    Camera* getTouchCamera();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    //    const Camera* getTouchCamera() const;
    /**
         *  <#Description#>
         *
         *  @param viewPort <#viewPort description#>
         */
    void getViewPort(s32 *viewPort) const;

    /**
     <#Description#>
     */
    void createScript();

    /**
     <#Description#>
     */
    void destroyScript();

    /**
         *  <#Description#>
         *
         *  @param timeStep <#timeStep description#>
         */
    void update(f32 timeStep, const u32 numSubSteps);

    /**
         *  <#Description#>
         */
    void render();

    /**
         *  <#Description#>
         *
         *  @param width       <#width description#>
         *  @param height      <#height description#>
         *  @param orientation <#orientation description#>
         */
    void resize(s32 x, s32 y, s32 width, s32 height, s32 orientation);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector2 &getViewportDimensions() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getAspectRatio() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual const char *getClassName() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 getType() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual operator std::string() const;

    /**
         *  <#Description#>
         *
         *  @param scene <#scene description#>
         */
    void setScene(Scene *scene);
    /**
         *  <#Description#>
         */
    void removeScene();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Scene *getScene();
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const Scene *getScene() const;

    /**
     <#Description#>

     @param camera <#camera description#>
     */
    void enableDebugDraw(Camera *camera);

    /**
         *  <#Description#>
         */
    void disableDebugDraw();

    /**
         *  <#Description#>
         *
         *  @param n0   <#n0 description#>
         *  @param n1   <#n1 description#>
         *  @param n2   <#n2 description#>
         *  @param n3   <#n3 description#>
         *  @param port <#port description#>
         */
    void startSocket(u8 n0, u8 n1, u8 n2, u8 n3, u16 port = 2223);
    void startSocket(u16 port = 2223);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isSocketEnabled() const;
    /**
         *  <#Description#>
         */
    void stopSocket();

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char *getSocketAddress() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    u16 getSocketPort() const;

    /**
         *  <#Description#>
         *
         *  @param alpha <#alpha description#>
         */
    void setBackgroundAlpha(const f32 alpha);
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void setBackgroundColor(const btVector3 &color);
    /**
         *  <#Description#>
         *
         *  @param color <#color description#>
         */
    void setBackgroundColor(const btVector4 &color);

    /**
     <#Description#>

     @param red <#red description#>
     @param green <#green description#>
     @param blue <#blue description#>
     */
    void setBackgroundColor(f32 red, f32 green, f32 blue);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector4 &getBackgroundColor() const;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const char *getDeviceName() const;
    /**
         *  <#Description#>
         *
         *  @param name <#name description#>
         */
    void setDeviceName(const char *name);

    void enablePauseAnimation(bool enable = true);

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    bool isAnimationPaused() const;

    void enablePauseGame(bool enable = true);
    bool isPausedGame() const;

    bool isDebug() const;

    bool runJavascript(const char *script);

  protected:
    //        void parseSocketMessage(const char *msg);
    void processMessage(const std::string &msg,
                        const std::string delimeter = "root");
    void handleSocketMessage();

    void checkRayCollision(DeviceTouch **touches, const char *code,
                           bool disableNodeTouched = false);
    void checkRayCollision(const DeviceTouch &touch, const char *code,
                           bool disableNodeTouched = false);
    void checkRayCollision(const DeviceMouse &mouse, const char *code,
                           bool disableNodeTouched = false);

  private:
    btAlignedObjectArray<njli::PhysicsRayContact *> m_RayContacts;

    World(const World &);
    World &operator=(const World &);

    static World *s_Instance;

    WorldFactory *m_WorldFactory;
    WorldResourceLoader *m_WorldResourceLoader;
    WorldClock *m_WorldClock;
    WorldLuaVirtualMachine *m_WorldLuaVirtualMachine;
    //        WorldPythonVirtualMachine *m_WorldPythonVirtualMachine;
    WorldStateMachine *m_stateMachine;

    btVector2 *m_ViewPortDimensions;

    Scene *m_Scene;
    WorldSocket *m_WorldSocket;
    WorldHUD *m_WorldHUD;
    WorldInput *m_WorldInput;
    WorldSound *m_WorldSound;
    WorldDebugDrawer *m_WorldDebugDrawer;
    // WorldSQLite* m_WorldSQLite;
    // WorldFacebook *m_WorldFacebook;
    bool m_enableDebugDraw;
    Camera *m_DebugDrawCamera;
    Material *m_DebugDrawMaterial;

    //    Camera* m_TouchCamera;

    bool m_SocketEnabled;
    std::string m_SocketAddress;
    u16 m_SocketPort;
    btVector4 *m_BackgroundColor;
    std::string m_DeviceName;

    bool m_AnimationPaused;
    bool m_GamePaused;
  };

  inline btVector2 SCREEN()
  {
    if (njli::World::getInstance())
      return njli::World::getInstance()->getViewportDimensions();
    return btVector2(0, 0);
  }
}

#endif /* defined(__JLIGameEngineTest__World__) */
