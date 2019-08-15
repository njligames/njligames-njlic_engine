
#ifndef _BTQUATERNIONDECORATOR_H_
#define _BTQUATERNIONDECORATOR_H_

#include "LinearMath/btQuaternion.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"
#include <string>

class btQuaternionDecorator {
    btQuaternion *m_btQuaternion;
    
    btQuaternionDecorator();
    btQuaternionDecorator(const btQuaternionDecorator&);
    const btQuaternionDecorator &operator=(const btQuaternionDecorator&);
public:
    btQuaternionDecorator(btQuaternion *p);
    
    operator std::string() const;
    operator glm::quat() const;
    
};

#endif


