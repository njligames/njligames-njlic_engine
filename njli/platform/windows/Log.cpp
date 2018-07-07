//http://mobilepearls.com/labs/native-android-api/
#include "Log.h"
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include <vector>

#include "World.h"
#include "WorldSocket.h"

njli::NJLIGameEngine::PlatformID njli::NJLIGameEngine::platformID()
{
    return njli::NJLIGameEngine::PlatformID_Linux;
}


void _script_error(const char* tag, const char* fmt, ...)
{
    char buffer[2048];
    va_list args;
    
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    
    njli::World::getInstance()->getWorldLuaVirtualMachine()->error(buffer);
    
}

void _script_crash()
{
    njli::World::getInstance()->getWorldLuaVirtualMachine()->error("");
}

void LUA_WRITE(const char* c)
{
}


void njliSleep(unsigned int _ms)
{
    // int microsecs;

    // struct timeval tv;

    // microsecs = _ms * 1000;

    // tv.tv_sec  = microsecs / 1000000;
    // tv.tv_usec = microsecs % 1000000;

    // select( 0, NULL, NULL, NULL, &tv );
}
///void __android_log_assert(const char *cond, const char *tag, const char *fmt, ...)

const char* string_format(const char* fmt, ...) {
    std::vector<char> str(100,'\0');
    va_list ap;
    while (1) {
        va_start(ap, fmt);
        auto n = vsnprintf(str.data(), str.size(), fmt, ap);
        va_end(ap);
        if ((n > -1) && (size_t(n) < str.size())) {
            return str.data();
        }
        if (n > -1)
            str.resize( n + 1 );
        else
            str.resize( str.size() * 2);
    }
    return str.data();
}
