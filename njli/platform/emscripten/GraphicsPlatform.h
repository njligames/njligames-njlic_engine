
#if defined(__GL_ES2__)
    #define glGenVertexArrays_NJLIC glGenVertexArraysOES
    #define glBindVertexArray_NJLIC glBindVertexArrayOES
    #define glDeleteVertexArrays_NJLIC glDeleteVertexArraysOES

    #define GL_GLEXT_PROTOTYPES

    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #include <GLES2/gl2platform.h>

    #define NANOVG_GLES2_IMPLEMENTATION
#elif defined(__GL_ES3__)
    #include <GLES3/gl3.h>
    #include <GLES3/gl2ext.h>
    #include <GLES3/gl3platform.h>
    #include <GLES3/gl31.h>
    #include <GLES3/gl32.h>
    #define NANOVG_GLES3_IMPLEMENTATION
#elif defined(__GL_2__)
#error Unsupported choice setting
#elif defined(__GL_3__)
    #error Unsupported choice setting
#else
    #error Unsupported choice setting
#endif

#ifndef __EMSCRIPTEN__
#define __EMSCRIPTEN__
#endif

#define USE_OPENAL
