#ifndef __ANDROID_FILE_H__
#define __ANDROID_FILE_H__

#include <stdio.h>

#if (defined(__ANDROID__) && __ANDROID__)

#include <android/asset_manager_jni.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

void initAssetManager(AAssetManager *assetManager);

FILE *android_fopen(const char *fname, const char *mode);

JNIEXPORT void JNICALL Java_org_libsdl_app_SDLActivity_initAssetManager(
    JNIEnv *env, jclass jclazz, jobject java_asset_manager);

#ifdef __cplusplus
}
#endif

#define mobile__fopen(x, y) android_fopen(x, y)

#else

#define mobile__fopen(x, y) fopen(x, y)

#endif

#endif
