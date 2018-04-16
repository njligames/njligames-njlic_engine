#include "File.h"
#include "Log.h"
#include <assert.h>
#include <errno.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include "android_file.h"

#define LINUX_PATH "assets/"

#include "GraphicsPlatform.h"


#ifndef _Included_com_example_njligameenginetest_File
#define _Included_com_example_njligameenginetest_File
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
#endif


const char* RESOURCE_PATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, LINUX_PATH);
    return tempBuffer;
}

const char* ASSET_PATH(const char* file)
{
    static char tempBuffer[4096];
    strcpy(tempBuffer, LINUX_PATH);
    strcat(tempBuffer, file);
    return tempBuffer;
}

const char* BUNDLE_PATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, "assets/");
    return tempBuffer;
}

const char* DOCUMENT_PATH(const char* file)
{
    static char tempBuffer[512];
    strcpy(tempBuffer, LINUX_PATH);
    strcat(tempBuffer, file);
    return tempBuffer;
}

void sleepThread(float milliseconds)
{
    usleep(milliseconds);
}

void setRunningPath(const char *file){}
void setScriptDir(const char *path) {}

const char* DOCUMENT_BASEPATH()
{
    static char tempBuffer[512];
    strcpy(tempBuffer, LINUX_PATH);
    return tempBuffer;
}


