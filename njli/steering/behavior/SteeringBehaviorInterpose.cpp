//
//  SteeringBehaviorInterpose.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorInterpose.h"
#include "JLIFactoryTypes.h"
#include "SteeringBehaviorInterposeBuilder.h"
#include "World.h"

#define TAG "SteeringBehaviorInterpose.cpp"

#define FORMATSTRING "{\"njli::SteeringBehaviorInterpose\":[{\"name\":\"%s\"}]}"
#include "JsonJLI.h"
#include "btPrint.h"

namespace njli
{
  SteeringBehaviorInterpose::SteeringBehaviorInterpose() : SteeringBehavior() {}

  SteeringBehaviorInterpose::SteeringBehaviorInterpose(
      const AbstractBuilder &builder)
      : SteeringBehavior(builder)
  {
  }

  SteeringBehaviorInterpose::SteeringBehaviorInterpose(
      const SteeringBehaviorInterpose &copy)
      : SteeringBehavior(copy)
  {
  }

  SteeringBehaviorInterpose::~SteeringBehaviorInterpose() {}

  SteeringBehaviorInterpose &SteeringBehaviorInterpose::
  operator=(const SteeringBehaviorInterpose &rhs)
  {
    if (this != &rhs)
      {
      }
    return *this;
  }

  s32 SteeringBehaviorInterpose::calculateSerializeBufferSize() const
  {
    // TODO: calculateSerializeBufferSize
    return 0;
  }

  void SteeringBehaviorInterpose::serialize(void *dataBuffer,
                                            btSerializer *serializer) const
  {
    // TODO: serialize
  }

  const char *SteeringBehaviorInterpose::getClassName() const
  {
    return "SteeringBehaviorInterpose";
  }

  s32 SteeringBehaviorInterpose::getType() const
  {
    return SteeringBehaviorInterpose::type();
  }

  SteeringBehaviorInterpose::operator std::string() const
  {
    std::string temp(string_format(FORMATSTRING, getName()));
    return temp;
  }

  SteeringBehaviorInterpose **
  SteeringBehaviorInterpose::createArray(const u32 size)
  {
    return (SteeringBehaviorInterpose **)World::getInstance()
        ->getWorldFactory()
        ->createArray(SteeringBehaviorInterpose::type(), size);
  }

  void
  SteeringBehaviorInterpose::destroyArray(SteeringBehaviorInterpose **array,
                                          const u32 size)
  {
    World::getInstance()->getWorldFactory()->destroyArray(
        (AbstractFactoryObject **)array, size);
  }

  SteeringBehaviorInterpose *SteeringBehaviorInterpose::create()
  {
    return dynamic_cast<SteeringBehaviorInterpose *>(
        World::getInstance()->getWorldFactory()->create(
            SteeringBehaviorInterpose::type()));
  }

  SteeringBehaviorInterpose *SteeringBehaviorInterpose::create(
      const SteeringBehaviorInterposeBuilder &builder)
  {
    AbstractBuilder *b = (AbstractBuilder *)&builder;

    return dynamic_cast<SteeringBehaviorInterpose *>(
        World::getInstance()->getWorldFactory()->create(*b));
  }

  SteeringBehaviorInterpose *
  SteeringBehaviorInterpose::clone(const SteeringBehaviorInterpose &object)
  {
    return dynamic_cast<SteeringBehaviorInterpose *>(
        World::getInstance()->getWorldFactory()->clone(object, false));
  }

  SteeringBehaviorInterpose *
  SteeringBehaviorInterpose::copy(const SteeringBehaviorInterpose &object)
  {
    return dynamic_cast<SteeringBehaviorInterpose *>(
        World::getInstance()->getWorldFactory()->clone(object, true));
  }

  void SteeringBehaviorInterpose::destroy(SteeringBehaviorInterpose *object)
  {
    World::getInstance()->getWorldFactory()->destroy(object);
  }

  void SteeringBehaviorInterpose::load(SteeringBehaviorInterpose &object,
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
            SteeringBehaviorInterpose::load(object, L, -2);
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

  u32 SteeringBehaviorInterpose::type()
  {
    return JLI_OBJECT_TYPE_SteeringBehaviorInterpose;
  }

  const btVector3 &SteeringBehaviorInterpose::calculateForce()
  {
    SDL_assertPrint(false, "TODO");
    return *m_CurrentForce;
  }
} // namespace njli
