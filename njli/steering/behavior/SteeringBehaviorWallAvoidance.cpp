//
//  SteeringBehaviorWallAvoidance.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/5/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorWallAvoidance.h"
#include "JLIFactoryTypes.h"
#include "SteeringBehaviorWallAvoidanceBuilder.h"
#include "World.h"

#define TAG "SteeringBehaviorWallAvoidance.cpp"

#define FORMATSTRING                                                           \
    "{\"njli::SteeringBehaviorWallAvoidance\":[{\"name\":\"%s\"}]}"
#include "JsonJLI.h"
#include "btPrint.h"

#include "SteeringBehaviorMachine.h"

#include <limits>

namespace njli
{
    SteeringBehaviorWallAvoidance::SteeringBehaviorWallAvoidance()
        : SteeringBehavior(), m_FeelerLength(1.0f)
    {
    }

    SteeringBehaviorWallAvoidance::SteeringBehaviorWallAvoidance(
        const AbstractBuilder &builder)
        : SteeringBehavior(builder), m_FeelerLength(1.0f)
    {
    }

    SteeringBehaviorWallAvoidance::SteeringBehaviorWallAvoidance(
        const SteeringBehaviorWallAvoidance &copy)
        : SteeringBehavior(copy), m_FeelerLength(copy.m_FeelerLength)
    {
    }

    SteeringBehaviorWallAvoidance::~SteeringBehaviorWallAvoidance() {}

    SteeringBehaviorWallAvoidance &SteeringBehaviorWallAvoidance::operator=(
        const SteeringBehaviorWallAvoidance &rhs)
    {
        if (this != &rhs)
        {
            m_FeelerLength = rhs.m_FeelerLength;
        }
        return *this;
    }

    s32 SteeringBehaviorWallAvoidance::calculateSerializeBufferSize() const
    {
        // TODO: calculateSerializeBufferSize
        return 0;
    }

    void
    SteeringBehaviorWallAvoidance::serialize(void *dataBuffer,
                                             btSerializer *serializer) const
    {
        // TODO: serialize
    }

    const char *SteeringBehaviorWallAvoidance::getClassName() const
    {
        return "SteeringBehaviorWallAvoidance";
    }

    s32 SteeringBehaviorWallAvoidance::getType() const
    {
        return SteeringBehaviorWallAvoidance::type();
    }

    SteeringBehaviorWallAvoidance::operator std::string() const
    {
        std::string temp(string_format(FORMATSTRING, getName()));
        return temp;
    }

    SteeringBehaviorWallAvoidance **
    SteeringBehaviorWallAvoidance::createArray(const u32 size)
    {
        return (SteeringBehaviorWallAvoidance **)World::getInstance()
            ->getWorldFactory()
            ->createArray(SteeringBehaviorWallAvoidance::type(), size);
    }

    void SteeringBehaviorWallAvoidance::destroyArray(
        SteeringBehaviorWallAvoidance **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray(
            (AbstractFactoryObject **)array, size);
    }

    SteeringBehaviorWallAvoidance *SteeringBehaviorWallAvoidance::create()
    {
        return dynamic_cast<SteeringBehaviorWallAvoidance *>(
            World::getInstance()->getWorldFactory()->create(
                SteeringBehaviorWallAvoidance::type()));
    }

    SteeringBehaviorWallAvoidance *SteeringBehaviorWallAvoidance::create(
        const SteeringBehaviorWallAvoidanceBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;

        return dynamic_cast<SteeringBehaviorWallAvoidance *>(
            World::getInstance()->getWorldFactory()->create(*b));
    }

    SteeringBehaviorWallAvoidance *SteeringBehaviorWallAvoidance::clone(
        const SteeringBehaviorWallAvoidance &object)
    {
        return dynamic_cast<SteeringBehaviorWallAvoidance *>(
            World::getInstance()->getWorldFactory()->clone(object, false));
    }

    SteeringBehaviorWallAvoidance *SteeringBehaviorWallAvoidance::copy(
        const SteeringBehaviorWallAvoidance &object)
    {
        return dynamic_cast<SteeringBehaviorWallAvoidance *>(
            World::getInstance()->getWorldFactory()->clone(object, true));
    }

    void SteeringBehaviorWallAvoidance::destroy(
        SteeringBehaviorWallAvoidance *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }

    void
    SteeringBehaviorWallAvoidance::load(SteeringBehaviorWallAvoidance &object,
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
            // copy the key so that lua_tostring does not modify the
            // original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 =>
            // table
            const char *key = lua_tostring(L, -1);
            //            const char *value = lua_tostring(L, -2);
            if (lua_istable(L, -2))
            {
                SteeringBehaviorWallAvoidance::load(object, L, -2);
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
                    //                    jli::AbstractFactoryObject
                    //                    *object =
                    //                    static_cast<jli::AbstractFactoryObject*>(usr->ptr);
                    //                    printf("%s => %d:%s\n",
                    //                    key, object->getType(),
                    //                    object->getClassName());
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the
        // key but does not push anything.) Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }

    u32 SteeringBehaviorWallAvoidance::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidance;
    }

    void SteeringBehaviorWallAvoidance::addWall(const Wall &wall)
    {

        m_Walls.push_back(wall);
    }

    void
    SteeringBehaviorWallAvoidance::setFeelerLength(const float feelerLength)
    {
        m_FeelerLength = feelerLength;
    }
    float SteeringBehaviorWallAvoidance::getFeelerLength() const
    {
        return m_FeelerLength;
    }

    const btVector3 &SteeringBehaviorWallAvoidance::calculateForce()
    {
        SteeringBehaviorMachine *machine = getParent();
        const Node *vehicleNode = machine->getParent();

        int ClosestWall = -1;
        btVector3 ClosestPoint;
        float DistToThisIP(0.0);
        float DistToClosestIP(std::numeric_limits<float>::max());

        *m_CurrentForce = btVector3(0, 0, 0);

        machine->createFeelers(vehicleNode->getOrigin(), m_FeelerLength,
                               m_Feelers);

        for (auto f = 0; f < m_Feelers.size(); ++f)
        {
            for (auto w = 0; w < m_Walls.size(); ++w)
            {
                btVector3 point;
                if (m_Walls[w].segmentIntersection(
                        vehicleNode->getOrigin(),
                        vehicleNode->getOrigin() + m_Feelers[f], point) > 0)
                {
                    DistToThisIP = point.distance(vehicleNode->getOrigin());

                    if (DistToThisIP < DistToClosestIP)
                    {
                        DistToClosestIP = DistToThisIP;

                        ClosestWall = w;

                        ClosestPoint = point;
                    }
                }
            }

            // if an intersection point has been detected, calculate a force
            // that will direct the agent away
            if (ClosestWall >= 0)
            {
                // calculate by what distance the projected position of
                // the agent will overshoot the wall
                btVector3 OverShoot(m_Feelers[f] - ClosestPoint);

                // create a force in the direction of the wall normal,
                // with a magnitude of the overshoot
                *m_CurrentForce =
                    m_Walls[ClosestWall].normal() * OverShoot.length();
            }
        }

        return *m_CurrentForce;
    }
} // namespace njli
