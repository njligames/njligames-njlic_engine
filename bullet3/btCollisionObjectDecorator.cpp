#include "btCollisionObjectDecorator.h"
#include "Log.h"

#define FORMATSTRING "{\"njli::btCollisionObject\":[]}"

btCollisionObjectDecorator::btCollisionObjectDecorator(btCollisionObject *p) : m_btCollisionObject(p) {}

btCollisionObjectDecorator::operator std::string() const {
    std::string temp(string_format(FORMATSTRING));
    return temp;
}
