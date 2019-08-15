#include "btManifoldPointDecorator.h"
#include "Log.h"
#include "btVector3Decorator.h"

#define FORMATSTRING "{\"btManifoldPoint\":[{\"distance\":\"%f\", \"lifetime\":\"%d\", \"Position On A\":%s, \"Position On B\":%s, \"Applied Impulse\":\"%f\"}]}"

btManifoldPointDecorator::btManifoldPointDecorator(btManifoldPoint *p) : m_btManifoldPoint(p) {}

btManifoldPointDecorator::operator std::string() const {
    btVector3 va(m_btManifoldPoint->getPositionWorldOnA());
    btVector3 vb(m_btManifoldPoint->getPositionWorldOnA());
    
    std::string pa = btVector3Decorator(&va);
    std::string pb = btVector3Decorator(&vb);
    
    std::string temp(string_format(FORMATSTRING,
                                   m_btManifoldPoint->getDistance(),
                                   m_btManifoldPoint->getLifeTime(),
                                   pa.c_str(),
                                   pb.c_str(),
                                   m_btManifoldPoint->getAppliedImpulse()));
    return temp;
}
