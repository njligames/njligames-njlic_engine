//Lua interface file

%module glm

%include "_Ignore.swg"

#if defined(SWIGLUA)
%include <lua/factory.i>
%include <lua/stl.i>
//%include <lua/lua_fnptr.i>
%include <lua/typemaps.i>
%include <lua/carrays.i>
%include <lua/std_string.i>
%include <lua/lua.swg>
#endif

%include "NJLICArray.swg"
%include "NJLICCast.swg"
%include "NJLICTypemaps.swg"
%include "NJLICSwigOverwrite.swg"

%include "_Apply.swg"

%include "_Rename.swg"

//#########################################################################################################
//!!!:TODO Including source files to Public interface
//#########################################################################################################

%{
    #define GLM_ENABLE_EXPERIMENTAL
    #include "glm/gtx/quaternion.hpp"
    #include "glm/glm.hpp"
%}

%include "_Template.swg"

%include "_Array.swg"

//#########################################################################################################
//Including source files to Public interface
//#########################################################################################################

%include "glm/gtx/quaternion.hpp"
%include "glm/glm.hpp"

//#########################################################################################################
//Interface files to Public interface
//#########################################################################################################

// %import "LinearMath/btVector3.swg"

