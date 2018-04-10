//
//  Sound.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "Sound.h"
#include "JLIFactoryTypes.h"
#include "World.h"
#include "SoundBuilder.h"
#include "Log.h"
#define TAG "Sound.mm"
#include "PhysicsBody.h"
#define FORMATSTRING "{\"njli::Sound\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

static void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%d): FMOD error %d - %s", file, line, result, FMOD_ErrorString(result));
    }
}

#define FMOD_ERRCHECK(_result) do { if (FMOD_LOGGING_ON) ERRCHECK_fn(_result, __FILE__, __LINE__); } while (0)

namespace njli
{
    Sound::Sound():
    AbstractFactoryObject(this),
    m_Sound(NULL),
    m_ChannelIndex(-1),
    m_Transform(new btTransform())
    {
        
    }
    
    Sound::Sound(const AbstractBuilder &builder):
    AbstractFactoryObject(this),
    m_Sound(NULL),
    m_ChannelIndex(-1),
    m_Transform(new btTransform())
    {
        
    }
    
    Sound::Sound(const Sound &copy):
    AbstractFactoryObject(this),
    m_Sound(NULL),
    m_ChannelIndex(-1),
    m_Transform(new btTransform())
    {
        
    }
    
    Sound::~Sound()
    {
        delete m_Transform;
        m_Transform = NULL;
        
        FMOD_RESULT result;
        if (m_Sound)
        {
            result = m_Sound->release();
            //SDL_assertPrint(result==FMOD_OK, (FMOD_ErrorString(result)));
            m_Sound = NULL;
        }
    }
    
    Sound &Sound::operator=(const Sound &rhs)
    {
        if(this != &rhs)
        {
            
        }
        return *this;
    }
    
    s32	Sound::calculateSerializeBufferSize() const
    {
        //TODO: calculateSerializeBufferSize
        return 0;
    }
    
    void Sound::serialize(void* dataBuffer, btSerializer* serializer) const
    {
        //TODO: serialize
    }
    
    const char *Sound::getClassName()const
    {
        return "Sound";
    }
    
    s32 Sound::getType()const
    {
        return Sound::type();
    }
    
    Sound::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    Sound **Sound::createArray(const u32 size)
    {
        return (Sound**)World::getInstance()->getWorldFactory()->createArray(Sound::type(), size);
    }
    
    void Sound::destroyArray(Sound **array, const u32 size)
    {
        World::getInstance()->getWorldFactory()->destroyArray((AbstractFactoryObject**)array, size);
    }
    
    Sound *Sound::create()
    {
        return dynamic_cast<Sound*>(World::getInstance()->getWorldFactory()->create(Sound::type()));
    }
    
    Sound *Sound::create(const SoundBuilder &builder)
    {
        AbstractBuilder *b = (AbstractBuilder *)&builder;
        
        return dynamic_cast<Sound*>(World::getInstance()->getWorldFactory()->create(*b));
    }
    
    Sound *Sound::clone(const Sound &object)
    {
        return dynamic_cast<Sound*>(World::getInstance()->getWorldFactory()->clone(object, false));
    }
    
    Sound *Sound::copy(const Sound &object)
    {
        return dynamic_cast<Sound*>(World::getInstance()->getWorldFactory()->clone(object, true));
    }
    
    void Sound::destroy(Sound *object)
    {
        World::getInstance()->getWorldFactory()->destroy(object);
    }
    
    void Sound::load(Sound &object, lua_State *L, int index)
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
            // copy the key so that lua_tostring does not modify the original
            lua_pushvalue(L, -2);
            // stack now contains: -1 => key; -2 => value; -3 => key; -4 => table
            const char *key = lua_tostring(L, -1);
//            const char *value = lua_tostring(L, -2);
            if(lua_istable(L, -2))
            {
                Sound::load(object, L, -2);
            }
            else
            {
                if(lua_isnumber(L, index))
                {
                    double number = lua_tonumber(L, index);
                    printf("%s => %f\n", key, number);
                }
                else if(lua_isstring(L, index))
                {
                    const char *v = lua_tostring(L, index);
                    printf("%s => %s\n", key, v);
                }
                else if(lua_isboolean(L, index))
                {
                    bool v = lua_toboolean(L, index);
                    printf("%s => %d\n", key, v);
                }
                else if(lua_isuserdata(L, index))
                {
                    //                    swig_lua_userdata *usr;
                    //                    swig_type_info *type;
                    //                    assert(lua_isuserdata(L,index));
                    //                    usr=(swig_lua_userdata*)lua_touserdata(L,index);  /* get data */
                    //                    type = usr->type;
                    //                    njli::AbstractFactoryObject *object = static_cast<njli::AbstractFactoryObject*>(usr->ptr);
                    //                    printf("%s => %d:%s\n", key, object->getType(), object->getClassName());
                    
                }
            }
            // pop value + copy of key, leaving original key
            lua_pop(L, 2);
            // stack now contains: -1 => key; -2 => table
        }
        // stack now contains: -1 => table (when lua_next returns 0 it pops the key
        // but does not push anything.)
        // Pop table
        lua_pop(L, 1);
        // Stack is now the same as it was on entry to this function
    }
    
    u32 Sound::type()
    {
        return JLI_OBJECT_TYPE_Sound;
    }
    
    f32 Sound::getTimePosition()
    {
        u32 _pos = 0;
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->getPosition(&_pos, FMOD_TIMEUNIT_MS);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
        return (f32)_pos/1000.0f;
    }
    
    void Sound::setTimePosition(f32 pos)
    {
        u32 _pos = (u32)pos * 1000.0f;
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->setPosition(_pos, FMOD_TIMEUNIT_MS);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
    }
    
    f32 Sound::getTimeLength()
    {
        u32 length = 0;
        m_Sound->getLength(&length, FMOD_TIMEUNIT_MS);
        return (f32)length/1000.0f;
    }
    
    bool Sound::isPlaying()
    {
        bool playing = false;
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->isPlaying(&playing);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
        return playing;
    }
    
    void Sound::play(bool isPaused)
    {
        if(m_Sound)
        {
            FMOD_MODE mode;
            m_Sound->getMode(&mode);
            
            if(IsOn(mode, FMOD_3D))
            {
                FMOD::Channel *channel = getChannel();
                if(channel)
                {
                    FMOD_VECTOR pos =
                    {
                        getWorldTransform().getOrigin().x(),
                        getWorldTransform().getOrigin().y(),
                        getWorldTransform().getOrigin().z()
                    };
                    FMOD_VECTOR vel = {  0.0f, 0.0f, 0.0f };
                    PhysicsBody *body = getParent()->getPhysicsBody();
                    if (body)
                    {
                        vel =
                        {
                            body->getVelocity().x(),
                            body->getVelocity().y(),
                            body->getVelocity().z(),
                        };
                    }
                    channel->set3DAttributes(&pos, &vel);
                }
            }
            
            njli::World::getInstance()->getWorldSound()->playSound(*this, isPaused);
        }
        else
        {
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "The sound is null\n");
        }
    }
    
    void Sound::stop()
    {
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->stop();
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
    }
    
    bool Sound::isPaused()
    {
        bool paused = false;
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->getPaused(&paused);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
        return paused;
    }
    
    void Sound::pause()
    {
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->setPaused(true);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
    }
    
    void Sound::unPause()
    {
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->setPaused(false);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
    }
    
    bool Sound::isMuted()
    {
        bool muted = false;
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->getMute(&muted);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
        return muted;
    }
    
    void Sound::mute()
    {
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->setMute(true);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
    }
    
    void Sound::unMute()
    {
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->setMute(false);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
    }
    
    f32 Sound::getVolume()
    {
        f32 volume = 1.0f;
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->getVolume(&volume);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
        return volume;
    }
    
    void Sound::setVolume(f32 vol)
    {
        FMOD::Channel *channel = getChannel();
        if(channel)
            channel->setVolume(vol);
        //        else
        //            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "Channel wasn't found");
    }
    
    s32 Sound::getLoopCount()
    {
        s32 count = 0;
        m_Sound->getLoopCount(&count);
        return count;
    }
    
    void Sound::setLoopCount(s32 count)
    {
        bool wasPlaying = isPlaying();
        
        if (wasPlaying) {
            stop();
        }
        
        if(count < 0)
            m_Sound->setMode(FMOD_LOOP_NORMAL);
        else
            m_Sound->setLoopCount(count);
        
        if (wasPlaying)
        {
            play();
        }
    }
    
    btTransform Sound::getWorldTransform()const
    {
        if(getParent())
            return getParent()->getWorldTransform() * getTransform();
        return btTransform::getIdentity();
    }
    
    bool Sound::load(void *system, const char *path)
    {
        FMOD::System *_system = (FMOD::System *)system;
        SDL_assert(_system);
        
        m_Sound = NULL;
        FMOD_RESULT result = _system->createSound(ASSET_PATH(path), FMOD_DEFAULT, 0, &m_Sound);
        FMOD_ERRCHECK(result);
        
        return (FMOD_OK == result);
    }
    
    bool Sound::load(void *system, const char* fileContent, u32 size)
    {
        FMOD::System *_system = (FMOD::System *)system;
        SDL_assert(_system);
        
        FMOD_CREATESOUNDEXINFO info;
        memset(&info, 0, sizeof(FMOD_CREATESOUNDEXINFO));
        info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
        info.length = size;
        info.numchannels = 1;
        
        info.suggestedsoundtype = FMOD_SOUND_TYPE_OGGVORBIS;
        
        
        FMOD_RESULT result = _system->createSound(fileContent, FMOD_OPENMEMORY, 0, &m_Sound);
        FMOD_ERRCHECK(result);
        
        return (result == FMOD_OK);
    }
    
    FMOD::Channel *Sound::getChannel()
    {
        FMOD::Channel *channel = NULL;
        FMOD_RESULT result;
        
        if(m_ChannelIndex > 0)
        {
            FMOD::Sound *sound = NULL;
            channel = njli::World::getInstance()->getWorldSound()->getChannel(m_ChannelIndex);
            if(channel)
            {
                result = channel->getCurrentSound(&sound);
                if(result != FMOD_OK)
                {
                    m_ChannelIndex = -1;
                }
                else if (sound == m_Sound)
                {
                    return channel;
                }
            }
            else
            {
                m_ChannelIndex = -1;
            }
        }
        return NULL;
    }
    
    Node *Sound::getParent()
    {
        return dynamic_cast<Node*>(getParent());
    }
    
    const Node *Sound::getParent()const
    {
        return dynamic_cast<const Node*>(getParent());
    }
}
