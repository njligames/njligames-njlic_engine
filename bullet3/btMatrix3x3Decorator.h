
#ifndef _BTMATRIX3X3DECORATOR_H_
#define _BTMATRIX3X3DECORATOR_H_

#include "LinearMath/btMatrix3x3.h"
#include "glm/glm.hpp"
#include <string>

class btMatrix3x3Decorator {
    btMatrix3x3 *m_btMatrix3x3;
    
    btMatrix3x3Decorator();
    btMatrix3x3Decorator(const btMatrix3x3Decorator&);
    const btMatrix3x3Decorator &operator=(const btMatrix3x3Decorator&);
public:
    btMatrix3x3Decorator(btMatrix3x3 *p);
    
    operator std::string() const;
    operator glm::mat3() const;
    
};

#endif


