//
//  WorldState.h
//  JLIGameEngineTest
//
//  Created by James Folk on 12/6/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__WorldState__
#define __JLIGameEngineTest__WorldState__

#include "AbstractBuilder.h"
#include "AbstractState.h"
#include "DeviceMouse.h"
#include "DeviceTouch.h"
#include "lua.hpp"

namespace njli
{
  class WorldStateBuilder;
  class Scene;
  class PhysicsRayContact;

  /**
       *  <#Description#>
       */
  ATTRIBUTE_ALIGNED16(class)
  WorldState : public AbstractState<void>
  {
    friend class WorldFactory;

  protected:
    WorldState();
    WorldState(const AbstractBuilder &);
    WorldState(const WorldState &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~WorldState();
    WorldState &operator=(const WorldState &);

  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
    //    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;
    using AbstractState::isFinished;
    using AbstractState::enableFinished;
    using AbstractState::enableCanDelete;

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
    static WorldState **createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(WorldState * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static WorldState *create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static WorldState *create(const WorldStateBuilder &builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static WorldState *clone(const WorldState &object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static WorldState *copy(const WorldState &object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(WorldState * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(WorldState & object, lua_State * L, int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

    /**
         *  <#Description#>
         */
    virtual void enter(void *);
    /**
         *  <#Description#>
         *
         *  @param f32 <#f32 description#>
         */
    virtual void update(void *, f32);
    /**
         *  <#Description#>
         */
    virtual void exit(void *);
    /**
         *  <#Description#>
         *
         *  @param Telegram& <#Telegram& description#>
         *
         *  @return <#return value description#>
         */
    virtual bool onMessage(void *, const Telegram &) const;

  public:
    // TODO: fill in specific methods for WorldState

    /**
     <#Description#>

     @param touches <#touches description#>
     */
    void touchDown(DeviceTouch * *touches);

    /**
     <#Description#>

     @param touches <#touches description#>
     */
    void touchUp(DeviceTouch * *touches);

    /**
     <#Description#>

     @param touches <#touches description#>
     */
    void touchMove(DeviceTouch * *touches);

    /**
     <#Description#>

     @param touches <#touches description#>
     */
    void touchCancelled(DeviceTouch * *touches);

    /**
     <#Description#>

     @param touch <#touch description#>
     */
    void touchDown(const DeviceTouch &touch);

    /**
     <#Description#>

     @param touch <#touch description#>
     */
    void touchUp(const DeviceTouch &touch);

    /**
     <#Description#>

     @param touch <#touch description#>
     */
    void touchMove(const DeviceTouch &touch);

    void mouseDown(const DeviceMouse &touch);
    void mouseUp(const DeviceMouse &touch);
    void mouseMove(const DeviceMouse &touch);

    void keyUp(const char *keycodeName, bool withCapsLock, bool withControl,
               bool withShift, bool withAlt, bool withGui);

    void keyDown(const char *keycodeName, bool withCapsLock, bool withControl,
                 bool withShift, bool withAlt, bool withGui);

    /**
     <#Description#>

     @param touch <#touch description#>
     */
    void touchCancelled(const DeviceTouch &touch);

  public:
  protected:
    //    void checkRayCollision(DeviceTouch * *touches, const char *code,
    //                           bool disableNodeTouched = false);
    //    void checkRayCollision(const DeviceTouch &touch, const char *code,
    //                           bool disableNodeTouched = false);
    //    void checkRayCollision(const DeviceMouse &mouse, const char *code,
    //                           bool disableNodeTouched = false);

  private:
    //    btAlignedObjectArray<njli::PhysicsRayContact *> m_RayContacts;
  };
}

#endif /* defined(__JLIGameEngineTest__WorldState__) */
