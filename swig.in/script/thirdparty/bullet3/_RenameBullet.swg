%rename(btScalarPtr) operator btScalar*;
%rename(btScalarConstPtr) operator const btScalar*;
%rename(operator_btVector3) operator btVector3;

//%rename(operator_new) operator new;
//%rename(operator_delete) operator delete;
//%rename(operator_new_array) operator new[];
//%rename(operator_delete_array) operator delete[];

//%rename(btSwapEndian_unsigned_short) btSwapEndian(unsigned short);
//%rename(btSwapEndian_signed_int) btSwapEndian(unsigned int);
//%rename(btSwapEndian_int) btSwapEndian(int);
//%rename(btSwapEndian_shore) btSwapEndian(short);
//
%rename(upcast_const) btGhostObject::upcast(btCollisionObject const *);
%rename(upcast_const) btSoftBody::upcast(btCollisionObject const *);
%rename(upcast_const) btRigidBody::upcast(btCollisionObject const *);
%rename(getOverlappingPairs_const) btGhostObject::getOverlappingPairs() const;
%rename(upcast_const) btMultiBodyLinkCollider::upcast(btCollisionObject const *);

%rename(rayTest_const) btBroadphaseInterface::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &);
%rename(rayTest_const_const) btBroadphaseInterface::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &,btVector3 const &);

%rename(rayTest_const) btDbvtBroadphase::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &);
%rename(rayTest_const_const) btDbvtBroadphase::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &,btVector3 const &);

%rename(rayTest_const) btMultiSapBroadphase::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &);
%rename(rayTest_const_const) btMultiSapBroadphase::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &,btVector3 const &);

%rename(rayTest_const) btSimpleBroadphase::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &);
%rename(rayTest_const_const) btSimpleBroadphase::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &,btVector3 const &);

%rename(rayTest2) btAxisSweep3Internal< unsigned int >::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &,btVector3 const &);
%rename(rayTest3) btAxisSweep3Internal< unsigned int >::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &);
%rename(rayTest2) btAxisSweep3Internal< unsigned short >::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &,btVector3 const &);
%rename(rayTest3) btAxisSweep3Internal< unsigned short >::rayTest(btVector3 const &,btVector3 const &,btBroadphaseRayCallback &,btVector3 const &);

%rename(str) operator std::string;
