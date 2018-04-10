//
//  SteeringBehaviorFlee.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorFlee.h"
#include "JLIFactoryTypes.h"
#include "SteeringBehaviorFleeBuilder.h"
#include "World.h"

#define TAG "SteeringBehaviorFlee.cpp"

#define FORMATSTRING "{\"jli::SteeringBehaviorFlee\":[]}"
#include "JsonJLI.h"
#include "btPrint.h"

namespace njli
{
  SteeringBehaviorFlee::SteeringBehaviorFlee() : SteeringBehavior() {}

  SteeringBehaviorFlee::SteeringBehaviorFlee(const AbstractBuilder &builder)
      : SteeringBehavior(builder)
  {
  }

  SteeringBehaviorFlee::SteeringBehaviorFlee(const SteeringBehaviorFlee &copy)
      : SteeringBehavior(copy)
  {
  }

  SteeringBehaviorFlee::~SteeringBehaviorFlee() {}

  SteeringBehaviorFlee &SteeringBehaviorFlee::
  operator=(const SteeringBehaviorFlee &rhs)
  {
    if (this != &rhs)
      {
      }
    return *this;
  }

  s32 SteeringBehaviorFlee::calculateSerializeBufferSize() const
  {
    // TODO: calculateSerializeBufferSize
    return 0;
  }

  void SteeringBehaviorFlee::serialize(void *dataBuffer,
                                       btSerializer *serializer) const
  {
    // TODO: serialize
  }

  const char *SteeringBehaviorFlee::getClassName() const
  {
    return "SteeringBehaviorFlee";
  }

  s32 SteeringBehaviorFlee::getType() const
  {
    return SteeringBehaviorFlee::type();
  }

  SteeringBehaviorFlee::operator std::string() const
  {
    // TODO: implement to string...

    std::string s = string_format("%s", FORMATSTRING);

    JsonJLI *json = JsonJLI::create();
    s = json->parse(s.c_str());
    JsonJLI::destroy(json);

    return s;
  }

  SteeringBehaviorFlee **SteeringBehaviorFlee::createArray(const u32 size)
  {
    return (SteeringBehaviorFlee **)World::getInstance()
        ->getWorldFactory()
        ->createArray(SteeringBehaviorFlee::type(), size);
  }

  void SteeringBehaviorFlee::destroyArray(SteeringBehaviorFlee **array,
                                          const u32 size)
  {
    World::getInstance()->getWorldFactory()->destroyArray(
        (AbstractFactoryObject **)array, size);
  }

  SteeringBehaviorFlee *SteeringBehaviorFlee::create()
  {
    return dynamic_cast<SteeringBehaviorFlee *>(
        World::getInstance()->getWorldFactory()->create(
            SteeringBehaviorFlee::type()));
  }

  SteeringBehaviorFlee *
  SteeringBehaviorFlee::create(const SteeringBehaviorFleeBuilder &builder)
  {
    AbstractBuilder *b = (AbstractBuilder *)&builder;

    return dynamic_cast<SteeringBehaviorFlee *>(
        World::getInstance()->getWorldFactory()->create(*b));
  }

  SteeringBehaviorFlee *
  SteeringBehaviorFlee::clone(const SteeringBehaviorFlee &object)
  {
    return dynamic_cast<SteeringBehaviorFlee *>(
        World::getInstance()->getWorldFactory()->clone(object, false));
  }

  SteeringBehaviorFlee *
  SteeringBehaviorFlee::copy(const SteeringBehaviorFlee &object)
  {
    return dynamic_cast<SteeringBehaviorFlee *>(
        World::getInstance()->getWorldFactory()->clone(object, true));
  }

  void SteeringBehaviorFlee::destroy(SteeringBehaviorFlee *object)
  {
    World::getInstance()->getWorldFactory()->destroy(object);
  }

  void SteeringBehaviorFlee::load(SteeringBehaviorFlee &object, lua_State *L,
                                  int index)
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
            SteeringBehaviorFlee::load(object, L, -2);
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

  u32 SteeringBehaviorFlee::type()
  {
    return JLI_OBJECT_TYPE_SteeringBehaviorFlee;
  }

  const btVector3 &SteeringBehaviorFlee::calculateForce()
  {
    SDL_assertPrint(false, "TODO");
    return *m_CurrentForce;
  }
}
