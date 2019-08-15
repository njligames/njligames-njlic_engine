
#ifndef _VEC3DECORATOR_H_
#define _VEC3DECORATOR_H_

#include "LinearMath/btVector3.h"
#include "glm/glm.hpp"
#include <string>

class Vec3Decorator {
    glm::vec3 *m_vec3;
    
    Vec3Decorator();
    Vec3Decorator(const Vec3Decorator&);
    const Vec3Decorator &operator=(const Vec3Decorator&);
public:
    Vec3Decorator(glm::vec3 *p);
    
    operator std::string() const;
    operator btVector3() const;
    
};

#endif

