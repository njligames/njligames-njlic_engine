#include "Vec3Decorator.h"
#include "Log.h"

#define FORMATSTRING                                                           \
    "{\"glm::vec3\":[{\"x\":\"%f\", \"y\":\"%f\",\"z\":\"%f\"}]}"

Vec3Decorator::Vec3Decorator(glm::vec3 *p) : m_vec3(p) {}

Vec3Decorator::operator std::string() const
{
    std::string temp(
        string_format(FORMATSTRING, m_vec3->x, m_vec3->y, m_vec3->z));
    return temp;
}

Vec3Decorator::operator btVector3() const
{
    return btVector3(m_vec3->x, m_vec3->y, m_vec3->z);
}
