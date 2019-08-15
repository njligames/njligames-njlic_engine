
#ifndef _BTMANIFOLDPOINTDECORATOR_H_
#define _BTMANIFOLDPOINTDECORATOR_H_

#include "BulletCollision/NarrowPhaseCollision/btManifoldPoint.h"
#include "glm/glm.hpp"
#include <string>

class btManifoldPointDecorator {
    btManifoldPoint *m_btManifoldPoint;
    
    btManifoldPointDecorator();
    btManifoldPointDecorator(const btManifoldPointDecorator&);
    const btManifoldPointDecorator &operator=(const btManifoldPointDecorator&);
public:
    btManifoldPointDecorator(btManifoldPoint *p);
    
    operator std::string() const;
};

#endif

