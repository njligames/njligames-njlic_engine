//
//  PhysicsConstraintHingeBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/18/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintHingeBuilder__
#define __JLIGameEngineTest__PhysicsConstraintHingeBuilder__

#pragma mark Header

#include "AbstractBuilder.h"
#include "Util.h"
#include "btAlignedObjectArray.h"
#include "btSerializer.h"
#include "lua.hpp"

#include "Log.h"

namespace njli
{
  /**
   *  <#Description#>
   */
  ATTRIBUTE_ALIGNED16(class)
  PhysicsConstraintHingeBuilder : public AbstractBuilder
  {
    friend class WorldFactory;

  protected:
    PhysicsConstraintHingeBuilder();
    PhysicsConstraintHingeBuilder(const PhysicsConstraintHingeBuilder &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsConstraintHingeBuilder();

    PhysicsConstraintHingeBuilder &operator=(
        const PhysicsConstraintHingeBuilder &);

  public:
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual s32 calculateSerializeBufferSize() const;

    /**
     *  @author James Folk, 16-02-11 15:02:19
     *
     *  @brief <#Description#>
     *
     *  @param dataBuffer   <#dataBuffer description#>
     *  @param btSerializer <#btSerializer description#>
     */
    virtual void serialize(void *dataBuffer, btSerializer *) const;

    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual u32 getObjectType() const;
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual const char *getClassName() const;
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual s32 getType() const;
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    operator std::string() const;

    /**
     *  <#Description#>
     *
     *  @param size <#size description#>
     *
     *  @return <#return value description#>
     */
    static PhysicsConstraintHingeBuilder **createArray(const u32 size);
    /**
     *  <#Description#>
     *
     *  @param array <#array description#>
     */
    static void destroyArray(PhysicsConstraintHingeBuilder * *array,
                             const u32 size = 0);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static PhysicsConstraintHingeBuilder *create();
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     *
     *  @return <#return value description#>
     */
    static PhysicsConstraintHingeBuilder *clone(
        const PhysicsConstraintHingeBuilder &object);
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     */
    static void destroy(PhysicsConstraintHingeBuilder * object);
    /**
     *  <#Description#>
     *
     *  @param object      <#object description#>
     *  @param L           <#L description#>
     *  @param stack_index <#stack_index description#>
     */
    static void load(PhysicsConstraintHingeBuilder & object, lua_State * L,
                     int stack_index);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static u32 type();
  };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintHingeBuilder__) */
