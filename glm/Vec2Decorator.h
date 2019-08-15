
#ifndef _VEC2DECORATOR_H_
#define _VEC2DECORATOR_H_

#include "btVector2.h"
#include "glm/glm.hpp"
#include <string>

class Vec2Decorator {
    glm::vec2 *m_vec2;
    
    Vec2Decorator();
    Vec2Decorator(const Vec2Decorator&);
    const Vec2Decorator &operator=(const Vec2Decorator&);
public:
    Vec2Decorator(glm::vec2 *p);
    
    operator std::string() const;
    operator btVector2() const;
    
};

#endif

