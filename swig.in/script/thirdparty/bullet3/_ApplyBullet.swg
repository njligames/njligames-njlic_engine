#if defined(SWIGLUA)
%include "typemaps.i"
#endif

SWIG_USERDATA_TYPEMAP(btManifoldPoint);
SWIG_USERDATA_TYPEMAP(btMatrix3x3);
SWIG_USERDATA_TYPEMAP(btQuaternion);
SWIG_USERDATA_TYPEMAP(btScalar);
SWIG_USERDATA_TYPEMAP(btTransform);
SWIG_USERDATA_TYPEMAP(btVector2);
SWIG_USERDATA_TYPEMAP(btVector3);
SWIG_USERDATA_TYPEMAP(btVector4);

SWIG_USERDATA_ARRAY_TYPEMAP(btScalarArray, 16);

//%apply btVector3** OUTPUT {btVector3& aabbMin,btVector3& aabbMax};
%apply btVector3** OUTPUT {btVector3& inertia};
%apply btVector3** OUTPUT {btVector3& planeNormal,btVector3& planeSupport};
%apply btVector3** OUTPUT {btVector3& vtx};
%apply btVector3** OUTPUT {btVector4& plane};
%apply btVector3** OUTPUT {btVector3& pa,btVector3& pb};
%apply btVector3** OUTPUT {btVector3& aabbMin,btVector3& aabbMax};
%apply btVector3** OUTPUT {Node *node,btVector3& aabbMin,btVector3& aabbMax};
%apply btVector3** OUTPUT {btVector3* supportVerticesOut};
%apply btVector3** OUTPUT {btVector3& inertia};
%apply btVector3** OUTPUT {btVector3& planeNormal,btVector3& planeSupport};
%apply btVector3** OUTPUT {btVector3& vtx};
%apply btVector3** OUTPUT {btVector4& plane};
%apply btVector3** OUTPUT {btVector3& pa,btVector3& pb};
%apply btVector3** OUTPUT {btVector4& pixel};
%apply btVector3** OUTPUT {btVector3 **vertices};
%apply btVector3** OUTPUT {btVector4 **colorVertices};
%apply btVector3** OUTPUT {btVector2 **textureCoordinates};

%apply btMatrix3x3** OUTPUT {btMatrix3x3 &ascender, btMatrix3x3 &descender, btMatrix3x3 &lineh};
%apply btMatrix3x3** OUTPUT {btMatrix3x3& floats};
%apply btMatrix3x3** OUTPUT {btMatrix3x3 &dstx, btMatrix3x3 &dsty, btMatrix3x3 &xform};

%apply (btScalarArray OUTPUT) {(btScalar *m)};

//%apply float* OUTPUT {float &x1, float &y1, float &z1, float &w1, float &x2, float &y2, float &z2, float &w2, float &x3, float &y3, float &z3, float &w3, float &x4, float &y4, float &z4, float &w4};
