//
//  SteeringBehaviorMachine.cpp
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#pragma mark Implementation

#include "SteeringBehaviorMachine.h"
#include "JLIFactoryTypes.h"
#include "SteeringBehaviorMachineBuilder.h"
#include "World.h"
#define TAG "SteeringBehaviorMachine.cpp"

#define FORMATSTRING "{\"njli::SteeringBehaviorMachine\":[{\"name\":\"%s\"}]}"
#include "JsonJLI.h"
#include "btPrint.h"

#include "SteeringBehavior.h"
#include "btVector3.h"

namespace njli
{

    SteeringBehaviorMachine::SteeringBehaviorMachine()
        : AbstractFactoryObject(this), m_CurrentForce(new btVector3(0, 0, 0)),
          m_CurrentVelocity(new btVector3(0, 0, 0)),
          m_HeadingVector(new btVector3(0, 0, 1)),
          m_UpVector(new btVector3(0, 1, 0)),
          m_MaxSpeed(std::numeric_limits<f32>::max()),
          m_MaxForce(sqrt(std::numeric_limits<f32>::max())),
          m_MaxForce2(std::numeric_limits<f32>::max()), m_Enable(false)
    {
    }

    SteeringBehaviorMachine::SteeringBehaviorMachine(
        const AbstractBuilder &builder)
        : AbstractFactoryObject(this), m_CurrentForce(new btVector3(0, 0, 0)),
          m_CurrentVelocity(new btVector3(0, 0, 0)),
          m_HeadingVector(new btVector3(0, 0, 1)),
          m_UpVector(new btVector3(0, 1, 0)),
          m_MaxSpeed(std::numeric_limits<f32>::max()),
          m_MaxForce(sqrt(std::numeric_limits<f32>::max())),
          m_MaxForce2(std::numeric_limits<f32>::max()), m_Enable(false)
    {
    }

    SteeringBehaviorMachine::SteeringBehaviorMachine(
        const SteeringBehaviorMachine &copy)
        : AbstractFactoryObject(this),
          m_CurrentForce(new btVector3(*(copy.m_CurrentForce))),
          m_CurrentVelocity(new btVector3(*(copy.m_CurrentVelocity))),
          m_HeadingVector(new btVector3(*(copy.m_HeadingVector))),
          m_UpVector(new btVector3(0, 1, 0)), m_MaxSpeed(copy.m_MaxSpeed),
          m_MaxForce(copy.m_MaxForce), m_MaxForce2(copy.m_MaxForce2),
          m_Enable(false)
    {
    }

    SteeringBehaviorMachine::~SteeringBehaviorMachine()
    {
        delete m_UpVector;
        m_UpVector = NULL;

        delete m_HeadingVector;
        m_HeadingVector = NULL;

        delete m_CurrentVelocity;
        m_CurrentVelocity = NULL;

        delete m_CurrentForce;
        m_CurrentForce = NULL;
    }

    SteeringBehaviorMachine &SteeringBehaviorMachine::
    operator=(const SteeringBehaviorMachine &rhs)
    {
        if (this != &rhs)
            {
                *m_UpVector = *rhs.m_UpVector;
                m_MaxSpeed = rhs.m_MaxSpeed;
                m_MaxForce = rhs.m_MaxForce;
                m_MaxForce2 = rhs.m_MaxForce2;
                *m_HeadingVector = *(rhs.m_HeadingVector);
                *m_CurrentVelocity = *(rhs.m_CurrentVelocity);
                *m_CurrentForce = *(rhs.m_CurrentForce);
            }

        return *this;
    }

    s32 SteeringBehaviorMachine::calculateSerializeBufferSize() const
    {
        // TODO: calculateSerializeBufferSize
        return 0;
    }

    void SteeringBehaviorMachine::serialize(void *dataBuffer,
                                            btSerializer *serializer) const
    {
        // TODO: serialize
    }

    const char *SteeringBehaviorMachine::getClassName() const
    {
        return "SteeringBehaviorMachine";
    }

    s32 SteeringBehaviorMachine::getType() const
    {
        return SteeringBehaviorMachine::type();
    }

    SteeringBehaviorMachine::operator std::string() const
    {
        std::string temp(string_format(FORMATSTRING, getName()));
        return temp;
    }

    SteeringBehaviorMachine **
    SteeringBehaviorMachine::createArray(const u32 size)
    {
        return (SteeringBehaviorMachine **)World::getInstance()
            ->getWorldFactory()
            ->createArray(SteeringBehaviorMachine::type(), size);
    }

    void SteeringBehaviorMachine::destroyArray(SteeringBehaviorMachine **array,
                                               const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray(
            (AbstractFactoryObject **)array, size);
    }

    SteeringBehaviorMachine *SteeringBehaviorMachine::create()
    {
        return dynamic_cast<SteeringBehaviorMachine *>(
            World::getInstance()->getWorldFactory()->create(
                SteeringBehaviorMachine::type()));
    }

    SteeringBehaviorMachine *SteeringBehaviorMachine::create(
        const SteeringBehaviorMachineBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;

        return dynamic_cast<SteeringBehaviorMachine *>(
            World::getInstance()->getWorldFactory()->create(*b));
    }

    SteeringBehaviorMachine *
    SteeringBehaviorMachine::clone(const SteeringBehaviorMachine &object)
    {
        return dynamic_cast<SteeringBehaviorMachine *>(
            World::getInstance()->getWorldFactory()->clone(object, false));
    }

    SteeringBehaviorMachine *
    SteeringBehaviorMachine::copy(const SteeringBehaviorMachine &object)
    {
        return dynamic_cast<SteeringBehaviorMachine *>(
            World::getInstance()->getWorldFactory()->clone(object, true));
    }

    void SteeringBehaviorMachine::destroy(SteeringBehaviorMachine *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }

    void SteeringBehaviorMachine::load(SteeringBehaviorMachine &object,
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
                        SteeringBehaviorMachine::load(object, L, -2);
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

    u32 SteeringBehaviorMachine::type()
    {
        return JLI_OBJECT_TYPE_SteeringBehaviorMachine;
    }

    Node *SteeringBehaviorMachine::getParent()
    {
        return dynamic_cast<Node *>(AbstractDecorator::getParent());
    }
    const Node *SteeringBehaviorMachine::getParent() const
    {
        return dynamic_cast<const Node *>(AbstractDecorator::getParent());
    }

    const btVector3 &SteeringBehaviorMachine::getCalculatedForce() const
    {
        return *m_CurrentForce;
    }

    bool SteeringBehaviorMachine::addSteeringBehavior(
        SteeringBehavior *steeringBehavior)
    {
        SDL_assert(NULL != steeringBehavior);

        std::vector<SteeringBehavior *>::const_iterator iter =
            std::find(m_SteeringBehaviorVector.begin(),
                      m_SteeringBehaviorVector.end(), steeringBehavior);

        if (iter == m_SteeringBehaviorVector.end())
            {
                m_SteeringBehaviorVector.push_back(steeringBehavior);

                addChild(steeringBehavior);
                return true;
            }
        return false;

        //    SteeringMap::const_iterator iter =
        //        m_SteeringBehaviorMap.find(steeringBehavior);
        //
        //    if (iter == m_SteeringBehaviorMap.end())
        //      {
        //        m_SteeringBehaviorMap.insert(SteeringPair(steeringBehavior,
        //        heuristic)); addChild(steeringBehavior); return true;
        //      }
        //
        //    return false;
    }

    bool SteeringBehaviorMachine::removeSteeringBehavior(
        SteeringBehavior *steeringBehavior)
    {
        SDL_assert(NULL != steeringBehavior);

        std::vector<SteeringBehavior *>::const_iterator iter =
            std::find(m_SteeringBehaviorVector.begin(),
                      m_SteeringBehaviorVector.end(), steeringBehavior);

        if (iter != m_SteeringBehaviorVector.end())
            {
                m_SteeringBehaviorVector.erase(iter);

                removeChild(*iter);

                return true;
            }
        return false;
    }

    void SteeringBehaviorMachine::removeAllSteeringBehaviors()
    {
        for (std::vector<SteeringBehavior *>::iterator iter =
                 m_SteeringBehaviorVector.begin();
             iter != m_SteeringBehaviorVector.end(); ++iter)
            {
                removeChild(*iter);
            }
        m_SteeringBehaviorVector.clear();
    }

    u64 SteeringBehaviorMachine::numberOfSteeringBehaviors() const
    {
        return m_SteeringBehaviorVector.size();
    }

    void SteeringBehaviorMachine::getSteeringBehaviors(
        std::vector<SteeringBehavior *> &steeringBehaviors) const
    {
        //    for (SteeringMap::const_iterator iter =
        //    m_SteeringBehaviorMap.begin();
        //         iter != m_SteeringBehaviorMap.end(); ++iter)
        //      {
        //        steeringBehaviors.push_back(iter->first);
        //      }
        steeringBehaviors.reserve(m_SteeringBehaviorVector.size());
        std::copy(m_SteeringBehaviorVector.begin(),
                  m_SteeringBehaviorVector.end(), steeringBehaviors.begin());
    }

    void SteeringBehaviorMachine::setMaxSpeed(const f32 speed)
    {
        SDL_assertCheck(speed > 0, "Speed must be greater than 0");

        m_MaxSpeed = speed;
    }

    f32 SteeringBehaviorMachine::getMaxSpeed() const { return m_MaxSpeed; }

    void SteeringBehaviorMachine::setMaxForce(const f32 speed)
    {
        SDL_assertCheck(speed > 0, "Speed must be greater than 0");

        m_MaxForce = speed;
        m_MaxForce2 = m_MaxForce * m_MaxForce;
    }

    f32 SteeringBehaviorMachine::getMaxForce() const { return m_MaxForce; }

    const btVector3 &SteeringBehaviorMachine::getHeadingVector() const
    {
        return *m_HeadingVector;
    }
    void SteeringBehaviorMachine::setUpVector(const btVector3 &vec)
    {
        *m_UpVector = vec;
    }

    const btVector3 &SteeringBehaviorMachine::getUpVector() const
    {
        return *m_UpVector;
    }

    btVector3 SteeringBehaviorMachine::getSideVector() const
    {
        return getHeadingVector().cross(*m_UpVector);
    }

    const btVector3 &SteeringBehaviorMachine::getCurrentVelocity() const
    {
        return *m_CurrentVelocity;
    }

    const btVector3 &SteeringBehaviorMachine::getCurrentForce() const
    {
        return *m_CurrentForce;
    }

    void SteeringBehaviorMachine::clearSteering()
    {
        *m_CurrentForce = btVector3Zero;
        *m_CurrentVelocity = btVector3Zero;
    }

    //    inline void Vec3DRotateAroundOrigin(btVector3 &v, double ang)
    //    {
    //        //    //create a transformation matrix
    //        //    C2DMatrix mat;
    //        //
    //        //    //rotate
    //        //    mat.Rotate(ang);
    //        //
    //        //    //now transform the object's vertices
    //        //    mat.TransformVector2Ds(v);
    //
    //        btQuaternion rotation(btVector3(1.0, 1.0, 1.0).normalized(), ang);
    //        v = quatRotate(rotation, v);
    //    }
    //
    //
    //    void SteeringBehavior::CreateFeelers()
    //    {
    //        //feeler pointing straight in front
    //        m_Feelers[0] = m_pVehicle->Pos() + m_dWallDetectionFeelerLength *
    //        m_pVehicle->Heading();
    //
    //        //feeler to left
    //        Vector2D temp = m_pVehicle->Heading();
    //        Vec2DRotateAroundOrigin(temp, HalfPi * 3.5f);
    //        m_Feelers[1] = m_pVehicle->Pos() +
    //        m_dWallDetectionFeelerLength/2.0f
    //        * temp;
    //
    //        //feeler to right
    //        temp = m_pVehicle->Heading();
    //        Vec2DRotateAroundOrigin(temp, HalfPi * 0.5f);
    //        m_Feelers[2] = m_pVehicle->Pos() +
    //        m_dWallDetectionFeelerLength/2.0f
    //        * temp;
    //    }

    void SteeringBehaviorMachine::createFeelers(const btVector3 &origin,
                                                const float feelerLength,
                                                std::vector<btVector3> &feelers)
    {
        const float angle(btRadians(45.0));

        feelers.clear();

        const btVector3 heading(getHeadingVector());
        const btVector3 up(getUpVector());
        const btVector3 side(getSideVector());

        const btQuaternion rotateLeft(up, angle);
        const btQuaternion rotateRight(up, -angle);
        const btQuaternion rotateUp(side, angle);
        const btQuaternion rotateDown(side, -angle);

        btVector3 feeler_forward(feelerLength * heading);

        // front
        feelers.push_back(feeler_forward);

        // up-left
        feelers.push_back(quatRotate(rotateUp * rotateLeft, feeler_forward));

        // up
        feelers.push_back(quatRotate(rotateUp, feeler_forward));

        // up-right
        feelers.push_back(quatRotate(rotateUp * rotateRight, feeler_forward));

        // right
        feelers.push_back(quatRotate(rotateRight, feeler_forward));

        // down-right
        feelers.push_back(quatRotate(rotateDown * rotateRight, feeler_forward));

        // down
        feelers.push_back(quatRotate(rotateDown, feeler_forward));

        // down-left
        feelers.push_back(quatRotate(rotateDown * rotateLeft, feeler_forward));

        // left
        feelers.push_back(quatRotate(rotateLeft, feeler_forward));
    }

    f32 SteeringBehaviorMachine::getMaxForce2() const { return m_MaxForce2; }

    void SteeringBehaviorMachine::setCalculatedForce(const btVector3 &force)
    {
        *m_CurrentForce = force;
    }

    const btVector3 &SteeringBehaviorMachine::calculate(f32 timestep)
    {
        *m_CurrentForce = calculateSteeringForce();

        Node *node = getParent();

        if (node)
            {
                f32 mass = 1.0f;
                if (node->getPhysicsBody() &&
                    node->getPhysicsBody()->isKinematicPhysics())
                    {
                        mass = node->getPhysicsBody()->getMass();
                    }
                else
                    {
#if !(defined(NDEBUG))
                        if (node->getPhysicsBody() &&
                            !node->getPhysicsBody()->isKinematicPhysics())
                            SDL_LogWarn(SDL_LOG_CATEGORY_TEST,
                                        "The PhysicsBody (%s) needs to be "
                                        "Kinematic for steering.",
                                        node->getPhysicsBody()->getName());
#endif
                    }

                btVector3 acceleration((*m_CurrentForce) / mass);

                *m_CurrentVelocity =
                    (*m_CurrentVelocity) + acceleration * timestep;

                if (m_CurrentVelocity->length() > getMaxSpeed())
                    *m_CurrentVelocity =
                        m_CurrentVelocity->normalized() * getMaxSpeed();

                node->setOrigin(node->getOrigin() +
                                (*m_CurrentVelocity) * timestep);

                if (m_CurrentVelocity->length() > 0.00000001)
                    {
                        const btVector3 newHeading(
                            m_CurrentVelocity->normalized());
                        const float angle(
                            btAngle(newHeading, *m_HeadingVector));
                        const btVector3 axis(
                            btCross(newHeading, *m_HeadingVector));
                        //              *m_UpVector =
                        //              quatRotate(btQuaternion(axis, angle),
                        //              getUpVector()).normalize();

                        *m_HeadingVector = newHeading;
                    }
            }

        return *m_CurrentForce;
    }
} // namespace njli
