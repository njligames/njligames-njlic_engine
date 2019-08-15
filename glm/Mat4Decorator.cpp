#include "Mat4Decorator.h"
#include "Log.h"
#include "Mat3Decorator.h"
#include "Vec3Decorator.h"

#define FORMATSTRING "{\"glm::mat4\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", \"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", \"ww\":\"%f\"}]}"

Mat4Decorator::Mat4Decorator(glm::mat4 *p) : m_buffer(new btScalar[16]), m_mat4(p) {}
Mat4Decorator::~Mat4Decorator()
{
    delete [] m_buffer;
}

Mat4Decorator::operator std::string() const {
    btTransform t(*this);
    t.getOpenGLMatrix(m_buffer);
    
    std::string temp(string_format(FORMATSTRING,
                                   m_buffer[0],
                                   m_buffer[1],
                                   m_buffer[2],
                                   m_buffer[3],
                                   m_buffer[4],
                                   m_buffer[5],
                                   m_buffer[6],
                                   m_buffer[7],
                                   m_buffer[8],
                                   m_buffer[9],
                                   m_buffer[10],
                                   m_buffer[11],
                                   m_buffer[12],
                                   m_buffer[13],
                                   m_buffer[14],
                                   m_buffer[15]));
    return temp;
}

Mat4Decorator::operator btTransform() const {
    glm::mat3 m3(*m_mat4);
    glm::vec3 v(glm::vec3((*m_mat4)[3][0], (*m_mat4)[3][1], (*m_mat4)[3][2]));
    
    btMatrix3x3 _btMatrix3x3 = Mat3Decorator(&m3);
    btVector3 _btVector3 = Vec3Decorator(&v);
    
    return btTransform(_btMatrix3x3, _btVector3);
}
