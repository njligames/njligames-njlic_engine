//
//  SceneFBO.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 4/04/19.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "SceneFBO.h"
#include "GraphicsPlatform.h"
#include "JLIFactoryTypes.h"
#include "Log.h"
#include "SceneFBOBuilder.h"
#include "World.h"
#define TAG "SceneFBO.cpp"
#include "SpriteFrameAtlas.h"
#include "btVector2.h"
#include "btVector3.h"
#define FORMATSTRING "{\"njli::SceneFBO\":[]}"
#include "JsonJLI.h"
#include "btPrint.h"

namespace njli
{
    SceneFBO::SceneFBO() : AbstractFactoryObject(this)
    {
        //        m_FBO =
        //        njli::World::getInstance()->getWorldHUD()->createFBO(512, 512,
        //        NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
    }

    SceneFBO::SceneFBO(const AbstractBuilder &builder)
        : AbstractFactoryObject(this)
    {
        //        m_FBO =
        //        njli::World::getInstance()->getWorldHUD()->createFBO(512, 512,
        //        NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
    }

    SceneFBO::SceneFBO(const SceneFBO &copy) : AbstractFactoryObject(this)
    {
        //        m_FBO =
        //        njli::World::getInstance()->getWorldHUD()->createFBO(512, 512,
        //        NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY);
    }

    SceneFBO::~SceneFBO() {}

    SceneFBO &SceneFBO::operator=(const SceneFBO &rhs)
    {
        if (this != &rhs)
            {
            }
        return *this;
    }

    void SceneFBO::renderFunction(Camera *camera) { mRenderFunction(camera); }

    s32 SceneFBO::calculateSerializeBufferSize() const
    {
        // TODO: calculateSerializeBufferSize
        return 0;
    }

    void SceneFBO::serialize(void *dataBuffer, btSerializer *serializer) const
    {
        // TODO: serialize
    }

    const char *SceneFBO::getClassName() const { return "SceneFBO"; }

    s32 SceneFBO::getType() const { return JLI_OBJECT_TYPE_SceneFBO; }

    SceneFBO::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }

    SceneFBO **SceneFBO::createArray(const u32 size)
    {
        return (SceneFBO **)World::getInstance()
            ->getWorldFactory()
            ->createArray(SceneFBO::type(), size);
    }

    void SceneFBO::destroyArray(SceneFBO **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray(
            (AbstractFactoryObject **)array, size);
    }

    SceneFBO *SceneFBO::create()
    {
        return dynamic_cast<SceneFBO *>(
            World::getInstance()->getWorldFactory()->create(SceneFBO::type()));
    }

    SceneFBO *SceneFBO::create(const SceneFBOBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;

        return dynamic_cast<SceneFBO *>(
            World::getInstance()->getWorldFactory()->create(*b));
    }

    SceneFBO *SceneFBO::clone(const SceneFBO &object)
    {
        return dynamic_cast<SceneFBO *>(
            World::getInstance()->getWorldFactory()->clone(object, false));
    }

    SceneFBO *SceneFBO::copy(const SceneFBO &object)
    {
        return dynamic_cast<SceneFBO *>(
            World::getInstance()->getWorldFactory()->clone(object, true));
    }

    void SceneFBO::destroy(SceneFBO *object)
    {
        if (object)
            {
                World::getInstance()->getWorldFactory()->destroy(object);
            }
    }

    void SceneFBO::load(SceneFBO &object, lua_State *L, int index)
    {
        // Push another reference to the table on top of the stack (so we know
        // where it is, and this function can work for negative, positive and
        // pseudo indices
        lua_pushvalue(L, index);
        // stack now contains: -1 => table
        lua_pushnil(L);
        // stack now contains: -1 => nil; -2 => table
        while (lua_next(L, -2))
            {
                // stack now contains: -1 => value; -2 => key; -3 => table
                // copy the key so that lua_tostring does not modify the
                // original
                lua_pushvalue(L, -2);
                // stack now contains: -1 => key; -2 => value; -3 => key; -4 =>
                // table
                const char *key = lua_tostring(L, -1);
                //            const char *value = lua_tostring(L, -2);
                if (lua_istable(L, -2))
                    {
                        SceneFBO::load(object, L, -2);
                    }
                else
                    {
                        if (lua_isnumber(L, index))
                            {
                                double number = lua_tonumber(L, index);
                                printf("%s => %f\n", key, number);
                            }
                        else if (lua_isstring(L, index))
                            {
                                const char *v = lua_tostring(L, index);
                                printf("%s => %s\n", key, v);
                            }
                        else if (lua_isboolean(L, index))
                            {
                                bool v = lua_toboolean(L, index);
                                printf("%s => %d\n", key, v);
                            }
                        else if (lua_isuserdata(L, index))
                            {
                                //                    swig_lua_userdata *usr;
                                //                    swig_type_info *type;
                                //                    assert(lua_isuserdata(L,index));
                                //                    usr=(swig_lua_userdata*)lua_touserdata(L,index);
                                //                    /* get data */
                                //                    type = usr->type;
                                //                    njli::AbstractFactoryObject
                                //                    *object =
                                //                    static_cast<njli::AbstractFactoryObject*>(usr->ptr);
                                //                    printf("%s => %d:%s\n",
                                //                    key, object->getType(),
                                //                    object->getClassName());
                            }
                    }
                // pop value + copy of key, leaving original key
                lua_pop(L, 2);
                // stack now contains: -1 => key; -2 => table
            }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the
        // key but does not push anything.) Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    u32 SceneFBO::type() { return JLI_OBJECT_TYPE_SceneFBO; }

    void SceneFBO::setRenderFunction(const std::function<void(Camera *)> &fn)
    {
        mRenderFunction = fn;
    }

} // namespace njli
