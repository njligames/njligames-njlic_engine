#if defined(NJLI_SOUND_FMOD)
#include "fmod.hpp"
#include "fmod_errors.h"
#elif defined(NJLI_SOUND_OPENAL)
#include <AL/al.h>
#include <AL/alc.h>
#elif defined(NJLI_SOUND_SDL)
#include "SDL_audio.h"
#else
#error Unsupported choice setting
#endif
