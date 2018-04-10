//
//  WorldState.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "WorldState.h"
#include "JLIFactoryTypes.h"
#include "Log.h"
#include "PhysicsRayContact.h"
#include "PhysicsWorld.h"
#include "Scene.h"
#include "SceneState.h"
#include "SceneStateMachine.h"
#include "World.h"
#include "WorldStateBuilder.h"
#define TAG "WorldState.cpp"
#define FORMATSTRING "{\"njli::WorldState\":[]}"
#include "JsonJLI.h"
#include "SDL_log.h"
#include "btPrint.h"

#define MAX_CONTACTS (100)

namespace njli
{
  WorldState::WorldState() : AbstractState<void>()
  {
    char buffer[1024];
    sprintf(buffer, "%s's PhysicsRayContact", getName());
  }

  WorldState::WorldState(const AbstractBuilder &builder)
      : AbstractState<void>(builder)
  {
    char buffer[1024];
    sprintf(buffer, "%s's PhysicsRayContact", getName());
  }

  WorldState::WorldState(const WorldState &copy) : AbstractState<void>(copy)
  {
    char buffer[1024];
    sprintf(buffer, "%s's PhysicsRayContact", getName());
  }

  WorldState::~WorldState() {}

  WorldState &WorldState::operator=(const WorldState &rhs)
  {
    if (this != &rhs)
      {
      }
    return *this;
  }

  s32 WorldState::calculateSerializeBufferSize() const
  {
    // TODO: calculateSerializeBufferSize
    return 0;
  }

  void WorldState::serialize(void *dataBuffer, btSerializer *serializer) const
  {
    // TODO: serialize
  }

  const char *WorldState::getClassName() const { return "WorldState"; }

  s32 WorldState::getType() const { return WorldState::type(); }

  WorldState::operator std::string() const
  {
    return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
  }

  WorldState **WorldState::createArray(const u32 size)
  {
    return (WorldState **)World::getInstance()->getWorldFactory()->createArray(
        WorldState::type(), size);
  }

  void WorldState::destroyArray(WorldState **array, const u32 size)
  {
    World::getInstance()->getWorldFactory()->destroyArray(
        (AbstractFactoryObject **)array, size);
  }

  WorldState *WorldState::create()
  {
    return dynamic_cast<WorldState *>(
        World::getInstance()->getWorldFactory()->create(WorldState::type()));
  }

  WorldState *WorldState::create(const WorldStateBuilder &builder)
  {
    AbstractBuilder *b = (AbstractBuilder *)&builder;

    return dynamic_cast<WorldState *>(
        World::getInstance()->getWorldFactory()->create(*b));
  }

  WorldState *WorldState::clone(const WorldState &object)
  {
    return dynamic_cast<WorldState *>(
        World::getInstance()->getWorldFactory()->clone(object, false));
  }

  WorldState *WorldState::copy(const WorldState &object)
  {
    return dynamic_cast<WorldState *>(
        World::getInstance()->getWorldFactory()->clone(object, true));
  }

  void WorldState::destroy(WorldState *object)
  {
    if (object)
      {
        //        for (s32 i = 0; i < MAX_CONTACTS; ++i)
        //          {
        //
        //            PhysicsRayContact *c = object->m_RayContacts.at(i);
        //            if (World::getInstance()->getWorldFactory()->has(c))
        //              PhysicsRayContact::destroy(c);
        //            object->removeChild(c);
        //          }
        //        object->m_RayContacts.clear();

        World::getInstance()->getWorldFactory()->destroy(object);
      }
  }

  void WorldState::load(WorldState &object, lua_State *L, int index)
  {
    // Push another reference to the table on top of the stack (so we know
    // where it is, and this function can work for negative, positive and
    // pseudo indices
    lua_pushvalue(L, index);
    // stack now contains: -1 => table
    lua_pushnil(L);
    // stack now contains: -1 => nil; -2 => table
    while (lua_next(L, -2))
      {
        // stack now contains: -1 => value; -2 => key; -3 => table
        // copy the key so that lua_tostring does not modify the original
        lua_pushvalue(L, -2);
        // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
        const char *key = lua_tostring(L, -1);
        //            const char *value = lua_tostring(L, -2);
        if (lua_istable(L, -2))
          {
            WorldState::load(object, L, -2);
          }
        else
          {
            if (lua_isnumber(L, index))
              {
                double number = lua_tonumber(L, index);
                printf("%s => %f\n", key, number);
              }
            else if (lua_isstring(L, index))
              {
                const char *v = lua_tostring(L, index);
                printf("%s => %s\n", key, v);
              }
            else if (lua_isboolean(L, index))
              {
                bool v = lua_toboolean(L, index);
                printf("%s => %d\n", key, v);
              }
            else if (lua_isuserdata(L, index))
              {
                //                    swig_lua_userdata *usr;
                //                    swig_type_info *type;
                //                    assert(lua_isuserdata(L,index));
                //                    usr=(swig_lua_userdata*)lua_touserdata(L,index);
                //                    /* get data */
                //                    type = usr->type;
                //                    njli::AbstractFactoryObject *object =
                //                    static_cast<njli::AbstractFactoryObject*>(usr->ptr);
                //                    printf("%s => %d:%s\n", key,
                //                    object->getType(),
                //                    object->getClassName());
              }
          }
        // pop value + copy of key, leaving original key
        lua_pop(L, 2);
        // stack now contains: -1 => key; -2 => table
      }
    // stack now contains: -1 => table (when lua_next returns 0 it pops the key
    // but does not push anything.)
    // Pop table
    lua_pop(L, 1);
    // Stack is now the same as it was on entry to this function
  }

  u32 WorldState::type() { return JLI_OBJECT_TYPE_WorldState; }

  void WorldState::enter(void *object)
  {
    char buffer[BUFFER_SIZE] = "__NJLIWorldEnterState";
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
  }

  void WorldState::update(void *object, f32 timeStep)
  {
    BT_PROFILE("WorldState::update");
    char buffer[BUFFER_SIZE] = "__NJLIWorldUpdateState";
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     timeStep);
  }

  void WorldState::exit(void *object)
  {
    Scene *scene = World::getInstance()->getScene();
    if (scene)
      {
        scene->clearAllStates();
      }

    char buffer[BUFFER_SIZE] = "__NJLIWorldExitState";
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer);
  }

  bool WorldState::onMessage(void *object, const Telegram &msg) const
  {
    bool ret;
    char buffer[BUFFER_SIZE] = "__NJLIWorldOnMessage";

    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     msg, ret);

    return ret;
  }

  void WorldState::touchDown(DeviceTouch **touch)
  {
    char action[BUFFER_SIZE] = "Down";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouches%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void WorldState::touchUp(DeviceTouch **touch)
  {
    char action[BUFFER_SIZE] = "Up";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouches%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void WorldState::touchMove(DeviceTouch **touch)
  {
    char action[BUFFER_SIZE] = "Move";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouches%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void WorldState::touchCancelled(DeviceTouch **touch)
  {
    char action[BUFFER_SIZE] = "Cancelled";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouches%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void WorldState::touchDown(const DeviceTouch &touch)
  {
    char action[BUFFER_SIZE] = "Down";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouch%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void WorldState::touchUp(const DeviceTouch &touch)
  {
    char action[BUFFER_SIZE] = "Up";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouch%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void WorldState::touchMove(const DeviceTouch &touch)
  {
    char action[BUFFER_SIZE] = "Move";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouch%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }

  void WorldState::mouseDown(const DeviceMouse &mouse)
  {
    char action[BUFFER_SIZE] = "Down";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldMouse%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     mouse);
  }

  void WorldState::mouseUp(const DeviceMouse &mouse)
  {
    char action[BUFFER_SIZE] = "Up";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldMouse%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     mouse);
  }

  void WorldState::mouseMove(const DeviceMouse &mouse)
  {
    char action[BUFFER_SIZE] = "Move";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldMouse%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     mouse);
  }

  void WorldState::keyUp(const char *keycodeName, bool withCapsLock,
                         bool withControl, bool withShift, bool withAlt,
                         bool withGui)
  {
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s", "__NJLIWorldKeyUp");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
        buffer, keycodeName, withCapsLock, withControl, withShift, withAlt,
        withGui);
  }

  void WorldState::keyDown(const char *keycodeName, bool withCapsLock,
                           bool withControl, bool withShift, bool withAlt,
                           bool withGui)
  {
    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%s", "__NJLIWorldKeyDown");
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(
        buffer, keycodeName, withCapsLock, withControl, withShift, withAlt,
        withGui);
  }

  void WorldState::touchCancelled(const DeviceTouch &touch)
  {
    char action[BUFFER_SIZE] = "Cancelled";
    char buffer[BUFFER_SIZE] = "";

    sprintf(buffer, "__NJLIWorldTouch%s", action);
    njli::World::getInstance()->getWorldLuaVirtualMachine()->execute(buffer,
                                                                     touch);
  }
}
