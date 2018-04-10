#include "File.h"
// #include <android/asset_manager_jni.h>
#include "Log.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string>
#include <unistd.h>

//#define MAC_PATH "/Users/jamesfolk/NJLI/GameEngine/COMMON/assets/"
//#define MAC_PATH
//"/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/Platform.in/common/assets/"
#define MAC_PATH "./"
char RUNNING_PATH[4096] = "./";
bool HAS_RUNNING_PATH = false;

char SCRIPT_DIR[4096] = "";
bool HAS_SCRIPT_DIR = false;

// static int emscripten_read(void* cookie, char* buf, int size) {
//   return AAsset_read((AAsset*)cookie, buf, size);
// }

// static int emscripten_write(void* cookie, const char* buf, int size) {
//   return EACCES; // can't provide write access to the apk
// }

// static fpos_t emscripten_seek(void* cookie, fpos_t offset, int whence) {
//   return AAsset_seek((AAsset*)cookie, offset, whence);
// }

// static int emscripten_close(void* cookie) {
//   AAsset_close((AAsset*)cookie);
//   return 0;
// }

// FILE* njli_fopen(const char* fname, const char* mode)
//{
//  // if(mode[0] == 'w') return NULL;
//
//  return fopen(fname, mode);
//  // AAsset* asset = AAssetManager_open(asset_manager, fname, 0);
//  // if(!asset) return NULL;
//
//  // return funopen(asset, emscripten_read, emscripten_write, emscripten_seek,
//  emscripten_close);
//}

const char *RESOURCE_PATH() {
  static char tempBuffer[4096];
  char *data_path = NULL;

  if (HAS_RUNNING_PATH) {
    data_path = RUNNING_PATH;
  } else {
    char *base_path = SDL_GetBasePath();
    if (base_path) {
      data_path = base_path;
    } else {
      data_path = SDL_strdup(MAC_PATH);
    }
  }

  strcpy(tempBuffer, data_path);
  if (!HAS_RUNNING_PATH)
    strcat(tempBuffer, "assets/");

  return tempBuffer;
}

static bool isScriptFile(const char *file, char *dir) {
  if (HAS_SCRIPT_DIR && strlen(file) > 8) {
    std::string str(file);
    if (str.find("scripts/") == 0) {
      std::string s = str.substr(8, str.length());

      strcpy(dir, SCRIPT_DIR);
      strcat(dir, s.c_str());
      return true;
    }
  }
  return false;
}

const char *ASSET_PATH(const char *file) {
  static char tempBuffer[4096];
  char *data_path = NULL;

  if (!isScriptFile(file, tempBuffer)) {
    if (HAS_RUNNING_PATH) {
      data_path = RUNNING_PATH;
    } else {
      char *base_path = SDL_GetBasePath();
      if (base_path) {
        data_path = base_path;
      } else {
        data_path = SDL_strdup(MAC_PATH);
      }
    }

    strcpy(tempBuffer, data_path);
    if (!HAS_RUNNING_PATH)
      strcat(tempBuffer, "assets/");
    strcat(tempBuffer, file);
  }

  return tempBuffer;
}

const char *BUNDLE_PATH() {
  static char tempBuffer[4096];
  char *data_path = NULL;

  if (HAS_RUNNING_PATH) {
    data_path = RUNNING_PATH;
  } else {
    char *base_path = SDL_GetBasePath();
    if (base_path) {
      data_path = base_path;
    } else {
      data_path = SDL_strdup(MAC_PATH);
    }
  }

  strcpy(tempBuffer, data_path);
  if (!HAS_RUNNING_PATH)
    strcat(tempBuffer, "assets/");
  return tempBuffer;
}

const char *DOCUMENT_PATH(const char *file) {
  static char tempBuffer[512];
  strcpy(tempBuffer, MAC_PATH);
  strcat(tempBuffer, file);
  return tempBuffer;
}

void sleepThread(float milliseconds) { usleep(milliseconds); }

const char *DOCUMENT_BASEPATH() {
  static char tempBuffer[512];
  strcpy(tempBuffer, MAC_PATH);
  return tempBuffer;
}

void setRunningPath(const char *file) {
  SDL_assert(file != NULL);

  strcpy(RUNNING_PATH, file);
  strcat(RUNNING_PATH, "/");

  SDL_Log("setting the running path to: %s", RUNNING_PATH);

  HAS_RUNNING_PATH = true;
}

void setScriptDir(const char *path) {
  SDL_assert(path != NULL);

  strcpy(SCRIPT_DIR, path);
  strcat(SCRIPT_DIR, "/");

  SDL_Log("setting the script dir to: %s", SCRIPT_DIR);

  HAS_SCRIPT_DIR = true;
}
