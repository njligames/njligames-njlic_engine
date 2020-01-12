
set(LIBRARY_NAME "bullet3")
set(SUB_LIBRARY_NAMES
        "BulletSoftBody"
        "BulletDynamics"
        "Bullet2FileLoader"
        "Bullet3Collision"
        "Bullet3Common"
        "Bullet3Dynamics"
        "Bullet3Geometry"
        "Bullet3OpenCL_clew"
        "BulletCollision"
        "BulletFileLoader"
        "BulletInverseDynamics"
        "BulletInverseDynamicsUtils"
        "BulletWorldImporter"
        "BulletXmlWorldImporter"
        "ConvexDecomposition"
        "GIMPACTUtils"
        "HACD"
        "LinearMath"
        )

set(INCLUDE_FILE "btBulletCollisionCommon.h")

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/FindLibrary.cmake")
