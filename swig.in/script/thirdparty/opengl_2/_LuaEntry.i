//Lua interface file

%module gl

%include "_Ignore.i"

#if defined(SWIGLUA)
%include <lua/factory.i>
%include <lua/stl.i>
%include <lua/typemaps.i>
%include <lua/carrays.i>
%include <lua/std_string.i>
%include <lua/lua.swg>
#endif

%include "../../../../../Engine/src/swig.in/script/NJLIArray.i"
%include "../../../../../Engine/src/swig.in/script/NJLICast.i"
%include "../../../../../Engine/src/swig.in/script/NJLITypemaps.i"
%include "../../../../../Engine/src/swig.in/script/NJLISwigOverwrite.i"

%include "_Apply.i"

%include "_Rename.i"

//#########################################################################################################
//!!!:TODO Including source files to Public interface
//#########################################################################################################

%{
    #include "GraphicsPlatform.h"
%}

%include "_Inline.i"

%include "_Template.i"

%include "_Array.i"

//#########################################################################################################
//Including source files to Public interface
//#########################################################################################################


//#########################################################################################################
//Interface files to Public interface
//#########################################################################################################
%include "gl.i"


