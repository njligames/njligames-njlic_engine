#include "Vec2Decorator.h"
#include "Log.h"

#define FORMATSTRING "{\"glm::vec2\":[{\"x\":\"%f\", \"y\":\"%f\"}]}"

Vec2Decorator::Vec2Decorator(glm::vec2 *p) : m_vec2(p) {}

Vec2Decorator::operator std::string() const
{
    std::string temp(string_format(FORMATSTRING, m_vec2->x, m_vec2->x));
    return temp;
}

Vec2Decorator::operator btVector2() const
{
    return btVector2(m_vec2->x, m_vec2->x);
}
