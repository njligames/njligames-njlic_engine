
#if defined(__GL_ES2__)
  #error Unsupported choice setting
#elif defined(__GL_ES3__)
  #error Unsupported choice setting
#elif defined(__GL_2__)

  #if defined(__APPLE__)
    #define glGenVertexArrays_NJLIC glGenVertexArraysAPPLE
    #define glBindVertexArray_NJLIC glBindVertexArrayAPPLE
    #define glDeleteVertexArrays_NJLIC glDeleteVertexArraysAPPLE
  #else
    #define glGenVertexArrays_NJLIC glGenVertexArrays
    #define glBindVertexArray_NJLIC glBindVertexArray
    #define glDeleteVertexArrays_NJLIC glDeleteVertexArrays
  #endif

  #include <OpenGL/gl.h>
  #include <OpenGL/glext.h>

  #define NANOVG_GL2_IMPLEMENTATION

#elif defined(__GL_3__)
  #include <OpenGL/gl3.h>
  #include <OpenGL/gl3ext.h>
  #define NANOVG_GL3_IMPLEMENTATION
#else
  #error Unsupported choice setting
#endif

// #ifndef __MACOSX__
// #define __MACOSX__
// #endif
// 
// #define USE_FMOD
