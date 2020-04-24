// Lua interface file

// clang-format off

%module njlic

// #define LLONG_MAX
//MARK: Tested Ignore, successfully
%include "_IgnoreNJLIC.swg"
%include "_IgnorePlatform.swg"
//             #ifdef USE_BULLET_LIBRARY
%import "../bullet3/_IgnoreBullet.swg"
//             #endif
//             %import "/Users/jamesfolk/Documents/NJLI/External/thirdparty/swig.in/script/OPENGL/_Ignore.swg"
//             
//             #ifdef USE_BULLET_LIBRARY
%include "_Module_Bullet.swg"
//             #endif
//             %import "/Users/jamesfolk/Documents/NJLI/External/thirdparty/swig.in/script/OPENGL/_LuaEntry.swg"

%include "AbstractActionable.swg"
%include "AbstractBuilder.swg"
%include "AbstractClock.swg"
%include "AbstractDecorator.swg"
%include "AbstractFactoryObject.swg"
%include "AbstractFrameBufferObject.swg"
%include "AbstractObject.swg"
%include "AbstractRender.swg"
%include "AbstractState.swg"
%include "AbstractStateMachine.swg"
%include "AbstractTransform.swg"
%include "AbstractPhysicsBody.swg"
%include "AbstractPhysicsShape.swg"
%include "AbstractGeometry.swg"

#if defined(SWIGLUA)
%import <lua/carrays.i>
%import <lua/factory.i>
%import <lua/lua_fnptr.i>
%import <lua/std_common.i>
%import <lua/std_deque.i>
%import <lua/std_except.i>
%import <lua/std_map.i>
%import <lua/std_pair.i>
%import <lua/std_string.i>
%import <lua/std_vector.i>
%import <lua/stl.i>
%import <lua/typemaps.i>
%import <lua/wchar.i>
%import <lua/lua.swg>
#endif

%include "NJLICArray.swg"
%include "NJLICCast.swg"
%include "NJLICTypemaps.swg"
%include "NJLICSwigOverwrite.swg"

//MARK: Tested Apply, successfully
%include "_ApplyNJLIC.swg"
%include "_ApplyPlatform.swg"

//MARK: Tested Rename, successfully
%include "_RenameNJLIC.swg"
%include "_RenamePlatform.swg"

%include "_Defines.swg"

#if defined(SWIGLUA)
//MARK: %luacode wrapper doesn't work in an external file.
%include "_LuaCodeNJLIC.swg"
#endif

%insert("runtime")

// #ifndef BT_INFINITY
// #define BT_INFINITY
// #endif

%{
#include "AbstractActionable.h"
#include "AbstractBuilder.h"
#include "AbstractClock.h"
#include "AbstractDecorator.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "AbstractObject.h"
#include "AbstractRender.h"
#include "AbstractState.h"
#include "AbstractStateMachine.h"
#include "AbstractTransform.h"
#include "Action.h"
#include "ActionBuilder.h"
#include "Camera.h"
#include "CameraBuilder.h"
#include "Clock.h"
#include "ClockBuilder.h"
#include "CollisionResponse.h"
#include "CollisionResponseBuilder.h"
#include "Cube.h"
#include "CubeBuilder.h"
#include "Font.h"
#include "FontBuilder.h"
//#include "GameClock.h"
#include "Geometry.h"
#include "Image.h"
#include "ImageBuilder.h"
//#include "JLIBuilders.h"
//#include "JLIEngine.h"
#include "JLIFactoryTypes.h"
//#include "JLITransform.h"
#include "JsonJLI.h"
#include "JsonJLIBuilder.h"
#include "LevelOfDetail.h"
#include "LevelOfDetailBuilder.h"
#include "Light.h"
#include "LightBuilder.h"
//#include "Lua.h"
//#include "LuaBuilder.h"
#include "Material.h"
#include "MaterialBuilder.h"
#include "MaterialProperty.h"
#include "MaterialPropertyBuilder.h"
#include "MeshGeometry.h"
#include "MeshGeometryBuilder.h"
#include "Node.h"
#include "NodeBuilder.h"
#include "NodeState.h"
#include "NodeStateBuilder.h"
#include "NodeStateMachine.h"
#include "NodeStateMachineBuilder.h"
#include "ParticleEmitter.h"
#include "ParticleEmitterBuilder.h"
#include "Path.h"
#include "PhysicsBody.h"
#include "PhysicsBodyGhost.h"
#include "PhysicsBodyGhostBuilder.h"
#include "PhysicsBodyRigid.h"
#include "PhysicsBodyRigidBuilder.h"
#include "PhysicsBodySoft.h"
#include "PhysicsBodySoftBuilder.h"
#include "PhysicsCloseContact.h"
#include "PhysicsCloseContactBuilder.h"
#include "PhysicsConstraint.h"
#include "PhysicsConstraintBuilder.h"
#include "PhysicsConstraintConeTwist.h"
#include "PhysicsConstraintConeTwistBuilder.h"
#include "PhysicsConstraintFixed.h"
#include "PhysicsConstraintFixedBuilder.h"
#include "PhysicsConstraintGeneric6Dof.h"
#include "PhysicsConstraintGeneric6DofBuilder.h"
#include "PhysicsConstraintGeneric6DofSpring.h"
#include "PhysicsConstraintGeneric6DofSpringBuilder.h"
#include "PhysicsConstraintHinge.h"
#include "PhysicsConstraintHingeBuilder.h"
#include "PhysicsConstraintPointToPoint.h"
#include "PhysicsConstraintPointToPointBuilder.h"
#include "PhysicsConstraintSlider.h"
#include "PhysicsConstraintSliderBuilder.h"
#include "PhysicsContact.h"
#include "PhysicsContactBuilder.h"
#include "PhysicsField.h"
#include "PhysicsFieldBuilder.h"
#include "PhysicsRayContact.h"
#include "PhysicsRayContactBuilder.h"
#include "PhysicsShape.h"
#include "PhysicsShapeBox.h"
#include "PhysicsShapeBox2D.h"
#include "PhysicsShapeBox2DBuilder.h"
#include "PhysicsShapeBoxBuilder.h"
#include "PhysicsShapeBvhTriangleMesh.h"
#include "PhysicsShapeBvhTriangleMeshBuilder.h"
#include "PhysicsShapeCapsule.h"
#include "PhysicsShapeCapsuleBuilder.h"
#include "PhysicsShapeCone.h"
#include "PhysicsShapeConeBuilder.h"
#include "PhysicsShapeConvexHull.h"
#include "PhysicsShapeConvexHullBuilder.h"
#include "PhysicsShapeConvexTriangleMesh.h"
#include "PhysicsShapeConvexTriangleMeshBuilder.h"
#include "PhysicsShapeCylinder.h"
#include "PhysicsShapeCylinderBuilder.h"
#include "PhysicsShapeHeightfieldTerrain.h"
#include "PhysicsShapeHeightfieldTerrainBuilder.h"
#include "PhysicsShapeMultiSphere.h"
#include "PhysicsShapeMultiSphereBuilder.h"
#include "PhysicsShapeSphere.h"
#include "PhysicsShapeSphereBuilder.h"
#include "PhysicsShapeStaticPlane.h"
#include "PhysicsShapeStaticPlaneBuilder.h"
#include "PhysicsWorld.h"
#include "PhysicsWorldBuilder.h"
#include "Plane.h"
#include "PlaneBuilder.h"
#include "Scene.h"
#include "SceneBuilder.h"
#include "SceneState.h"
#include "SceneStateBuilder.h"
#include "SceneStateMachine.h"
#include "SceneStateMachineBuilder.h"
#include "ShaderProgram.h"
#include "ShaderProgramBuilder.h"
#include "Skinner.h"
#include "SkinnerBuilder.h"
#include "SoundBuilder.h"
#include "Sprite2D.h"
#include "Sprite2DBuilder.h"
#include "SpriteFrameAtlas.h"
#include "SpriteFrameAtlasBuilder.h"
#include "SteeringBehavior.h"
#include "SteeringBehaviorBuilder.h"
#include "SteeringBehaviorAlignment.h"
#include "SteeringBehaviorAlignmentBuilder.h"
#include "SteeringBehaviorArrive.h"
#include "SteeringBehaviorArriveBuilder.h"
#include "SteeringBehaviorCohesion.h"
#include "SteeringBehaviorCohesionBuilder.h"
#include "SteeringBehaviorEvade.h"
#include "SteeringBehaviorEvadeBuilder.h"
#include "SteeringBehaviorFlee.h"
#include "SteeringBehaviorFleeBuilder.h"
#include "SteeringBehaviorFollowPath.h"
#include "SteeringBehaviorFollowPathBuilder.h"
#include "SteeringBehaviorHide.h"
#include "SteeringBehaviorHideBuilder.h"
#include "SteeringBehaviorInterpose.h"
#include "SteeringBehaviorInterposeBuilder.h"
#include "SteeringBehaviorMachine.h"
#include "SteeringBehaviorMachineBuilder.h"
#include "SteeringBehaviorMachineDithered.h"
#include "SteeringBehaviorMachineDitheredBuilder.h"
#include "SteeringBehaviorMachinePrioritized.h"
#include "SteeringBehaviorMachinePrioritizedBuilder.h"
#include "SteeringBehaviorMachineWeighted.h"
#include "SteeringBehaviorMachineWeightedBuilder.h"
#include "SteeringBehaviorObstacleAvoidance.h"
#include "SteeringBehaviorObstacleAvoidanceBuilder.h"
#include "SteeringBehaviorOffsetPursuit.h"
#include "SteeringBehaviorOffsetPursuitBuilder.h"
#include "SteeringBehaviorPursuit.h"
#include "SteeringBehaviorPursuitBuilder.h"
#include "SteeringBehaviorSeek.h"
#include "SteeringBehaviorSeekBuilder.h"
#include "SteeringBehaviorSeparation.h"
#include "SteeringBehaviorSeparationBuilder.h"
#include "SteeringBehaviorWallAvoidance.h"
#include "SteeringBehaviorWallAvoidanceBuilder.h"
#include "SteeringBehaviorWander.h"
#include "SteeringBehaviorWanderBuilder.h"
#include "StopWatch.h"
#include "StopWatchBuilder.h"
#include "Thread.h"
#include "ThreadBuilder.h"
#include "Timer.h"
#include "TimerBuilder.h"
#include "World.h"
#include "WorldClock.h"
#include "WorldDebugDrawer.h"
#include "WorldFactory.h"
#ifdef USE_NANOVG_LIBRARY
    #include "ButtonHUD.h"
    #include "ButtonHUDBuilder.h"
    #include "CheckboxHUD.h"
    #include "CheckboxHUDBuilder.h"
    #include "DropdownHUD.h"
    #include "DropdownHUDBuilder.h"
    #include "LabelHUD.h"
    #include "LabelHUDBuilder.h"
    #include "SliderHUD.h"
    #include "SliderHUDBuilder.h"
    #include "TextboxHUD.h"
    #include "TextboxHUDBuilder.h"
    #include "WorldHUD.h"
#endif
#include "WorldLuaVirtualMachine.h"
#include "WorldResourceLoader.h"
//#include "WorldSQLite.h"
#include "WorldSocket.h"
#include "WorldState.h"
#include "WorldStateBuilder.h"
#include "WorldStateMachine.h"
#include "WorldStateMachineBuilder.h"
#include "Xml.h"
#include "XmlBuilder.h"
//#########################################################################################################
#include "DeviceInputTime.h"
#include "DeviceTouch.h"
#include "File.h"
//#include "Game.h"
//#include "JLIAssetUtil.h"
//#include "JLIFileUtil.h"
#include "Localization.h"
#include "Log.h"
#include "Macros.h"
#include "Sound.h"
#include "Util.h"
#include "ColorUtil.h"
//#include "WorldFacebook.h"
#include "WorldInput.h"
//#include "WorldPythonVirtualMachine.h"
#include "WorldSound.h"
%}

//MARK: Tested Template, successfully
%include "_TemplatePlatform.swg"
%include "_TemplateNJLIC.swg"


//MARK: Tested Array, succesfully.
%include "_ArrayPlatform.swg"
%include "_ArrayNJLIC.swg"

//MARK: Tested Factory, successfully
//%include "AbstractActionable.swg"
//%include "AbstractBuilder.swg"
//%include "AbstractClock.swg"
//%include "AbstractDecorator.swg"
//%include "AbstractFactoryObject.swg"
//%include "AbstractFrameBufferObject.swg"
//%include "AbstractObject.swg"
//%include "AbstractRender.swg"
//%include "AbstractState.swg"
//%include "AbstractStateMachine.swg"
//%include "AbstractTransform.swg"
//%include "AbstractPhysicsBody.swg"
//%include "AbstractPhysicsShape.swg"
//%include "AbstractGeometry.swg"
%include "Action.swg"
%include "ActionBuilder.swg"
%include "Camera.swg"
%include "CameraBuilder.swg"
%include "Clock.swg"
%include "ClockBuilder.swg"
%include "CollisionResponse.swg"
%include "CollisionResponseBuilder.swg"
%include "Cube.swg"
%include "CubeBuilder.swg"
%include "Font.swg"
%include "FontBuilder.swg"
//%include "GameClock.swg"
%include "Geometry.swg"
%include "Image.swg"
%include "ImageBuilder.swg"
//%include "JLIBuilders.swg"
//%include "JLIEngine.swg"
//%include "JLIFactoryTypes.swg"
//%include "JLITransform.swg"
%include "JsonJLI.swg"
%include "JsonJLIBuilder.swg"
%include "LevelOfDetail.swg"
%include "LevelOfDetailBuilder.swg"
%include "Light.swg"
%include "LightBuilder.swg"
//%include "LuaBuilder.swg"
%include "Material.swg"
%include "MaterialBuilder.swg"
%include "MaterialProperty.swg"
%include "MaterialPropertyBuilder.swg"
%include "MeshGeometry.swg"
%include "MeshGeometryBuilder.swg"
%include "Node.swg"
%include "NodeBuilder.swg"
%include "NodeState.swg"
%include "NodeStateBuilder.swg"
%include "NodeStateMachine.swg"
%include "NodeStateMachineBuilder.swg"
%include "ParticleEmitter.swg"
%include "ParticleEmitterBuilder.swg"
%include "Path.swg"
%include "PhysicsBody.swg"
%include "PhysicsBodyGhost.swg"
%include "PhysicsBodyGhostBuilder.swg"
%include "PhysicsBodyRigid.swg"
%include "PhysicsBodyRigidBuilder.swg"
%include "PhysicsBodySoft.swg"
%include "PhysicsBodySoftBuilder.swg"
%include "PhysicsCloseContact.swg"
%include "PhysicsCloseContactBuilder.swg"
%include "PhysicsConstraint.swg"
%include "PhysicsConstraintBuilder.swg"
%include "PhysicsConstraintConeTwist.swg"
%include "PhysicsConstraintConeTwistBuilder.swg"
%include "PhysicsConstraintFixed.swg"
%include "PhysicsConstraintFixedBuilder.swg"
%include "PhysicsConstraintGeneric6Dof.swg"
%include "PhysicsConstraintGeneric6DofBuilder.swg"
%include "PhysicsConstraintGeneric6DofSpring.swg"
%include "PhysicsConstraintGeneric6DofSpringBuilder.swg"
%include "PhysicsConstraintHinge.swg"
%include "PhysicsConstraintHingeBuilder.swg"
%include "PhysicsConstraintPointToPoint.swg"
%include "PhysicsConstraintPointToPointBuilder.swg"
%include "PhysicsConstraintSlider.swg"
%include "PhysicsConstraintSliderBuilder.swg"
%include "PhysicsContact.swg"
%include "PhysicsContactBuilder.swg"
%include "PhysicsField.swg"
%include "PhysicsFieldBuilder.swg"
%include "PhysicsRayContact.swg"
%include "PhysicsRayContactBuilder.swg"
%include "PhysicsShape.swg"
%include "PhysicsShapeBox.swg"
%include "PhysicsShapeBox2D.swg"
%include "PhysicsShapeBox2DBuilder.swg"
%include "PhysicsShapeBoxBuilder.swg"
%include "PhysicsShapeBvhTriangleMesh.swg"
%include "PhysicsShapeBvhTriangleMeshBuilder.swg"
%include "PhysicsShapeCapsule.swg"
%include "PhysicsShapeCapsuleBuilder.swg"
%include "PhysicsShapeCone.swg"
%include "PhysicsShapeConeBuilder.swg"
%include "PhysicsShapeConvexHull.swg"
%include "PhysicsShapeConvexHullBuilder.swg"
%include "PhysicsShapeConvexTriangleMesh.swg"
%include "PhysicsShapeConvexTriangleMeshBuilder.swg"
%include "PhysicsShapeCylinder.swg"
%include "PhysicsShapeCylinderBuilder.swg"
%include "PhysicsShapeHeightfieldTerrain.swg"
%include "PhysicsShapeHeightfieldTerrainBuilder.swg"
%include "PhysicsShapeMultiSphere.swg"
%include "PhysicsShapeMultiSphereBuilder.swg"
%include "PhysicsShapeSphere.swg"
%include "PhysicsShapeSphereBuilder.swg"
%include "PhysicsShapeStaticPlane.swg"
%include "PhysicsShapeStaticPlaneBuilder.swg"
%include "PhysicsWorld.swg"
%include "PhysicsWorldBuilder.swg"
%include "Plane.swg"
%include "PlaneBuilder.swg"
%include "Scene.swg"
%include "SceneBuilder.swg"
%include "SceneState.swg"
%include "SceneStateBuilder.swg"
%include "SceneStateMachine.swg"
%include "SceneStateMachineBuilder.swg"
%include "ShaderProgram.swg"
%include "ShaderProgramBuilder.swg"
%include "Skinner.swg"
%include "SkinnerBuilder.swg"
%include "SoundBuilder.swg"
%include "Sprite2D.swg"
%include "Sprite2DBuilder.swg"
%include "SpriteFrameAtlas.swg"
%include "SpriteFrameAtlasBuilder.swg"
%include "SteeringBehavior.swg"
%include "SteeringBehaviorBuilder.swg"
%include "SteeringBehaviorAlignment.swg"
%include "SteeringBehaviorAlignmentBuilder.swg"
%include "SteeringBehaviorArrive.swg"
%include "SteeringBehaviorArriveBuilder.swg"
%include "SteeringBehaviorCohesion.swg"
%include "SteeringBehaviorCohesionBuilder.swg"
%include "SteeringBehaviorEvade.swg"
%include "SteeringBehaviorEvadeBuilder.swg"
%include "SteeringBehaviorFlee.swg"
%include "SteeringBehaviorFleeBuilder.swg"
%include "SteeringBehaviorFollowPath.swg"
%include "SteeringBehaviorFollowPathBuilder.swg"
%include "SteeringBehaviorHide.swg"
%include "SteeringBehaviorHideBuilder.swg"
%include "SteeringBehaviorInterpose.swg"
%include "SteeringBehaviorInterposeBuilder.swg"
%include "SteeringBehaviorMachine.swg"
%include "SteeringBehaviorMachineBuilder.swg"
%include "SteeringBehaviorMachineDithered.swg"
%include "SteeringBehaviorMachineDitheredBuilder.swg"
%include "SteeringBehaviorMachinePrioritized.swg"
%include "SteeringBehaviorMachinePrioritizedBuilder.swg"
%include "SteeringBehaviorMachineWeighted.swg"
%include "SteeringBehaviorMachineWeightedBuilder.swg"
%include "SteeringBehaviorObstacleAvoidance.swg"
%include "SteeringBehaviorObstacleAvoidanceBuilder.swg"
%include "SteeringBehaviorOffsetPursuit.swg"
%include "SteeringBehaviorOffsetPursuitBuilder.swg"
%include "SteeringBehaviorPursuit.swg"
%include "SteeringBehaviorPursuitBuilder.swg"
%include "SteeringBehaviorSeek.swg"
%include "SteeringBehaviorSeekBuilder.swg"
%include "SteeringBehaviorSeparation.swg"
%include "SteeringBehaviorSeparationBuilder.swg"
%include "SteeringBehaviorWallAvoidance.swg"
%include "SteeringBehaviorWallAvoidanceBuilder.swg"
%include "SteeringBehaviorWander.swg"
%include "SteeringBehaviorWanderBuilder.swg"
%include "StopWatch.swg"
%include "StopWatchBuilder.swg"
%include "Thread.swg"
%include "ThreadBuilder.swg"
%include "Timer.swg"
%include "TimerBuilder.swg"
%include "World.swg"
%include "WorldClock.swg"
%include "WorldDebugDrawer.swg"
%include "WorldFactory.swg"
#ifdef USE_NANOVG_LIBRARY
    %include "ButtonHUD.swg"
    %include "ButtonHUDBuilder.swg"
    %include "CheckboxHUD.swg"
    %include "CheckboxHUDBuilder.swg"
    %include "DropdownHUD.swg"
    %include "DropdownHUDBuilder.swg"
    %include "LabelHUD.swg"
    %include "LabelHUDBuilder.swg"
    %include "SliderHUD.swg"
    %include "SliderHUDBuilder.swg"
    %include "TextboxHUD.swg"
    %include "TextboxHUDBuilder.swg"
    %include "WorldHUD.swg"
#endif
%include "WorldLuaVirtualMachine.swg"
%include "WorldResourceLoader.swg"
//%include "WorldSQLite.swg"
%include "WorldSocket.swg"
%include "WorldState.swg"
%include "WorldStateBuilder.swg"
%include "WorldStateMachine.swg"
%include "WorldStateMachineBuilder.swg"
%include "Xml.swg"
%include "XmlBuilder.swg"
//#########################################################################################################
%include "DeviceInputTime.swg"
%include "DeviceTouch.swg"
%include "File.swg"
%include "Localization.swg"
%include "Log.swg"
%include "Macros.swg"
%include "Sound.swg"
%include "Util.swg"
%include "ColorUtil.swg"
%include "WorldInput.swg"
%include "WorldSound.swg"

//#########################################################################################################
//Including source files to Public interface
//#########################################################################################################

%include "AbstractActionable.h"
%include "AbstractBuilder.h"
%include "AbstractClock.h"
%include "AbstractDecorator.h"
%include "AbstractFactoryObject.h"
%include "AbstractFrameBufferObject.h"
%include "AbstractObject.h"
%include "AbstractRender.h"
%include "AbstractState.h"
%include "AbstractStateMachine.h"
%include "AbstractTransform.h"
%include "Action.h"
%include "ActionBuilder.h"
%include "Camera.h"
%include "CameraBuilder.h"
%include "Clock.h"
%include "ClockBuilder.h"
%include "CollisionResponse.h"
%include "CollisionResponseBuilder.h"
%include "Cube.h"
%include "CubeBuilder.h"
%include "Font.h"
%include "FontBuilder.h"
//%include "GameClock.h"
%include "Geometry.h"
%include "Image.h"
%include "ImageBuilder.h"
//%include "JLIBuilders.h"
//%include "JLIEngine.h"
%include "JLIFactoryTypes.h"
//%include "JLITransform.h"
%include "JsonJLI.h"
%include "JsonJLIBuilder.h"
%include "LevelOfDetail.h"
%include "LevelOfDetailBuilder.h"
%include "Light.h"
%include "LightBuilder.h"
//%include "Lua.h"
//%include "LuaBuilder.h"
%include "Material.h"
%include "MaterialBuilder.h"
%include "MaterialProperty.h"
%include "MaterialPropertyBuilder.h"
%include "MeshGeometry.h"
%include "MeshGeometryBuilder.h"
%include "Node.h"
%include "NodeBuilder.h"
%include "NodeState.h"
%include "NodeStateBuilder.h"
%include "NodeStateMachine.h"
%include "NodeStateMachineBuilder.h"
%include "ParticleEmitter.h"
%include "ParticleEmitterBuilder.h"
%include "Path.h"
%include "PhysicsBody.h"
%include "PhysicsBodyGhost.h"
%include "PhysicsBodyGhostBuilder.h"
%include "PhysicsBodyRigid.h"
%include "PhysicsBodyRigidBuilder.h"
%include "PhysicsBodySoft.h"
%include "PhysicsBodySoftBuilder.h"
%include "PhysicsCloseContact.h"
%include "PhysicsCloseContactBuilder.h"
%include "PhysicsConstraint.h"
%include "PhysicsConstraintBuilder.h"
%include "PhysicsConstraintConeTwist.h"
%include "PhysicsConstraintConeTwistBuilder.h"
%include "PhysicsConstraintFixed.h"
%include "PhysicsConstraintFixedBuilder.h"
%include "PhysicsConstraintGeneric6Dof.h"
%include "PhysicsConstraintGeneric6DofBuilder.h"
%include "PhysicsConstraintGeneric6DofSpring.h"
%include "PhysicsConstraintGeneric6DofSpringBuilder.h"
%include "PhysicsConstraintHinge.h"
%include "PhysicsConstraintHingeBuilder.h"
%include "PhysicsConstraintPointToPoint.h"
%include "PhysicsConstraintPointToPointBuilder.h"
%include "PhysicsConstraintSlider.h"
%include "PhysicsConstraintSliderBuilder.h"
%include "PhysicsContact.h"
%include "PhysicsContactBuilder.h"
%include "PhysicsField.h"
%include "PhysicsFieldBuilder.h"
%include "PhysicsRayContact.h"
%include "PhysicsRayContactBuilder.h"
%include "PhysicsShape.h"
%include "PhysicsShapeBox.h"
%include "PhysicsShapeBox2D.h"
%include "PhysicsShapeBox2DBuilder.h"
%include "PhysicsShapeBoxBuilder.h"
%include "PhysicsShapeBvhTriangleMesh.h"
%include "PhysicsShapeBvhTriangleMeshBuilder.h"
%include "PhysicsShapeCapsule.h"
%include "PhysicsShapeCapsuleBuilder.h"
%include "PhysicsShapeCone.h"
%include "PhysicsShapeConeBuilder.h"
%include "PhysicsShapeConvexHull.h"
%include "PhysicsShapeConvexHullBuilder.h"
%include "PhysicsShapeConvexTriangleMesh.h"
%include "PhysicsShapeConvexTriangleMeshBuilder.h"
%include "PhysicsShapeCylinder.h"
%include "PhysicsShapeCylinderBuilder.h"
%include "PhysicsShapeHeightfieldTerrain.h"
%include "PhysicsShapeHeightfieldTerrainBuilder.h"
%include "PhysicsShapeMultiSphere.h"
%include "PhysicsShapeMultiSphereBuilder.h"
%include "PhysicsShapeSphere.h"
%include "PhysicsShapeSphereBuilder.h"
%include "PhysicsShapeStaticPlane.h"
%include "PhysicsShapeStaticPlaneBuilder.h"
%include "PhysicsWorld.h"
%include "PhysicsWorldBuilder.h"
%include "Plane.h"
%include "PlaneBuilder.h"
%include "Scene.h"
%include "SceneBuilder.h"
%include "SceneState.h"
%include "SceneStateBuilder.h"
%include "SceneStateMachine.h"
%include "SceneStateMachineBuilder.h"
%include "ShaderProgram.h"
%include "ShaderProgramBuilder.h"
%include "Skinner.h"
%include "SkinnerBuilder.h"
%include "SoundBuilder.h"
%include "Sprite2D.h"
%include "Sprite2DBuilder.h"
%include "SpriteFrameAtlas.h"
%include "SpriteFrameAtlasBuilder.h"
%include "SteeringBehavior.h"
%include "SteeringBehaviorBuilder.h"
%include "SteeringBehaviorAlignment.h"
%include "SteeringBehaviorAlignmentBuilder.h"
%include "SteeringBehaviorArrive.h"
%include "SteeringBehaviorArriveBuilder.h"
%include "SteeringBehaviorCohesion.h"
%include "SteeringBehaviorCohesionBuilder.h"
%include "SteeringBehaviorEvade.h"
%include "SteeringBehaviorEvadeBuilder.h"
%include "SteeringBehaviorFlee.h"
%include "SteeringBehaviorFleeBuilder.h"
%include "SteeringBehaviorFollowPath.h"
%include "SteeringBehaviorFollowPathBuilder.h"
%include "SteeringBehaviorHide.h"
%include "SteeringBehaviorHideBuilder.h"
%include "SteeringBehaviorInterpose.h"
%include "SteeringBehaviorInterposeBuilder.h"
%include "SteeringBehaviorMachine.h"
%include "SteeringBehaviorMachineBuilder.h"
%include "SteeringBehaviorMachineDithered.h"
%include "SteeringBehaviorMachineDitheredBuilder.h"
%include "SteeringBehaviorMachinePrioritized.h"
%include "SteeringBehaviorMachinePrioritizedBuilder.h"
%include "SteeringBehaviorMachineWeighted.h"
%include "SteeringBehaviorMachineWeightedBuilder.h"
%include "SteeringBehaviorObstacleAvoidance.h"
%include "SteeringBehaviorObstacleAvoidanceBuilder.h"
%include "SteeringBehaviorOffsetPursuit.h"
%include "SteeringBehaviorOffsetPursuitBuilder.h"
%include "SteeringBehaviorPursuit.h"
%include "SteeringBehaviorPursuitBuilder.h"
%include "SteeringBehaviorSeek.h"
%include "SteeringBehaviorSeekBuilder.h"
%include "SteeringBehaviorSeparation.h"
%include "SteeringBehaviorSeparationBuilder.h"
%include "SteeringBehaviorWallAvoidance.h"
%include "SteeringBehaviorWallAvoidanceBuilder.h"
%include "SteeringBehaviorWander.h"
%include "SteeringBehaviorWanderBuilder.h"
%include "StopWatch.h"
%include "StopWatchBuilder.h"
%include "Thread.h"
%include "ThreadBuilder.h"
%include "Timer.h"
%include "TimerBuilder.h"
%include "World.h"
%include "WorldClock.h"
%include "WorldDebugDrawer.h"
%include "WorldFactory.h"
#ifdef USE_NANOVG_LIBRARY
    %include "ButtonHUD.h"
    %include "ButtonHUDBuilder.h"
    %include "CheckboxHUD.h"
    %include "CheckboxHUDBuilder.h"
    %include "DropdownHUD.h"
    %include "DropdownHUDBuilder.h"
    %include "LabelHUD.h"
    %include "LabelHUDBuilder.h"
    %include "SliderHUD.h"
    %include "SliderHUDBuilder.h"
    %include "TextboxHUD.h"
    %include "TextboxHUDBuilder.h"
    %include "WorldHUD.h"
#endif
%include "WorldLuaVirtualMachine.h"
%include "WorldResourceLoader.h"
//%include "WorldSQLite.h"
%include "WorldSocket.h"
%include "WorldState.h"
%include "WorldStateBuilder.h"
%include "WorldStateMachine.h"
%include "WorldStateMachineBuilder.h"
%include "Xml.h"
%include "XmlBuilder.h"
//#########################################################################################################
%include "DeviceInputTime.h"
%include "DeviceTouch.h"
%include "File.h"
//%include "Game.h"
//%include "JLIAssetUtil.h"
//%include "JLIFileUtil.h"
%include "Localization.h"
%include "Log.h"
%include "Macros.h"
%include "Sound.h"
%include "Util.h"
%include "ColorUtil.h"
//%include "WorldFacebook.h"
%include "WorldInput.h"
//%include "WorldPythonVirtualMachine.h"
%include "WorldSound.h"

%native(getSublimeCompletions) void getSublimeCompletions(lua_State *L);
%{
    // clang-format on
    static std::string sublimeCompletions()
    {
        std::string output = "-- Automatically generated tests for ";
        output += SWIG_name;
        output += " game engine.\n\n";

        char trigger_value[512];
        char completion_value[512];

        std::string trigger0 = "\t\t{\"trigger\": \"";
        std::string trigger1 = "\", \"contents\": \"";
        std::string trigger2 = "\" },\n";

        //    std::string sublime_completions = "\n{\n\t\"scope\": \"source.lua
        //    -
        // source - meta.tag, punctuation.definition.tag.begin\",\n";
        //
        //    sublime_completions += "\n\n\t\"completions\":\n\t[\n";

        std::string sublime_completions = "";
        std::vector<std::string> sublime_completion_list;

        // this touches the SWIG internals, please be careful:
        for (int i = 0; swig_types[i]; i++)
        {
            if (swig_types[i]->clientdata)
            {
                swig_lua_class *ptr =
                    (swig_lua_class *)(swig_types[i]->clientdata);

                // if (strcmp(name,ptr->name)==0)
                {
                    //                sprintf("test%sFunctions",
                    //                ptr->name);

                    for (int j = 0; ptr->cls_static->ns_constants[j].name; ++j)
                    {

                        sprintf(trigger_value, "%s",
                                ptr->cls_static->ns_constants[j].name);
                        sprintf(completion_value, "%s.%s", SWIG_name,
                                ptr->cls_static->ns_constants[j].name);

                        std::string completion("");

                        completion += trigger0;
                        completion += trigger_value;
                        completion += trigger1;
                        completion += completion_value;
                        completion += trigger2;

                        std::vector<std::string>::const_iterator iter =
                            std::find(sublime_completion_list.begin(),
                                      sublime_completion_list.end(),
                                      completion);
                        if (iter == sublime_completion_list.end())
                        {
                            sublime_completion_list.push_back(completion);
                        }

                        //                        sublime_completions
                        //                        += completions;
                    }

                    for (int j = 0; ptr->cls_static->ns_methods[j].name; ++j)
                    {
                        sprintf(trigger_value, "static %s.%s", ptr->name,
                                ptr->cls_static->ns_methods[j].name);
                        sprintf(completion_value, "%s.%s.%s", SWIG_name,
                                ptr->name, ptr->cls_static->ns_methods[j].name);

                        std::string completion("");

                        completion += trigger0;
                        completion += trigger_value;
                        completion += trigger1;
                        completion += completion_value;
                        completion += trigger2;

                        std::vector<std::string>::const_iterator iter =
                            std::find(sublime_completion_list.begin(),
                                      sublime_completion_list.end(),
                                      completion);
                        if (iter == sublime_completion_list.end())
                        {
                            sublime_completion_list.push_back(completion);
                        }

                        //                        sublime_completions
                        //                        += completions;
                    }

                    for (int j = 0; ptr->metatable[j].name; ++j)
                    {
                        //                        if(strcmp("Node",
                        //                        ptr->name) == 0)
                        //                        {
                        //                            printf("%s:%s\n",ptr->name,ptr->metatable[j].name);
                        //                        }
                    }
                    for (int j = 0; ptr->methods[j].name; ++j)
                    {
                        //                        if(strcmp("Node",
                        //                        ptr->name) == 0)
                        //                        {
                        //                            printf("%s:%s\n",ptr->name,ptr->methods[j].name);
                        //
                        //                            printf("%s:%s\n",ptr->name,ptr->methods[j].name);
                        //                        }
                    }

                    for (int j = 0; ptr->methods[j].name; ++j)
                    {
                        //                        if(strcmp("Node",
                        //                        ptr->name) == 0)
                        //                        {
                        //                            //
                        //                            swig_lua_method
                        //                            method =
                        //                            ptr->methods[j];
                        //                            sprintf(trigger_value,
                        //                            "%s.%s",ptr->name,ptr->methods[j].name);
                        //                            sprintf(completion_value,
                        //                            "%s",ptr->methods[j].name);
                        //                        }

                        sprintf(trigger_value, "%s.%s", ptr->name,
                                ptr->methods[j].name);
                        sprintf(completion_value, "%s", ptr->methods[j].name);

                        std::string completion("");

                        completion += trigger0;
                        completion += trigger_value;
                        completion += trigger1;
                        completion += completion_value;
                        completion += trigger2;

                        std::vector<std::string>::const_iterator iter =
                            std::find(sublime_completion_list.begin(),
                                      sublime_completion_list.end(),
                                      completion);
                        if (iter == sublime_completion_list.end())
                        {
                            sublime_completion_list.push_back(completion);
                        }

                        //                        sublime_completions
                        //                        += completions;
                    }

                    //                for(int
                    //                j=0;ptr->methods[j].name;j++)
                    //                {
                    //                    sprintf(buffer,
                    //"%s::%s()\n",ptr->name,ptr->methods[j].name);
                    ////                    functions += buffer;
                    // SDL_LogVerbose(SDL_LOG_CATEGORY_TEST,
                    //"%s::%s()\n",ptr->name,ptr->methods[j].name);
                    //                }
                }
            }
        }
        //    sublime_completions += "\t]\n}";
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST,
        //    "%s",sublime_completions.c_str());

        for (std::vector<std::string>::const_iterator iter =
                 sublime_completion_list.begin();
             iter != sublime_completion_list.end(); iter++)
        {
            sublime_completions += *iter;
        }
        return sublime_completions;
        //    Log("%s", functions.c_str());
    }

    int getSublimeCompletions(lua_State * L) // my native code
    {
        lua_pushstring(L, sublimeCompletions().c_str());
        return 1;
    }
    // clang-format off
%}
#if defined(SWIGLUA)
//MARK: %native wrapper doesn't work in an external file.
//%native(my_func) int native_function(lua_State*L);  // registers native_function() with SWIG
%native(build) int build(lua_State*L);  // registers native_function() with SWIG
//...
%{
    // clang-format on
    //    int native_function(lua_State*L) // my native code
    //    {
    //        //...
    //    }

    int build(lua_State * L)
    {
        int SWIG_arg = 0;

        if (lua_gettop(L) < 2 || lua_gettop(L) > 2)
        {
            SWIG_Lua_pushferrstring(L,
                                    "Error in %s expected %d..%d args, got %d",
                                    "create", 2, 2, lua_gettop(L));
            lua_error(L);
            return SWIG_arg;
        }

        if (!((lua_tonumber(L, 1) >= 0)))
        {
            SWIG_Lua_pusherrstring(L, "number must not be negative");
            lua_error(L);
            return SWIG_arg;
        }

        if (!lua_isnumber(L, 2))
        {
            SWIG_Lua_pushferrstring(
                L, "Error in %s (arg %d), expected '%s' got '%s'", "create", 2,
                "u32", SWIG_Lua_typename(L, 2));
            lua_error(L);
            return SWIG_arg;
        }
        if (!lua_istable(L, 1))
        {
            SWIG_Lua_pushferrstring(
                L, "Error in %s (arg %d), expected '%s' got '%s'", "create", 1,
                "table", SWIG_Lua_typename(L, 2));
            lua_error(L);
            return SWIG_arg;
        }

        u32 arg1 = (u32 const)lua_tonumber(L, 2);

        switch (arg1)
        {
        case njli::JLI_OBJECT_TYPE_Action: {
            njli::Action *result = njli::Action::create();
            lua_pop(L, 1);
            njli::Action::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Action, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ActionBuilder: {
            njli::ActionBuilder *result = njli::ActionBuilder::create();
            lua_pop(L, 1);
            njli::ActionBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__ActionBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Camera: {
            njli::Camera *result = njli::Camera::create();
            lua_pop(L, 1);
            njli::Camera::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Camera, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_CameraBuilder: {
            njli::CameraBuilder *result = njli::CameraBuilder::create();
            lua_pop(L, 1);
            njli::CameraBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__CameraBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Clock: {
            njli::Clock *result = njli::Clock::create();
            lua_pop(L, 1);
            njli::Clock::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Clock, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ClockBuilder: {
            njli::ClockBuilder *result = njli::ClockBuilder::create();
            lua_pop(L, 1);
            njli::ClockBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__ClockBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_CollisionResponse: {
            njli::CollisionResponse *result = njli::CollisionResponse::create();
            lua_pop(L, 1);
            njli::CollisionResponse::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__CollisionResponse,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_CollisionResponseBuilder: {
            njli::CollisionResponseBuilder *result =
                njli::CollisionResponseBuilder::create();
            lua_pop(L, 1);
            njli::CollisionResponseBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__CollisionResponseBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Font: {
            njli::Font *result = njli::Font::create();
            lua_pop(L, 1);
            njli::Font::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Font, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_FontBuilder: {
            njli::FontBuilder *result = njli::FontBuilder::create();
            lua_pop(L, 1);
            njli::FontBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__FontBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Image: {
            njli::Image *result = njli::Image::create();
            lua_pop(L, 1);
            njli::Image::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Image, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ImageBuilder: {
            njli::ImageBuilder *result = njli::ImageBuilder::create();
            lua_pop(L, 1);
            njli::ImageBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__ImageBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_JsonJLI: {
            njli::JsonJLI *result = njli::JsonJLI::create();
            lua_pop(L, 1);
            njli::JsonJLI::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__JsonJLI, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_JsonJLIBuilder: {
            njli::JsonJLIBuilder *result = njli::JsonJLIBuilder::create();
            lua_pop(L, 1);
            njli::JsonJLIBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__JsonJLIBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Light: {
            njli::Light *result = njli::Light::create();
            lua_pop(L, 1);
            njli::Light::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Light, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_LightBuilder: {
            njli::LightBuilder *result = njli::LightBuilder::create();
            lua_pop(L, 1);
            njli::LightBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__LightBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_LevelOfDetail: {
            njli::LevelOfDetail *result = njli::LevelOfDetail::create();
            lua_pop(L, 1);
            njli::LevelOfDetail::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__LevelOfDetail, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_LevelOfDetailBuilder: {
            njli::LevelOfDetailBuilder *result =
                njli::LevelOfDetailBuilder::create();
            lua_pop(L, 1);
            njli::LevelOfDetailBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__LevelOfDetailBuilder,
                               0);
            SWIG_arg++;
        }
        break;
            //        case njli::JLI_OBJECT_TYPE_Lua:
            //        {
            //            njli::Lua *result = njli::Lua::create();
            //            lua_pop(L, 1);
            //            njli::Lua::load(*result, L, -1);
            //            SWIG_NewPointerObj(L, result,
            //            SWIGTYPE_p_njli__Lua, 0); SWIG_arg++;
            //        }
            //            break;
            //        case njli::JLI_OBJECT_TYPE_LuaBuilder:
            //        {
            //            njli::LuaBuilder *result =
            //            njli::LuaBuilder::create(); lua_pop(L, 1);
            //            njli::LuaBuilder::load(*result, L, -1);
            //            SWIG_NewPointerObj(L, result,
            //            SWIGTYPE_p_njli__LuaBuilder, 0); SWIG_arg++;
            //        }
            //            break;
        case njli::JLI_OBJECT_TYPE_Material: {
            njli::Material *result = njli::Material::create();
            lua_pop(L, 1);
            njli::Material::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Material, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_MaterialBuilder: {
            njli::MaterialBuilder *result = njli::MaterialBuilder::create();
            lua_pop(L, 1);
            njli::MaterialBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__MaterialBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_MaterialProperty: {
            njli::MaterialProperty *result = njli::MaterialProperty::create();
            lua_pop(L, 1);
            njli::MaterialProperty::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__MaterialProperty, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_MaterialPropertyBuilder: {
            njli::MaterialPropertyBuilder *result =
                njli::MaterialPropertyBuilder::create();
            lua_pop(L, 1);
            njli::MaterialPropertyBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__MaterialPropertyBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Node: {
            njli::Node *result = njli::Node::create();
            lua_pop(L, 1);
            njli::Node::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Node, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_NodeBuilder: {
            njli::NodeBuilder *result = njli::NodeBuilder::create();
            lua_pop(L, 1);
            njli::NodeBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__NodeBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_NodeState: {
            njli::NodeState *result = njli::NodeState::create();
            lua_pop(L, 1);
            njli::NodeState::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__NodeState, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_NodeStateBuilder: {
            njli::NodeStateBuilder *result = njli::NodeStateBuilder::create();
            lua_pop(L, 1);
            njli::NodeStateBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__NodeStateBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_NodeStateMachine: {
            njli::NodeStateMachine *result = njli::NodeStateMachine::create();
            lua_pop(L, 1);
            njli::NodeStateMachine::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__NodeStateMachine, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_NodeStateMachineBuilder: {
            njli::NodeStateMachineBuilder *result =
                njli::NodeStateMachineBuilder::create();
            lua_pop(L, 1);
            njli::NodeStateMachineBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__NodeStateMachineBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ParticleEmitter: {
            njli::ParticleEmitter *result = njli::ParticleEmitter::create();
            lua_pop(L, 1);
            njli::ParticleEmitter::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__ParticleEmitter, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ParticleEmitterBuilder: {
            njli::ParticleEmitterBuilder *result =
                njli::ParticleEmitterBuilder::create();
            lua_pop(L, 1);
            njli::ParticleEmitterBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__ParticleEmitterBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsBodyGhost: {
            njli::PhysicsBodyGhost *result = njli::PhysicsBodyGhost::create();
            lua_pop(L, 1);
            njli::PhysicsBodyGhost::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsBodyGhost, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsBodyGhostBuilder: {
            njli::PhysicsBodyGhostBuilder *result =
                njli::PhysicsBodyGhostBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsBodyGhostBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsBodyGhostBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsBodyRigid: {
            njli::PhysicsBodyRigid *result = njli::PhysicsBodyRigid::create();
            lua_pop(L, 1);
            njli::PhysicsBodyRigid::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsBodyRigid, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsBodyRigidBuilder: {
            njli::PhysicsBodyRigidBuilder *result =
                njli::PhysicsBodyRigidBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsBodyRigidBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsBodyRigidBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsBodySoft: {
            njli::PhysicsBodySoft *result = njli::PhysicsBodySoft::create();
            lua_pop(L, 1);
            njli::PhysicsBodySoft::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsBodySoft, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsBodySoftBuilder: {
            njli::PhysicsBodySoftBuilder *result =
                njli::PhysicsBodySoftBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsBodySoftBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsBodySoftBuilder, 0);
            SWIG_arg++;
        }

        case njli::JLI_OBJECT_TYPE_PhysicsConstraint: {
            njli::PhysicsConstraint *result = njli::PhysicsConstraint::create();
            lua_pop(L, 1);
            njli::PhysicsConstraint::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsConstraint,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintBuilder: {
            njli::PhysicsConstraintBuilder *result =
                njli::PhysicsConstraintBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsConstraintBuilder, 0);
            SWIG_arg++;
        }

        case njli::JLI_OBJECT_TYPE_PhysicsConstraintHinge: {
            njli::PhysicsConstraintHinge *result =
                njli::PhysicsConstraintHinge::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintHinge::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsConstraintHinge, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintHingeBuilder: {
            njli::PhysicsConstraintHingeBuilder *result =
                njli::PhysicsConstraintHingeBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintHingeBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintHingeBuilder, 0);
            SWIG_arg++;
        }

        case njli::JLI_OBJECT_TYPE_PhysicsConstraintPointToPoint: {
            njli::PhysicsConstraintPointToPoint *result =
                njli::PhysicsConstraintPointToPoint::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintPointToPoint::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintPointToPoint, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintPointToPointBuilder: {
            njli::PhysicsConstraintPointToPointBuilder *result =
                njli::PhysicsConstraintPointToPointBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintPointToPointBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__PhysicsConstraintPointToPointBuilder, 0);
            SWIG_arg++;
        }

        case njli::JLI_OBJECT_TYPE_PhysicsConstraintSlider: {
            njli::PhysicsConstraintSlider *result =
                njli::PhysicsConstraintSlider::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintSlider::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsConstraintSlider, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintSliderBuilder: {
            njli::PhysicsConstraintSliderBuilder *result =
                njli::PhysicsConstraintSliderBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintSliderBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintSliderBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintConeTwist: {
            njli::PhysicsConstraintConeTwist *result =
                njli::PhysicsConstraintConeTwist::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintConeTwist::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsConstraintConeTwist, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintConeTwistBuilder: {
            njli::PhysicsConstraintConeTwistBuilder *result =
                njli::PhysicsConstraintConeTwistBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintConeTwistBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintConeTwistBuilder,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintFixed: {
            njli::PhysicsConstraintFixed *result =
                njli::PhysicsConstraintFixed::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintFixed::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsConstraintFixed, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintFixedBuilder: {
            njli::PhysicsConstraintFixedBuilder *result =
                njli::PhysicsConstraintFixedBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintFixedBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintFixedBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintGeneric6Dof: {
            njli::PhysicsConstraintGeneric6Dof *result =
                njli::PhysicsConstraintGeneric6Dof::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintGeneric6Dof::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintGeneric6Dof, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofBuilder: {
            njli::PhysicsConstraintGeneric6DofBuilder *result =
                njli::PhysicsConstraintGeneric6DofBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintGeneric6DofBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintGeneric6DofBuilder,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpring: {
            njli::PhysicsConstraintGeneric6DofSpring *result =
                njli::PhysicsConstraintGeneric6DofSpring::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintGeneric6DofSpring::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsConstraintGeneric6DofSpring,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsConstraintGeneric6DofSpringBuilder: {
            njli::PhysicsConstraintGeneric6DofSpringBuilder *result =
                njli::PhysicsConstraintGeneric6DofSpringBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsConstraintGeneric6DofSpringBuilder::load(*result, L,
                                                                  -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__PhysicsConstraintGeneric6DofSpringBuilder, 0);
            SWIG_arg++;
        }
        break;

            break;
        case njli::JLI_OBJECT_TYPE_PhysicsCloseContact: {
            njli::PhysicsCloseContact *result =
                njli::PhysicsCloseContact::create();
            lua_pop(L, 1);
            njli::PhysicsCloseContact::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsCloseContact,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsCloseContactBuilder: {
            njli::PhysicsCloseContactBuilder *result =
                njli::PhysicsCloseContactBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsCloseContactBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsCloseContactBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsContact: {
            njli::PhysicsContact *result = njli::PhysicsContact::create();
            lua_pop(L, 1);
            njli::PhysicsContact::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsContact, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsContactBuilder: {
            njli::PhysicsContactBuilder *result =
                njli::PhysicsContactBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsContactBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsContactBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsField: {
            njli::PhysicsField *result = njli::PhysicsField::create();
            lua_pop(L, 1);
            njli::PhysicsField::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsField, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsFieldBuilder: {
            njli::PhysicsFieldBuilder *result =
                njli::PhysicsFieldBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsFieldBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsFieldBuilder,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsRayContact: {
            njli::PhysicsRayContact *result = njli::PhysicsRayContact::create();
            lua_pop(L, 1);
            njli::PhysicsRayContact::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsRayContact,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsRayContactBuilder: {
            njli::PhysicsRayContactBuilder *result =
                njli::PhysicsRayContactBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsRayContactBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsRayContactBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeBox: {
            njli::PhysicsShapeBox *result = njli::PhysicsShapeBox::create();
            lua_pop(L, 1);
            njli::PhysicsShapeBox::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsShapeBox, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeBoxBuilder: {
            njli::PhysicsShapeBoxBuilder *result =
                njli::PhysicsShapeBoxBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeBoxBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeBoxBuilder, 0);
            SWIG_arg++;
        }
        break;

        case njli::JLI_OBJECT_TYPE_PhysicsShapeBox2D: {
            njli::PhysicsShapeBox2D *result = njli::PhysicsShapeBox2D::create();
            lua_pop(L, 1);
            njli::PhysicsShapeBox2D::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsShapeBox2D,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeBox2DBuilder: {
            njli::PhysicsShapeBox2DBuilder *result =
                njli::PhysicsShapeBox2DBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeBox2DBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeBox2DBuilder, 0);
            SWIG_arg++;
        }
        break;

        case njli::JLI_OBJECT_TYPE_PhysicsShapeSphere: {
            njli::PhysicsShapeSphere *result =
                njli::PhysicsShapeSphere::create();
            lua_pop(L, 1);
            njli::PhysicsShapeSphere::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsShapeSphere,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeSphereBuilder: {
            njli::PhysicsShapeSphereBuilder *result =
                njli::PhysicsShapeSphereBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeSphereBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeSphereBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeCylinder: {
            njli::PhysicsShapeCylinder *result =
                njli::PhysicsShapeCylinder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeCylinder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsShapeCylinder,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeCylinderBuilder: {
            njli::PhysicsShapeCylinderBuilder *result =
                njli::PhysicsShapeCylinderBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeCylinderBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeCylinderBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeCapsule: {
            njli::PhysicsShapeCapsule *result =
                njli::PhysicsShapeCapsule::create();
            lua_pop(L, 1);
            njli::PhysicsShapeCapsule::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsShapeCapsule,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeCapsuleBuilder: {
            njli::PhysicsShapeCapsuleBuilder *result =
                njli::PhysicsShapeCapsuleBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeCapsuleBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeCapsuleBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeCone: {
            njli::PhysicsShapeCone *result = njli::PhysicsShapeCone::create();
            lua_pop(L, 1);
            njli::PhysicsShapeCone::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsShapeCone, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeConeBuilder: {
            njli::PhysicsShapeConeBuilder *result =
                njli::PhysicsShapeConeBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeConeBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeConeBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeMultiSphere: {
            njli::PhysicsShapeMultiSphere *result =
                njli::PhysicsShapeMultiSphere::create();
            lua_pop(L, 1);
            njli::PhysicsShapeMultiSphere::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeMultiSphere, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeMultiSphereBuilder: {
            njli::PhysicsShapeMultiSphereBuilder *result =
                njli::PhysicsShapeMultiSphereBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeMultiSphereBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsShapeMultiSphereBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeConvexHull: {
            njli::PhysicsShapeConvexHull *result =
                njli::PhysicsShapeConvexHull::create();
            lua_pop(L, 1);
            njli::PhysicsShapeConvexHull::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeConvexHull, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeConvexHullBuilder: {
            njli::PhysicsShapeConvexHullBuilder *result =
                njli::PhysicsShapeConvexHullBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeConvexHullBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsShapeConvexHullBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMesh: {
            njli::PhysicsShapeConvexTriangleMesh *result =
                njli::PhysicsShapeConvexTriangleMesh::create();
            lua_pop(L, 1);
            njli::PhysicsShapeConvexTriangleMesh::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsShapeConvexTriangleMesh, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeConvexTriangleMeshBuilder: {
            njli::PhysicsShapeConvexTriangleMeshBuilder *result =
                njli::PhysicsShapeConvexTriangleMeshBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeConvexTriangleMeshBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__PhysicsShapeConvexTriangleMeshBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMesh: {
            njli::PhysicsShapeBvhTriangleMesh *result =
                njli::PhysicsShapeBvhTriangleMesh::create();
            lua_pop(L, 1);
            njli::PhysicsShapeBvhTriangleMesh::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeBvhTriangleMesh, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeBvhTriangleMeshBuilder: {
            njli::PhysicsShapeBvhTriangleMeshBuilder *result =
                njli::PhysicsShapeBvhTriangleMeshBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeBvhTriangleMeshBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsShapeBvhTriangleMeshBuilder,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrain: {
            njli::PhysicsShapeHeightfieldTerrain *result =
                njli::PhysicsShapeHeightfieldTerrain::create();
            lua_pop(L, 1);
            njli::PhysicsShapeHeightfieldTerrain::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsShapeHeightfieldTerrain, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeHeightfieldTerrainBuilder: {
            njli::PhysicsShapeHeightfieldTerrainBuilder *result =
                njli::PhysicsShapeHeightfieldTerrainBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeHeightfieldTerrainBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__PhysicsShapeHeightfieldTerrainBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeStaticPlane: {
            njli::PhysicsShapeStaticPlane *result =
                njli::PhysicsShapeStaticPlane::create();
            lua_pop(L, 1);
            njli::PhysicsShapeStaticPlane::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__PhysicsShapeStaticPlane, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsShapeStaticPlaneBuilder: {
            njli::PhysicsShapeStaticPlaneBuilder *result =
                njli::PhysicsShapeStaticPlaneBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsShapeStaticPlaneBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__PhysicsShapeStaticPlaneBuilder, 0);
            SWIG_arg++;
        }
        break;

        case njli::JLI_OBJECT_TYPE_PhysicsWorld: {
            njli::PhysicsWorld *result = njli::PhysicsWorld::create();
            lua_pop(L, 1);
            njli::PhysicsWorld::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsWorld, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PhysicsWorldBuilder: {
            njli::PhysicsWorldBuilder *result =
                njli::PhysicsWorldBuilder::create();
            lua_pop(L, 1);
            njli::PhysicsWorldBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PhysicsWorldBuilder,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Plane: {
            njli::Plane *result = njli::Plane::create();
            lua_pop(L, 1);
            njli::Plane::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Plane, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_PlaneBuilder: {
            njli::PlaneBuilder *result = njli::PlaneBuilder::create();
            lua_pop(L, 1);
            njli::PlaneBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__PlaneBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Scene: {
            njli::Scene *result = njli::Scene::create();
            lua_pop(L, 1);
            njli::Scene::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Scene, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SceneBuilder: {
            njli::SceneBuilder *result = njli::SceneBuilder::create();
            lua_pop(L, 1);
            njli::SceneBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SceneBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SceneState: {
            njli::SceneState *result = njli::SceneState::create();
            lua_pop(L, 1);
            njli::SceneState::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SceneState, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SceneStateBuilder: {
            njli::SceneStateBuilder *result = njli::SceneStateBuilder::create();
            lua_pop(L, 1);
            njli::SceneStateBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SceneStateBuilder,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SceneStateMachine: {
            njli::SceneStateMachine *result = njli::SceneStateMachine::create();
            lua_pop(L, 1);
            njli::SceneStateMachine::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SceneStateMachine,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SceneStateMachineBuilder: {
            njli::SceneStateMachineBuilder *result =
                njli::SceneStateMachineBuilder::create();
            lua_pop(L, 1);
            njli::SceneStateMachineBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SceneStateMachineBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ShaderProgram: {
            njli::ShaderProgram *result = njli::ShaderProgram::create();
            lua_pop(L, 1);
            njli::ShaderProgram::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__ShaderProgram, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ShaderProgramBuilder: {
            njli::ShaderProgramBuilder *result =
                njli::ShaderProgramBuilder::create();
            lua_pop(L, 1);
            njli::ShaderProgramBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__ShaderProgramBuilder,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Skinner: {
            njli::Skinner *result = njli::Skinner::create();
            lua_pop(L, 1);
            njli::Skinner::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Skinner, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SkinnerBuilder: {
            njli::SkinnerBuilder *result = njli::SkinnerBuilder::create();
            lua_pop(L, 1);
            njli::SkinnerBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SkinnerBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Sound: {
            njli::Sound *result = njli::Sound::create();
            lua_pop(L, 1);
            njli::Sound::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Sound, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SoundBuilder: {
            njli::SoundBuilder *result = njli::SoundBuilder::create();
            lua_pop(L, 1);
            njli::SoundBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SoundBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Sprite2D: {
            njli::Sprite2D *result = njli::Sprite2D::create();
            lua_pop(L, 1);
            njli::Sprite2D::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Sprite2D, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Sprite2DBuilder: {
            njli::Sprite2DBuilder *result = njli::Sprite2DBuilder::create();
            lua_pop(L, 1);
            njli::Sprite2DBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Sprite2DBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SpriteFrameAtlas: {
            njli::SpriteFrameAtlas *result = njli::SpriteFrameAtlas::create();
            lua_pop(L, 1);
            njli::SpriteFrameAtlas::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SpriteFrameAtlas, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SpriteFrameAtlasBuilder: {
            njli::SpriteFrameAtlasBuilder *result =
                njli::SpriteFrameAtlasBuilder::create();
            lua_pop(L, 1);
            njli::SpriteFrameAtlasBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SpriteFrameAtlasBuilder, 0);
            SWIG_arg++;
        }
        break;

        case njli::JLI_OBJECT_TYPE_SteeringBehavior: {
            njli::SteeringBehavior *result = njli::SteeringBehavior::create();
            lua_pop(L, 1);
            njli::SteeringBehavior::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SteeringBehavior, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorBuilder: {
            njli::SteeringBehaviorBuilder *result =
                njli::SteeringBehaviorBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorAlignment: {
            njli::SteeringBehaviorAlignment *result =
                njli::SteeringBehaviorAlignment::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorAlignment::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorAlignment, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorAlignmentBuilder: {
            njli::SteeringBehaviorAlignmentBuilder *result =
                njli::SteeringBehaviorAlignmentBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorAlignmentBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorAlignmentBuilder,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorArrive: {
            njli::SteeringBehaviorArrive *result =
                njli::SteeringBehaviorArrive::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorArrive::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorArrive, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorArriveBuilder: {
            njli::SteeringBehaviorArriveBuilder *result =
                njli::SteeringBehaviorArriveBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorArriveBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorArriveBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorCohesion: {
            njli::SteeringBehaviorCohesion *result =
                njli::SteeringBehaviorCohesion::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorCohesion::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorCohesion, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorCohesionBuilder: {
            njli::SteeringBehaviorCohesionBuilder *result =
                njli::SteeringBehaviorCohesionBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorCohesionBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorCohesionBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorEvade: {
            njli::SteeringBehaviorEvade *result =
                njli::SteeringBehaviorEvade::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorEvade::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorEvade, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorEvadeBuilder: {
            njli::SteeringBehaviorEvadeBuilder *result =
                njli::SteeringBehaviorEvadeBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorEvadeBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorEvadeBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorFlee: {
            njli::SteeringBehaviorFlee *result =
                njli::SteeringBehaviorFlee::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorFlee::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SteeringBehaviorFlee,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorFleeBuilder: {
            njli::SteeringBehaviorFleeBuilder *result =
                njli::SteeringBehaviorFleeBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorFleeBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorFleeBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorFollowPath: {
            njli::SteeringBehaviorFollowPath *result =
                njli::SteeringBehaviorFollowPath::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorFollowPath::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorFollowPath, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorFollowPathBuilder: {
            njli::SteeringBehaviorFollowPathBuilder *result =
                njli::SteeringBehaviorFollowPathBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorFollowPathBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorFollowPathBuilder,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorHide: {
            njli::SteeringBehaviorHide *result =
                njli::SteeringBehaviorHide::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorHide::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SteeringBehaviorHide,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorHideBuilder: {
            njli::SteeringBehaviorHideBuilder *result =
                njli::SteeringBehaviorHideBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorHideBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorHideBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorInterpose: {
            njli::SteeringBehaviorInterpose *result =
                njli::SteeringBehaviorInterpose::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorInterpose::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorInterpose, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorInterposeBuilder: {
            njli::SteeringBehaviorInterposeBuilder *result =
                njli::SteeringBehaviorInterposeBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorInterposeBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorInterposeBuilder,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachine: {
            njli::SteeringBehaviorMachine *result =
                njli::SteeringBehaviorMachine::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachine::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorMachine, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachineBuilder: {
            njli::SteeringBehaviorMachineBuilder *result =
                njli::SteeringBehaviorMachineBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachineBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorMachineBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachineDithered: {
            njli::SteeringBehaviorMachineDithered *result =
                njli::SteeringBehaviorMachineDithered::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachineDithered::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorMachineDithered, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachineDitheredBuilder: {
            njli::SteeringBehaviorMachineDitheredBuilder *result =
                njli::SteeringBehaviorMachineDitheredBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachineDitheredBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__SteeringBehaviorMachineDitheredBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritized: {
            njli::SteeringBehaviorMachinePrioritized *result =
                njli::SteeringBehaviorMachinePrioritized::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachinePrioritized::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorMachinePrioritized,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachinePrioritizedBuilder: {
            njli::SteeringBehaviorMachinePrioritizedBuilder *result =
                njli::SteeringBehaviorMachinePrioritizedBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachinePrioritizedBuilder::load(*result, L,
                                                                  -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__SteeringBehaviorMachinePrioritizedBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachineWeighted: {
            njli::SteeringBehaviorMachineWeighted *result =
                njli::SteeringBehaviorMachineWeighted::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachineWeighted::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorMachineWeighted, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorMachineWeightedBuilder: {
            njli::SteeringBehaviorMachineWeightedBuilder *result =
                njli::SteeringBehaviorMachineWeightedBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorMachineWeightedBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__SteeringBehaviorMachineWeightedBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidance: {
            njli::SteeringBehaviorObstacleAvoidance *result =
                njli::SteeringBehaviorObstacleAvoidance::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorObstacleAvoidance::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorObstacleAvoidance,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorObstacleAvoidanceBuilder: {
            njli::SteeringBehaviorObstacleAvoidanceBuilder *result =
                njli::SteeringBehaviorObstacleAvoidanceBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorObstacleAvoidanceBuilder::load(*result, L,
                                                                 -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__SteeringBehaviorObstacleAvoidanceBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuit: {
            njli::SteeringBehaviorOffsetPursuit *result =
                njli::SteeringBehaviorOffsetPursuit::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorOffsetPursuit::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorOffsetPursuit, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorOffsetPursuitBuilder: {
            njli::SteeringBehaviorOffsetPursuitBuilder *result =
                njli::SteeringBehaviorOffsetPursuitBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorOffsetPursuitBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__SteeringBehaviorOffsetPursuitBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorPursuit: {
            njli::SteeringBehaviorPursuit *result =
                njli::SteeringBehaviorPursuit::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorPursuit::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorPursuit, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorPursuitBuilder: {
            njli::SteeringBehaviorPursuitBuilder *result =
                njli::SteeringBehaviorPursuitBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorPursuitBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorPursuitBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorSeek: {
            njli::SteeringBehaviorSeek *result =
                njli::SteeringBehaviorSeek::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorSeek::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__SteeringBehaviorSeek,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorSeekBuilder: {
            njli::SteeringBehaviorSeekBuilder *result =
                njli::SteeringBehaviorSeekBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorSeekBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorSeekBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorSeparation: {
            njli::SteeringBehaviorSeparation *result =
                njli::SteeringBehaviorSeparation::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorSeparation::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorSeparation, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorSeparationBuilder: {
            njli::SteeringBehaviorSeparationBuilder *result =
                njli::SteeringBehaviorSeparationBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorSeparationBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorSeparationBuilder,
                0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidance: {
            njli::SteeringBehaviorWallAvoidance *result =
                njli::SteeringBehaviorWallAvoidance::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorWallAvoidance::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorWallAvoidance, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorWallAvoidanceBuilder: {
            njli::SteeringBehaviorWallAvoidanceBuilder *result =
                njli::SteeringBehaviorWallAvoidanceBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorWallAvoidanceBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result,
                SWIGTYPE_p_njli__SteeringBehaviorWallAvoidanceBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorWander: {
            njli::SteeringBehaviorWander *result =
                njli::SteeringBehaviorWander::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorWander::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__SteeringBehaviorWander, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_SteeringBehaviorWanderBuilder: {
            njli::SteeringBehaviorWanderBuilder *result =
                njli::SteeringBehaviorWanderBuilder::create();
            lua_pop(L, 1);
            njli::SteeringBehaviorWanderBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(
                L, result, SWIGTYPE_p_njli__SteeringBehaviorWanderBuilder, 0);
            SWIG_arg++;
        }
        break;

        case njli::JLI_OBJECT_TYPE_StopWatch: {
            njli::StopWatch *result = njli::StopWatch::create();
            lua_pop(L, 1);
            njli::StopWatch::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__StopWatch, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_StopWatchBuilder: {
            njli::StopWatchBuilder *result = njli::StopWatchBuilder::create();
            lua_pop(L, 1);
            njli::StopWatchBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__StopWatchBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Timer: {
            njli::Timer *result = njli::Timer::create();
            lua_pop(L, 1);
            njli::Timer::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Timer, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_TimerBuilder: {
            njli::TimerBuilder *result = njli::TimerBuilder::create();
            lua_pop(L, 1);
            njli::TimerBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__TimerBuilder, 0);
            SWIG_arg++;
        }
        break;

        case njli::JLI_OBJECT_TYPE_Thread: {
            njli::Thread *result = njli::Thread::create();
            lua_pop(L, 1);
            njli::Thread::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Thread, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_ThreadBuilder: {
            njli::ThreadBuilder *result = njli::ThreadBuilder::create();
            lua_pop(L, 1);
            njli::ThreadBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__ThreadBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_WorldState: {
            njli::WorldState *result = njli::WorldState::create();
            lua_pop(L, 1);
            njli::WorldState::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__WorldState, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_WorldStateBuilder: {
            njli::WorldStateBuilder *result = njli::WorldStateBuilder::create();
            lua_pop(L, 1);
            njli::WorldStateBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__WorldStateBuilder,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_WorldStateMachine: {
            njli::WorldStateMachine *result = njli::WorldStateMachine::create();
            lua_pop(L, 1);
            njli::WorldStateMachine::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__WorldStateMachine,
                               0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_WorldStateMachineBuilder: {
            njli::WorldStateMachineBuilder *result =
                njli::WorldStateMachineBuilder::create();
            lua_pop(L, 1);
            njli::WorldStateMachineBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result,
                               SWIGTYPE_p_njli__WorldStateMachineBuilder, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_Xml: {
            njli::Xml *result = njli::Xml::create();
            lua_pop(L, 1);
            njli::Xml::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__Xml, 0);
            SWIG_arg++;
        }
        break;
        case njli::JLI_OBJECT_TYPE_XmlBuilder: {
            njli::XmlBuilder *result = njli::XmlBuilder::create();
            lua_pop(L, 1);
            njli::XmlBuilder::load(*result, L, -1);
            SWIG_NewPointerObj(L, result, SWIGTYPE_p_njli__XmlBuilder, 0);
            SWIG_arg++;
        }
        break;
        default:
            lua_error(L);
            return SWIG_arg;
        }

        return SWIG_arg;
    }
    // clang-format off

    %}
#endif //SWIGLUA

//#########################################################################################################
//Interface files to Public interface
//#########################################################################################################
//%include "AbstractActionable.swg"
//%include "AbstractBuilder.swg"
//%include "AbstractClock.swg"
//%include "AbstractDecorator.swg"
//%include "AbstractFactoryObject.swg"
//%include "AbstractFrameBufferObject.swg"
//%include "AbstractObject.swg"
//%include "AbstractRender.swg"
//%include "AbstractState.swg"
//%include "AbstractStateMachine.swg"
//%include "AbstractTransform.swg"
//%include "AbstractPhysicsBody.swg"
//%include "AbstractPhysicsShape.swg"
//%include "AbstractGeometry.swg"
%include "Action.swg"
%include "ActionBuilder.swg"
%include "Camera.swg"
%include "CameraBuilder.swg"
%include "Clock.swg"
%include "ClockBuilder.swg"
%include "CollisionResponse.swg"
%include "CollisionResponseBuilder.swg"
%include "Cube.swg"
%include "CubeBuilder.swg"
%include "Font.swg"
%include "FontBuilder.swg"
//%include "GameClock.swg"
%include "Geometry.swg"
%include "Image.swg"
%include "ImageBuilder.swg"
//%include "JLIBuilders.swg"
//%include "JLIEngine.swg"
//%include "JLIFactoryTypes.swg"
//%include "JLITransform.swg"
%include "JsonJLI.swg"
%include "JsonJLIBuilder.swg"
%include "LevelOfDetail.swg"
%include "LevelOfDetailBuilder.swg"
%include "Light.swg"
%include "LightBuilder.swg"
//%include "LuaBuilder.swg"
%include "Material.swg"
%include "MaterialBuilder.swg"
%include "MaterialProperty.swg"
%include "MaterialPropertyBuilder.swg"
%include "MeshGeometry.swg"
%include "MeshGeometryBuilder.swg"
%include "Node.swg"
%include "NodeBuilder.swg"
%include "NodeState.swg"
%include "NodeStateBuilder.swg"
%include "NodeStateMachine.swg"
%include "NodeStateMachineBuilder.swg"
%include "ParticleEmitter.swg"
%include "ParticleEmitterBuilder.swg"
%include "Path.swg"
%include "PhysicsBody.swg"
%include "PhysicsBodyGhost.swg"
%include "PhysicsBodyGhostBuilder.swg"
%include "PhysicsBodyRigid.swg"
%include "PhysicsBodyRigidBuilder.swg"
%include "PhysicsBodySoft.swg"
%include "PhysicsBodySoftBuilder.swg"
%include "PhysicsCloseContact.swg"
%include "PhysicsCloseContactBuilder.swg"
%include "PhysicsConstraint.swg"
%include "PhysicsConstraintBuilder.swg"
%include "PhysicsConstraintConeTwist.swg"
%include "PhysicsConstraintConeTwistBuilder.swg"
%include "PhysicsConstraintFixed.swg"
%include "PhysicsConstraintFixedBuilder.swg"
%include "PhysicsConstraintGeneric6Dof.swg"
%include "PhysicsConstraintGeneric6DofBuilder.swg"
%include "PhysicsConstraintGeneric6DofSpring.swg"
%include "PhysicsConstraintGeneric6DofSpringBuilder.swg"
%include "PhysicsConstraintHinge.swg"
%include "PhysicsConstraintHingeBuilder.swg"
%include "PhysicsConstraintPointToPoint.swg"
%include "PhysicsConstraintPointToPointBuilder.swg"
%include "PhysicsConstraintSlider.swg"
%include "PhysicsConstraintSliderBuilder.swg"
%include "PhysicsContact.swg"
%include "PhysicsContactBuilder.swg"
%include "PhysicsField.swg"
%include "PhysicsFieldBuilder.swg"
%include "PhysicsRayContact.swg"
%include "PhysicsRayContactBuilder.swg"
%include "PhysicsShape.swg"
%include "PhysicsShapeBox.swg"
%include "PhysicsShapeBox2D.swg"
%include "PhysicsShapeBox2DBuilder.swg"
%include "PhysicsShapeBoxBuilder.swg"
%include "PhysicsShapeBvhTriangleMesh.swg"
%include "PhysicsShapeBvhTriangleMeshBuilder.swg"
%include "PhysicsShapeCapsule.swg"
%include "PhysicsShapeCapsuleBuilder.swg"
%include "PhysicsShapeCone.swg"
%include "PhysicsShapeConeBuilder.swg"
%include "PhysicsShapeConvexHull.swg"
%include "PhysicsShapeConvexHullBuilder.swg"
%include "PhysicsShapeConvexTriangleMesh.swg"
%include "PhysicsShapeConvexTriangleMeshBuilder.swg"
%include "PhysicsShapeCylinder.swg"
%include "PhysicsShapeCylinderBuilder.swg"
%include "PhysicsShapeHeightfieldTerrain.swg"
%include "PhysicsShapeHeightfieldTerrainBuilder.swg"
%include "PhysicsShapeMultiSphere.swg"
%include "PhysicsShapeMultiSphereBuilder.swg"
%include "PhysicsShapeSphere.swg"
%include "PhysicsShapeSphereBuilder.swg"
%include "PhysicsShapeStaticPlane.swg"
%include "PhysicsShapeStaticPlaneBuilder.swg"
%include "PhysicsWorld.swg"
%include "PhysicsWorldBuilder.swg"
%include "Plane.swg"
%include "PlaneBuilder.swg"
%include "Scene.swg"
%include "SceneBuilder.swg"
%include "SceneState.swg"
%include "SceneStateBuilder.swg"
%include "SceneStateMachine.swg"
%include "SceneStateMachineBuilder.swg"
%include "ShaderProgram.swg"
%include "ShaderProgramBuilder.swg"
%include "Skinner.swg"
%include "SkinnerBuilder.swg"
%include "SoundBuilder.swg"
%include "Sprite2D.swg"
%include "Sprite2DBuilder.swg"
%include "SpriteFrameAtlas.swg"
%include "SpriteFrameAtlasBuilder.swg"

%include "SteeringBehavior.swg"
%include "SteeringBehaviorBuilder.swg"
%include "SteeringBehaviorAlignment.swg"
%include "SteeringBehaviorAlignmentBuilder.swg"
%include "SteeringBehaviorArrive.swg"
%include "SteeringBehaviorArriveBuilder.swg"
%include "SteeringBehaviorCohesion.swg"
%include "SteeringBehaviorCohesionBuilder.swg"
%include "SteeringBehaviorEvade.swg"
%include "SteeringBehaviorEvadeBuilder.swg"
%include "SteeringBehaviorFlee.swg"
%include "SteeringBehaviorFleeBuilder.swg"
%include "SteeringBehaviorFollowPath.swg"
%include "SteeringBehaviorFollowPathBuilder.swg"
%include "SteeringBehaviorHide.swg"
%include "SteeringBehaviorHideBuilder.swg"
%include "SteeringBehaviorInterpose.swg"
%include "SteeringBehaviorInterposeBuilder.swg"
%include "SteeringBehaviorMachine.swg"
%include "SteeringBehaviorMachineBuilder.swg"
%include "SteeringBehaviorMachineDithered.swg"
%include "SteeringBehaviorMachineDitheredBuilder.swg"
%include "SteeringBehaviorMachinePrioritized.swg"
%include "SteeringBehaviorMachinePrioritizedBuilder.swg"
%include "SteeringBehaviorMachineWeighted.swg"
%include "SteeringBehaviorMachineWeightedBuilder.swg"
%include "SteeringBehaviorObstacleAvoidance.swg"
%include "SteeringBehaviorObstacleAvoidanceBuilder.swg"
%include "SteeringBehaviorOffsetPursuit.swg"
%include "SteeringBehaviorOffsetPursuitBuilder.swg"
%include "SteeringBehaviorPursuit.swg"
%include "SteeringBehaviorPursuitBuilder.swg"
%include "SteeringBehaviorSeek.swg"
%include "SteeringBehaviorSeekBuilder.swg"
%include "SteeringBehaviorSeparation.swg"
%include "SteeringBehaviorSeparationBuilder.swg"
%include "SteeringBehaviorWallAvoidance.swg"
%include "SteeringBehaviorWallAvoidanceBuilder.swg"
%include "SteeringBehaviorWander.swg"
%include "SteeringBehaviorWanderBuilder.swg"
%include "StopWatch.swg"
%include "StopWatchBuilder.swg"
%include "Thread.swg"
%include "ThreadBuilder.swg"
%include "Timer.swg"
%include "TimerBuilder.swg"
%include "World.swg"
%include "WorldClock.swg"
%include "WorldDebugDrawer.swg"
%include "WorldFactory.swg"
#ifdef USE_NANOVG_LIBRARY
    %include "ButtonHUD.swg"
    %include "ButtonHUDBuilder.swg"
    %include "CheckboxHUD.swg"
    %include "CheckboxHUDBuilder.swg"
    %include "DropdownHUD.swg"
    %include "DropdownHUDBuilder.swg"
    %include "LabelHUD.swg"
    %include "LabelHUDBuilder.swg"
    %include "SliderHUD.swg"
    %include "SliderHUDBuilder.swg"
    %include "TextboxHUD.swg"
    %include "TextboxHUDBuilder.swg"
    %include "WorldHUD.swg"
#endif
%include "WorldLuaVirtualMachine.swg"
%include "WorldResourceLoader.swg"
//%include "WorldSQLite.swg"
%include "WorldSocket.swg"
%include "WorldState.swg"
%include "WorldStateBuilder.swg"
%include "WorldStateMachine.swg"
%include "WorldStateMachineBuilder.swg"
%include "Xml.swg"
%include "XmlBuilder.swg"
//#########################################################################################################
%include "DeviceInputTime.swg"
%include "DeviceTouch.swg"
%include "File.swg"
%include "Localization.swg"
%include "Log.swg"
%include "Macros.swg"
%include "Sound.swg"
%include "Util.swg"
%include "ColorUtil.swg"
%include "WorldInput.swg"
%include "WorldSound.swg"

    // clang-format on
