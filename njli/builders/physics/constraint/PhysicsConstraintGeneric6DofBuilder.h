//
//  PhysicsConstraintGeneric6DofBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 6/19/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsConstraintGeneric6DofBuilder__
#define __JLIGameEngineTest__PhysicsConstraintGeneric6DofBuilder__

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
  PhysicsConstraintGeneric6DofBuilder : public AbstractBuilder
  {
    friend class WorldFactory;

  protected:
    PhysicsConstraintGeneric6DofBuilder();
    PhysicsConstraintGeneric6DofBuilder(
        const PhysicsConstraintGeneric6DofBuilder &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsConstraintGeneric6DofBuilder();

    PhysicsConstraintGeneric6DofBuilder &operator=(
        const PhysicsConstraintGeneric6DofBuilder &);

  public:
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual s32 calculateSerializeBufferSize() const;

    /**
     *  @author James Folk, 16-02-11 15:02:48
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
    static PhysicsConstraintGeneric6DofBuilder **createArray(const u32 size);
    /**
     *  <#Description#>
     *
     *  @param array <#array description#>
     */
    static void destroyArray(PhysicsConstraintGeneric6DofBuilder * *array,
                             const u32 size = 0);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static PhysicsConstraintGeneric6DofBuilder *create();
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     *
     *  @return <#return value description#>
     */
    static PhysicsConstraintGeneric6DofBuilder *clone(
        const PhysicsConstraintGeneric6DofBuilder &object);
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     */
    static void destroy(PhysicsConstraintGeneric6DofBuilder * object);
    /**
     *  <#Description#>
     *
     *  @param object      <#object description#>
     *  @param L           <#L description#>
     *  @param stack_index <#stack_index description#>
     */
    static void load(PhysicsConstraintGeneric6DofBuilder & object,
                     lua_State * L, int stack_index);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static u32 type();
  };
}

#endif /* defined(__JLIGameEngineTest__PhysicsConstraintGeneric6DofBuilder__)  \
          */
