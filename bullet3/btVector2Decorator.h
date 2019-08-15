
#ifndef _BTVECTOR2DECORATOR_H_
#define _BTVECTOR2DECORATOR_H_

#include "btVector2.h"
#include "glm/glm.hpp"
#include <string>

class btVector2Decorator {
    btVector2 *m_btVector2;
    
    btVector2Decorator();
    btVector2Decorator(const btVector2Decorator&);
    const btVector2Decorator &operator=(const btVector2Decorator&);
public:
    btVector2Decorator(btVector2 *p);
    
    operator std::string() const;
    operator glm::vec2() const;
    
};

#endif

