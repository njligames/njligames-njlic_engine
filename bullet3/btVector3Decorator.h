
#ifndef _BTVECTOR3DECORATOR_H_
#define _BTVECTOR3DECORATOR_H_

#include "LinearMath/btVector3.h"
#include "glm/glm.hpp"
#include <string>

class btVector3Decorator {
    btVector3 *m_btVector3;
    
    btVector3Decorator();
    btVector3Decorator(const btVector3Decorator&);
    const btVector3Decorator &operator=(const btVector3Decorator&);
public:
    btVector3Decorator(btVector3 *p);
    
    operator std::string() const;
    operator glm::vec3() const;
    
};

#endif

