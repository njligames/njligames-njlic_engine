
#ifndef _BTRIGIDBODYDECORATOR_H_
#define _BTRIGIDBODYDECORATOR_H_

#include "BulletDynamics/Dynamics/btRigidBody.h"
#include "glm/glm.hpp"
#include <string>

class btRigidBodyDecorator {
    btRigidBody *m_btRigidBody;
    
    btRigidBodyDecorator();
    btRigidBodyDecorator(const btRigidBodyDecorator&);
    const btRigidBodyDecorator &operator=(const btRigidBodyDecorator&);
public:
    btRigidBodyDecorator(btRigidBody *p);
    
    operator std::string() const;
};

#endif


