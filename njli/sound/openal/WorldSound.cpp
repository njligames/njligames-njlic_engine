#include "WorldSound.h"
#include "Log.h"
#define TAG "WorldSound.mm"
#include "JLIFactoryTypes.h"
#include "Sound.h"

#include "File.h"

#define MAXCHANNELS (32)

// https://www.gamedev.net/resources/_/technical/game-programming/basic-openal-sound-manager-for-your-project-r3791

static const char *GetOpenALErrorString(int errID)
{
  if (errID == AL_NO_ERROR)
    return "";
  if (errID == AL_INVALID_NAME)
    return "Invalid name";
  if (errID == AL_INVALID_ENUM)
    return " Invalid enum ";
  if (errID == AL_INVALID_VALUE)
    return " Invalid value ";
  if (errID == AL_INVALID_OPERATION)
    return " Invalid operation ";
  if (errID == AL_OUT_OF_MEMORY)
    return " Out of memory like! ";

  return " Don't know ";
}

static inline void CheckOpenALError(const char *stmt, const char *fname,
                                    int line)
{

  ALenum err = alGetError();
  if (err != AL_NO_ERROR)
    {
      SDL_Log("OpenAL error %08x, (%s) at %s:%i - for %s", err,
              GetOpenALErrorString(err), fname, line, stmt);
    }
};

#ifndef AL_CHECK
//#if !(defined(NDEBUG))
#define AL_CHECK(stmt)                                                         \
  do                                                                           \
    {                                                                          \
      stmt;                                                                    \
      CheckOpenALError(#stmt, __FILE__, __LINE__);                             \
    }                                                                          \
  while (0);
#else
#define AL_CHECK(stmt) stmt
//#endif
#endif

// https://www.gamedev.net/resources/_/technical/game-programming/basic-openal-sound-manager-for-your-project-r3791
// https://www.pcworld.idg.com.au/article/62412/audio_compression_formats_compared/
// https://ffainelli.github.io/openal-example/

//#define TEST_ERROR(_msg) \
//if (alGetError() != AL_NO_ERROR) {	\
//SDL_Log("%s", _msg); \
//}

// static inline ALenum to_al_format(short channels, short samples)
//{
//    bool stereo = (channels > 1);
//
//    switch (samples) {
//        case 16:
//            if (stereo)
//                return AL_FORMAT_STEREO16;
//            else
//                return AL_FORMAT_MONO16;
//        case 8:
//            if (stereo)
//                return AL_FORMAT_STEREO8;
//            else
//                return AL_FORMAT_MONO8;
//        default:
//            return -1;
//    }
//}
//
// static void list_audio_devices(const ALCchar *devices)
//{
//    const ALCchar *device = devices, *next = devices + 1;
//    size_t len = 0;
//
//    SDL_Log("%s", "Devices list:\n");
//    SDL_Log("%s", "----------\n");
//    while (device && *device != '\0' && next && *next != '\0') {
//        SDL_Log("%s", device);
//        len = strlen(device);
//        device += (len + 1);
//        next += (len + 2);
//    }
//    SDL_Log("%s", "----------\n");
//}

namespace njli
{
  WorldSound::WorldSound()
      : mDeviceAL(NULL), mContextAL(NULL), mDeviceName(""), mEnabled(false),
        mLastVolume(1.0f), mMasterVolume(1.0f)
  {
    Init();
    //        ALboolean enumeration = alcIsExtensionPresent(NULL,
    //        "ALC_ENUMERATION_EXT");
    //        if (enumeration == AL_FALSE)
    //            fprintf(stderr, "enumeration extension not available\n");
    //
    //        list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    //
    //        const ALCchar *defaultDeviceName = alcGetString(NULL,
    //        ALC_DEFAULT_DEVICE_SPECIFIER);
    //
    //        m_ALCdevice = alcOpenDevice(defaultDeviceName);
    //        if (!m_ALCdevice)
    //        {
    //            SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s", "unable to open
    //            default device\n");
    //        }
    //
    //        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Device: %s\n",
    //        alcGetString(m_ALCdevice, ALC_DEVICE_SPECIFIER));
    //
    //        TEST_ERROR("make default device");
    //
    //        m_ALCcontext = alcCreateContext(m_ALCdevice, NULL);
    //        if (!alcMakeContextCurrent(m_ALCcontext)) {
    //            SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s", "failed to make
    //            default context\n");
    //        }
    //        TEST_ERROR("make default context");
    //
    //        ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    //        /* set orientation */
    //        alListener3f(AL_POSITION, 0, 0, 1.0f);
    //        TEST_ERROR("listener position");
    //        alListener3f(AL_VELOCITY, 0, 0, 0);
    //        TEST_ERROR("listener velocity");
    //        alListenerfv(AL_ORIENTATION, listenerOri);
    //        TEST_ERROR("listener orientation");
  }
  WorldSound::~WorldSound()
  {
    //        this->ended = true;
    //
    //        if (this->useThreadUpdate)
    //        {
    //            pthread_join(this->updateThread, NULL);
    //        }

    std::unordered_map<std::string, Sound *>::iterator it;
    for (it = mSounds.begin(); it != mSounds.end(); it++)
      {
        it->second->stop();
        //            SAFE_DELETE(it->second);
      }

    mSounds.clear();

    for (u32 i = 0; i < mBuffers.size(); i++)
      {
        SoundBuffer buffer = mBuffers[i];
        AL_CHECK(alDeleteBuffers(1, &buffer.refID));
      }

    for (u32 i = 0; i < mSources.size(); i++)
      {
        AL_CHECK(alDeleteSources(1, &mSources[i].refID));
      }

    alcDestroyContext(mContextAL);
    alcCloseDevice(mDeviceAL);

    //        alcMakeContextCurrent(NULL);
    //        alcDestroyContext(m_ALCcontext);
    //        alcCloseDevice(m_ALCdevice);
  }

  const s8 *WorldSound::getClassName() const { return "WorldSound"; }

  s32 WorldSound::getType() const { return JLI_OBJECT_TYPE_WorldSound; }

  WorldSound::operator std::string() const { return std::string("TODO"); }

  void WorldSound::update()
  {
    //        for (std::vector<Sound*>::iterator i = mPlayingSounds.begin(); i
    //        != mPlayingSounds.end(); )
    //        {
    //            Sound *sound = *i;
    //
    //            sound->update();
    //
    //            if(sound->isPlaying())
    //            {
    //                i++;
    //            }
    //            else
    //            {
    //                i = mPlayingSounds.erase(i);
    //            }
    //        }
    Update();
  }

  void WorldSound::playSound(Sound &sound, bool isPaused)
  {
    //        mPlayingSounds.push_back(&sound);
  }

  bool WorldSound::loadSound(const char *path, Sound &sound)
  {
    if (sound.load(NULL, path))
      {
        AddSound(&sound);
        return true;
      }
    //        if(sound.load(NULL, path))
    //        {
    //            mSounds.push_back(&sound);
    //            return true;
    //        }
    return false;
  }

  bool WorldSound::loadSound(const char *fileContent, u32 size, Sound &sound)
  {
    //        return sound.load(NULL, fileContent, size);
    return false;
  }

  bool WorldSound::unLoadSound(const Sound &sound) { return true; }

  void WorldSound::enablePause(bool enable)
  {
    if (enable)
      {
      }
    else
      {
      }
  }

  void WorldSound::Init()
  {
    // reset error stack
    alGetError();

    mDeviceAL = alcOpenDevice(NULL);

    if (mDeviceAL == NULL)
      {
        SDL_Log("Failed to init OpenAL device.");
        return;
      }

    mContextAL = alcCreateContext(mDeviceAL, NULL);
    AL_CHECK(alcMakeContextCurrent(mContextAL));

    for (int i = 0; i < 512; i++)
      {
        SoundBuffer buffer;
        AL_CHECK(alGenBuffers((ALuint)1, &buffer.refID));
        mBuffers.push_back(buffer);
      }

    for (int i = 0; i < 16; i++)
      {
        SoundSource source;
        AL_CHECK(alGenSources((ALuint)1, &source.refID));
        mSources.push_back(source);
      }

    for (u32 i = 0; i < mBuffers.size(); i++)
      {
        mFreeBuffers.push_back(&mBuffers[i]);
      }

    for (u32 i = 0; i < mSources.size(); i++)
      {
        mFreeSources.push_back(&mSources[i]);
      }

    //        if (this->useThreadUpdate)
    //        {
    //            this->fakeMutex = PTHREAD_MUTEX_INITIALIZER;
    //            this->fakeCond = PTHREAD_COND_INITIALIZER;
    //
    //            if(pthread_create(&this->updateThread, NULL,
    //            &WorldSound::UpdateThread, this))
    //            {
    //                SDL_Log("Error creating thread");
    //                return;
    //            }
    //        }
  }

  SoundSource *WorldSound::GetFreeSource()
  {
    if (mFreeSources.size() == 0)
      {
        return NULL;
      }

    SoundSource *source = mFreeSources.front();
    mFreeSources.pop_front();
    source->free = false;

    return source;
  }

  SoundBuffer *WorldSound::GetFreeBuffer()
  {
    if (mFreeBuffers.size() == 0)
      {
        return NULL;
      }

    SoundBuffer *buf = mFreeBuffers.front();
    mFreeBuffers.pop_front();
    buf->free = false;

    return buf;
  }

  void WorldSound::FreeSource(SoundSource *source)
  {
    if (source == NULL)
      {
        return;
      }
    source->free = true;
    mFreeSources.push_back(source);
  }

  void WorldSound::FreeBuffer(SoundBuffer *buffer)
  {
    if (buffer == NULL)
      {
        return;
      }

    AL_CHECK(alDeleteBuffers(1, &buffer->refID));
    AL_CHECK(alGenBuffers(1, &buffer->refID));

    buffer->free = true;
    mFreeBuffers.push_back(buffer);
  }

  bool WorldSound::ExistSound(const std::string &name) const
  {
    if (mSounds.find(name) == mSounds.end())
      {
        return false;
      }

    return true;
  }

  void WorldSound::ReleaseSound(const std::string &name)
  {
    if (!this->ExistSound(name))
      {
        return;
      }

    mSounds[name]->stop();
    //        SAFE_DELETE(mSounds[name]);
    mSounds.erase(mSounds.find(name));
  }

  //    void WorldSound::AddSound(const std::string & fileName, const
  //    std::string & name)
  //    {
  //        if (this->ExistSound(name))
  //        {
  //            SDL_Log("Sound with name %s already exist.", name.c_str());
  //            return;
  //        }
  //
  //        Sound * sound = new Sound(fileName, name);
  //        mSounds.insert(std::make_pair(name, sound));
  //
  //        //sound->Play();
  //    }

  void WorldSound::AddSound(Sound *sound)
  {

    std::string name = sound->getName();
    if (this->ExistSound(name))
      {
        SDL_Log("Sound with name %s already exist.", name.c_str());
        return;
      }

    mSounds.insert(std::make_pair(name, sound));

    // sound->Play();
  }

  Sound *WorldSound::GetSound(const std::string &name)
  {
    if (!this->ExistSound(name))
      {
        return NULL;
      }

    return mSounds[name];
  }

  void WorldSound::Update()
  {
    std::unordered_map<std::string, Sound *>::iterator it;

    for (it = mSounds.begin(); it != mSounds.end(); it++)
      {
        if (it->second->isPlaying())
          {
            it->second->update();
          }
      }
  }

  void WorldSound::SetMasterVolume(float volume)
  {
    mMasterVolume = (volume < 0.0f) ? 0.0f : (volume > 1.0f) ? 1.0f : volume;
    AL_CHECK(alListenerf(AL_GAIN, mMasterVolume));
  }

  void WorldSound::VolumeUp(float amount)
  {
    this->SetMasterVolume(mMasterVolume + amount);
  }

  void WorldSound::VolumeDown(float amount)
  {
    this->SetMasterVolume(mMasterVolume - amount);
  }

  bool WorldSound::IsEnabled() { return mEnabled; }

  void WorldSound::Disable()
  {
    if (mEnabled == false)
      {
        return;
      }

    mEnabled = false;
    mLastVolume = mMasterVolume; // store last volume

    this->SetMasterVolume(0.0f);
  }

  void WorldSound::Enable()
  {
    if (mEnabled)
      {
        return;
      }
    mEnabled = true;

    this->SetMasterVolume(mLastVolume); // restore volume
  }
}
