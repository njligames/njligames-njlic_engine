#include "WorldSound.h"
#include "Log.h"
#define TAG "WorldSound.mm"
#include "JLIFactoryTypes.h"
#include "Sound.h"
#if defined (__IOS__)
#import <AVFoundation/AVAudioSession.h>
#import <Foundation/Foundation.h>
#endif
#define FORMATSTRING "{\"njli::WorldSound\":[]}"
#include "btPrint.h"
#include "JsonJLI.h"

#include "File.h"

#include "btQuickprof.h"
#include "SDL_log.h"
#include "android_file.h"

#define MAXCHANNELS (32)

//void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line);
#define FMOD_ERRCHECK(_result) do { if (FMOD_LOGGING_ON) ERRCHECK_fn(_result, __FILE__, __LINE__); } while (0)

//void FMOD_ERRCHECK(FMOD_RESULT _result)
//{
//    do { if (FMOD_LOGGING_ON) ERRCHECK_fn(_result, __FILE__, __LINE__); } while (0);
//}

FMOD_RESULT F_CALLBACK fmodDebugCallback(FMOD_DEBUG_FLAGS flags, const char *file, int line, const char *func, const char *message)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_DEBUG_CALLBACK occured.\n");
    return FMOD_OK;
}

float  F_CALLBACK fmod3DRolloffCallback(FMOD_CHANNELCONTROL *channelcontrol, float distance)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_3D_ROLLOFF_CALLBACK occured.\n");
    return 0;
}

// fileName is actually a pointer to a SoundInstance, passed in from CreateSound().
FMOD_RESULT F_CALLBACK fmodFileOpenCallback(const char *name, unsigned int *filesize, void **handle, void *userdata)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_FILE_OPEN_CALLBACK occured.\n");
    *handle = mobile__fopen(name, "r");
    //    SoundInstance *soundInstance;
    //
    //    assert(fileName);
    //
    //    soundInstance = (SoundInstance *)fileName;
    //    assert(soundInstance->fileArchive);
    //
    //    *handle = (void *)soundInstance;
    //    *userdata = NULL;
    //
    //    soundInstance->streamPtr = soundInstance->fileArchive->open(soundInstance->fileName);
    //    if (soundInstance->streamPtr.isNull())
    //    {
    //        *filesize = 0;
    //        return FMOD_ERR_FILE_NOTFOUND;
    //    }
    //
    //    *filesize = (unsigned int)soundInstance->streamPtr->size();
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileCloseCallback(void *handle, void *userdata)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_FILE_CLOSE_CALLBACK occured.\n");
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileReadCallback(void *handle, void *buffer, unsigned int sizeBytes, unsigned int *bytesRead, void *userData)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_FILE_READ_CALLBACK occured.\n");
    //    SoundInstance *soundInstance;
    //
    //    soundInstance = (SoundInstance *)handle;
    //    *bytesRead = (unsigned int)soundInstance->streamPtr->read(buffer, (size_t)sizeBytes);
    //    if (*bytesRead == 0)
    //        return FMOD_ERR_FILE_EOF;
    
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileSeekCallback(void *handle, unsigned int pos, void *userdata)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_FILE_SEEK_CALLBACK occured.\n");
    //    SoundInstance *soundInstance;
    //
    //    soundInstance = (SoundInstance *)handle;
    //    soundInstance->streamPtr->seek((size_t)pos);
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileAsyncReadCallback(FMOD_ASYNCREADINFO *info, void *userdata)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_FILE_ASYNCREAD_CALLBACK occured.\n");
    return FMOD_OK;
}

FMOD_RESULT F_CALLBACK fmodFileAsyncCancelCallback(FMOD_ASYNCREADINFO *info, void *userdata)
{
    if(FMOD_LOGGING_ON)
        SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_FILE_ASYNCCANCEL_CALLBACK occured.\n");
    return FMOD_OK;
}

static FMOD_RESULT F_CALLBACK fmodErrorCallback(FMOD_DEBUG_FLAGS flags, const char *file, int line, const char *func, const char *message)
{
    
    //MOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG
    switch (flags)
    {
        case FMOD_DEBUG_LEVEL_ERROR:
            SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s - %d - %s - %s\n", file, line, func, message);
            break;
        case FMOD_DEBUG_LEVEL_WARNING:
            SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "%s - %d - %s - %s\n", file, line, func, message);
            break;
        case FMOD_DEBUG_LEVEL_LOG:
            SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s - %d - %s - %s\n", file, line, func, message);
            break;
        default:
            break;
    }
    
    return FMOD_OK;
}

//http://www.fmod.org/docs/content/generated/FMOD_SYSTEM_CALLBACK.html
static FMOD_RESULT F_CALLBACK fmodSystemcallback(FMOD_SYSTEM *system, FMOD_SYSTEM_CALLBACK_TYPE type, void *commanddata1, void *commanddata2, void* userdata)
{
    FMOD::System *sys = (FMOD::System *)system;
    
    switch (type)
    {
        case FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED:
        {
            int numdrivers;
            
            if(FMOD_LOGGING_ON)
                SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_DEVICELISTCHANGED occured.\n");
            
            sys->getNumDrivers(&numdrivers);
            
            if(FMOD_LOGGING_ON)
                SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Numdevices = %d\n", numdrivers);
        }
            break;
        case FMOD_SYSTEM_CALLBACK_DEVICELOST:
        {
            if(FMOD_LOGGING_ON)
                SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_DEVICELOST occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_MEMORYALLOCATIONFAILED:
        {
            if(FMOD_LOGGING_ON)
                SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "ERROR : FMOD_SYSTEM_CALLBACK_MEMORYALLOCATIONFAILED occured.\n");
            if(FMOD_LOGGING_ON)
                SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s.\n", commanddata1);
            if(FMOD_LOGGING_ON)
                SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%d bytes.\n", commanddata2);
        }
            break;
        case FMOD_SYSTEM_CALLBACK_THREADCREATED:
        {
            if(FMOD_LOGGING_ON)
                SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_THREADCREATED occured.\n");
            //            if(FMOD_LOGGING_ON)SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Thread ID = %d\n", (int)commanddata1);
            //            if(FMOD_LOGGING_ON)SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "Thread Name = %s\n", (char *)commanddata2);
        }
            break;
        case FMOD_SYSTEM_CALLBACK_BADDSPCONNECTION:
        {
            FMOD::DSP *source = (FMOD::DSP *)commanddata1;
            FMOD::DSP *dest = (FMOD::DSP *)commanddata2;
            
            if(FMOD_LOGGING_ON)
                SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "ERROR : FMOD_SYSTEM_CALLBACK_BADDSPCONNECTION occured.\n");
            if (source)
            {
                char name[256];
                source->getInfo(name, 0,0,0,0);
                if(FMOD_LOGGING_ON)
                    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "SOURCE = %s\n", name);
            }
            if (dest)
            {
                char name[256];
                dest->getInfo(name, 0,0,0,0);
                if(FMOD_LOGGING_ON)
                    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "DEST = %s\n", name);
            }
        }
            break;
        case FMOD_SYSTEM_CALLBACK_PREMIX:
        {
            //            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_PREMIX occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_POSTMIX:
        {
            //            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_POSTMIX occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_ERROR:
        {
            /*
             typedef struct {
             FMOD_RESULT result;
             FMOD_ERRORCALLBACK_INSTANCETYPE instancetype;
             void *instance;
             const char *functionname;
             const char *functionparams;
             } FMOD_ERRORCALLBACK_INFO;
             */
            FMOD_ERRORCALLBACK_INFO *errorInfo = (FMOD_ERRORCALLBACK_INFO *)commanddata1;
            switch (errorInfo->instancetype)
            {
                case FMOD_ERRORCALLBACK_INSTANCETYPE_NONE:
                {
                    if(FMOD_LOGGING_ON)
                        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_SYSTEM:
                {
                    FMOD::System *ptr = (FMOD::System*)errorInfo->instance;
                    
                    if(FMOD_LOGGING_ON)
                        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNEL:
                {
                    FMOD::Channel *ptr = (FMOD::Channel*)errorInfo->instance;
                    
                    if(FMOD_LOGGING_ON)
                        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELGROUP:
                {
                    FMOD::ChannelGroup *ptr = (FMOD::ChannelGroup*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)
                        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_CHANNELCONTROL:
                {
                    FMOD::ChannelControl *ptr = (FMOD::ChannelControl*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)
                        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_SOUND:
                {
                    FMOD::Sound *ptr = (FMOD::Sound*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)
                        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_SOUNDGROUP:
                {
                    FMOD::SoundGroup *ptr = (FMOD::SoundGroup*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_DSP:
                {
                    FMOD::DSP *ptr = (FMOD::DSP*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_DSPCONNECTION:
                {
                    FMOD::DSPConnection *ptr = (FMOD::DSPConnection*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_GEOMETRY:
                {
                    FMOD::Geometry *ptr = (FMOD::Geometry*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_REVERB3D:
                {
                    FMOD::Reverb3D *ptr = (FMOD::Reverb3D*)errorInfo->instance;
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_SYSTEM:
                {
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTDESCRIPTION:
                {
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_EVENTINSTANCE:
                {
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_PARAMETERINSTANCE:
                {
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                    //                    case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_CUEINSTANCE:
                    //                {
                    //                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    //
                    //                }
                    //                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BUS:
                {
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_VCA:
                {
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                case FMOD_ERRORCALLBACK_INSTANCETYPE_STUDIO_BANK:
                {
                    if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%s)", errorInfo->functionname, errorInfo->functionparams);
                    
                }
                    break;
                    
                default:
                    break;
            }
            //            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_ERROR occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_MIDMIX:
        {
            //            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_MIDMIX occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_THREADDESTROYED:
        {
            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_THREADDESTROYED occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_PREUPDATE:
        {
            //            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_PREUPDATE occured.\n");
        }
            break;
        case FMOD_SYSTEM_CALLBACK_POSTUPDATE:
        {
            //            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "NOTE : FMOD_SYSTEM_CALLBACK_POSTUPDATE occured.\n");
        }
            break;
    }
    
    return FMOD_OK;
}

void ERRCHECK_fn(FMOD_RESULT result, const char *file, int line)
{
    if (result != FMOD_OK)
    {
        SDL_LogError(SDL_LOG_CATEGORY_TEST, "%s(%d): FMOD error %d - %s", file, line, result, FMOD_ErrorString(result));
    }
}



//@interface AudioBufferPlayer : NSObject <AVAudioSessionDelegate>
//@end
//
//@implementation AudioBufferPlayer
//- (void)beginInterruption
//{
//}
//
//- (void)endInterruption
//{
//}
//@end


//static void interruptionListenerCallback(void *inUserData, UInt32 interruptionState)
//{
//    if (interruptionState == kAudioSessionBeginInterruption)
//    {
////        gSuspendState = true;
//    }
//    else if (interruptionState == kAudioSessionEndInterruption)
//    {
////        UInt32 sessionCategory = kAudioSessionCategory_PlayAndRecord;
////        AudioSessionSetProperty(kAudioSessionProperty_AudioCategory, sizeof(sessionCategory), &sessionCategory);
////        AudioSessionSetActive(true);
//
////        gSuspendState = false;
//    }
//}

namespace njli
{
    WorldSound::WorldSound()
    {
#if defined (__IOS__)
        BOOL success = NO;
        NSError *error = nil;
        AVAudioSession *session = [AVAudioSession sharedInstance];
        
        success = [session setCategory:AVAudioSessionCategoryPlayback error:&error];
        if(FMOD_LOGGING_ON)SDL_assertPrint(success, "%s", [[error localizedDescription] UTF8String]);
        
        success = [session setActive:YES error:&error];
        if(FMOD_LOGGING_ON)
            SDL_assertPrint(success, "%s", [[error localizedDescription] UTF8String]);
#endif
        FMOD_RESULT   result        = FMOD_OK;
        unsigned int  version       = 0;
        
        FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG, FMOD_DEBUG_MODE_CALLBACK, fmodErrorCallback);
//        FMOD::Debug_Initialize(FMOD_DEBUG_LEVEL_NONE | FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG);
        
        result = FMOD::System_Create(&m_System);
        FMOD_ERRCHECK(result);
        
        result = m_System->getVersion(&version);
        FMOD_ERRCHECK(result);
        
//                s32 d = FMOD_DEBUG_LEVEL_ERROR | FMOD_DEBUG_LEVEL_WARNING | FMOD_DEBUG_LEVEL_LOG | FMOD_DEBUG_TYPE_MEMORY | FMOD_DEBUG_TYPE_FILE | FMOD_DEBUG_TYPE_CODEC | FMOD_DEBUG_TYPE_TRACE | FMOD_DEBUG_DISPLAY_TIMESTAMPS | FMOD_DEBUG_DISPLAY_LINENUMBERS | FMOD_DEBUG_DISPLAY_THREAD;
//                result = FMOD::Debug_Initialize(d, FMOD_DEBUG_MODE_TTY, fmodDebugCallback);
//                FMOD_ERRCHECK(result);
        
        if (version < FMOD_VERSION)
        {
            if(FMOD_LOGGING_ON)SDL_LogError(SDL_LOG_CATEGORY_TEST, "FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
        }
        result = m_System->init(MAXCHANNELS, FMOD_INIT_NORMAL, 0);
        FMOD_ERRCHECK(result);
        
        result = m_System->setCallback(fmodSystemcallback);
        FMOD_ERRCHECK(result);
        
//        result = m_System->setFileSystem(fmodFileOpenCallback, fmodFileCloseCallback, fmodFileReadCallback, fmodFileSeekCallback, fmodFileAsyncReadCallback, fmodFileAsyncCancelCallback, 2048);
//        FMOD_ERRCHECK(result);
        
        result = m_System->set3DRolloffCallback(fmod3DRolloffCallback);
        FMOD_ERRCHECK(result);
        
    }
    WorldSound::~WorldSound()
    {
        FMOD_RESULT   result        = FMOD_OK;
        
        result = m_System->close();
        FMOD_ERRCHECK(result);
        result = m_System->release();
        FMOD_ERRCHECK(result);
        
#if defined (__IOS__)
        NSError *error = nil;
        BOOL success = [[AVAudioSession sharedInstance] setActive:NO error:&error];
        if(FMOD_LOGGING_ON)
            SDL_assertPrint(success, "%s", [[error localizedDescription] UTF8String]);
#endif
    }
    
    const s8 *WorldSound::getClassName()const
    {
        return "WorldSound";
    }
    
    s32 WorldSound::getType()const
    {
        return JLI_OBJECT_TYPE_WorldSound;
    }
    
    WorldSound::operator std::string() const
    {
        return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
    }
    
    void WorldSound::update()
    {
        BT_PROFILE("WorldSound::update");
        FMOD_RESULT result = m_System->update();
        FMOD_ERRCHECK(result);
    }
    
    void WorldSound::playSound(Sound &sound, bool isPaused)
    {
        if(sound.m_Sound)
        {
            FMOD_RESULT   result        = FMOD_OK;
            FMOD::Channel *channel = NULL;
            result = m_System->playSound(sound.m_Sound, 0, isPaused, &channel);
            FMOD_ERRCHECK(result);
            
            if(channel)
            {
                result = channel->getIndex(&sound.m_ChannelIndex);
                FMOD_ERRCHECK(result);
            }
        }
        else
        {
            if(FMOD_LOGGING_ON)SDL_LogWarn(SDL_LOG_CATEGORY_TEST, "The sound is not loaded");
        }
    }
    
//    bool WorldSound::createSound(const char *path, Sound& sound)
//    {
//        FMOD::Sound * s = 0;
//        FMOD_RESULT result = m_System->createSound(ASSET_PATH(path), FMOD_LOOP_NORMAL, 0, &s);
//        FMOD_ERRCHECK(result);
//        sound.m_Sound = s;
//        sound.m_Mode = FMOD_LOOP_NORMAL;
//        
//        return (result == FMOD_OK);
//    }
//    bool WorldSound::createSound(const char *fileContent, size_t file_size, Sound &sound)
//    {
//        FMOD_CREATESOUNDEXINFO info;
//        memset(&info, 0, sizeof(FMOD_CREATESOUNDEXINFO));
//        info.cbsize = sizeof(FMOD_CREATESOUNDEXINFO);
//        info.length = file_size;
////        info.format = FMOD_SOUND_FORMAT_PCM16;
//        info.numchannels = 1;
//        
//        info.suggestedsoundtype = FMOD_SOUND_TYPE_WAV;
//        
////        info.defaultfrequency = 44100;
//        
//        //channels 1, format 2, freq 44100, mode 00000809
//        
//        FMOD::Sound * s = 0;
//        FMOD_MODE mode = FMOD_OPENMEMORY;// | FMOD_LOOP_OFF | FMOD_OPENRAW;
//        //        FMOD_MODE mode = FMOD_DEFAULT | FMOD_LOOP_OFF;
////        FMOD_RESULT result = m_System->createSound(fileContent, mode, &info, &s);
//        FMOD_RESULT result = m_System->createSound(fileContent, FMOD_OPENMEMORY, 0, &s);
//        FMOD_ERRCHECK(result);
//        sound.m_Sound = s;
//        sound.m_Mode = mode;
//        
//        return (result == FMOD_OK);
//    }
    
    bool WorldSound::loadSound(const char *path, Sound& sound)
    {
        return sound.load(m_System, path);
    }
    
    bool WorldSound::loadSound(const char* path, u32 size, Sound& sound)
    {
        return sound.load(m_System, path, size);
    }

    bool WorldSound::unLoadSound(const Sound &sound)
    {
        return true;
    }
    
    void WorldSound::enablePause(bool enable)
    {
        if (enable)
        {
            m_System->mixerSuspend();
        }
        else
        {
            m_System->mixerResume();
        }
        
#if defined (__IOS__)
        BOOL success = NO;
        NSError *error = nil;
        AVAudioSession *session = [AVAudioSession sharedInstance];
        
        success = [session setCategory:AVAudioSessionCategoryPlayback error:&error];
        success = [session setActive:(enable)?NO:YES error:&error];
#endif
    }
    
    FMOD::Channel *WorldSound::getChannel(s32 channelindex)
    {
        
        //        int channels;
        //        m_System->getChannelsPlaying(&channels);
        //        
        //        if(FMOD_LOGGING_ON)SDL_LogDebug(SDL_LOG_CATEGORY_TEST, "Number of Channels Playing %d", channels);
        
        FMOD::Channel *channel;
        m_System->getChannel(channelindex, &channel);
        return channel;
    }
}
