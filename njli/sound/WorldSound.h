//#include "AbstractSingleton.h"
#ifndef __JLIGameEngineTest__WorldSound__
#define __JLIGameEngineTest__WorldSound__

//#include "SoundPlatform.h"

#include "GraphicsPlatform.h"
#include "SoundPlatform.h"

#include "AbstractObject.h"
#include "Util.h"
#include <string>

#include "Sound.h"
#include <list>
#include <unordered_map>
#include <vector>
class ISoundFileWrapper;

//#if !(defined(NDEBUG))
//#define FMOD_LOGGING_ON 1
//#else
//#define FMOD_LOGGING_ON 0
//#endif

// http://www.ogre3d.org/tikiwiki/tiki-index.php?page=FMOD+SoundManager

#if defined(NJLI_SOUND_OPENAL)
typedef struct SoundBuffer
{
  bool free;
  u32 refID;
} SoundBuffer;

typedef struct SoundSource
{
  bool free;
  u32 refID;
} SoundSource;
#endif

namespace njli
{
  class Sound;

  class WorldSound : public AbstractObject
  {
    //    friend class WorldResourceLoader;
    friend class Sound;
    friend class World;

  public:
    using AbstractDecorator::setName;
    using AbstractDecorator::getName;

    WorldSound();
    ~WorldSound();

    virtual const s8 *getClassName() const;
    virtual s32 getType() const;
    virtual operator std::string() const;

    void enablePause(bool enable = true);

    //    bool createSound(const char* fileContent, size_t file_size, Sound&
    //    sound);
    //    bool createSound(const char *path, Sound& sound);

    bool loadSound(const char *path, Sound &sound);
    bool loadSound(const char *fileContent, u32 file_size, Sound &sound);
    bool unLoadSound(const Sound &sound);

  protected:
    void update();

    void playSound(Sound &sound, bool isPaused = false);

#if defined(NJLI_SOUND_OPENAL)
  protected:
    ALCdevice *mDeviceAL;
    ALCcontext *mContextAL;
    std::string mDeviceName;

    //    pthread_t updateThread;
    //    pthread_mutex_t fakeMutex;
    //    pthread_cond_t fakeCond;
    //    bool useThreadUpdate;
    //    bool ended;

    bool mEnabled;
    float mLastVolume;

    float mMasterVolume;

    std::unordered_map<std::string, Sound *> mSounds;

    std::vector<SoundSource> mSources;
    std::vector<SoundBuffer> mBuffers;

    std::list<SoundSource *> mFreeSources;
    std::list<SoundBuffer *> mFreeBuffers;

    void Init();

    SoundSource *GetFreeSource();
    SoundBuffer *GetFreeBuffer();

    void FreeSource(SoundSource *source);
    void FreeBuffer(SoundBuffer *buffer);

    bool ExistSound(const std::string &name) const;
    void ReleaseSound(const std::string &name);
    //    void AddSound(const std::string & fileName, const std::string & name);
    void AddSound(Sound *sound);

    Sound *GetSound(const std::string &name);

    void Update();

    void SetMasterVolume(float volume);
    void VolumeUp(float amount = 0.1f);
    void VolumeDown(float amount = 0.1f);

    bool IsEnabled();
    void Disable();
    void Enable();

  private:
//    // OpenAL context for playing sounds
//    ALCcontext* m_ALCcontext;
//    // The device we are going to use to play sounds
//    ALCdevice* m_ALCdevice;
//    std::vector<Sound*> mSounds;
//    std::vector<Sound*> mPlayingSounds;

#elif defined(NJLI_SOUND_FMOD)
  protected:
    FMOD::Channel *getChannel(s32 channelindex);

  private:
    FMOD::System *m_System;
    FMOD::ChannelGroup *m_MasterChannel;
    int *m_ChannelsPlaying;
#elif defined(NJLI_SOUND_SDL)
#endif
  };
}

#endif
