//https://www.khronos.org/opengles/sdk/docs/
//https://www.khronos.org/registry/gles/specs/2.0/GLSL_ES_Specification_1.0.17.pdf
//https://developer.apple.com/library/ios/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/BestPracticesforShaders/BestPracticesforShaders.html

#if defined(NJLI_GL_ES2)
    #import <OpenGLES/ES2/glext.h>
    #import <OpenGLES/ES2/gl.h>
    #define NANOVG_GLES2_IMPLEMENTATION
#elif defined(NJLI_GL_ES3)
    #import <OpenGLES/ES3/glext.h>
    #import <OpenGLES/ES3/gl.h>
    #define NANOVG_GLES3_IMPLEMENTATION
#elif defined(NJLI_GL_2)
    #error Unsupported choice setting
#elif defined(NJLI_GL_3)
    #error Unsupported choice setting
#else
    #error Unsupported choice setting
#endif

#ifndef __TVOS__
#define __TVOS__
#endif

#define USE_FMOD
