
#if defined(__GL_ES2__)
    #define glGenVertexArrays_NJLIC glGenVertexArraysOES
    #define glBindVertexArray_NJLIC glBindVertexArrayOES
    #define glDeleteVertexArrays_NJLIC glDeleteVertexArraysOES

    #include <OpenGLES/ES2/glext.h>
    #include <OpenGLES/ES2/gl.h>

    #define NANOVG_GLES2_IMPLEMENTATION

#elif defined(__GL_ES3__)
    #include <OpenGLES/ES3/glext.h>
    #include <OpenGLES/ES3/gl.h>
    #define NANOVG_GLES3_IMPLEMENTATION
#elif defined(__GL_2__)
    #error Unsupported choice setting
#elif defined(__GL_3__)
    #error Unsupported choice setting
#else
    #error Unsupported choice setting
#endif

//https://www.khronos.org/opengles/sdk/docs/
//https://www.khronos.org/registry/gles/specs/2.0/GLSL_ES_Specification_1.0.17.pdf
//https://developer.apple.com/library/ios/documentation/3DDrawing/Conceptual/OpenGLES_ProgrammingGuide/BestPracticesforShaders/BestPracticesforShaders.html

#ifndef __IOS__
#define __IOS__
#endif

#define USE_FMOD

//#if defined(__GL_ES2__)
//    #include <OpenGLES/ES2/glext.h>
//    #include <OpenGLES/ES2/gl.h>
//
//    #define glDeleteVertexArraysNJLIC glDeleteVertexArraysOES
//    #define glBindVertexArrayNJLIC glBindVertexArrayOES
//    #define glGenVertexArraysNJLIC glGenVertexArraysOES
//
//    #define NANOVG_GLES2_IMPLEMENTATION
//#elif defined(__GL_ES3__)
//    #include <OpenGLES/ES3/glext.h>
//    #include <OpenGLES/ES3/gl.h>
//
//    #define glDeleteVertexArraysNJLIC glDeleteVertexArrays
//    #define glBindVertexArrayNJLIC glBindVertexArray
//    #define glGenVertexArraysNJLIC glGenVertexArrays
//
//
//    #define NANOVG_GLES3_IMPLEMENTATION
//#elif defined(__GL_2__)
//
//    #if defined(__APPLE__)
//        #define glDeleteVertexArraysNJLIC glDeleteVertexArraysAPPLE
//        #define glBindVertexArrayNJLIC glBindVertexArrayAPPLE
//        #define glGenVertexArraysNJLIC glGenVertexArraysAPPLE
//    #else
//        #define glDeleteVertexArraysNJLIC glDeleteVertexArrays
//        #define glBindVertexArrayNJLIC glBindVertexArray
//        #define glGenVertexArraysNJLIC glGenVertexArrays
//    #endif
//
//#elif defined(__GL_3__)
//    #define glDeleteVertexArraysNJLIC glDeleteVertexArrays
//    #define glBindVertexArrayNJLIC glBindVertexArray
//    #define glGenVertexArraysNJLIC glGenVertexArrays
//#else
//    #error Unsupported choice setting
//#endif
//
