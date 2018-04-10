
#if defined(NJLI_GL_ES2)
    #define GL_GLEXT_PROTOTYPES
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #include <GLES2/gl2platform.h>
    #define NANOVG_GLES2_IMPLEMENTATION
#elif defined(NJLI_GL_ES3)
    #include <GLES3/gl3.h>
    #include <GLES3/gl2ext.h>
    #include <GLES3/gl3platform.h>
    #include <GLES3/gl31.h>
    #include <GLES3/gl32.h>
    #define NANOVG_GLES3_IMPLEMENTATION
#elif defined(NJLI_GL_2)
#error Unsupported choice setting
#elif defined(NJLI_GL_3)
    #error Unsupported choice setting
#else
    #error Unsupported choice setting
#endif

#ifndef __EMSCRIPTEN__
#define __EMSCRIPTEN__
#endif

#define USE_OPENAL
