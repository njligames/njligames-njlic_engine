//
//  World.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/21/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "World.h"
#include "GraphicsPlatform.h"
#include "SceneState.h"
#include "SceneStateMachine.h"
#include "btVector2.h"

#include "tinyxml.h"

#include "Log.h"
#define TAG "World.cpp"
#include "AbstractRender.h"
#include "Image.h"
#include "Material.h"
#include "MaterialProperty.h"
#include "PhysicsWorld.h"
#include "ShaderProgram.h"
#define FORMATSTRING "{\"njli::World\":[]}"
#include "JsonJLI.h"
#include "btPrint.h"

#include "SDL_log.h"
#include "btQuickprof.h"
#include "unistd.h"
#include <signal.h>
#ifdef USE_NANOVG_LIBRARY
#include "WorldHUD.h"
#endif

#include "imgui.h"

bool done;

bool show_test_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImColor(114, 144, 154);

#define MAX_CONTACTS (100)

#if defined(__EMSCRIPTEN__)
#include "emscripten/emscripten.h"
#endif

namespace njli
{
  World *World::s_Instance = NULL;

  void World::createInstance()
  {
    if (NULL == s_Instance)
      {
        s_Instance = new World();
      }
    MaterialProperty::initReferences();
  }

  void World::destroyInstance()
  {
    delete s_Instance;
    s_Instance = NULL;
  }

  World *World::getInstance()
  {
    SDL_assert(s_Instance);
    //        if(NULL == s_Instance)
    //        {
    //            s_Instance = new World();
    //        }

    return s_Instance;
  }

  bool World::hasInstance() { return (NULL != s_Instance); }

  World::World()
      : m_WorldFactory(new WorldFactory()),
        m_WorldResourceLoader(new WorldResourceLoader()),
        m_WorldClock(new WorldClock()),
        m_WorldLuaVirtualMachine(new WorldLuaVirtualMachine()),
        //    m_WorldPythonVirtualMachine(new WorldPythonVirtualMachine()),
        m_stateMachine(new WorldStateMachine()),
        //    m_Name("MyWorld"),
        m_ViewPortDimensions(new btVector2()), m_Scene(NULL),
        m_WorldSocket(new WorldSocket),
#if defined(USE_NANOVG_LIBRARY)
        m_WorldHUD(new WorldHUD),
#endif
        m_WorldInput(new WorldInput), m_WorldSound(new WorldSound),
        m_WorldDebugDrawer(new WorldDebugDrawer),
        // m_WorldSQLite(new WorldSQLite),
        // m_WorldFacebook(new WorldFacebook),
        m_enableDebugDraw(false), m_DebugDrawCamera(NULL),
        m_DebugDrawMaterial(NULL),
        //    m_TouchCamera(NULL),
        m_SocketEnabled(false), m_SocketAddress("192.168.1.10"),
        m_SocketPort(2223), m_BackgroundColor(new btVector4(.5, .5, .5, .5)),
        m_DeviceName("NOT - SET"), m_AnimationPaused(false), m_GamePaused(false)
  {
    m_WorldDebugDrawer->init();

    addChild(m_WorldSound);
    addChild(m_WorldInput);
#ifdef USE_NANOVG_LIBRARY
    addChild(m_WorldHUD);
#endif
    addChild(m_WorldSocket);
    addChild(m_stateMachine);
    addChild(m_WorldLuaVirtualMachine);
    addChild(m_WorldClock);
    addChild(m_WorldResourceLoader);
    addChild(m_WorldFactory);
    // addChild(m_WorldFacebook);

    //    for (s32 i = 0; i < MAX_CONTACTS; ++i)
    //      {
    //        PhysicsRayContact *contact = PhysicsRayContact::create();
    //        m_RayContacts.push_back(contact);
    //      }
  }

  World::~World()
  {
    //        getWorldSQLite()->deleteBuffer();

    delete m_BackgroundColor;
    m_BackgroundColor = NULL;
    // delete m_WorldFacebook;m_WorldFacebook=NULL;
    // delete m_WorldSQLite;m_WorldSQLite=NULL;
    delete m_WorldDebugDrawer;
    m_WorldDebugDrawer = NULL;
    delete m_WorldSound;
    m_WorldSound = NULL;
    delete m_WorldInput;
    m_WorldInput = NULL;
#if defined(USE_NANOVG_LIBRARY)
    delete m_WorldHUD;
    m_WorldHUD = NULL;
#endif
    delete m_WorldSocket;
    m_WorldSocket = NULL;
    delete m_ViewPortDimensions;
    m_ViewPortDimensions = NULL;
    delete m_stateMachine;
    m_stateMachine = NULL;
    delete m_WorldLuaVirtualMachine;
    m_WorldLuaVirtualMachine = NULL;
    delete m_WorldClock;
    m_WorldClock = NULL;
    delete m_WorldResourceLoader;
    m_WorldResourceLoader = NULL;
    delete m_WorldFactory;
    m_WorldFactory = NULL;

    if (m_DebugDrawMaterial)
      {
        Material::destroy(m_DebugDrawMaterial);
        m_DebugDrawMaterial = NULL;
      }

    for (s32 i = 0; i < m_RayContacts.size(); ++i)
      {

        PhysicsRayContact *c = m_RayContacts.at(i);
        if (World::getInstance()->getWorldFactory()->has(c))
          PhysicsRayContact::destroy(c);
        removeChild(c);
      }
    m_RayContacts.clear();
  }

  WorldFactory *World::getWorldFactory()
  {
    s32 idx = getChildIndex(m_WorldFactory);
    if (idx != -1)
      return dynamic_cast<WorldFactory *>(getChild(idx));
    return NULL;
  }

  const WorldFactory *World::getWorldFactory() const
  {
    s32 idx = getChildIndex(m_WorldFactory);
    if (idx != -1)
      return dynamic_cast<const WorldFactory *>(getChild(idx));
    return NULL;
  }

  WorldResourceLoader *World::getWorldResourceLoader()
  {
    s32 idx = getChildIndex(m_WorldResourceLoader);
    if (idx != -1)
      return dynamic_cast<WorldResourceLoader *>(getChild(idx));
    return NULL;
  }

  const WorldResourceLoader *World::getWorldResourceLoader() const
  {
    s32 idx = getChildIndex(m_WorldResourceLoader);
    if (idx != -1)
      return dynamic_cast<const WorldResourceLoader *>(getChild(idx));
    return NULL;
  }

  WorldClock *World::getWorldClock()
  {
    s32 idx = getChildIndex(m_WorldClock);
    if (idx != -1)
      return dynamic_cast<WorldClock *>(getChild(idx));
    return NULL;
  }

  const WorldClock *World::getWorldClock() const
  {
    s32 idx = getChildIndex(m_WorldClock);
    if (idx != -1)
      return dynamic_cast<const WorldClock *>(getChild(idx));
    return NULL;
  }

  WorldLuaVirtualMachine *World::getWorldLuaVirtualMachine()
  {
    s32 idx = getChildIndex(m_WorldLuaVirtualMachine);
    if (idx != -1)
      //#if !(defined(NDEBUG))
      //        {
      //            return dynamic_cast<WorldLuaVirtualMachine*>(getChild(idx));
      //        }
      //#else
      {
        //            SDL_assert(dynamic_cast<WorldLuaVirtualMachine*>(getChild(idx)));
        return dynamic_cast<WorldLuaVirtualMachine *>(getChild(idx));
      }
    //#endif
    return NULL;
  }

  const WorldLuaVirtualMachine *World::getWorldLuaVirtualMachine() const
  {
    s32 idx = getChildIndex(m_WorldLuaVirtualMachine);
    if (idx != -1)
      //#if !(defined(NDEBUG))
      //        {
      //            return dynamic_cast<const
      //            WorldLuaVirtualMachine*>(getChild(idx));
      //        }
      //#else
      {
        //            SDL_assert(dynamic_cast<const
        //            WorldLuaVirtualMachine*>(getChild(idx)));
        return dynamic_cast<const WorldLuaVirtualMachine *>(getChild(idx));
      }
    //#endif

    return NULL;
  }

  //    WorldPythonVirtualMachine *World::getWorldPythonVirtualMachine()
  //    {
  //        s32 idx = getChildIndex(m_WorldPythonVirtualMachine);
  //        if(idx != -1)
  //            return dynamic_cast<WorldPythonVirtualMachine*>(getChild(idx));
  //        return NULL;
  //    }
  //
  //    const WorldPythonVirtualMachine *World::getWorldPythonVirtualMachine()
  //    const
  //    {
  //        s32 idx = getChildIndex(m_WorldPythonVirtualMachine);
  //        if(idx != -1)
  //            return dynamic_cast<const
  //            WorldPythonVirtualMachine*>(getChild(idx));
  //        return NULL;
  //    }

  WorldSocket *World::getWorldSocket()
  {
    s32 idx = getChildIndex(m_WorldSocket);
    if (idx != -1)
      return dynamic_cast<WorldSocket *>(getChild(idx));
    return NULL;
  }

  const WorldSocket *World::getWorldSocket() const
  {
    s32 idx = getChildIndex(m_WorldSocket);
    if (idx != -1)
      return dynamic_cast<const WorldSocket *>(getChild(idx));
    return NULL;
  }

/*WorldFacebook *World::getWorldFacebook()
{
    s32 idx = getChildIndex(m_WorldFacebook);
    if(idx != -1)
        return dynamic_cast<WorldFacebook*>(getChild(idx));
    return NULL;
}*/

/*const WorldFacebook *World::getWorldFacebook() const
{
    s32 idx = getChildIndex(m_WorldFacebook);
    if(idx != -1)
        return dynamic_cast<const WorldFacebook*>(getChild(idx));
    return NULL;
}*/

#if defined(USE_NANOVG_LIBRARY)
  WorldHUD *World::getWorldHUD()
  {
    s32 idx = getChildIndex(m_WorldHUD);
    if (idx != -1)
      return dynamic_cast<WorldHUD *>(getChild(idx));
    return NULL;
  }

  const WorldHUD *World::getWorldHUD() const
  {
    s32 idx = getChildIndex(m_WorldHUD);
    if (idx != -1)
      return dynamic_cast<const WorldHUD *>(getChild(idx));
    return NULL;
  }
#endif

  WorldInput *World::getWorldInput()
  {
    s32 idx = getChildIndex(m_WorldInput);
    if (idx != -1)
      return dynamic_cast<WorldInput *>(getChild(idx));
    return NULL;
  }

  const WorldInput *World::getWorldInput() const
  {
    s32 idx = getChildIndex(m_WorldInput);
    if (idx != -1)
      return dynamic_cast<const WorldInput *>(getChild(idx));
    return NULL;
  }

  WorldSound *World::getWorldSound()
  {
    s32 idx = getChildIndex(m_WorldSound);
    if (idx != -1)
      return dynamic_cast<WorldSound *>(getChild(idx));
    return NULL;
  }
  const WorldSound *World::getWorldSound() const
  {
    s32 idx = getChildIndex(m_WorldSound);
    if (idx != -1)
      return dynamic_cast<const WorldSound *>(getChild(idx));
    return NULL;
  }

  WorldStateMachine *World::getStateMachine()
  {
    s32 idx = getChildIndex(m_stateMachine);
    if (idx != -1)
      return dynamic_cast<WorldStateMachine *>(getChild(idx));
    return NULL;
  }

  const WorldStateMachine *World::getStateMachine() const
  {
    s32 idx = getChildIndex(m_stateMachine);
    if (idx != -1)
      return dynamic_cast<const WorldStateMachine *>(getChild(idx));
    return NULL;
  }

  WorldDebugDrawer *World::getDebugDrawer() { return m_WorldDebugDrawer; }

  const WorldDebugDrawer *World::getDebugDrawer() const
  {
    return m_WorldDebugDrawer;
  }

  // WorldSQLite *World::getWorldSQLite()
  //{
  //    return m_WorldSQLite;
  //}

  //    const WorldSQLite *World::getWorldSQLite()const
  //    {
  //        return m_WorldSQLite;
  //    }

  void World::touchDown(DeviceTouch **touch)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->touchDown(touch);
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
      }

    char action[BUFFER_SIZE] = "Down";
    char buffer[BUFFER_SIZE] = "";
    sprintf(buffer, "Touches%s", action);
    checkRayCollision(touch, buffer);

    if (getScene())
      getScene()->touchDown(touch);

    sprintf(buffer, "%s", "__NJLITouchesDown");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void World::touchUp(DeviceTouch **touch)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->touchUp(touch);
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
      }

    char action[BUFFER_SIZE] = "Up";
    char buffer[BUFFER_SIZE] = "";
    sprintf(buffer, "Touches%s", action);
    checkRayCollision(touch, buffer);

    if (getScene())
      getScene()->touchUp(touch);

    sprintf(buffer, "%s", "__NJLITouchesUp");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void World::touchMove(DeviceTouch **touch)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->touchMove(touch);
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
      }

    char action[BUFFER_SIZE] = "Move";
    char buffer[BUFFER_SIZE] = "";
    sprintf(buffer, "Touches%s", action);
    checkRayCollision(touch, buffer);

    if (getScene())
      getScene()->touchMove(touch);

    sprintf(buffer, "%s", "__NJLITouchesMove");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void World::touchCancelled(DeviceTouch **touch)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->touchCancelled(touch);
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
      }

    char action[BUFFER_SIZE] = "Cancelled";
    char buffer[BUFFER_SIZE] = "";
    sprintf(buffer, "Touches%s", action);
    checkRayCollision(touch, buffer);

    if (getScene())
      getScene()->touchCancelled(touch);

    sprintf(buffer, "%s", "__NJLITouchesCancelled");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void World::touchDown(const DeviceTouch &touch)
  {
    //        getDebugDrawer()->connectSynergyServer("192.168.7.22");
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->touchDown(touch);
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
      }

    char action[BUFFER_SIZE] = "Down";
    char buffer[BUFFER_SIZE] = "";
    sprintf(buffer, "Touch%s", action);
    checkRayCollision(touch, buffer);

    if (getScene())
      getScene()->touchDown(touch);

    sprintf(buffer, "%s", "__NJLITouchDown");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void World::touchUp(const DeviceTouch &touch)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->touchUp(touch);
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
      }

    char action[BUFFER_SIZE] = "Up";
    char buffer[BUFFER_SIZE] = "";
    sprintf(buffer, "Touch%s", action);
    checkRayCollision(touch, buffer);

    if (getScene())
      getScene()->touchUp(touch);

    sprintf(buffer, "%s", "__NJLITouchUp");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void World::touchMove(const DeviceTouch &touch)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->touchMove(touch);
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
      }

    char action[BUFFER_SIZE] = "Move";
    char buffer[BUFFER_SIZE] = "";
    sprintf(buffer, "Touch%s", action);
    checkRayCollision(touch, buffer);

    if (getScene())
      getScene()->touchMove(touch);

    sprintf(buffer, "%s", "__NJLITouchMove");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void World::mouseDown(const DeviceMouse &mouse)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->mouseDown(mouse);
      }
    else
      {
        //        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no
        //        WorldState\n");
      }

    char action[BUFFER_SIZE] = "Down";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "Mouse%s", action);
    checkRayCollision(mouse, buffer);

    if (getScene())
      getScene()->mouseDown(mouse);

    //    char buffer[256];
    sprintf(buffer, "%s", "__NJLIMouseDown");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     mouse);
  }

  void World::mouseUp(const DeviceMouse &mouse)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->mouseUp(mouse);
      }
    else
      {
        //        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no
        //        WorldState\n");
      }

    char action[BUFFER_SIZE] = "Up";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "Mouse%s", action);
    checkRayCollision(mouse, buffer);

    if (getScene())
      getScene()->mouseUp(mouse);

    //    char buffer[256];
    sprintf(buffer, "%s", "__NJLIMouseUp");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     mouse);
  }

  void World::mouseMove(const DeviceMouse &mouse)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->mouseMove(mouse);
      }
    else
      {
        //        SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no
        //        WorldState\n");
      }

    char action[BUFFER_SIZE] = "Move";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "Mouse%s", action);
    checkRayCollision(mouse, buffer);

    if (getScene())
      getScene()->mouseMove(mouse);

    //    char buffer[256];
    sprintf(buffer, "%s", "__NJLIMouseMove");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     mouse);
  }

  void World::keyUp(const char *keycodeName, bool withCapsLock,
                    bool withControl, bool withShift, bool withAlt,
                    bool withGui)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->keyUp(keycodeName, withCapsLock, withControl, withShift,
                            withAlt, withGui);
      }
    else
      {
        //            SDL_LogDebug(SDL _LOG_CATEGORY_TEST, "There is no
        //            WorldState\n");
      }

    if (getScene())
      getScene()->keyUp(keycodeName, withCapsLock, withControl, withShift,
                        withAlt, withGui);

    char buffer[256];
    sprintf(buffer, "%s", "__NJLIKeyUp");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
        buffer, keycodeName, withCapsLock, withControl, withShift, withAlt,
        withGui);
  }

  void World::keyDown(const char *keycodeName, bool withCapsLock,
                      bool withControl, bool withShift, bool withAlt,
                      bool withGui)
  {
    WorldState *currentState =
        dynamic_cast<WorldState *>(m_stateMachine->getState());

    if (currentState)
      {
        currentState->keyDown(keycodeName, withCapsLock, withControl, withShift,
                              withAlt, withGui);
      }
    else
      {
        //            SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no
        //            WorldState\n");
      }

    if (getScene())
      getScene()->keyDown(keycodeName, withCapsLock, withControl, withShift,
                          withAlt, withGui);

    char buffer[256];
    sprintf(buffer, "%s", "__NJLIKeyDown");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
        buffer, keycodeName, withCapsLock, withControl, withShift, withAlt,
        withGui);
  }

  //    void World::touchCancelled(const DeviceTouch &touches)
  //    {
  //        WorldState *currentState =
  //        dynamic_cast<WorldState*>(m_stateMachine->getState());
  //
  //        if(currentState)
  //        {
  //            currentState->touchCancelled(touches);
  //        }
  //        else
  //        {
  //            SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "There is no WorldState\n");
  //        }
  //
  //        if(getScene())
  //            getScene()->touchCancelled(touch);
  //
  //        char buffer[256];
  //        sprintf(buffer, "%s", "__NJLITouchCancelled");
  //        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
  //        touches);
  //    }

  void World::keyboardShow()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldKeyboardShow");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (getScene())
      getScene()->keyboardShow();
  }

  void World::keyboardCancel()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldKeyboardCancel");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

    if (getScene())
      getScene()->keyboardCancel();
  }

  void World::keyboardReturn(const char *text)
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIWorldKeyboardReturn");

    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     text);

    if (getScene())
      getScene()->keyboardReturn(text);
  }

  //    void World::setTouchCamera(Camera *camera)
  //    {
  //        m_TouchCamera = camera;
  //    }
  //    Camera *World::getTouchCamera()
  //    {
  //        return m_TouchCamera;
  //    }
  //    const Camera *World::getTouchCamera()const
  //    {
  //        return m_TouchCamera;
  //    }

  void World::getViewPort(s32 *viewPort) const
  {
    viewPort[0] = 0;
    viewPort[1] = 0;

    //        if
    //        (njli::World::getInstance()->getWorldInput()->isPortraitOrientation())
    {
      viewPort[2] = static_cast<s32>(
          njli::World::getInstance()->getViewportDimensions().x());
      viewPort[3] = static_cast<s32>(
          njli::World::getInstance()->getViewportDimensions().y());
    }
    //        else if
    //        (njli::World::getInstance()->getWorldInput()->isLandscapeOrientation())
    //        {
    //            viewPort[2] =
    //            static_cast<s32>(njli::World::getInstance()->getViewportDimensions().y());
    //            viewPort[3] =
    //            static_cast<s32>(njli::World::getInstance()->getViewportDimensions().x());
    //        }
  }

  void World::createScript()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLICreate");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
  }

  void World::destroyScript()
  {
    char buffer[256];
    sprintf(buffer, "%s", "__NJLIDestroy()");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
  }

  void World::update(f32 timeStep, const u32 numSubSteps)
  {
    BT_PROFILE("World::update");

    m_WorldClock->update(timeStep);

    if (getScene())
      getScene()->update(timeStep, numSubSteps);

    m_stateMachine->update(timeStep);

    char buffer[256];
    sprintf(buffer, "%s", "__NJLIUpdate");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     timeStep);

    //        for (s32 cameraIndex = 0; cameraIndex < m_cameraArray.size();
    //        ++cameraIndex)
    //        {
    //            m_cameraArray[cameraIndex]->updateProjection();
    //        }
    //        for (s32 nodeIndex = 0; nodeIndex < m_nodeArray.size();
    //        ++nodeIndex)
    //        {
    //            m_nodeArray[nodeIndex]->update(timeStep);
    //        }

    if (m_SocketEnabled)
      handleSocketMessage();
    m_WorldSound->update();

    //        u64 before = m_WorldFactory->collectGarbageSize();
    m_WorldFactory->collectGarbage();
    //        u64 after = m_WorldFactory->collectGarbageSize();

    //        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "There were (%lld) objects
    //        before and (%lld) objects after", before, after);
  }

  void World::render()
  {

#if defined(USE_NANOVG_LIBRARY)
    getWorldHUD()->renderFBOs();
#endif
    renderGL();

    Scene *scene = getScene();

    if (scene)
      scene->render();
#if defined(USE_NANOVG_LIBRARY)
    getWorldHUD()->render();
#endif

    char buffer[256];
    sprintf(buffer, "%s", "__NJLIRender");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);

#if !defined(NDEBUG)

    if (m_enableDebugDraw)
      {
        getDebugDrawer()->beginDraw();

        if (scene)
          {
            PhysicsWorld *physicsWorld = scene->getPhysicsWorld();
            if (physicsWorld)
              {
                physicsWorld->debugDrawWorld();
              }
            else
              {
                SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                            "Debug draw is enabled without a physics World.");
              }
          }
        else
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "Debug draw is enabled without a scene.");
          }

        if (m_DebugDrawCamera)
          {
            getDebugDrawer()->draw(m_DebugDrawCamera);
          }
        else
          {
            //                SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Debug draw is
            //                enabled without a camera.");
          }

        //            // 1. Show a simple window
        //            // Tip: if we don't call ImGui::Begin()/ImGui::End() the
        //            widgets appears in a window automatically called "Debug"
        //            {
        //                static float f = 0.0f;
        //                ImGui::Text("Hello, world!");
        //                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        //                ImGui::ColorEdit3("clear color",
        //                (float*)&clear_color);
        //                if (ImGui::Button("Test Window")) show_test_window ^=
        //                1;
        //                if (ImGui::Button("Another Window"))
        //                show_another_window ^= 1;
        //                ImGui::Text("Application average %.3f ms/frame (%.1f
        //                FPS)", 1000.0f / ImGui::GetIO().Framerate,
        //                ImGui::GetIO().Framerate);
        //            }
        //
        //            // 2. Show another simple window, this time using an
        //            explicit Begin/End pair
        //            if (show_another_window)
        //            {
        //                ImGui::SetNextWindowSize(ImVec2(200,100),
        //                ImGuiSetCond_FirstUseEver);
        //                ImGui::Begin("Another Window", &show_another_window);
        //                ImGui::Text("Hello");
        //                ImGui::End();
        //            }
        //
        //            // 3. Show the ImGui test window. Most of the sample code
        //            is in ImGui::ShowTestWindow()
        //            if (show_test_window)
        //            {
        //                ImGui::SetNextWindowPos(ImVec2(650, 20),
        //                ImGuiSetCond_FirstUseEver);
        //                ImGui::ShowTestWindow(&show_test_window);
        //            }

        getDebugDrawer()->endDraw();
      }
#endif
    m_WorldFactory->collectGarbage_GPU();
  }

  void World::resize(s32 x, s32 y, s32 width, s32 height, s32 orientation)
  {
    setGLViewSize(x, y, width, height);
    m_ViewPortDimensions->setX(width);
    m_ViewPortDimensions->setY(height);
    getWorldInput()->setOrientation(orientation);

    if (getScene())
      getScene()->updateViewSize();

    char buffer[256];
    sprintf(buffer, "%s", "__NJLIResize");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
        buffer, width, height, orientation);

    //        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Screen Dimensions:
    //        `%dx%d`", width, height);
  }

  const btVector2 &World::getViewportDimensions() const
  {
    return *m_ViewPortDimensions;
  }

  f32 World::getAspectRatio() const
  {
    return fabsf(m_ViewPortDimensions->x() / m_ViewPortDimensions->y());
  }

  const char *World::getClassName() const { return "World"; }

  s32 World::getType() const { return JLI_OBJECT_TYPE_World; }

  World::operator std::string() const
  {
    return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
  }

  //    Scene *World::getScene()const
  //    {
  //        return m_Scene;
  //    }

  void World::setScene(Scene *scene)
  {
    SDL_assert(scene != NULL);

    Scene *currentScene = getScene();
    if (scene != currentScene)
      {
        if (currentScene)
          {
            removeChild(currentScene);

            SceneStateMachine *sm = currentScene->getStateMachine();
            sm->clear();
          }

        m_Scene = scene;
        m_Scene->updateViewSize();

        addChild(m_Scene);
      }
  }

  void World::removeScene()
  {
    if (getScene())
      removeChild(getScene());

    m_Scene = NULL;
  }

  Scene *World::getScene()
  {
    s32 idx = getChildIndex(m_Scene);
    if (idx != -1)
      //#if !(defined(NDEBUG))
      //        {
      //            return dynamic_cast<Scene*>(getChild(idx));
      //        }
      //#else
      {
        //            SDL_assert(dynamic_cast<Scene*>(getChild(idx)));
        return dynamic_cast<Scene *>(getChild(idx));
      }
    //#endif

    return NULL;
  }

  const Scene *World::getScene() const
  {
    s32 idx = getChildIndex(m_Scene);
    if (idx != -1)
      //#if !(defined(NDEBUG))
      //        {
      //            return dynamic_cast<const Scene*>(getChild(idx));
      //        }
      //#else
      {
        //            SDL_assert(dynamic_cast<const Scene*>(getChild(idx)));
        return dynamic_cast<const Scene *>(getChild(idx));
      }
    //#endif

    return NULL;
  }

  void World::enableDebugDraw(Camera *camera)
  {
    if (camera)
      {
        m_enableDebugDraw = true;
        m_DebugDrawCamera = camera;
      }
    else
      {
        SDL_LogDebug(SDL_LOG_CATEGORY_TEST,
                     "Unable to enableDebugDraw, camera is NULL\n");
      }
  }

  void World::disableDebugDraw()
  {
    m_enableDebugDraw = false;
    m_DebugDrawCamera = NULL;
  }

  //    void World::enableDebugDraw(bool enable)
  //    {
  //        m_enableDebugDraw = enable;
  //    }
  //    void World::setDebugDrawCamera(Camera *camera)
  //    {
  //        njliAssert(camera);
  //        m_DebugDrawCamera = camera;
  //    }
  //
  //    void World::setDebugShader(ShaderProgram *shaderProgram)
  //    {
  //        njliAssert(shaderProgram);
  //
  //        getDebugDrawer()->addShaderProgram(shaderProgram);
  //    }
  //
  //    void World::setDebugMaterial(Material *material)
  //    {
  //        njliAssert(material);
  //
  //        getDebugDrawer()->addMaterial(material);
  //    }

  void World::startSocket(u8 n0, u8 n1, u8 n2, u8 n3, u16 port)
  {
    stopSocket();

    char buffer[1024];
    sprintf(buffer, "%d.%d.%d.%d", n0, n1, n2, n3);
    if ((n0 >= 0 && n0 <= 255) && (n1 >= 0 && n1 <= 255) &&
        (n2 >= 0 && n2 <= 255) && (n3 >= 0 && n3 <= 255))
      {
        m_SocketAddress = buffer;
        m_SocketPort = port;
        m_SocketEnabled = true;
      }
    else
      {
        SDL_LogError(SDL_LOG_CATEGORY_TEST, "Invalid ip %s", buffer);
      }
  }

  void World::startSocket(u16 port)
  {
    stopSocket();

    m_SocketAddress = std::string("localhost");
    m_SocketPort = port;
    m_SocketEnabled = true;
  }

  bool World::isSocketEnabled() const { return m_SocketEnabled; }
  void World::stopSocket()
  {
    m_SocketEnabled = false;
    if (getWorldSocket()->isConnected())
      getWorldSocket()->disconnectJLI();
  }

  const char *World::getSocketAddress() const
  {
    return m_SocketAddress.c_str();
  }
  u16 World::getSocketPort() const { return m_SocketPort; }

  void World::setBackgroundAlpha(const f32 alpha)
  {
    btVector4 _color(m_BackgroundColor->x(), m_BackgroundColor->y(),
                     m_BackgroundColor->z(), clampColor(alpha));
    setBackgroundColor(_color);
  }

  void World::setBackgroundColor(const btVector3 &color)
  {
    btVector4 _color(color.x(), color.y(), color.z(), m_BackgroundColor->w());
    setBackgroundColor(_color);
  }

  void World::setBackgroundColor(const btVector4 &color)
  {
    *m_BackgroundColor = color;
    setGLBackgroundColor(
        clampColor(m_BackgroundColor->x()), clampColor(m_BackgroundColor->y()),
        clampColor(m_BackgroundColor->z()), clampColor(m_BackgroundColor->w()));
  }

  void World::setBackgroundColor(f32 red, f32 green, f32 blue)
  {
    btVector4 _color(red, green, blue, m_BackgroundColor->w());
    setBackgroundColor(_color);
  }

  const btVector4 &World::getBackgroundColor() const
  {
    return *m_BackgroundColor;
  }

  const char *World::getDeviceName() const { return m_DeviceName.c_str(); }

  void World::setDeviceName(const char *name) { m_DeviceName = name; }

  void World::enablePauseAnimation(bool enable) { m_AnimationPaused = enable; }

  bool World::isAnimationPaused() const { return m_AnimationPaused; }

  void World::enablePauseGame(bool enable)
  {
    if (enable && !isPausedGame())
      {
        s8 buffer[BUFFER_SIZE];
        sprintf(buffer, "%s", "__NJLIWorldGamePause");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
            buffer);

        if (getScene())
          getScene()->pauseGame();
      }

    if (!enable && isPausedGame())
      {
        s8 buffer[BUFFER_SIZE];
        sprintf(buffer, "%s", "__NJLIWorldGameUnPause");
        njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
            buffer);

        if (getScene())
          getScene()->unPauseGame();
      }

    m_GamePaused = enable;
  }

  bool World::isPausedGame() const { return m_GamePaused; }

  bool World::isDebug() const
  {
#if !(defined(NDEBUG))
    return true;
#endif
    return false;
  }
  bool World::runJavascript(const char *script)
  {
#if defined(__EMSCRIPTEN__)
    emscripten_run_script(script);
    return true;
#endif
    return false;
  }

  //    void World::addNode(Node *node)
  //    {
  //        if(!hasNode(node))
  //            m_nodeArray.push_back(node);
  //    }
  //
  //    void World::removeNode(Node *node)
  //    {
  //        if(hasNode(node))
  //            m_nodeArray.push_back(node);
  //    }
  //
  //    bool World::hasNode(Node *node)
  //    {
  //        return m_nodeArray.size() != m_nodeArray.findLinearSearch(node);
  //    }
  //
  //    void World::removeAllNodes()
  //    {
  //        m_nodeArray.clear();
  //    }
  //    void World::parseSocketMessage(const char *msg)
  //    {
  //        if(NULL!=msg)// && strcmp(msg, "") != 0)
  //        {
  //            std::string socketMessage(msg);
  //            size_t found=socketMessage.find("<root>");
  //            if (found != -1)
  //            {
  //                found=socketMessage.find("</root>");
  //                if(found != -1)
  //                {
  //                    TiXmlDocument document;
  //                    document.Parse(socketMessage.c_str());
  //
  //                    TiXmlNode* ele = NULL;
  //                    while ( (ele = document.FirstChildElement( "root"
  //                    )->IterateChildren( ele ) ) != 0 )
  //                    {
  //                        TiXmlElement *e = ele->ToElement();
  //
  //                        std::string contentType(e->Value());
  //                        std::transform(contentType.begin(),
  //                        contentType.end(), contentType.begin(), ::tolower);
  //
  //                        if(contentType == std::string("lua"))
  //                        {
  //                            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
  //                            e->GetText());
  //                            World::getInstance()->getWorldLuaVirtualMachine()->loadString(e->GetText());
  //                        }
  //                        else if(contentType == std::string("vertex"))
  //                        {
  //                            std::string name(e->Attribute("name"));
  //
  //                            //                    Log("%s\n%s\b%s",
  //                            e->Value(), name.c_str(), e->GetText());
  //                        }
  //                        else if(contentType == std::string("fragment"))
  //                        {
  //                            std::string name(e->Attribute("name"));
  //
  //                            //                    Log("%s\n%s\b%s",
  //                            e->Value(), name.c_str(), e->GetText());
  //
  //                        }
  //                    }
  //                }
  //                else
  //                {
  //                    SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Maybe need to resize
  //                    the Socket buffer?\n%s", msg);
  //
  //                }
  //            }
  //        }
  //    }

  void World::processMessage(const std::string &socketMessage,
                             const std::string delimeter)
  {
    TiXmlDocument document;
    document.Parse(socketMessage.c_str());

    TiXmlNode *ele = NULL;
    while ((ele = document.FirstChildElement(delimeter.c_str())
                      ->IterateChildren(ele)) != 0)
      {
        TiXmlElement *e = ele->ToElement();

        std::string contentType(e->Value());
        std::transform(contentType.begin(), contentType.end(),
                       contentType.begin(), ::tolower);

        if (contentType == std::string("lua"))
          {
            std::string type(e->Attribute("type"));
            std::string name(e->Attribute("name"));

            //                std::string source;
            //                const TiXmlNode* child = e->FirstChild();
            //                if ( child ) {
            //                    source = child->Value();
            ////                    const TiXmlText* childText =
            /// child->ToText();
            ////                    if ( childText ) {
            ////                        TiXmlString s = childText->ValueTStr();
            ////                        source = s.data();
            //////                        return childText->Value();
            ////                    }
            //                }

            std::string source(e->GetText());
            std::string filePath = DOCUMENT_PATH(name.c_str());
            int numwrote = 0;

            if (type == std::string("build") || type == std::string("run"))
              {
                if (type == std::string("build"))
                  {
                    bool wrote = false;

                    if (access(filePath.c_str(), F_OK) != -1)
                      {
                        FILE *f = fopen(filePath.c_str(), "wb");

                        if (f != NULL)
                          {
                            numwrote = fwrite(source.c_str(), sizeof(char),
                                              source.length(), f);

                            fclose(f);

                            if (0 == ferror(f))
                              wrote = true;
                          }
                      }

                    if (!wrote)
                      SDL_LogVerbose(
                          SDL_LOG_CATEGORY_TEST,
                          "Couldn't write file %s - (%d bytes of %u)",
                          filePath.c_str(), numwrote, source.length());
                    else
                      SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Wrote file %s",
                                     filePath.c_str());
                  }

                if (type == std::string("run"))
                  {
                    World::getInstance()->getWorldLuaVirtualMachine()->reset();

                    World::getInstance()
                        ->getWorldLuaVirtualMachine()
                        ->loadString(source.c_str());
                    World::getInstance()->getWorldLuaVirtualMachine()->loadFile(
                        DOCUMENT_PATH("scripts/main.lua"));
                    World::getInstance()
                        ->getWorldLuaVirtualMachine()
                        ->compile();
                  }
                else
                  {
                    World::getInstance()
                        ->getWorldLuaVirtualMachine()
                        ->loadString(source.c_str());
                    World::getInstance()
                        ->getWorldLuaVirtualMachine()
                        ->compile();
                  }
              }
          }
        else if (contentType == std::string("vertex"))
          {
            std::string name(e->Attribute("name"));

            //                    Log("%s\n%s\b%s", e->Value(), name.c_str(),
            //                    e->GetText());
          }
        else if (contentType == std::string("fragment"))
          {
            std::string name(e->Attribute("name"));

            //                    Log("%s\n%s\b%s", e->Value(), name.c_str(),
            //                    e->GetText());
          }
      }
  }

  void World::handleSocketMessage()
  {
    if (getWorldSocket()->hasMessage())
      {
        processMessage(getWorldSocket()->popMessage());
      }

    if (getWorldSocket()->isConnected())
      {
        getWorldSocket()->parseMessage("root");
      }
    else
      {
        getWorldSocket()->connectJLI(m_SocketAddress.c_str(), m_SocketPort);
      }
  }

  void World::checkRayCollision(DeviceTouch **m_CurrentTouches,
                                const char *code, bool disableNodeTouched)
  {
    Scene *scene = njli::World::getInstance()->getScene();

    if (scene)
      {
        Camera *camera = scene->getTouchCamera();
        if (NULL != camera)
          {
            PhysicsWorld *physicsWorld = scene->getPhysicsWorld();
            if (physicsWorld)
              {
                btAlignedObjectArray<Node *> untouchedNodes;
                untouchedNodes.clear();

                scene->getActiveNodes(untouchedNodes);

                bool touched = false;
                for (s32 i = 0; i < DeviceTouch::MAX_TOUCHES; ++i)
                  {
                    if (m_CurrentTouches[i])
                      {
                        btVector2 touchPosition =
                            m_CurrentTouches[i]->getPosition();
                        btVector3 from, to;
                        camera->getTouchRay(touchPosition, from, to);

                        if (m_RayContacts.size() <= 0)
                          {
                            for (s32 i = 0; i < MAX_CONTACTS; ++i)
                              {
                                PhysicsRayContact *contact =
                                    PhysicsRayContact::create();
                                m_RayContacts.push_back(contact);
                              }
                          }
                        s32 numContacts = 0;
                        if (physicsWorld->rayTestAll(from, to, m_RayContacts,
                                                     numContacts))
                          {
                            for (s32 i = 0; i < numContacts; ++i)
                              {
                                PhysicsRayContact *contact =
                                    m_RayContacts.at(i);

                                if (disableNodeTouched)
                                  {
                                    contact->getHitNode()->enableTouched(false);
                                  }
                                untouchedNodes.remove(contact->getHitNode());
                                contact->screenPosition(
                                    btVector2(from.x(), from.y()));
                                char buffer[BUFFER_SIZE];
                                sprintf(buffer, "%s%s", "__NJLINodeRay", code);
                                njli::World::getInstance()
                                    ->getWorldLuaVirtualMachine()
                                    ->execute(buffer, *contact);
                                touched = true;
                              }
                          }
                        //                        if(physicsWorld->rayTestClosest(from,
                        //                        to, *m_RayContact))
                        //                        {
                        //                            if (disableNodeTouched)
                        //                            {
                        //                                m_RayContact->getHitNode()->enableTouched(false);
                        //                            }
                        //                            m_RayContact->screenPosition(btVector2(from.x(),
                        //                            from.y()));
                        //                            char buffer[BUFFER_SIZE];
                        //                            sprintf(buffer, "%s%s",
                        //                            code, "Ray");
                        //                            njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                        //                            *m_RayContact);
                        //                            touched = true;
                        //                        }
                      }
                  }

                for (unsigned int i = 0; i < untouchedNodes.size(); i++)
                  {
                    Node *n = untouchedNodes[i];

                    char buffer[BUFFER_SIZE];
                    sprintf(buffer, "%s", "__NJLINodeRayTouchesMissed");
                    njli::World::getInstance()
                        ->getWorldLuaVirtualMachine()
                        ->execute(buffer, n);
                  }
                //                if (!touched)
                //                {
                //                    char buffer[BUFFER_SIZE];
                //                    sprintf(buffer, "%s%s", code,
                //                    "RayMissed");
                //                    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
                //                }
              }
          }
        else
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "setTouchCamera() must be called on the scene\n");
          }
      }
  }

  void World::checkRayCollision(const DeviceTouch &touch, const char *code,
                                bool disableNodeTouched)
  {
    Scene *scene = njli::World::getInstance()->getScene();

    if (scene)
      {
        Camera *camera = scene->getTouchCamera();
        if (NULL != camera)
          {
            PhysicsWorld *physicsWorld = scene->getPhysicsWorld();
            if (physicsWorld)
              {
                btAlignedObjectArray<Node *> untouchedNodes;
                untouchedNodes.clear();

                scene->getActiveNodes(untouchedNodes);

                bool touched = false;
                btVector2 touchPosition = touch.getPosition();
                btVector3 from, to;
                camera->getTouchRay(touchPosition, from, to);

                if (m_RayContacts.size() <= 0)
                  {
                    for (s32 i = 0; i < MAX_CONTACTS; ++i)
                      {
                        PhysicsRayContact *contact =
                            PhysicsRayContact::create();
                        m_RayContacts.push_back(contact);
                      }
                  }

                if (m_RayContacts.size() <= 0)
                  {
                    for (s32 i = 0; i < MAX_CONTACTS; ++i)
                      {
                        PhysicsRayContact *contact =
                            PhysicsRayContact::create();
                        m_RayContacts.push_back(contact);
                      }
                  }

                s32 numContacts = 0;
                if (physicsWorld->rayTestAll(from, to, m_RayContacts,
                                             numContacts))
                  {
                    for (s32 i = 0; i < numContacts; ++i)
                      {
                        PhysicsRayContact *contact = m_RayContacts.at(i);

                        if (disableNodeTouched)
                          {
                            contact->getHitNode()->enableTouched(false);
                          }
                        untouchedNodes.remove(contact->getHitNode());
                        contact->screenPosition(btVector2(from.x(), from.y()));
                        char buffer[BUFFER_SIZE];
                        sprintf(buffer, "%s%s", "__NJLINodeRay", code);
                        njli::World::getInstance()
                            ->getWorldLuaVirtualMachine()
                            ->execute(buffer, *contact);
                        touched = true;
                      }
                  }

                for (unsigned int i = 0; i < untouchedNodes.size(); i++)
                  {
                    Node *n = untouchedNodes[i];

                    char buffer[BUFFER_SIZE];
                    sprintf(buffer, "%s", "__NJLINodeRayTouchMissed");
                    njli::World::getInstance()
                        ->getWorldLuaVirtualMachine()
                        ->execute(buffer, n);
                  }
              }
          }
        else
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "setTouchCamera() must be called on the scene\n");
          }
      }
  }

  void World::checkRayCollision(const DeviceMouse &mouse, const char *code,
                                bool disableNodeTouched)
  {
    Scene *scene = njli::World::getInstance()->getScene();

    if (scene)
      {
        Camera *camera = scene->getTouchCamera();
        if (NULL != camera)
          {
            PhysicsWorld *physicsWorld = scene->getPhysicsWorld();
            if (physicsWorld)
              {
                btAlignedObjectArray<Node *> untouchedNodes;
                untouchedNodes.clear();

                scene->getActiveNodes(untouchedNodes);

                bool touched = false;
                btVector2 touchPosition = mouse.getPosition();
                btVector3 from, to;
                camera->getTouchRay(touchPosition, from, to);

                if (m_RayContacts.size() <= 0)
                  {
                    for (s32 i = 0; i < MAX_CONTACTS; ++i)
                      {
                        PhysicsRayContact *contact =
                            PhysicsRayContact::create();
                        m_RayContacts.push_back(contact);
                      }
                  }

                PhysicsRayContact *contact = m_RayContacts.at(0);
                s32 numContacts = 0;
                if (physicsWorld->rayTestAll(from, to, m_RayContacts,
                                             numContacts))
                  {
                    //                      SDL_LogInfo(SDL_LOG_CATEGORY_TEST,
                    //                                  "RayTest Hit (all).\n");
                    for (s32 i = 0; i < numContacts; ++i)
                      {
                        contact = m_RayContacts.at(i);

                        if (disableNodeTouched)
                          {
                            contact->getHitNode()->enableTouched(false);
                          }
                        untouchedNodes.remove(contact->getHitNode());
                        contact->screenPosition(btVector2(from.x(), from.y()));
                        char buffer[BUFFER_SIZE];
                        sprintf(buffer, "%s%s", "__NJLINodeRay", code);
                        njli::World::getInstance()
                            ->getWorldLuaVirtualMachine()
                            ->execute(buffer, *contact);
                        touched = true;
                      }
                  }
                else if (physicsWorld->rayTestClosest(from, to, *contact))
                  {
                    //                      SDL_LogInfo(SDL_LOG_CATEGORY_TEST,
                    //                                  "RayTest Hit
                    //                                  (closest).\n");

                    if (disableNodeTouched)
                      {
                        contact->getHitNode()->enableTouched(false);
                      }
                    untouchedNodes.remove(contact->getHitNode());
                    contact->screenPosition(btVector2(from.x(), from.y()));
                    char buffer[BUFFER_SIZE];
                    sprintf(buffer, "%s%s", "__NJLINodeRay", code);
                    njli::World::getInstance()
                        ->getWorldLuaVirtualMachine()
                        ->execute(buffer, *contact);
                    touched = true;
                  }
                else
                  {
                    //                      SDL_LogInfo(SDL_LOG_CATEGORY_TEST,
                    //                                  "RayTest Missed.\n");
                  }

                for (unsigned int i = 0; i < untouchedNodes.size(); i++)
                  {
                    Node *n = untouchedNodes[i];
                    std::string name = n->getName();

                    if (n->getPhysicsBody() != NULL)
                      {
                        char buffer[BUFFER_SIZE];
                        sprintf(buffer, "%s", "__NJLINodeRayMouseMissed");
                        njli::World::getInstance()
                            ->getWorldLuaVirtualMachine()
                            ->execute(buffer, n);
                      }
                  }
              }
          }
        else
          {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                        "setTouchCamera() must be called on the scene\n");
          }
      }
  }
  /*
   new (TestsWorldState)
   enter (TestsWorldState)
      new (BasicTestSceneState)
      enter (BasicTestSceneState)
          new (myTestNode)
          enter (myTestNode->myTestNode)
          exit (myTestNode->myTestNode)
          delete (myTestNode)
      exit (BasicTestSceneState)
      delete (BasicTestSceneState)
   exit (TestsWorldState)

   enter (TestsWorldState)
      new (BasicTestSceneState)
      enter (BasicTestSceneState)
          new (myTestNode)
          enter (myTestNode->myTestNode)
          exit (myTestNode->myTestNode)
          delete (myTestNode)
      exit (BasicTestSceneState)
      delete (BasicTestSceneState)
   exit (TestsWorldState)

   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)
   exit (myTestNode->myTestNode)
   delete (myTestNode)
   exit (BasicTestSceneState)
   delete (BasicTestSceneState)
   exit (TestsWorldState)
   enter (TestsWorldState)
   new (BasicTestSceneState)
   enter (BasicTestSceneState)
   new (myTestNode)
   enter (myTestNode->myTestNode)

   */
}
