#include "Mat3Decorator.h"
#include "Log.h"

#define FORMATSTRING                                                           \
    "{\"glm::mat3\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", "           \
    "\"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"zx\":\"%f\", "             \
    "\"zy\":\"%f\", \"zz\":\"%f\"}]}"

Mat3Decorator::Mat3Decorator(glm::mat3 *p) : m_mat3(p) {}

Mat3Decorator::operator std::string() const
{
    std::string temp(string_format(
        FORMATSTRING, (*m_mat3)[0][0], (*m_mat3)[1][0], (*m_mat3)[2][0],
        (*m_mat3)[0][1], (*m_mat3)[1][1], (*m_mat3)[2][1], (*m_mat3)[0][2],
        (*m_mat3)[1][2], (*m_mat3)[2][2]));
    return temp;
}

Mat3Decorator::operator btMatrix3x3() const
{
    return btMatrix3x3((*m_mat3)[0][0], (*m_mat3)[1][0], (*m_mat3)[2][0],
                       (*m_mat3)[0][1], (*m_mat3)[1][1], (*m_mat3)[2][1],
                       (*m_mat3)[0][2], (*m_mat3)[1][2], (*m_mat3)[2][2]);
}
