//
//  SceneStateMachineBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SceneStateMachineBuilder__
#define __JLIGameEngineTest__SceneStateMachineBuilder__

#include "AbstractBuilder.h"
#include "Util.h"
#include "btAlignedObjectArray.h"
#include "btSerializer.h"
#include "lua.hpp"

namespace njli
{
  /**
   *  <#Description#>
   */
  ATTRIBUTE_ALIGNED16(class) SceneStateMachineBuilder : public AbstractBuilder
  {
    friend class WorldFactory;

  protected:
    SceneStateMachineBuilder();
    SceneStateMachineBuilder(const SceneStateMachineBuilder &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SceneStateMachineBuilder();

    SceneStateMachineBuilder &operator=(const SceneStateMachineBuilder &);

  public:
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual s32 calculateSerializeBufferSize() const;
    /**
     *  <#Description#>
     *
     *  @param btSerializer <#btSerializer description#>
     */
    virtual void serialize(void *, btSerializer *) const;

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
    static SceneStateMachineBuilder **createArray(const u32 size);
    /**
     *  <#Description#>
     *
     *  @param array <#array description#>
     */
    static void destroyArray(SceneStateMachineBuilder * *array,
                             const u32 size = 0);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static SceneStateMachineBuilder *create();
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     *
     *  @return <#return value description#>
     */
    static SceneStateMachineBuilder *clone(
        const SceneStateMachineBuilder &object);
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     */
    static void destroy(SceneStateMachineBuilder * object);
    /**
     *  <#Description#>
     *
     *  @param object      <#object description#>
     *  @param L           <#L description#>
     *  @param stack_index <#stack_index description#>
     */
    static void load(SceneStateMachineBuilder & object, lua_State * L,
                     int stack_index);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static u32 type();
  };
}

#endif /* defined(__JLIGameEngineTest__SceneStateMachineBuilder__) */
