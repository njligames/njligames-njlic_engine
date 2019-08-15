#include "Vec4Decorator.h"
#include "Log.h"

#define FORMATSTRING "{\"glm::vec4\":[{\"x\":\"%f\", \"y\":\"%f\",\"z\":\"%f\", \"w\":\"%f\"}]}"

Vec4Decorator::Vec4Decorator(glm::vec4 *p) : m_vec4(p) {}

Vec4Decorator::operator std::string() const {
    std::string temp(string_format(FORMATSTRING, m_vec4->x, m_vec4->y, m_vec4->z, m_vec4->w));
    return temp;
}

Vec4Decorator::operator btVector4() const {
    return btVector4(m_vec4->x, m_vec4->y, m_vec4->z, m_vec4->w);
}
