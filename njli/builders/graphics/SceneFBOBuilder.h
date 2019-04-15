//
//  SceneFBOBuilder.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SceneFBOBuilder__
#define __JLIGameEngineTest__SceneFBOBuilder__

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
  ATTRIBUTE_ALIGNED16(class) SceneFBOBuilder : public AbstractBuilder
  {
    friend class WorldFactory;

  protected:
    SceneFBOBuilder();
    SceneFBOBuilder(const SceneFBOBuilder &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SceneFBOBuilder();

    SceneFBOBuilder &operator=(const SceneFBOBuilder &);

  public:
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    virtual s32 calculateSerializeBufferSize() const;

    /**
     *  @author James Folk, 16-02-11 15:02:37
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
    static SceneFBOBuilder **createArray(const u32 size);
    /**
     *  <#Description#>
     *
     *  @param array <#array description#>
     */
    static void destroyArray(SceneFBOBuilder * *array, const u32 size = 0);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static SceneFBOBuilder *create();
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     *
     *  @return <#return value description#>
     */
    static SceneFBOBuilder *clone(const SceneFBOBuilder &object);
    /**
     *  <#Description#>
     *
     *  @param object <#object description#>
     */
    static void destroy(SceneFBOBuilder * object);
    /**
     *  <#Description#>
     *
     *  @param object      <#object description#>
     *  @param L           <#L description#>
     *  @param stack_index <#stack_index description#>
     */
    static void load(SceneFBOBuilder & object, lua_State * L, int stack_index);
    /**
     *  <#Description#>
     *
     *  @return <#return value description#>
     */
    static u32 type();
  };
}

#endif /* defined(__JLIGameEngineTest__SceneFBOBuilder__) */