
#ifndef _MAT3DECORATOR_H_
#define _MAT3DECORATOR_H_

#include "LinearMath/btMatrix3x3.h"
#include "glm/glm.hpp"
#include <string>

class Mat3Decorator {
    glm::mat3 *m_mat3;
    
    Mat3Decorator();
    Mat3Decorator(const Mat3Decorator&);
    const Mat3Decorator &operator=(const Mat3Decorator&);
public:
    Mat3Decorator(glm::mat3 *p);
    
    operator std::string() const;
    operator btMatrix3x3() const;
    
};

#endif


