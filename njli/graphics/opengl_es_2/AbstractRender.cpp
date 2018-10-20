//
//  AbstractRender.h
//  JLIGameEngineTest
//
//  Created by James Folk on 5/10/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_AbstractRender_h
#define JLIGameEngineTest_AbstractRender_h

#define TAG "AbstractRender.cpp"
#include "AbstractRender.h"
#include "GraphicsPlatform.h"
#include "Log.h"
#include "Util.h"
#include <cstring>
#include <string>

extern void CheckOpenGLError(const char *stmt, const char *fname, int line);

#ifndef GL_CHECK
#define GL_CHECK(stmt) do { \
stmt; \
CheckOpenGLError(#stmt, __FILE__, __LINE__); \
} while(0);
//#else
//    #define GL_CHECK(stmt) stmt
#endif


static f32 bgRed = 0.0f;
static f32 bgGreen = 0.0f;
static f32 bgBlue = 0.0f;
static f32 bgAlpha = 1.0f;

static int viewX;
static int viewY;
static int viewWidth;
static int viewHeight;

static const char * GetOpenGLErrorString(int errID)
{
    switch(errID) {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
//#if !defined(PLATFORM_IOS) && !defined(PLATFORM_TVOS) && !defined(PLATFORM_ANDROID) && !defined(PLATFORM_EMSCRIPTEN)
//        case GL_STACK_OVERFLOW:
//            return "GL_STACK_OVERFLOW";
//        case GL_STACK_UNDERFLOW:
//            return "GL_STACK_UNDERFLOW";
//#endif
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_NO_ERROR:
            return "GL_NO_ERROR";
        default:
            return "UNKNOWN ERROR";
    }
    return "";
}

void CheckOpenGLError(const char *stmt, const char *fname, int line)
{
    int error = glGetError();
    
    SDL_LogError(SDL_LOG_CATEGORY_TEST, "glGetError = %d, (%s) at %s:%d - for %s", error,
                 GetOpenGLErrorString(error), fname, line, stmt);
    SDL_assert((error != GL_NO_ERROR));
    
//    SDL_assertPrint((error != GL_NO_ERROR), "glGetError = %d, (%s) at %s:%d - for %s", error,
//                    GetOpenGLErrorString(error), fname, line, stmt);
}

void initGL()
{
  //    glEnable(GL_BLEND);
  //    glDisable(GL_DEPTH_TEST);
}

void renderGL(bool leftEye)
{
#if !(defined(NDEBUG)) && defined(__APPLE__)
    glPushGroupMarkerEXT(0, "renderGL()");
#endif
    GL_CHECK(glViewport(viewX, viewY, viewWidth, viewHeight));
    GL_CHECK(glClearColor(bgRed, bgGreen, bgBlue, bgAlpha));
    
    GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
    
  //    glEnable(GL_BLEND);
  //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //    glBlendEquation(GL_FUNC_ADD);

  GL_CHECK(glEnable(GL_STENCIL_TEST));
  GL_CHECK(glEnable(GL_DEPTH_TEST));
  GL_CHECK(glFrontFace(GL_CW));
#if !(defined(NDEBUG)) && defined(__APPLE__)
  GL_CHECK(glPopGroupMarkerEXT());
#endif
}

void printGLInfo()
{
  // gl begin printGLInfo
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_VERSION",
                 (const char *)glGetString(GL_VERSION));
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_VENDOR",
                 (const char *)glGetString(GL_VENDOR));
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_RENDERER",
                 (const char *)glGetString(GL_RENDERER));

  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s\n", "GL_EXTENSIONS");
  const char *the_extensions = (const char *)glGetString(GL_EXTENSIONS);
  char *extensions = new char[strlen(the_extensions) + 1];
  SDL_assert(extensions);
  strcpy(extensions, the_extensions);
  char *extension = strtok(extensions, " ");
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "\t%s\n", extension);
  while (NULL != (extension = strtok(NULL, " ")))
    {
      SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "\t%s\n", extension);
    }
  delete[] extensions;
  extensions = NULL;

  //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s", "GL_EXTENSIONS", (const
  //    char *) glGetString(GL_EXTENSIONS));
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n",
                 "GL_SHADING_LANGUAGE_VERSION",
                 (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

  int param;

  GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &param));
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The max texture size",
                 param);

  GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &param));
  SDL_LogVerbose(
      SDL_LOG_CATEGORY_TEST, "%s = %d\n",
      "The count texture units of allowed for usage in vertex shader", param);

  GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &param));
  SDL_LogVerbose(
      SDL_LOG_CATEGORY_TEST, "%s = %d\n",
      "The count texture units of allowed for usage in fragmet shader", param);

  GL_CHECK(glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &param));
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                 "The count texture units of allowed for usage in both shaders",
                 param);

  //    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &param);
  //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum amount
  //    of uniform vectors in the vertex shader", param);
  //
  //    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &param);
  //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum amount
  //    of uniform vectors in the fragment shader", param);
  //
  //    glGetIntegerv(GL_MAX_VARYING_VECTORS, &param);
  //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum amount
  //    of varying vectors", param);

  GL_CHECK(glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &param));
  SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                 "The maximumum amount of vertex attributes", param);

  //

  //    GL_MAX_VERTEX_UNIFORM_VECTORS
  //    GL_MAX_FRAGMENT_UNIFORM_VECTORS
  /*
   Actually there is GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, and
   GL_MAX_TEXTURE_IMAGE_UNITS and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS enums.
   First is for count texture units of allowed for usage in vertex shader,
   second one is for fragment shader, and third is combined for both shaders
   combined.
   */

  // gl end printGLInfo
}

void setGLBackgroundColor(float red, float green, float blue, float alpha)
{
  bgRed = red;
  bgGreen = green;
  bgBlue = blue;
  bgAlpha = alpha;
}
void setGLViewSize(int x, int y, int width, int height)
{
  viewX = x;
  viewY = y;
  viewWidth = width;
  viewHeight = height;
}

#endif
