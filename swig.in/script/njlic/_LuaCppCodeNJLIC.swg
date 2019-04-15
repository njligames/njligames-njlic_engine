
%native(getSublimeCompletions) void getSublimeCompletions(lua_State *L);
%{
%include "getSublimeCompletions.swg"
%}

%native(build) int build(lua_State*L);
%{
%include "build.swg"
%}
