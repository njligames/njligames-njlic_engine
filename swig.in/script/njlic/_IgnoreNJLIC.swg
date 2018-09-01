%ignore operator std::string;

%ignore njli::WorldLuaVirtualMachine::execute;

%ignore njli::Geometry::TexturedColoredVertex;
%ignore njli::Geometry::TexturedNormaledColoredVertex;

%ignore njli::Cube::CubeVerts;

%ignore njli::PhysicsWorld::CustomFilterCallback;

%ignore njli::Sprite2D::SpriteQuad;

%ignore njli::WorldDebugDrawer::Line;

%ignore operator new;
%ignore operator delete;
%ignore operator new[];
%ignore operator delete[];

%ignore SDL_vsscanf;
%ignore SDL_vsnprintf;
%ignore SDL_LogMessageV;
%ignore lua_pushvfstring;

%ignore Json::Value::demand;

%ignore SDL_main;

%ignore SDL_GetShapedWindowMode;
%ignore SDL_SetWindowShape;
%ignore SDL_IsShapedWindow;
%ignore SDL_CreateShapedWindow;

%ignore _debug_log_v;
%ignore _debug_log_d;
%ignore _debug_log_w;
%ignore _debug_log_e;
%ignore _debug_log_stderr;

%ignore lua_load;

%ignore DUMMY_ENUM_VALUE;
