//
//  Sound.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef __JLIGameEngineTest__Sound__
#define __JLIGameEngineTest__Sound__

#include "GraphicsPlatform.h"

#include "AbstractBuilder.h"
#include "AbstractFactoryObject.h"
#include "AbstractTransform.h"
#include "lua.hpp"

#include "SoundPlatform.h"

//#if defined(NJLI_SOUND_OPENAL)
//#define STB_VORBIS_HEADER_ONLY
//#include "stb_vorbis.c"
//#endif

#if defined(NJLI_SOUND_OPENAL)

#define PRELOAD_BUFFERS_COUNT 3

#include "btVector3.h"
struct SoundSource;
struct SoundBuffer;

typedef enum SOUND_STATE { PLAYING = 1, PAUSED = 2, STOPPED = 3 } SOUND_STATE;

typedef struct SoundSettings
{

  std::string name;
  std::string fileName;

  float pitch;
  float gain;
  bool loop;
  btVector3 pos;
  btVector3 velocity;

} SoundSettings;

typedef struct SoundInfo
{
  long freqency;
  int channels;
  int format;
  int bitsPerChannel;

  /* The below bitrate declarations are *hints*.
   Combinations of the three values carry the following implications:

   all three set to the same value:
   implies a fixed rate bitstream
   only nominal set:
   implies a VBR stream that averages the nominal bitrate.  No hard
   upper/lower limit
   upper and or lower set:
   implies a VBR bitstream that obeys the bitrate limits. nominal
   may also be set to give a nominal rate.
   none set:
   the coder does not care to speculate.
   */

  long bitrate_upper;
  long bitrate_nominal;
  long bitrate_lower;
  long bitrate_window;

  bool seekable;

} SoundInfo;

#endif

namespace njli
{

  class ISoundFileWrapper;
  class SoundBuilder;
  class Node;

  ATTRIBUTE_ALIGNED16(class)
  Sound :
      //    class Sound:
      public AbstractFactoryObject,
      public AbstractTransform
  {
    friend class WorldFactory;
    friend class WorldSound;

  protected:
    Sound();
    Sound(const AbstractBuilder &);
    Sound(const Sound &);
    BT_DECLARE_ALIGNED_ALLOCATOR();
    virtual ~Sound();
    Sound &operator=(const Sound &);

  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;
    using AbstractFactoryObject::create;
    //    using AbstractFactoryObject::clone;
    using AbstractFactoryObject::getPointer;
    using AbstractFactoryObject::getPointerValue;
    using AbstractFactoryObject::serializeObject;

    virtual s32 calculateSerializeBufferSize() const;
    virtual void serialize(void *, btSerializer *) const;

    virtual const char *getClassName() const;
    virtual s32 getType() const;
    operator std::string() const;

    static Sound **createArray(const u32 size);
    static void destroyArray(Sound * *array, const u32 size = 0);
    static Sound *create();
    static Sound *create(const SoundBuilder &builder);
    static Sound *clone(const Sound &object);
    static Sound *copy(const Sound &object);
    static void destroy(Sound * object);
    static void load(Sound & object, lua_State * L, int stack_index);
    static u32 type();

  public:
    // TODO: fill in specific methods for Sound
    f32 getTimePosition();
    void setTimePosition(f32 pos);
    f32 getTimeLength();

    bool isPlaying();
    void play(bool isPaused = false);
    void stop();

    bool isPaused();
    void pause();
    void unPause();

    bool isMuted();
    void mute();
    void unMute();

    f32 getVolume();
    void setVolume(f32 vol = 1.0f);

    s32 getLoopCount();
    void setLoopCount(s32 count);

    virtual btTransform getWorldTransform() const;

    bool load(void *system, const char *path);
    bool load(void *system, const char *fileContent, u32 size);

    Node *getParent();
    const Node *getParent() const;

#if defined(NJLI_SOUND_OPENAL)
  public:
    void update();

  protected:
    const SoundSettings &GetSettings() const;
    const SoundInfo &GetInfo() const;

    void PlayInLoop(bool val);

    float GetTime() const;
    float GetMaxBufferedTime() const;
    int GetPlayedCount() const;

    bool IsPlaying() const;

    void Release();

    void Play();
    void Pause();
    void Stop();

    void Rewind();

    void GetRawData(std::vector<char> * rawData);

    template <typename T> void GetRawDataNormalized(std::vector<T> * rawData);

    //    class ISoundFileWrapper;

    SoundSource *mSource;
    SoundBuffer *mBuffers[PRELOAD_BUFFERS_COUNT];
    int mActiveBufferID;
    int SINGLE_BUFFER_SIZE;

    SoundSettings mSettings;
    SoundInfo mSoundInfo;

    FILE *mVfsFile;
    char *mSoundData;
    int mDataSize;
    ISoundFileWrapper *mSoundFileWrapper;
    SOUND_STATE mState;
    int mRemainBuffers;
    int mPlayedCount;

    void LoadData();
    void LoadRawData(char *rawData, u32 dataSize);

    bool Preload();
    bool PreloadBuffer(int bufferID);
    void Update();

    bool mSpinLock;

    float GetBufferedTime(int buffersCount) const;

    bool mLoaded;

  private:
//    typedef struct{
//        ALuint ID;
//
//        stb_vorbis* stream;
//        stb_vorbis_info info;
//
//        ALuint buffers[2];
//        ALuint source;
//        ALenum format;
//
//        size_t bufferSize;
//
//        size_t totalSamplesLeft;
//
//        bool shouldLoop;
//    }AudioStream;
//
//    void AudioStreamInit(AudioStream* self);
//    void AudioStreamDeinit(AudioStream* self);
//    bool AudioStreamStream(AudioStream* self, ALuint buffer);
//    bool AudioStreamOpen(AudioStream* self, const char* filename);
//    bool AudioStreamUpdate(AudioStream* self);
//    bool AudioStreamPlay(AudioStream* self);
//
//    AudioStream *mAudioStream;

#elif defined(NJLI_SOUND_FMOD)
  public:
  protected:
    FMOD::Channel *getChannel();

  private:
    FMOD::Sound *m_Sound;
    s32 m_ChannelIndex;
    btTransform *m_Transform;
#elif defined(NJLI_SOUND_SDL)
#endif
  };
}

#endif /* defined(__JLIGameEngineTest__Sound__) */
