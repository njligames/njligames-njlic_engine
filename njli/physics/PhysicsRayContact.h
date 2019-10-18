//
//  PhysicsRayContact.h
//  JLIGameEngineTest
//
//  Created by James Folk on 1/8/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__PhysicsRayContact__
#define __JLIGameEngineTest__PhysicsRayContact__

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "lua.hpp"

class btVector3;
class btVector2;

namespace njli
{
  class PhysicsRayContactBuilder;
  class Node;
class DeviceTouch;

  /**
       *  <#Description#>
       */
  ATTRIBUTE_ALIGNED16(class)
  PhysicsRayContact : public AbstractFactoryObject
  {
    friend class WorldFactory;
    friend class PhysicsWorld;
    friend class WorldState;
    friend class World;

  protected:
    PhysicsRayContact();
    PhysicsRayContact(const AbstractBuilder &);
    PhysicsRayContact(const PhysicsRayContact &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~PhysicsRayContact();
    PhysicsRayContact &operator=(const PhysicsRayContact &);

  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
      using AbstractDecorator::getUuid;
    using AbstractFactoryObject::create;
    //    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    virtual s32 calculateSerializeBufferSize() const;

    /**
         *  @author James Folk, 16-02-11 15:02:25
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
    static PhysicsRayContact **createArray(const u32 size);
    /**
         *  <#Description#>
         *
         *  @param array <#array description#>
         */
    static void destroyArray(PhysicsRayContact * *array, const u32 size = 0);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsRayContact *create();
    /**
         *  <#Description#>
         *
         *  @param builder <#builder description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsRayContact *create(const PhysicsRayContactBuilder &builder);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsRayContact *clone(const PhysicsRayContact &object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         *
         *  @return <#return value description#>
         */
    static PhysicsRayContact *copy(const PhysicsRayContact &object);
    /**
         *  <#Description#>
         *
         *  @param object <#object description#>
         */
    static void destroy(PhysicsRayContact * object);
    /**
         *  <#Description#>
         *
         *  @param object      <#object description#>
         *  @param L           <#L description#>
         *  @param stack_index <#stack_index description#>
         */
    static void load(PhysicsRayContact & object, lua_State * L,
                     int stack_index);
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    static u32 type();

  public:
    // TODO: fill in specific methods for PhysicsRayContact

    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    f32 getClosestHitFraction() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector3 &getHitNormalWorld() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector3 &getHitPointWorld() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    Node *getHitNode() const;
    /**
         *  <#Description#>
         *
         *  @return <#return value description#>
         */
    const btVector2 &getTouchPosition() const;
      
      void setDeviceTouch(const DeviceTouch &touch);
      const DeviceTouch &getDeviceTouch()const;

  protected:
    void screenPosition(const btVector2 &pos);
    void set(f32 m_closestHitFraction, const btVector3 &m_hitNormalWorld,
             const btVector3 &m_hitPointWorld, Node *m_node);

  private:
    f32 m_closestHitFraction;
    btVector3 *m_hitNormalWorld;
    btVector3 *m_hitPointWorld;
    Node *m_node;
    btVector2 *m_touchPosition;
      DeviceTouch *mDeviceTouch;
  };
}

#endif /* defined(__JLIGameEngineTest__PhysicsRayContact__) */
