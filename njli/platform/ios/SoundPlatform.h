#if defined(__FMOD__)
#include "fmod.hpp"
#include "fmod_errors.h"
#elif defined(__OPENAL__)
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#elif defined(__SDL__)
#include "SDL_audio.h"
#else
#error Unsupported choice setting
#endif

bool setupSoundPlatform();
