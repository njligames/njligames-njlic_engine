//
//  SteeringBehaviorMachine.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehaviorMachine_hpp
#define SteeringBehaviorMachine_hpp

#pragma mark Header

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "Log.h"
#include "btVector3.h"
#include "lua.hpp"

#include <map>
#include "Path.h"
#include "btMatrix3x3.h"
#include "btTransform.h"

namespace njli
{
  class SteeringBehaviorMachineBuilder;
  class Node;
  class SteeringBehavior;

  /**
   *  <#Description#>
   */
  ATTRIBUTE_ALIGNED16(class)
  SteeringBehaviorMachine : public AbstractFactoryObject
  {
    friend class WorldFactory;
    friend class Node;

  protected:
    SteeringBehaviorMachine();
    SteeringBehaviorMachine(const AbstractBuilder &);
    SteeringBehaviorMachine(const SteeringBehaviorMachine &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SteeringBehaviorMachine();
    SteeringBehaviorMachine &operator=(const SteeringBehaviorMachine &);

  public:
    /**
     *  Calculate the buffer size of this object.
     *
     *  @return The buffer size.
     */
    virtual s32 calculateSerializeBufferSize() const;
    /**
     *  Serialize this object.
     *
     *  @param btSerializer the serializer which does the serialize.
     */
    virtual void serialize(void *, btSerializer *) const;

    /**
     *  The name of this class.
     *
     *  @return The name of this class.
     */
    virtual const char *getClassName() const;
    /**
     *  Get the type of ::jliObjectEnumType enum value.
     *
     *  @return The ::jliObjectEnumType enum value.
     */
    virtual s32 getType() const;
    /**
     *  The string value for this object, which can be used for debugging.
     *
     *  @return "The string value for this object.
     */
    operator std::string() const;

    /**
     *  Create an Array of instances of this class.
     *
     *  @param size The amount of elements in the array.
     *
     *  @return Pointer to the newly created array.
     */
    static SteeringBehaviorMachine **createArray(const u32 size);
    /**
     *  Destroy an Array of this class type.
     *
     *  @param array The Pointer to the array to delete.
     */
    static void destroyArray(SteeringBehaviorMachine * *array,
                             const u32 size = 0);
    /**
     *  Create an instance of this class.
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachine *create();
    /**
     *  Create an instance of this class using a builder.
     *
     *  @param builder The builder to use for construction
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachine *create(
        const SteeringBehaviorMachineBuilder &builder);
    /**
     *  Create a shallow copy of an instance of this class (sharing pointers).
     *
     *  @param object The object to clone.
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachine *clone(
        const SteeringBehaviorMachine &object);
    /**
     *  Create a deep copy of an instance of this class (NOT sharing pointers).
     *
     *  @param object The object to clone.
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachine *copy(const SteeringBehaviorMachine &object);
    /**
     *  Destroy an instance of this class.
     *
     *  @param object The object to destroy.
     */
    static void destroy(SteeringBehaviorMachine * object);
    /**
     *  Load a lua table representation of this class. This is used for
     * JLIM.create(object).
     *
     *  @param object      The object to load.
     *  @param L           The current lua state.
     *  @param stack_index The stack index of the lua stack.
     */
    static void load(SteeringBehaviorMachine & object, lua_State * L,
                     int stack_index);
    /**
     *  Get the type of ::jliObjectEnumType enum value.
     *
     *  @return The ::jliObjectEnumType enum value.
     */
    static u32 type();

  public:
    // TODO: fill in specific methods for SteeringBehaviorMachine
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    Node *getParent();
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    const Node *getParent() const;

    virtual const btVector3 &calculateSteeringForce() = 0;

    const btVector3 &getCalculatedForce() const;

    bool setHeuristic(SteeringBehavior * steeringBehavior, f32 heuristic);
    f32 getHeuristic(SteeringBehavior * steeringBehavior) const;

    /**
     *  @author James Folk, 16-02-10 21:02:01
     *
     *  @brief <#Description#>
     *
     *  @param steeringBehavior <#emitter description#>
     *
     *  @return <#return value description#>
     *
     *  @section ex1 Lua example
     *  @snippet SteeringBehaviorMachine.lua
     * SteeringBehaviorMachine_addSteeringBehavior_
     */
    bool addSteeringBehavior(SteeringBehavior * steeringBehavior,
                             f32 heuristic);

    /**
     *  @author James Folk, 16-02-10 21:02:05
     *
     *  @brief <#Description#>
     *
     *  @param steeringBehavior <#emitter description#>
     *
     *  @return <#return value description#>
     *
     *  @section ex1 Lua example
     *  @snippet SteeringBehaviorMachine.lua
     * SteeringBehaviorMachine_removeSteeringBehavior_
     */
    bool removeSteeringBehavior(SteeringBehavior * steeringBehavior);

    /**
     *  @author James Folk, 16-02-10 21:02:09
     *
     *  @brief <#Description#>
     *
     *  @section ex1 Lua example
     *  @snippet SteeringBehaviorMachine.lua
     * SteeringBehaviorMachine_removeAllSteeringBehaviors_
     */
    void removeAllSteeringBehaviors();

    /**
     *  @author James Folk, 16-02-10 21:02:14
     *
     *  @brief <#Description#>
     *
     *  @return <#return value description#>
     *
     *  @section ex1 Lua example
     *  @snippet SteeringBehaviorMachine.lua
     * SteeringBehaviorMachine_numberOfSteeringBehaviors_
     */
    u64 numberOfSteeringBehaviors() const;

    /**
     *  @author James Folk, 16-02-10 21:02:19
     *
     *  @brief <#Description#>
     *
     *  @param particleEmitters <#particleEmitters description#>
     *
     *  @section ex1 Lua example
     *  @snippet SteeringBehaviorMachine.lua
     * SteeringBehaviorMachine_getSteeringBehaviors
     */
    virtual void getSteeringBehaviors(std::vector<SteeringBehavior *> &
                                      steeringBehaviors) const;

    void setMaxSpeed(const f32 speed);
    f32 getMaxSpeed() const;

    void setMaxForce(const f32 speed);
    f32 getMaxForce() const;

    const btVector3 &getHeadingVector() const;
      void setUpVector(const btVector3 &vec);
      const btVector3 &getUpVector() const;
    btVector3 getSideVector() const;
      
      const btVector3 &getCurrentVelocity() const;
      const btVector3 &getCurrentForce() const;
   
      void enable(bool enable=true){m_Enable=enable;}
      bool isEnabled()const{return m_Enable;}
      
  public:
      static inline btVector3 seek(const btVector3 &targetPos,
                                   const btVector3 &vehiclePos,
                                   const btVector3 &vehicleVelocity,
                                   const float vehicleMaxSpeed = 1.0)
      {
          const btVector3 diffPosition(targetPos - vehiclePos);
          const btVector3 desiredVelocity(diffPosition.normalized() * vehicleMaxSpeed);
          const btVector3 seek(desiredVelocity - vehicleVelocity);
          return seek;
      }
      
      static inline btVector3 flee(const btVector3 &targetPos,
                                       const btVector3 &vehiclePos,
                                       const btVector3 &vehicleVelocity,
                                       const float vehicleMaxSpeed = 1.0)
      {
          const btVector3 diffPosition(vehiclePos - targetPos);
          const btVector3 desiredVelocity(diffPosition.normalized() * vehicleMaxSpeed);
          const btVector3 flee(desiredVelocity - vehicleVelocity);
          return flee;
      }
      
      
      
      
      
      static inline btVector3 arrive(const btVector3 &targetPos,
                                     const btVector3 &vehiclePos,
                                     const btVector3 &vehicleVelocity,
                                     const float vehicleMaxSpeed,
                                     float deceleration)
      {
          if(deceleration > 0)
          {
              btVector3 toTarget(targetPos - vehiclePos);
              btScalar dist(toTarget.length());
              
              if(dist > 0)
              {
                  const btScalar decelerationDenominator(deceleration);
                  assert(decelerationDenominator != 0);
                  
                  btScalar speed(dist / decelerationDenominator);
                  speed = fmin(speed, vehicleMaxSpeed);
                  
                  const btVector3 desiredVelocity(toTarget * speed / dist);
                  
                  return (desiredVelocity - vehicleVelocity);
              }
          }
          return btVector3(0.0, 0.0, 0.0);
      }
      
      static inline btVector3 pursuit(const btVector3 &evaderPos,
                                      const btVector3 &evaderHeading,
                                      const btVector3 &evaderVelocity,
                                      const float evaderSpeed,
                                      
                                      const btVector3 &vehiclePos,
                                      const btVector3 &vehicleHeading,
                                      const btVector3 &vehicleVelocity,
                                      const float vehicleMaxSpeed = 1.0)
      {
          //if the evader is ahead and facing the agent then we can just seek
          //for the evader's current position.
          const btVector3 toEvader(evaderPos - vehiclePos);
          const btScalar relativeHeading(vehicleHeading.dot(evaderHeading));
          
          if( (toEvader.dot(vehicleHeading) > 0 ) &&
             (relativeHeading < -0.95)) //acos(0.95)=18 degs
          {
              return seek(evaderPos, vehiclePos, vehicleVelocity, vehicleMaxSpeed);
          }
          
          //Not considered ahead so we predict where the evader will be.
          
          //the lookahead time is propotional to the distance between the evader
          //and the pursuer; and is inversely proportional to the sum of the
          //agent's velocities
          btScalar lookAheadTime(toEvader.length() / (vehicleMaxSpeed + evaderSpeed));
          return seek(evaderPos + evaderVelocity * lookAheadTime, vehiclePos, vehicleVelocity, vehicleMaxSpeed);
      }
      
      static inline btVector3 evade(const btVector3 &pursuerPos,
                                    const btVector3 &pursuerVelocity,
                                    const float pursuerSpeed,
                                    
                                    const btVector3 &vehiclePos,
                                    const btVector3 &vehicleVelocity,
                                    const float vehicleMaxSpeed = 1.0)
      {
          const btVector3 toPursuer(pursuerPos - vehiclePos);
          const btScalar lookAheadTime(toPursuer.length() / (vehicleMaxSpeed + pursuerSpeed));
          
          return flee(pursuerPos + pursuerVelocity * lookAheadTime, vehiclePos, vehicleVelocity, vehicleMaxSpeed);
      }
      
      static inline btVector3 followPath(const btVector3 &vehiclePos,
                                         const btVector3 &vehicleVelocity,
                                         Path &path,
                                         const btScalar waypointSeekDist,
                                         const float vehicleMaxSpeed,
                                         float deceleration)
      {
          assert(waypointSeekDist >= 0);
          
          if(path.size() > 0)
          {
              const btScalar waypointSeekDistSq(waypointSeekDist*waypointSeekDist);
              
              if(path.currentWaypoint().distance(vehiclePos) < waypointSeekDistSq)
              {
                  path.setNextWaypoint();
              }
              
              if(!path.finished())
              {
                  seek(path.currentWaypoint(), vehiclePos, vehicleVelocity, vehicleMaxSpeed);
              }
              return arrive(path.currentWaypoint(), vehiclePos, vehicleVelocity, vehicleMaxSpeed, deceleration);
          }
          
          return btVector3(0,0,0);
      }
      
      static inline btVector3 offsetPursuit(const btVector3 &offsetTargetPos,
                                            const btVector3 &leaderPos,
                                            const btVector3 &leaderVelocity,
                                            const btVector3 &leaderSide,
                                            const float leaderSpeed,
                                            const btVector3 &vehiclePos,
                                            const btVector3 &vehicleVelocity,
                                            const float vehicleMaxSpeed,
                                            float deceleration)
      {
          const btMatrix3x3 matTransform(btMatrix3x3::getIdentity());
          
          btTransform transform(matTransform, leaderPos);
          
          const btVector3 worldOffsetPost(transform * offsetTargetPos);
          const btVector3 toOffset(worldOffsetPost - vehiclePos);
          
          const btScalar lookAheadTime = toOffset.length() / (vehicleMaxSpeed + leaderSpeed);
          
//          return arrive(worldOffsetPost + leaderVelocity * lookAheadTime, vehiclePos, vehicleVelocity, deceleration, 3.0);
          return arrive(worldOffsetPost + leaderVelocity * lookAheadTime, vehiclePos, vehicleVelocity, vehicleMaxSpeed, deceleration);
      }
      

  protected:
    f32 getMaxForce2() const;

    void setCalculatedForce(const btVector3 &force);
    typedef std::pair<SteeringBehavior *, f32> SteeringPair;
    typedef std::map<SteeringBehavior *, f32> SteeringMap;

    SteeringMap m_SteeringBehaviorMap;

  private:
    virtual const btVector3 &calculate(f32 timestep);

    btVector3 *m_CurrentForce;

    //        std::vector<SteeringPair> m_SteeringBehaviorList;
    btVector3 *m_CurrentVelocity;
    btVector3 *m_HeadingVector;
      btVector3 *m_UpVector;
    f32 m_MaxSpeed;
    f32 m_MaxForce;
    f32 m_MaxForce2;
      bool m_Enable;
  };
}

#endif /* SteeringBehaviorMachine_hpp */
