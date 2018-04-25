%ignore btMultiSapBroadphase::quicksort(btBroadphasePairArray& a, int lo, int hi);


%ignore isInside;
%ignore btInternalTriangleInfoMap;

%ignore btSelect(unsigned int,int,int) ;
%ignore btSelect(unsigned int,unsigned int,unsigned int);
%ignore btSelect(unsigned int,unsigned int,unsigned int);
%ignore btSwapEndian(unsigned short);
%ignore btSwapEndian(unsigned int);
%ignore btSwapEndian(unsigned int);
%ignore btSwapEndian(short);
%ignore btSwapEndian(unsigned int);

%ignore btCollisionObjectWrapper;

%ignore operator new;
%ignore operator delete;
%ignore operator new[];
%ignore operator delete[];

%ignore btAlignedAllocator::rebind;
%ignore btAlignedObjectArray::less;
%ignore btRigidBody::btRigidBodyConstructionInfo;

%ignore btDbvt::sStkNN;
%ignore btDbvt::sStkNP;
%ignore btDbvt::sStkNPS;
%ignore btDbvt::sStkCLN;
%ignore btDbvt::ICollide;
%ignore btDbvt::IWriter;
%ignore btDbvt::IClone;

%ignore btAxisSweep3Internal::Edge;
%ignore btAxisSweep3Internal::Handle;

%ignore btMultiSapBroadphase::btMultiSapProxy;

%ignore btBoxBoxCollisionAlgorithm::CreateFunc;
%ignore btBox2dBox2dCollisionAlgorithm::CreateFunc;

//%ignore btDiscreteCollisionDetectorInterface::Result;
%ignore btDiscreteCollisionDetectorInterface::ClosestPointInput;

%ignore btCollisionWorld::LocalShapeInfo;
%ignore btCollisionWorld::LocalRayResult;
%ignore btCollisionWorld::RayResultCallback;
%ignore btCollisionWorld::ClosestRayResultCallback;
%ignore btCollisionWorld::AllHitsRayResultCallback;
%ignore btCollisionWorld::LocalConvexResult;
%ignore btCollisionWorld::ConvexResultCallback;
%ignore btCollisionWorld::ClosestConvexResultCallback;
%ignore btCollisionWorld::ContactResultCallback;

%ignore btCompoundCollisionAlgorithm::CreateFunc;
%ignore btCompoundCollisionAlgorithm::SwappedCreateFunc;

%ignore btCompoundCompoundCollisionAlgorithm::CreateFunc;
%ignore btCompoundCompoundCollisionAlgorithm::SwappedCreateFunc;

%ignore btConvex2dConvex2dAlgorithm::CreateFunc;

%ignore btConvexConcaveCollisionAlgorithm::CreateFunc;
%ignore btConvexConcaveCollisionAlgorithm::SwappedCreateFunc;

%ignore btConvexConvexAlgorithm::CreateFunc;

%ignore btConvexPlaneCollisionAlgorithm::CreateFunc;

%ignore btEmptyAlgorithm::CreateFunc;

%ignore btSimulationIslandManager::IslandCallback;

%ignore btSphereBoxCollisionAlgorithm::CreateFunc;

%ignore btSphereSphereCollisionAlgorithm::CreateFunc;

%ignore btSphereTriangleCollisionAlgorithm::CreateFunc;

%ignore btConvexCast::CastResult;

%ignore btGjkEpaSolver2::sResults;

%ignore btTypedConstraint::btConstraintInfo1;
%ignore btTypedConstraint::btConstraintInfo2;

%ignore btVehicleRaycaster::btVehicleRaycasterResult;

%ignore btWheelInfo::RaycastInfo;

%ignore btRaycastVehicle::btVehicleTuning;

%ignore btSparseSdf::IntFrac;
%ignore btSparseSdf::Cell;

%ignore btSoftBody::eAeroModel;
%ignore btSoftBody::eVSolver;
%ignore btSoftBody::ePSolver;
%ignore btSoftBody::eSolverPresets;
%ignore btSoftBody::eFeature;
%ignore btSoftBody::fCollision;
%ignore btSoftBody::fMaterial;
%ignore btSoftBody::sRayCast;
%ignore btSoftBody::ImplicitFn;
%ignore btSoftBody::sCti;
%ignore btSoftBody::sMedium;
%ignore btSoftBody::Element;
%ignore btSoftBody::Material;
%ignore btSoftBody::Feature;
%ignore btSoftBody::Node;
%ignore btSoftBody::Link;
%ignore btSoftBody::Face;
%ignore btSoftBody::Tetra;
%ignore btSoftBody::RContact;
%ignore btSoftBody::SContact;
%ignore btSoftBody::Anchor;
%ignore btSoftBody::Note;
%ignore btSoftBody::Pose;
%ignore btSoftBody::Cluster;
%ignore btSoftBody::Impulse;
%ignore btSoftBody::Body;
%ignore btSoftBody::Joint;
%ignore btSoftBody::LJoint;
%ignore btSoftBody::AJoint;
%ignore btSoftBody::CJoint;
%ignore btSoftBody::Config;
%ignore btSoftBody::SolverState;
%ignore btSoftBody::RayFromToCaster;

%ignore btSoftBodyConcaveCollisionAlgorithm::CreateFunc;
%ignore btSoftBodyConcaveCollisionAlgorithm::SwappedCreateFunc;

%ignore btSoftColliders::ClusterBase;
%ignore btSoftColliders::CollideCL_RS;
%ignore btSoftColliders::CollideCL_SS;
%ignore btSoftColliders::CollideSDF_RS;
%ignore btSoftColliders::CollideVF_SS;

%ignore btSoftRigidCollisionAlgorithm::CreateFunc;

%ignore btSoftSoftCollisionAlgorithm::CreateFunc;

%ignore ConvexH::HalfEdge;

%ignore btConvexHullComputer::Edge;

%ignore btHashString;

%ignore  btStorageResult;

%ignore setFromOpenGLSubMatrix;
%ignore setFromOpenGLMatrix;

%ignore CProfileIterator;
%ignore btSequentialImpulseConstraintSolver;

%ignore btIDebugDraw::DefaultColors;
%ignore btAlignedAllocator::rebind;
%ignore btAlignedObjectArray::less;
%ignore btDbvt::sStkNN;
%ignore btDbvt::sStkNP;
%ignore btDbvt::sStkNPS;
%ignore btDbvt::sStkCLN;
%ignore btDbvt::ICollide;
%ignore btDbvt::IWriter;
%ignore btDbvt::IClone;
%ignore btBox2dBox2dCollisionAlgorithm::CreateFunc;
%ignore btDiscreteCollisionDetectorInterface::Result;
%ignore btDiscreteCollisionDetectorInterface::ClosestPointInput;
%ignore btCollisionWorld::LocalShapeInfo;
%ignore btCollisionWorld::LocalRayResult;
%ignore btCollisionWorld::RayResultCallback;
%ignore btCollisionWorld::ClosestRayResultCallback;
%ignore btCollisionWorld::AllHitsRayResultCallback;
%ignore btCollisionWorld::LocalConvexResult;
%ignore btCollisionWorld::ConvexResultCallback;
%ignore btCollisionWorld::ClosestConvexResultCallback;
%ignore btCollisionWorld::ContactResultCallback;
%ignore btCollisionWorld::CreateFunc;
%ignore btCollisionWorld::SwappedCreateFunc;
%ignore btCompoundCompoundCollisionAlgorithm::CreateFunc;
%ignore btCompoundCompoundCollisionAlgorithm::SwappedCreateFunc;
%ignore btConvex2dConvex2dAlgorithm::CreateFunc;
%ignore btConvexConcaveCollisionAlgorithm::CreateFunc;
%ignore btConvexConcaveCollisionAlgorithm::SwappedCreateFunc;
%ignore btConvexConvexAlgorithm::CreateFunc;
%ignore btConvexPlaneCollisionAlgorithm::CreateFunc;
%ignore btEmptyAlgorithm::CreateFunc;
%ignore btSimulationIslandManager::IslandCallback;
%ignore btSphereBoxCollisionAlgorithm::CreateFunc;
%ignore btSphereSphereCollisionAlgorithm::CreateFunc;
%ignore btSphereTriangleCollisionAlgorithm::CreateFunc;
%ignore btConvexCast::CastResult;
%ignore btGjkEpaSolver2::sResults;
%ignore btRigidBody::btRigidBodyConstructionInfo;
%ignore btTypedConstraint::btConstraintInfo1;
%ignore btTypedConstraint::btConstraintInfo2;
%ignore btVehicleRaycaster::btVehicleRaycasterResult;
%ignore btWheelInfo::RaycastInfo;
%ignore btRaycastVehicle::btVehicleTuning;
%ignore btSparseSdf::IntFrac;
%ignore btSparseSdf::Cell;
%ignore btSoftBody::eAeroModel;
%ignore btSoftBody::eVSolver;
%ignore btSoftBody::ePSolver;
%ignore btSoftBody::eSolverPresets;
%ignore btSoftBody::eFeature;
%ignore btSoftBody::fCollision;
%ignore btSoftBody::fMaterial;
%ignore btSoftBody::sRayCast;
%ignore btSoftBody::ImplicitFn;
%ignore btSoftBody::sCti;
%ignore btSoftBody::sMedium;
%ignore btSoftBody::Element;
%ignore btSoftBody::Material;
%ignore btSoftBody::Feature;
%ignore btSoftBody::Node;
%ignore btSoftBody::Link;
%ignore btSoftBody::Face;
%ignore btSoftBody::Tetra;
%ignore btSoftBody::RContact;
%ignore btSoftBody::SContact;
%ignore btSoftBody::Anchor;
%ignore btSoftBody::Note;
%ignore btSoftBody::Pose;
%ignore btSoftBody::Cluster;
%ignore btSoftBody::Impulse;
%ignore btSoftBody::Body;
%ignore btSoftBody::Joint;
%ignore btSoftBody::LJoint;
%ignore btSoftBody::AJoint;
%ignore btSoftBody::CJoint;
%ignore btSoftBody::Config;
%ignore btSoftBody::SolverState;
%ignore btSoftBody::RayFromToCaster;


%ignore btSoftBodyConcaveCollisionAlgorithm::CreateFunc;
%ignore btSoftBodyConcaveCollisionAlgorithm::SwappedCreateFunc;
%ignore btSoftColliders::ClusterBase;
%ignore btSoftColliders::CollideCL_RS;
%ignore btSoftColliders::CollideCL_SS;
%ignore btSoftColliders::CollideSDF_RS;
%ignore btSoftColliders::CollideVF_SS;

%ignore btSoftRigidCollisionAlgorithm::CreateFunc;
%ignore btSoftSoftCollisionAlgorithm::CreateFunc;
%ignore ConvexH::HalfEdge;
%ignore btConvexHullComputer::Edge;



%ignore btMultibodyLink::m_linkName;
%ignore btMultibodyLink::m_jointName;

//%ignore btStorageResult;
//%ignore btManifoldResult;
//%ignore btTriangleInfoMap;

#if defined(SWIGEMBIND)
%ignore btSelect;
%ignore btSwapEndian;
%ignore btAngle;
%ignore dot;
#endif
