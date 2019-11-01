#include "btMatrix3x3Decorator.h"
#include "Log.h"

#define FORMATSTRING                                                           \
    "{\"btMatrix3x3\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", "         \
    "\"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"zx\":\"%f\", "             \
    "\"zy\":\"%f\", \"zz\":\"%f\"}]}"

btMatrix3x3Decorator::btMatrix3x3Decorator(btMatrix3x3 *p) : m_btMatrix3x3(p) {}

btMatrix3x3Decorator::operator std::string() const
{
    std::string temp(string_format(
        FORMATSTRING, m_btMatrix3x3->getRow(0).x(),
        m_btMatrix3x3->getRow(0).y(), m_btMatrix3x3->getRow(0).z(),
        m_btMatrix3x3->getRow(1).x(), m_btMatrix3x3->getRow(1).y(),
        m_btMatrix3x3->getRow(1).z(), m_btMatrix3x3->getRow(2).x(),
        m_btMatrix3x3->getRow(2).y(), m_btMatrix3x3->getRow(2).z()));
    return temp;
}

btMatrix3x3Decorator::operator glm::mat3() const
{
    return glm::mat3(
        (*m_btMatrix3x3)[0][0], (*m_btMatrix3x3)[1][0], (*m_btMatrix3x3)[2][0],
        (*m_btMatrix3x3)[0][1], (*m_btMatrix3x3)[1][1], (*m_btMatrix3x3)[2][1],
        (*m_btMatrix3x3)[0][2], (*m_btMatrix3x3)[1][2], (*m_btMatrix3x3)[2][2]);
}
