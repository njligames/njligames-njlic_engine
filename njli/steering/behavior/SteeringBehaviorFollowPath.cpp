//
//  SteeringBehaviorFollowPath.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorFollowPath.h"
#include "JLIFactoryTypes.h"
#include "SteeringBehaviorFollowPathBuilder.h"
#include "World.h"

#define TAG "SteeringBehaviorFollowPath.cpp"

#define FORMATSTRING "{\"njli::SteeringBehaviorFollowPath\":[{\"name\":\"%s\"}]}"
#include "JsonJLI.h"
#include "btPrint.h"

#include "SteeringBehaviorMachine.h"

namespace njli
{
  SteeringBehaviorFollowPath::SteeringBehaviorFollowPath() : SteeringBehavior(),m_CurrentForce(new btVector3(0,0,0)),m_Path(new Path()),m_waypointSeekDist(1.0)
  {
  }

  SteeringBehaviorFollowPath::SteeringBehaviorFollowPath(
      const AbstractBuilder &builder)
    : SteeringBehavior(builder), m_CurrentForce(new btVector3(0,0,0)),m_Path(new Path()),m_waypointSeekDist(1.0)
  {
  }

  SteeringBehaviorFollowPath::SteeringBehaviorFollowPath(
      const SteeringBehaviorFollowPath &copy)
      : SteeringBehavior(copy), m_CurrentForce(new btVector3(0,0,0)),m_Path(new Path(*copy.m_Path)),m_waypointSeekDist(copy.m_waypointSeekDist)
  {
  }

    SteeringBehaviorFollowPath::~SteeringBehaviorFollowPath() {delete m_CurrentForce;delete m_Path;}

  SteeringBehaviorFollowPath &SteeringBehaviorFollowPath::
  operator=(const SteeringBehaviorFollowPath &rhs)
  {
    if (this != &rhs)
      {
      }
    return *this;
  }

  s32 SteeringBehaviorFollowPath::calculateSerializeBufferSize() const
  {
    // TODO: calculateSerializeBufferSize
    return 0;
  }

  void SteeringBehaviorFollowPath::serialize(void *dataBuffer,
                                             btSerializer *serializer) const
  {
    // TODO: serialize
  }

  const char *SteeringBehaviorFollowPath::getClassName() const
  {
    return "SteeringBehaviorFollowPath";
  }

  s32 SteeringBehaviorFollowPath::getType() const
  {
    return SteeringBehaviorFollowPath::type();
  }

    SteeringBehaviorFollowPath::operator std::string() const
    {
        std::string temp(string_format(FORMATSTRING, getName()));
        return temp;
//        return njli::JsonJLI::parse(temp.c_str());
    }

  SteeringBehaviorFollowPath **
  SteeringBehaviorFollowPath::createArray(const u32 size)
  {
    return (SteeringBehaviorFollowPath **)World::getInstance()
        ->getWorldFactory()
        ->createArray(SteeringBehaviorFollowPath::type(), size);
  }

  void
  SteeringBehaviorFollowPath::destroyArray(SteeringBehaviorFollowPath **array,
                                           const u32 size)
  {
    World::getInstance()->getWorldFactory()->destroyArray(
        (AbstractFactoryObject **)array, size);
  }

  SteeringBehaviorFollowPath *SteeringBehaviorFollowPath::create()
  {
    return dynamic_cast<SteeringBehaviorFollowPath *>(
        World::getInstance()->getWorldFactory()->create(
            SteeringBehaviorFollowPath::type()));
  }

  SteeringBehaviorFollowPath *SteeringBehaviorFollowPath::create(
      const SteeringBehaviorFollowPathBuilder &builder)
  {
    AbstractBuilder *b = (AbstractBuilder *)&builder;

    return dynamic_cast<SteeringBehaviorFollowPath *>(
        World::getInstance()->getWorldFactory()->create(*b));
  }

  SteeringBehaviorFollowPath *
  SteeringBehaviorFollowPath::clone(const SteeringBehaviorFollowPath &object)
  {
    return dynamic_cast<SteeringBehaviorFollowPath *>(
        World::getInstance()->getWorldFactory()->clone(object, false));
  }

  SteeringBehaviorFollowPath *
  SteeringBehaviorFollowPath::copy(const SteeringBehaviorFollowPath &object)
  {
    return dynamic_cast<SteeringBehaviorFollowPath *>(
        World::getInstance()->getWorldFactory()->clone(object, true));
  }

  void SteeringBehaviorFollowPath::destroy(SteeringBehaviorFollowPath *object)
  {
    World::getInstance()->getWorldFactory()->destroy(object);
  }

  void SteeringBehaviorFollowPath::load(SteeringBehaviorFollowPath &object,
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
            SteeringBehaviorFollowPath::load(object, L, -2);
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

  u32 SteeringBehaviorFollowPath::type()
  {
    return JLI_OBJECT_TYPE_SteeringBehaviorFollowPath;
  }

  const btVector3 &SteeringBehaviorFollowPath::calculateForce()
  {
      if(m_TargetList.size() > 0)
      {
          SteeringBehaviorMachine *machine = getParent();
          assert(machine);
          
          const Node *vehicleNode = m_TargetList.at(0);
          
          *m_CurrentForce = SteeringBehaviorMachine::followPath(vehicleNode->getOrigin(), machine->getCurrentVelocity(), *m_Path, m_waypointSeekDist, machine->getMaxSpeed());
      }
      else
      {
          *m_CurrentForce = btVector3(0,0,0);
      }
      
    return *m_CurrentForce;
  }
    
    void SteeringBehaviorFollowPath::setPath(const Path &path)
    {
        *m_Path = path;
        
    }
    const Path &SteeringBehaviorFollowPath::getPath()const{return *m_Path;}
} // namespace njli
