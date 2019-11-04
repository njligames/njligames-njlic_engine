#include "btQuaternionDecorator.h"
#include "Log.h"
#include "btVector3Decorator.h"

#define FORMATSTRING "{\"btQuaternion\":[{\"angle\":\"%f\", \"axis\":%s}]}"

btQuaternionDecorator::btQuaternionDecorator(btQuaternion *p)
    : m_btQuaternion(p)
{
}

btQuaternionDecorator::operator std::string() const
{
    btVector3 a(m_btQuaternion->getAxis());

    std::string axis = btVector3Decorator(&a);

    std::string temp(
        string_format(FORMATSTRING, m_btQuaternion->getAngle(), axis.c_str()));
    return temp;
}

btQuaternionDecorator::operator glm::quat() const
{
    return glm::quat(m_btQuaternion->w(), m_btQuaternion->x(),
                     m_btQuaternion->y(), m_btQuaternion->z());
}
