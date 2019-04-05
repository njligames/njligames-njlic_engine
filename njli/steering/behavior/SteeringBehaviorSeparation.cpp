//
//  SteeringBehaviorSeparation.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorSeparation.h"
#include "JLIFactoryTypes.h"
#include "SteeringBehaviorSeparationBuilder.h"
#include "World.h"

#define TAG "SteeringBehaviorSeparation.cpp"

#define FORMATSTRING                                                           \
  "{\"njli::SteeringBehaviorSeparation\":[{\"name\":\"%s\"}]}"
#include "JsonJLI.h"
#include "btPrint.h"

#include "SteeringBehaviorMachine.h"

namespace njli
{
  SteeringBehaviorSeparation::SteeringBehaviorSeparation() : SteeringBehavior()
  {
  }

  SteeringBehaviorSeparation::SteeringBehaviorSeparation(
      const AbstractBuilder &builder)
      : SteeringBehavior(builder)
  {
  }

  SteeringBehaviorSeparation::SteeringBehaviorSeparation(
      const SteeringBehaviorSeparation &copy)
      : SteeringBehavior(copy)
  {
  }

  SteeringBehaviorSeparation::~SteeringBehaviorSeparation() {}

  SteeringBehaviorSeparation &SteeringBehaviorSeparation::
  operator=(const SteeringBehaviorSeparation &rhs)
  {
    if (this != &rhs)
      {
      }
    return *this;
  }

  s32 SteeringBehaviorSeparation::calculateSerializeBufferSize() const
  {
    // TODO: calculateSerializeBufferSize
    return 0;
  }

  void SteeringBehaviorSeparation::serialize(void *dataBuffer,
                                             btSerializer *serializer) const
  {
    // TODO: serialize
  }

  const char *SteeringBehaviorSeparation::getClassName() const
  {
    return "SteeringBehaviorSeparation";
  }

  s32 SteeringBehaviorSeparation::getType() const
  {
    return SteeringBehaviorSeparation::type();
  }

  SteeringBehaviorSeparation::operator std::string() const
  {
    std::string temp(string_format(FORMATSTRING, getName()));
    return temp;
  }

  SteeringBehaviorSeparation **
  SteeringBehaviorSeparation::createArray(const u32 size)
  {
    return (SteeringBehaviorSeparation **)World::getInstance()
        ->getWorldFactory()
        ->createArray(SteeringBehaviorSeparation::type(), size);
  }

  void
  SteeringBehaviorSeparation::destroyArray(SteeringBehaviorSeparation **array,
                                           const u32 size)
  {
    World::getInstance()->getWorldFactory()->destroyArray(
        (AbstractFactoryObject **)array, size);
  }

  SteeringBehaviorSeparation *SteeringBehaviorSeparation::create()
  {
    return dynamic_cast<SteeringBehaviorSeparation *>(
        World::getInstance()->getWorldFactory()->create(
            SteeringBehaviorSeparation::type()));
  }

  SteeringBehaviorSeparation *SteeringBehaviorSeparation::create(
      const SteeringBehaviorSeparationBuilder &builder)
  {
    AbstractBuilder *b = (AbstractBuilder *)&builder;

    return dynamic_cast<SteeringBehaviorSeparation *>(
        World::getInstance()->getWorldFactory()->create(*b));
  }

  SteeringBehaviorSeparation *
  SteeringBehaviorSeparation::clone(const SteeringBehaviorSeparation &object)
  {
    return dynamic_cast<SteeringBehaviorSeparation *>(
        World::getInstance()->getWorldFactory()->clone(object, false));
  }

  SteeringBehaviorSeparation *
  SteeringBehaviorSeparation::copy(const SteeringBehaviorSeparation &object)
  {
    return dynamic_cast<SteeringBehaviorSeparation *>(
        World::getInstance()->getWorldFactory()->clone(object, true));
  }

  void SteeringBehaviorSeparation::destroy(SteeringBehaviorSeparation *object)
  {
    World::getInstance()->getWorldFactory()->destroy(object);
  }

  void SteeringBehaviorSeparation::load(SteeringBehaviorSeparation &object,
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
            SteeringBehaviorSeparation::load(object, L, -2);
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

  u32 SteeringBehaviorSeparation::type()
  {
    return JLI_OBJECT_TYPE_SteeringBehaviorSeparation;
  }

  //    s32 SteeringBehaviorSeparation::addNeighbor(Node *Neighbor)
  //    {
  //        SDL_assert(NULL != Neighbor);
  //
  //        if(Neighbor != getParent()->getParent())
  //        {
  //            std::vector<Node *>::const_iterator iter =
  //            std::find(m_NeighborList.begin(), m_NeighborList.end(),
  //            Neighbor);
  //
  //            if (iter == m_NeighborList.end())
  //            {
  //                m_NeighborList.push_back(Neighbor);
  //
  //                addChild(Neighbor);
  //            }
  //        }
  //        return getNeighborIndex(Neighbor);
  //    }
  //
  //    bool SteeringBehaviorSeparation::removeNeighbor(Node *Neighbor)
  //    {
  //        SDL_assert(NULL != Neighbor);
  //
  //        std::vector<Node *>::iterator iter =
  //        std::find(m_NeighborList.begin(), m_NeighborList.end(), Neighbor);
  //
  //        if (iter != m_NeighborList.end())
  //        {
  //            removeChild(*iter);
  //            m_NeighborList.erase(iter);
  //            return true;
  //        }
  //        return false;
  //    }
  //
  //    void SteeringBehaviorSeparation::removeAllNeighbors()
  //    {
  //        for (std::vector<Node *>::iterator iter = m_NeighborList.begin();
  //             iter != m_NeighborList.end(); ++iter)
  //        {
  //            removeChild(*iter);
  //        }
  //        m_NeighborList.clear();
  //    }
  //
  //    s32 SteeringBehaviorSeparation::numberOfNeighbors() const { return
  //    m_NeighborList.size(); }
  //
  //    void SteeringBehaviorSeparation::getNeighbors(std::vector<Node *>
  //    &Neighbors) const
  //    {
  //        for (std::vector<Node *>::const_iterator iter =
  //        m_NeighborList.begin();
  //             iter != m_NeighborList.end(); ++iter)
  //        {
  //            if (getChildIndex(*iter) != -1)
  //                Neighbors.push_back(*iter);
  //        }
  //    }
  //
  //    s32 SteeringBehaviorSeparation::getNeighborIndex(Node *Neighbor) const
  //    {
  //        std::vector<Node *>::const_iterator iter =
  //        std::find(m_NeighborList.begin(), m_NeighborList.end(), Neighbor);
  //
  //        if (iter != m_NeighborList.end())
  //        {
  //            return std::distance(m_NeighborList.begin(), iter);
  //        }
  //        return -1;
  //    }
  //
  //    Node *SteeringBehaviorSeparation::getNeighbor(const u32 index)
  //    {
  //        if (index < m_NeighborList.size())
  //        {
  //            s32 idx = getChildIndex(m_NeighborList.at(index));
  //            if (idx != -1)
  //                return dynamic_cast<Node *>(getChild(idx));
  //        }
  //        return NULL;
  //    }
  //
  //    const Node *SteeringBehaviorSeparation::getNeighbor(const u32 index)
  //    const
  //    {
  //        if (index < m_NeighborList.size())
  //        {
  //            s32 idx = getChildIndex(m_NeighborList.at(index));
  //            if (idx != -1)
  //                return dynamic_cast<const Node *>(getChild(idx));
  //        }
  //        return NULL;
  //    }

  const btVector3 &SteeringBehaviorSeparation::calculateForce()
  {
    SteeringBehaviorMachine *machine = getParent();
    Node *vehicleNode = machine->getParent();

    //      *m_CurrentForce = btVector3(0,0,0);
    //      for (std::vector<Node *>::const_iterator i = m_NeighborList.begin();
    //      i != m_NeighborList.end(); i++)
    //      {
    //          Node *leader = *i;
    *m_CurrentForce =
        SteeringBehaviorMachine::separation(vehicleNode, m_TargetList);
    //      }

    return *m_CurrentForce;
  }
} // namespace njli
