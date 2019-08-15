
#ifndef _MAT4DECORATOR_H_
#define _MAT4DECORATOR_H_

#include "LinearMath/btTransform.h"
#include "glm/glm.hpp"
#include <string>

class Mat4Decorator {
    btScalar *m_buffer;
    glm::mat4 *m_mat4;
    
    Mat4Decorator();
    Mat4Decorator(const Mat4Decorator&);
    const Mat4Decorator &operator=(const Mat4Decorator&);
public:
    Mat4Decorator(glm::mat4 *p);
    virtual ~Mat4Decorator();
    
    operator std::string() const;
    operator btTransform() const;
    
};

#endif


