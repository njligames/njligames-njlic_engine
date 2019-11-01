#include "QuatDecorator.h"
#include "Log.h"
#include "btVector3Decorator.h"

#define FORMATSTRING "{\"glm::quat\":[{\"angle\":\"%f\", \"axis\":%s}]}"

QuatDecorator::QuatDecorator(glm::quat *p) : m_quat(p) {}

QuatDecorator::operator std::string() const
{
    btQuaternion q(*this);

    btVector3 a(q.getAxis());

    std::string axis = btVector3Decorator(&a);

    std::string temp(string_format(FORMATSTRING, q.getAngle(), axis.c_str()));
    return temp;
}

QuatDecorator::operator btQuaternion() const
{
    return btQuaternion(m_quat->x, m_quat->y, m_quat->z, m_quat->w);
}
