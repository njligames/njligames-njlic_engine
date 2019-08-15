
#ifndef _BTVECTOR4DECORATOR_H_
#define _BTVECTOR4DECORATOR_H_

#include "LinearMath/btVector3.h"
#include "glm/glm.hpp"
#include <string>

class btVector4Decorator {
    btVector3 *m_btVector4;
    
    btVector4Decorator();
    btVector4Decorator(const btVector4Decorator&);
    const btVector4Decorator &operator=(const btVector4Decorator&);
public:
    btVector4Decorator(btVector4 *p);
    
    operator std::string() const;
    operator glm::vec4() const;
    
};

#endif

