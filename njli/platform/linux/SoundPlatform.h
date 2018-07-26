#if defined(__FMOD__)
#include "fmod.hpp"
#include "fmod_errors.h"
#elif defined(__OPENAL__)
#include <AL/al.h>
#include <AL/alc.h>
#elif defined(__SDL_SOUND__)
#include "SDL_audio.h"
#else
#error Unsupported choice setting
#endif
