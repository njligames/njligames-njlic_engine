
#if defined(NJLI_GL_ES2)
#error Unsupported choice setting
#elif defined(NJLI_GL_ES3)
#error Unsupported choice setting
#elif defined(NJLI_GL_2)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#define NANOVG_GL2_IMPLEMENTATION
#elif defined(NJLI_GL_3)
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#define NANOVG_GL3_IMPLEMENTATION
#else
#error Unsupported choice setting
#endif

#ifndef __MACOSX__
#define __MACOSX__
#endif

#define USE_FMOD
