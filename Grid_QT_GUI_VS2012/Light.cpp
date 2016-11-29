#include "Light.h"

//-----------------------------------------------------------------------------
Light::Light(const glm::vec3 & direction) :
    _direction(direction)
{
}

glm::vec3 Light::direction() const
{
    return _direction;
}

void Light::setDirection(const glm::vec3 & direction)
{
    _direction = direction;
}