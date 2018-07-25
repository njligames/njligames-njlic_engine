
#if defined(__GL_ES2__)
#error Unsupported choice setting
#elif defined(__GL_ES3__)
#error Unsupported choice setting
#elif defined(__GL_2__)
  #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
    #define NANOVG_GL2_IMPLEMENTATION
#elif defined(__GL_3__)
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
    #define NANOVG_GL3_IMPLEMENTATION
#else
#error Unsupported choice setting
#endif
