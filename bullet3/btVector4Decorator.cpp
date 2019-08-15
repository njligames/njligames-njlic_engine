#include "btVector4Decorator.h"
#include "Log.h"

#define FORMATSTRING "{\"btVector4\":[{\"x\":\"%f\", \"y\":\"%f\",\"z\":\"%f\", \"w\":\"%f\"}]}"

btVector4Decorator::btVector4Decorator(btVector4 *p) : m_btVector4(p) {}

btVector4Decorator::operator std::string() const {
    std::string temp(string_format(FORMATSTRING, m_btVector4->x(), m_btVector4->y(), m_btVector4->z(), m_btVector4->w()));
    return temp;
}

btVector4Decorator::operator glm::vec4() const {
    return glm::vec4(m_btVector4->x(), m_btVector4->y(), m_btVector4->z(), m_btVector4->w());
}


//static inline glm::vec3 bulletToGlm(const btVector3& v) { return glm::vec3(v.getX(), v.getY(), v.getZ()); }
//
//static inline btVector3 glmToBullet(const glm::vec3& v) { return btVector3(v.x, v.y, v.z); }
//
//static inline glm::quat bulletToGlm(const btQuaternion& q) { return glm::quat(q.getW(), q.getX(), q.getY(), q.getZ()); }
//
//static inline btQuaternion glmToBullet(const glm::quat& q) { return btQuaternion(q.x, q.y, q.z, q.w); }
//
//static inline btMatrix3x3 glmToBullet(const glm::mat3& m) { return btMatrix3x3(m[0][0], m[1][0], m[2][0], m[0][1], m[1][1], m[2][1], m[0][2], m[1][2], m[2][2]); }
//
//// btTransform does not contain a full 4x4 matrix, so this transform is lossy.
//// Affine transformations are OK but perspective transformations are not.
//static inline btTransform glmToBullet(const glm::mat4& m)
//{
//    glm::mat3 m3(m);
//    return btTransform(glmToBullet(m3), glmToBullet(glm::vec3(m[3][0], m[3][1], m[3][2])));
//}
//
//static inline glm::mat4 bulletToGlm(const btTransform& t)
//{
//    glm::mat4 m;
//    const btMatrix3x3& basis = t.getBasis();
//    // rotation
//    for (int r = 0; r < 3; r++)
//    {
//        for (int c = 0; c < 3; c++)
//        {
//            m[c][r] = basis[r][c];
//        }
//    }
//    // traslation
//    btVector3 origin = t.getOrigin();
//    m[3][0] = origin.getX();
//    m[3][1] = origin.getY();
//    m[3][2] = origin.getZ();
//    // unit scale
//    m[0][3] = 0.0f;
//    m[1][3] = 0.0f;
//    m[2][3] = 0.0f;
//    m[3][3] = 1.0f;
//    return m;
//}
//
//
//static inline glm::vec2 convert(const btVector2& vec) { return glm::vec2(vec.x(), vec.y()); }
//static inline glm::vec3 convert(const btVector3& vec) { return glm::vec3(vec.x(), vec.y(), vec.z()); }
//
//static inline glm::quat convert(const btQuaternion& quat)     { return glm::quat(quat.w(), quat.x(), quat.y(), quat.z()); }
//static inline glm::mat4 convert(const btTransform& transform) { return glm::mat4(glm::mat4_cast(convert(transform.getRotation())) * glm::translate(convert(transform.getOrigin()))); }
//
//static inline btVector2 convert(const glm::vec2& vec) { return btVector2(vec.x, vec.y); }
//static inline btVector3 convert(const glm::vec3& vec) { return btVector3(vec.x, vec.y, vec.z); }
//
//static inline btQuaternion convert(const glm::quat& quat)      { return btQuaternion(quat.x, quat.y, quat.z, quat.w); }
//static inline btTransform  convert(const glm::mat4& transform)
//{
//    glm::vec3 scale;
//    glm::quat rot;
//    glm::vec3 pos;
//    glm::vec3 s;
//    glm::vec4 p;
//    glm::decompose(transform, scale, rot, pos, s, p);
//
//    return btTransform(convert(rot), convert(pos));
//    }
