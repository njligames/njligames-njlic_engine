
#ifndef _VEC4DECORATOR_H_
#define _VEC4DECORATOR_H_

#include "LinearMath/btVector3.h"
#include "glm/glm.hpp"
#include <string>

class Vec4Decorator {
    glm::vec4 *m_vec4;
    
    Vec4Decorator();
    Vec4Decorator(const Vec4Decorator&);
    const Vec4Decorator &operator=(const Vec4Decorator&);
public:
    Vec4Decorator(glm::vec4 *p);
    
    operator std::string() const;
    operator btVector4() const;
    
};

#endif

