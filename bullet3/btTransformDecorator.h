
#ifndef _BTTRANSFORMDECORATOR_H_
#define _BTTRANSFORMDECORATOR_H_

#include "LinearMath/btTransform.h"
#include "glm/glm.hpp"
#include <string>

class btTransformDecorator {
    btScalar *m_buffer;
    btTransform *m_btTransform;
    
    btTransformDecorator();
    btTransformDecorator(const btTransformDecorator&);
    const btTransformDecorator &operator=(const btTransformDecorator&);
public:
    btTransformDecorator(btTransform *p);
    virtual ~btTransformDecorator();
    
    operator std::string() const;
    operator glm::mat4() const;
    
};

#endif


