//
//  SceneFBO.h
//  JLIGameEngineTest
//
//  Created by James Folk on 2/13/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__SceneFBO__
#define __JLIGameEngineTest__SceneFBO__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "lua.hpp"
#include <functional>

//#include "nanovg_gl_utils.h"

class btVector2;
class btVector4;

namespace njli
{
  class SceneFBOBuilder;

  /**
       *  <#Description#>
       */
  ATTRIBUTE_ALIGNED16(class)
  SceneFBO : public AbstractFactoryObject, public AbstractFrameBufferObject
  {
    friend class WorldFactory;

  protected:
    SceneFBO();
    SceneFBO(const AbstractBuilder &);
    SceneFBO(const SceneFBO &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~SceneFBO();
    SceneFBO &operator=(const SceneFBO &);
    virtual void renderFunction(Camera * camera);

  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
      using AbstractDecorator::getUuid;
    using AbstractFactoryObject::create;
    //    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;
    using AbstractFrameBufferObject::isHidden;
    using AbstractFrameBufferObject::hide;
    using AbstractFrameBufferObject::show;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:30
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
    static SceneFBO **createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(SceneFBO * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static SceneFBO *create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static SceneFBO *create(const SceneFBOBuilder &builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SceneFBO *clone(const SceneFBO &object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static SceneFBO *copy(const SceneFBO &object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(SceneFBO * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(SceneFBO & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

  public:
      void setRenderFunction(const std::function<void(Camera *)> &fn);

  protected:
  private:
      std::function<void(Camera *)> mRenderFunction;
  };
}

#endif /* defined(__JLIGameEngineTest__SceneFBO__) */
