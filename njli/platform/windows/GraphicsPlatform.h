
#if defined(__GL_ES2__)
#error Unsupported choice setting
#elif defined(__GL_ES3__)
#error Unsupported choice setting
#elif defined(__GL_2__)
//// For historical reasons the windows.h file includes Winsock.h which has been replaced by and is incompatible with Winsock2.h
//// WIN32_LEAN_AND_MEAN prevents Winsock.h from being included
#define WIN32_LEAN_AND_MEAN
//
#ifndef NOMINMAX
#define NOMINMAX
#endif

#undef near
#undef far

#undef min
#undef max

//#define NOGDI

#include <windows.h>

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#define glGenVertexArrays_NJLIC glGenVertexArrays
#define glBindVertexArray_NJLIC glBindVertexArray
#define glDeleteVertexArrays_NJLIC glDeleteVertexArrays

#define NANOVG_GL2_IMPLEMENTATION

#elif defined(__GL_3__)
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#define NANOVG_GL3_IMPLEMENTATION
#else
#error Unsupported choice setting
#endif

#ifndef __WINDOWS32__
#define __WINDOWS32__
#endif

