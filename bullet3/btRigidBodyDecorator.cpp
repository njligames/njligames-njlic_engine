#include "btRigidBodyDecorator.h"
#include "Log.h"

#define FORMATSTRING "{\"njli::btRigidBody\":[]}"

btRigidBodyDecorator::btRigidBodyDecorator(btRigidBody *p) : m_btRigidBody(p) {}

btRigidBodyDecorator::operator std::string() const
{
    std::string temp(string_format(FORMATSTRING));
    return temp;
}
