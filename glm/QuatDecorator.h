
#ifndef _QUATDECORATOR_H_
#define _QUATDECORATOR_H_

#include "LinearMath/btQuaternion.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"
#include <string>

class QuatDecorator {
    glm::quat *m_quat;
    
    QuatDecorator();
    QuatDecorator(const QuatDecorator&);
    const QuatDecorator &operator=(const QuatDecorator&);
public:
    QuatDecorator(glm::quat *p);
    
    operator std::string() const;
    operator btQuaternion() const;
    
};

#endif


