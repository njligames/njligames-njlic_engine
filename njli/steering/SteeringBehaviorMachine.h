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
#include "btVector3.h"
#include "btQuaternion.h"

#include "Node.h"

namespace njli
{
  class SteeringBehaviorMachineBuilder;
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

//    bool setHeuristic(SteeringBehavior * steeringBehavior, f32 heuristic);
//    f32 getHeuristic(SteeringBehavior * steeringBehavior) const;

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
    bool addSteeringBehavior(SteeringBehavior * steeringBehavior);

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
      
      void clearSteering();
      
      void enable(bool enable=true){m_Enable=enable;}
      bool isEnabled()const{return m_Enable;}
      
      
  public:
      void createFeelers(const btVector3 &origin, const float feelerLength, std::vector<btVector3> &feelers);
      
      static inline btVector3 seek(const btVector3 &targetPos,
                                   const btVector3 &vehiclePos,
                                   const btVector3 &vehicleVelocity,
                                   const float vehicleMaxSpeed)
      {
          float speed(vehicleMaxSpeed);
          if(isinf(vehicleMaxSpeed))
              speed = std::numeric_limits<float>::max();
              
          const btVector3 diffPosition(targetPos - vehiclePos);
          const btVector3 desiredVelocity(diffPosition.normalized() * speed);
          const btVector3 seek(desiredVelocity - vehicleVelocity);
          return seek;
      }
      
      static inline btVector3 flee(const btVector3 &targetPos,
                                       const btVector3 &vehiclePos,
                                       const btVector3 &vehicleVelocity,
                                       const float vehicleMaxSpeed)
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
              float speed(vehicleMaxSpeed);
              if(isinf(vehicleMaxSpeed))
                  speed = std::numeric_limits<float>::max();
              
              btVector3 toTarget(targetPos - vehiclePos);
              btScalar dist(toTarget.length());
              
              if(dist > 0)
              {
                  const btScalar decelerationDenominator(deceleration);
                  assert(decelerationDenominator != 0);
                  
                  btScalar speed(dist / decelerationDenominator);
                  speed = fmin(speed, speed);
                  
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
                                      const float vehicleMaxSpeed)
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
                                    const float vehicleMaxSpeed)
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
                  return seek(path.currentWaypoint(), vehiclePos, vehicleVelocity, vehicleMaxSpeed);
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
      
      static inline btVector3 pointToWorldSpace(const btVector3 &point,
                                                const btVector3 &agentHeading,
                                                const btVector3 &agentSide,
                                                const btVector3 &agentUp,
                                                const btVector3 &agentPosition)
      {
          const float upAngle(btAngle(agentUp, btVector3(0,1,0)));
          const float sideAngle(btAngle(agentSide, btVector3(1,0,0)));
          const float headingAngle(btAngle(agentHeading, btVector3(0,0,1)));
          
          btQuaternion upRot(btVector3(0,1,0), upAngle);
          btQuaternion sideRot(btVector3(1,0,0), sideAngle);
          btQuaternion headingRot(btVector3(0,0,1), headingAngle);
          
          
          btTransform pointTransform(btMatrix3x3(upRot * sideRot * headingRot), point);
          
          return pointTransform * agentPosition;
          
//          const btMatrix3x3 matTransform(btMatrix3x3::getIdentity());
//
//          btTransform transform(matTransform, point);
//
//          return transform * offsetTargetPos;
      }
      
      static inline float RandFloat()      {return ((rand())/(RAND_MAX+1.0));}
      static inline float RandomClamped()    {return RandFloat() - RandFloat();}
      
      static inline btVector3 wander(const btVector3 &vehiclePosition,
                                     btVector3 &wanderTarget,
                                     float wanderJitter,
                                     float wanderRadius,
                                     float wanderDistance,
                                     const btVector3 &sbClamp = btVector3(1,1,1))
      {
          
//          this behavior is dependent on the update rate, so this line must
//          be included when using time independent framerate.
//          double JitterThisTimeSlice = m_dWanderJitter * m_pVehicle->TimeElapsed();
          const float jitterThisTimeSlice = wanderJitter;
          wanderTarget += btVector3(RandomClamped() * jitterThisTimeSlice,
                                      RandomClamped() * jitterThisTimeSlice,
                                      RandomClamped() * jitterThisTimeSlice);
          wanderTarget.normalize();
          wanderTarget *= wanderRadius;
          const btVector3 target(wanderTarget + (sbClamp * btVector3(wanderDistance, wanderDistance, wanderDistance)));
          
          btTransform targetTransform(btMatrix3x3(btMatrix3x3::getIdentity()), target);
          
          const btVector3 transformedTarget(targetTransform * target);
          
          return (transformedTarget - vehiclePosition) * sbClamp;
          
//          //this behavior is dependent on the update rate, so this line must
//          //be included when using time independent framerate.
//          double JitterThisTimeSlice = m_dWanderJitter * m_pVehicle->TimeElapsed();
//          
//          //first, add a small random vector to the target's position
//          m_vWanderTarget += Vector2D(RandomClamped() * JitterThisTimeSlice,
//                                      RandomClamped() * JitterThisTimeSlice);
//          
//          //reproject this new vector back on to a unit circle
//          m_vWanderTarget.Normalize();
//          
//          //increase the length of the vector to the same as the radius
//          //of the wander circle
//          m_vWanderTarget *= m_dWanderRadius;
//          
//          //move the target into a position WanderDist in front of the agent
//          Vector2D target = m_vWanderTarget + Vector2D(m_dWanderDistance, 0);
//          
//          //project the target into world space
//          Vector2D Target = PointToWorldSpace(target,
//                                              m_pVehicle->Heading(),
//                                              m_pVehicle->Side(),
//                                              m_pVehicle->Pos());
//          
//          //and steer towards it
//          return Target - m_pVehicle->Pos();
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
//      //---------------------------- Separation --------------------------------
//      //
//      // this calculates a force repelling from the other neighbors
//      //------------------------------------------------------------------------
//      Vector2D SteeringBehavior::Separation(const vector<Vehicle*> &neighbors)
//      {
//          Vector2D SteeringForce;
//
//          for (unsigned int a=0; a<neighbors.size(); ++a)
//          {
//              //make sure this agent isn't included in the calculations and that
//              //the agent being examined is close enough. ***also make sure it doesn't
//              //include the evade target ***
//              if((neighbors[a] != m_pVehicle) && neighbors[a]->IsTagged() &&
//                 (neighbors[a] != m_pTargetAgent1))
//              {
//                  Vector2D ToAgent = m_pVehicle->Pos() - neighbors[a]->Pos();
//
//                  //scale the force inversely proportional to the agents distance
//                  //from its neighbor.
//                  SteeringForce += Vec2DNormalize(ToAgent)/ToAgent.Length();
//              }
//          }
//
//          return SteeringForce;
//      }
      
      static inline btVector3 separation(Node *currentVehicle,
                                         const std::vector<Node*>& neighbors,
                                         const btVector3 &steeringFactor = btVector3(1,1,1))
      {
          btVector3 cumulativeSteeringForce(0,0,0);
          
          for(size_t a = 0; a < neighbors.size(); ++a)
          {
              if(neighbors[a] != currentVehicle &&
                 neighbors[a]->isTagged())
              {
                  const btVector3 to(currentVehicle->getOrigin() * steeringFactor);
                  const btVector3 from(neighbors[a]->getOrigin() * steeringFactor);
                  const btVector3 toAgent(to - from);
                  cumulativeSteeringForce += (toAgent.normalized() / toAgent.length());
              }
          }
          return cumulativeSteeringForce;
      }
      
//      //-------------------------------- Cohesion ------------------------------
//      //
//      //  returns a steering force that attempts to move the agent towards the
//      //  center of mass of the agents in its immediate area
//      //------------------------------------------------------------------------
//      Vector2D SteeringBehavior::Cohesion(const vector<Vehicle*> &neighbors)
//      {
//          //first find the center of mass of all the agents
//          Vector2D CenterOfMass, SteeringForce;
//
//          int NeighborCount = 0;
//
//          //iterate through the neighbors and sum up all the position vectors
//          for (unsigned int a=0; a<neighbors.size(); ++a)
//          {
//              //make sure *this* agent isn't included in the calculations and that
//              //the agent being examined is close enough ***also make sure it doesn't
//              //include the evade target ***
//              if((neighbors[a] != m_pVehicle) && neighbors[a]->IsTagged() &&
//                 (neighbors[a] != m_pTargetAgent1))
//              {
//                  CenterOfMass += neighbors[a]->Pos();
//
//                  ++NeighborCount;
//              }
//          }
//
//          if (NeighborCount > 0)
//          {
//              //the center of mass is the average of the sum of positions
//              CenterOfMass /= (double)NeighborCount;
//
//              //now seek towards that position
//              SteeringForce = Seek(CenterOfMass);
//          }
//
//          //the magnitude of cohesion is usually much larger than separation or
//          //allignment so it usually helps to normalize it.
//          return Vec2DNormalize(SteeringForce);
//      }

      static inline btVector3 cohesion(Node *currentVehicle,
                                         Node *targetVehicle,
                                         const std::vector<Node*>& neighbors)
      {
          btVector3 cumulativeSteeringForce(0,0,0), centerOfMass(0,0,0);
          int neighborCount(0);
          
          for(size_t a = 0; a < neighbors.size(); ++a)
          {
              if(neighbors[a] != currentVehicle &&
                 neighbors[a]->isTagged() &&
                 neighbors[a] != targetVehicle)
              {
                  centerOfMass += neighbors[a]->getOrigin();
                  ++neighborCount;
                  
              }
          }
          if(neighborCount > 0)
          {
              centerOfMass /= (double)neighborCount;
              
              cumulativeSteeringForce = seek(centerOfMass, currentVehicle->getOrigin(), currentVehicle->getOrigin(), currentVehicle->getSteeringBehaviorMachine()->getMaxSpeed());
              return cumulativeSteeringForce.normalized();
          }
          return cumulativeSteeringForce;
      }
      
      static inline btVector3 obstacleAvoidance(const std::vector<Node*>& obstacles,
                                                const float minDetectionBoxLength,
                                                const float vehicleSpeed,
                                                const float vehicleMaxSpeed)
      {
          assert(false && "doesn't work");
          
//          //the detection box length is proportional to the agent's velocity
//          m_dDBoxLength = Prm.MinDetectionBoxLength +
//          (m_pVehicle->Speed()/m_pVehicle->MaxSpeed()) *
//          Prm.MinDetectionBoxLength;
          const float boxLength(minDetectionBoxLength + (vehicleSpeed / vehicleMaxSpeed) * minDetectionBoxLength);
//
//          //tag all obstacles within range of the box for processing
//          m_pVehicle->World()->TagObstaclesWithinViewRange(m_pVehicle, m_dDBoxLength);
//
//          //this will keep track of the closest intersecting obstacle (CIB)
//          BaseGameEntity* ClosestIntersectingObstacle = NULL;
//
//          //this will be used to track the distance to the CIB
//          double DistToClosestIP = MaxDouble;
          double distToClosestIP = std::numeric_limits<double>::max();
//
//          //this will record the transformed local coordinates of the CIB
//          Vector2D LocalPosOfClosestObstacle;
          btVector3 localPosOfClosestObstacle;
          
          std::vector<Node*>::const_iterator curOb = obstacles.begin();
          
          while(curOb != obstacles.end())
          {
              Node *node = *curOb;
              
              if(node->isTagged())
              {
                  
              }
          }

		  return btVector3(0, 0, 0);
          //
//          std::vector<BaseGameEntity*>::const_iterator curOb = obstacles.begin();
//
//          while(curOb != obstacles.end())
//          {
//              //if the obstacle has been tagged within range proceed
//              if ((*curOb)->IsTagged())
//              {
//                  //calculate this obstacle's position in local space
//                  Vector2D LocalPos = PointToLocalSpace((*curOb)->Pos(),
//                                                        m_pVehicle->Heading(),
//                                                        m_pVehicle->Side(),
//                                                        m_pVehicle->Pos());
//
//                  //if the local position has a negative x value then it must lay
//                  //behind the agent. (in which case it can be ignored)
//                  if (LocalPos.x >= 0)
//                  {
//                      //if the distance from the x axis to the object's position is less
//                      //than its radius + half the width of the detection box then there
//                      //is a potential intersection.
//                      double ExpandedRadius = (*curOb)->BRadius() + m_pVehicle->BRadius();
//
//                      if (fabs(LocalPos.y) < ExpandedRadius)
//                      {
//                          //now to do a line/circle intersection test. The center of the
//                          //circle is represented by (cX, cY). The intersection points are
//                          //given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0.
//                          //We only need to look at the smallest positive value of x because
//                          //that will be the closest point of intersection.
//                          double cX = LocalPos.x;
//                          double cY = LocalPos.y;
//
//                          //we only need to calculate the sqrt part of the above equation once
//                          double SqrtPart = sqrt(ExpandedRadius*ExpandedRadius - cY*cY);
//
//                          double ip = cX - SqrtPart;
//
//                          if (ip <= 0.0)
//                          {
//                              ip = cX + SqrtPart;
//                          }
//
//                          //test to see if this is the closest so far. If it is keep a
//                          //record of the obstacle and its local coordinates
//                          if (ip < DistToClosestIP)
//                          {
//                              DistToClosestIP = ip;
//
//                              ClosestIntersectingObstacle = *curOb;
//
//                              LocalPosOfClosestObstacle = LocalPos;
//                          }
//                      }
//                  }
//              }
//
//              ++curOb;
//          }
//
//          //if we have found an intersecting obstacle, calculate a steering
//          //force away from it
//          Vector2D SteeringForce;
//
//          if (ClosestIntersectingObstacle)
//          {
//              //the closer the agent is to an object, the stronger the
//              //steering force should be
//              double multiplier = 1.0 + (m_dDBoxLength - LocalPosOfClosestObstacle.x) /
//              m_dDBoxLength;
//
//              //calculate the lateral force
//              SteeringForce.y = (ClosestIntersectingObstacle->BRadius()-
//                                 LocalPosOfClosestObstacle.y)  * multiplier;
//
//              //apply a braking force proportional to the obstacles distance from
//              //the vehicle.
//              const double BrakingWeight = 0.2;
//
//              SteeringForce.x = (ClosestIntersectingObstacle->BRadius() -
//                                 LocalPosOfClosestObstacle.x) *
//              BrakingWeight;
//          }
//
//          //finally, convert the steering vector from local to world space
//          return VectorToWorldSpace(SteeringForce,
//                                    m_pVehicle->Heading(),
//                                    m_pVehicle->Side());
      }
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      

  protected:
    f32 getMaxForce2() const;

    void setCalculatedForce(const btVector3 &force);
      
      std::vector<SteeringBehavior*> m_SteeringBehaviorVector;

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
