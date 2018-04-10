
#if defined(NJLI_GL_ES2)
    #define GL_GLEXT_PROTOTYPES
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
    #include <GLES2/gl2platform.h>
    #define NANOVG_GLES2_IMPLEMENTATION
#elif defined(NJLI_GL_ES3)
    #include <GLES2/gl3.h>
    #include <GLES2/gl3ext.h>
    #include <GLES2/gl3platform.h>
    #define NANOVG_GLES3_IMPLEMENTATION
#elif defined(NJLI_GL_2)
#error Unsupported choice setting
#elif defined(NJLI_GL_3)
#error Unsupported choice setting
#else
#error Unsupported choice setting
#endif

#include <dlfcn.h>

#include <android/asset_manager_jni.h>

#ifndef __ANDROID__
#define __ANDROID__
#endif

