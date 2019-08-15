
#ifndef _BTCOLLISIONOBJECTDECORATOR_H_
#define _BTCOLLISIONOBJECTDECORATOR_H_

#include "BulletCollision/CollisionDispatch/btCollisionObject.h"
#include "glm/glm.hpp"
#include <string>

class btCollisionObjectDecorator {
    btCollisionObject *m_btCollisionObject;
    
    btCollisionObjectDecorator();
    btCollisionObjectDecorator(const btCollisionObjectDecorator&);
    const btCollisionObjectDecorator &operator=(const btCollisionObjectDecorator&);
public:
    btCollisionObjectDecorator(btCollisionObject *p);
    
    operator std::string() const;
};

#endif

