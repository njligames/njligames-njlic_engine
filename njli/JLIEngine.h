//
//  JLIEngine.h
//  JLIGameEngineTest
//
//  Created by James Folk on 11/22/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#ifndef JLIGameEngineTest_JLIEngine_h
#define JLIGameEngineTest_JLIEngine_h

#include "AbstractActionable.h"
#include "AbstractBuilder.h"
#include "AbstractClock.h"
#include "AbstractDecorator.h"
#include "AbstractFactoryObject.h"
#include "AbstractFrameBufferObject.h"
#include "AbstractObject.h"
#include "AbstractState.h"
#include "AbstractStateMachine.h"
//#include "AbstractTransform.h"

#include "JLIFactoryTypes.h"
#include "PhysicsBody.h"
//#include "JLITransform.h"
#include "Geometry.h"
#include "PhysicsShape.h"

#include "World.h"
#include "WorldFactory.h"
#include "WorldLuaVirtualMachine.h"
#include "WorldSQLite.h"
//#include "WorldPythonVirtualMachine.h"
#include "WorldClock.h"
#include "WorldDebugDrawer.h"
#include "WorldResourceLoader.h"
#include "WorldSocket.h"
//#include "WorldFacebook.h"
//#include "WorldInput.h"

#pragma mark Start AbstractFactoryObjects includes

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
#include "Image.h"
#include "ImageBuilder.h"
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
#include "Node.h"
#include "NodeBuilder.h"
#include "NodeState.h"
#include "NodeStateBuilder.h"
#include "NodeStateMachine.h"
#include "NodeStateMachineBuilder.h"
#include "ParticleEmitter.h"
#include "ParticleEmitterBuilder.h"
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
#include "PhysicsConstraintHinge.h"
#include "PhysicsConstraintHingeBuilder.h"
#include "PhysicsConstraintPointToPoint.h"
#include "PhysicsConstraintPointToPointBuilder.h"

#include "PhysicsConstraintConeTwist.h"
#include "PhysicsConstraintConeTwistBuilder.h"
#include "PhysicsConstraintFixed.h"
#include "PhysicsConstraintFixedBuilder.h"
#include "PhysicsConstraintGeneric6Dof.h"
#include "PhysicsConstraintGeneric6DofBuilder.h"
#include "PhysicsConstraintGeneric6DofSpring.h"
#include "PhysicsConstraintGeneric6DofSpringBuilder.h"
#include "PhysicsConstraintSlider.h"
#include "PhysicsConstraintSliderBuilder.h"

#include "PhysicsContact.h"
#include "PhysicsContactBuilder.h"
#include "PhysicsField.h"
#include "PhysicsFieldBuilder.h"
#include "PhysicsRayContact.h"
#include "PhysicsRayContactBuilder.h"
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
#include "Sound.h"
#include "SoundBuilder.h"
#include "Sprite2D.h"
#include "Sprite2DBuilder.h"
#include "SpriteFrameAtlas.h"
#include "SpriteFrameAtlasBuilder.h"

#include "SteeringBehavior.h"
#include "SteeringBehaviorAlignment.h"
#include "SteeringBehaviorAlignmentBuilder.h"
#include "SteeringBehaviorArrive.h"
#include "SteeringBehaviorArriveBuilder.h"
#include "SteeringBehaviorBuilder.h"
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
#include "Thread.h"
#include "ThreadBuilder.h"
#include "Timer.h"
#include "TimerBuilder.h"
#include "WorldState.h"
#include "WorldStateBuilder.h"
#include "WorldStateMachine.h"
#include "WorldStateMachineBuilder.h"
#include "Xml.h"
#include "XmlBuilder.h"

#pragma mark End AbstractFactoryObjects includes

#endif
