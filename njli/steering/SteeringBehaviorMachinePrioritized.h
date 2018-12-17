//
//  SteeringBehaviorMachinePrioritized.h
//  NJLIGameEngine_iOS
//
//  Created by James Folk on 5/6/16.
//  Copyright © 2016 NJLIGames Ltd. All rights reserved.
//

#ifndef SteeringBehaviorMachinePrioritized_hpp
#define SteeringBehaviorMachinePrioritized_hpp

#pragma mark Header

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "Log.h"
#include "btVector3.h"
#include "lua.hpp"

#include "SteeringBehaviorMachine.h"

namespace njli
{
  class SteeringBehaviorMachinePrioritizedBuilder;
  class Node;
  class SteeringBehavior;

  /**
   *  <#Description#>
   */
  ATTRIBUTE_ALIGNED16(class)
  SteeringBehaviorMachinePrioritized : public SteeringBehaviorMachine
  {
    friend class WorldFactory;

  protected:
    SteeringBehaviorMachinePrioritized();
    SteeringBehaviorMachinePrioritized(const AbstractBuilder &);
    SteeringBehaviorMachinePrioritized(
        const SteeringBehaviorMachinePrioritized &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SteeringBehaviorMachinePrioritized();
    SteeringBehaviorMachinePrioritized &operator=(
        const SteeringBehaviorMachinePrioritized &);

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
    static SteeringBehaviorMachinePrioritized **createArray(const u32 size);
    /**
     *  Destroy an Array of this class type.
     *
     *  @param array The Pointer to the array to delete.
     */
    static void destroyArray(SteeringBehaviorMachinePrioritized * *array,
                             const u32 size = 0);
    /**
     *  Create an instance of this class.
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachinePrioritized *create();
    /**
     *  Create an instance of this class using a builder.
     *
     *  @param builder The builder to use for construction
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachinePrioritized *create(
        const SteeringBehaviorMachinePrioritizedBuilder &builder);
    /**
     *  Create a shallow copy of an instance of this class (sharing pointers).
     *
     *  @param object The object to clone.
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachinePrioritized *clone(
        const SteeringBehaviorMachinePrioritized &object);
    /**
     *  Create a deep copy of an instance of this class (NOT sharing pointers).
     *
     *  @param object The object to clone.
     *
     *  @return Pointer to the newly created instance.
     */
    static SteeringBehaviorMachinePrioritized *copy(
        const SteeringBehaviorMachinePrioritized &object);
    /**
     *  Destroy an instance of this class.
     *
     *  @param object The object to destroy.
     */
    static void destroy(SteeringBehaviorMachinePrioritized * object);
    /**
     *  Load a lua table representation of this class. This is used for
     * JLIM.create(object).
     *
     *  @param object      The object to load.
     *  @param L           The current lua state.
     *  @param stack_index The stack index of the lua stack.
     */
    static void load(SteeringBehaviorMachinePrioritized & object, lua_State * L,
                     int stack_index);
    /**
     *  Get the type of ::jliObjectEnumType enum value.
     *
     *  @return The ::jliObjectEnumType enum value.
     */
    static u32 type();

  public:
    // TODO: fill in specific methods for SteeringBehaviorMachinePrioritized

    virtual const btVector3 &calculateSteeringForce();

  protected:
      static inline bool accumulateForce(btVector3 &runningTot,
                                         const btVector3 &forceToAdd,
                                         float maxForce)
      {
          
          const btScalar magnitudeSoFar(runningTot.length());
          const btScalar magnitudeRemaining(maxForce - magnitudeSoFar);
          if(magnitudeRemaining)
          {
              return false;
          }
          btScalar magnitudeToAdd(forceToAdd.length());
          
          if(magnitudeToAdd < magnitudeRemaining)
          {
              runningTot += forceToAdd;
          }
          else
          {
              runningTot += (forceToAdd.normalized() * magnitudeRemaining);
          }
          return true;
          
//          //calculate how much steering force the vehicle has used so far
//          double MagnitudeSoFar = RunningTot.Length();
//
//          //calculate how much steering force remains to be used by this vehicle
//          double MagnitudeRemaining = m_pVehicle->MaxForce() - MagnitudeSoFar;
//
//          //return false if there is no more force left to use
//          if (MagnitudeRemaining <= 0.0) return false;
//
//          //calculate the magnitude of the force we want to add
//          double MagnitudeToAdd = ForceToAdd.Length();
//
//          //if the magnitude of the sum of ForceToAdd and the running total
//          //does not exceed the maximum force available to this vehicle, just
//          //add together. Otherwise add as much of the ForceToAdd vector is
//          //possible without going over the max.
//          if (MagnitudeToAdd < MagnitudeRemaining)
//          {
//              RunningTot += ForceToAdd;
//          }
//
//          else
//          {
//              //add it to the steering force
//              RunningTot += (Vec2DNormalize(ForceToAdd) * MagnitudeRemaining);
//          }
//
//          return true;
      }

  private:
  };
}

#endif /* SteeringBehaviorMachinePrioritized_hpp */
