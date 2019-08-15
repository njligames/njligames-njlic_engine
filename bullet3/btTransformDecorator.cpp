#include "btTransformDecorator.h"
#include "Log.h"

#define FORMATSTRING "{\"btTransform\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", \"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", \"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", \"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", \"ww\":\"%f\"}]}"

btTransformDecorator::btTransformDecorator(btTransform *p) : m_buffer(new btScalar[16]), m_btTransform(p) {}
btTransformDecorator::~btTransformDecorator()
{
    delete [] m_buffer;
}

btTransformDecorator::operator std::string() const {
    m_btTransform->getOpenGLMatrix(m_buffer);
    
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

btTransformDecorator::operator glm::mat4() const {
    glm::mat4 m;
    const btMatrix3x3& basis = m_btTransform->getBasis();
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            m[c][r] = basis[r][c];
        }
    }

    btVector3 origin = m_btTransform->getOrigin();
    
    m[3][0] = origin.getX();
    m[3][1] = origin.getY();
    m[3][2] = origin.getZ();
    // unit scale
    m[0][3] = 0.0f;
    m[1][3] = 0.0f;
    m[2][3] = 0.0f;
    m[3][3] = 1.0f;

    
    return m;
}
