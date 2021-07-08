//
//  SteeringBehaviorWander.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorWander.h"
#include "JLIFactoryTypes.h"
#include "SteeringBehaviorWanderBuilder.h"
#include "World.h"

#define TAG "SteeringBehaviorWander.cpp"

#define FORMATSTRING "{\"njli::SteeringBehaviorWander\":[{\"name\":\"%s\"}]}"
#include "JsonJLI.h"
#include "btPrint.h"

#include "SteeringBehaviorMachine.h"

namespace njli
{
    SteeringBehaviorWander::SteeringBehaviorWander() : SteeringBehavior(),
    m_WanderTarget(new btVector3(0, 0, 0)),
    m_WanderJitter(1.333333333333333),
    m_WanderRadius(1.2f),
    m_WanderDistance(2.0f)
    {}

  SteeringBehaviorWander::SteeringBehaviorWander(const AbstractBuilder &builder)
    : SteeringBehavior(builder),
    m_WanderTarget(new btVector3(0, 0, 0)),
    m_WanderJitter(1.333333333333333),
    m_WanderRadius(1.2f),
    m_WanderDistance(2.0f)
  {
  }

  SteeringBehaviorWander::SteeringBehaviorWander(
      const SteeringBehaviorWander &copy)
    : SteeringBehavior(copy),
    m_WanderTarget(new btVector3(0, 0, 0)),
    m_WanderJitter(1.333333333333333),
    m_WanderRadius(1.2f),
    m_WanderDistance(2.0f)
  {
  }

    SteeringBehaviorWander::~SteeringBehaviorWander() {delete m_WanderTarget; }

  SteeringBehaviorWander &SteeringBehaviorWander::
  operator=(const SteeringBehaviorWander &rhs)
  {
    if (this != &rhs)
      {
      }
    return *this;
  }

  s32 SteeringBehaviorWander::calculateSerializeBufferSize() const
  {
    // TODO: calculateSerializeBufferSize
    return 0;
  }

  void SteeringBehaviorWander::serialize(void *dataBuffer,
                                         btSerializer *serializer) const
  {
    // TODO: serialize
  }

  const char *SteeringBehaviorWander::getClassName() const
  {
    return "SteeringBehaviorWander";
  }

  s32 SteeringBehaviorWander::getType() const
  {
    return SteeringBehaviorWander::type();
  }

  SteeringBehaviorWander::operator std::string() const
  {
    std::string temp(string_format(FORMATSTRING, getName()));
    return temp;
  }

  SteeringBehaviorWander **SteeringBehaviorWander::createArray(const u32 size)
  {
    return (SteeringBehaviorWander **)World::getInstance()
        ->getWorldFactory()
        ->createArray(SteeringBehaviorWander::type(), size);
  }

  void SteeringBehaviorWander::destroyArray(SteeringBehaviorWander **array,
                                            const u32 size)
  {
    World::getInstance()->getWorldFactory()->destroyArray(
        (AbstractFactoryObject **)array, size);
  }

  SteeringBehaviorWander *SteeringBehaviorWander::create()
  {
    return dynamic_cast<SteeringBehaviorWander *>(
        World::getInstance()->getWorldFactory()->create(
            SteeringBehaviorWander::type()));
  }

  SteeringBehaviorWander *
  SteeringBehaviorWander::create(const SteeringBehaviorWanderBuilder &builder)
  {
    AbstractBuilder *b = (AbstractBuilder *)&builder;

    return dynamic_cast<SteeringBehaviorWander *>(
        World::getInstance()->getWorldFactory()->create(*b));
  }

  SteeringBehaviorWander *
  SteeringBehaviorWander::clone(const SteeringBehaviorWander &object)
  {
    return dynamic_cast<SteeringBehaviorWander *>(
        World::getInstance()->getWorldFactory()->clone(object, false));
  }

  SteeringBehaviorWander *
  SteeringBehaviorWander::copy(const SteeringBehaviorWander &object)
  {
    return dynamic_cast<SteeringBehaviorWander *>(
        World::getInstance()->getWorldFactory()->clone(object, true));
  }

  void SteeringBehaviorWander::destroy(SteeringBehaviorWander *object)
  {
    World::getInstance()->getWorldFactory()->destroy(object);
  }

  void SteeringBehaviorWander::load(SteeringBehaviorWander &object,
                                    lua_State *L, int index)
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
            SteeringBehaviorWander::load(object, L, -2);
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
                //                    jli::AbstractFactoryObject *object =
                //                    static_cast<jli::AbstractFactoryObject*>(usr->ptr);
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

  u32 SteeringBehaviorWander::type()
  {
    return JLI_OBJECT_TYPE_SteeringBehaviorWander;
  }

  const btVector3 &SteeringBehaviorWander::calculateForce()
  {
      SteeringBehaviorMachine *machine = getParent();
      const Node *vehicleNode = machine->getParent();
      
      *m_CurrentForce = SteeringBehaviorMachine::wander(vehicleNode->getOrigin(), *m_WanderTarget, m_WanderJitter, m_WanderRadius, m_WanderDistance);
      
      return *m_CurrentForce;
  }
} // namespace njli
