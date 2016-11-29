#pragma once

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------
class Light
{
protected:
    glm::vec3 _direction;

public:
    Light(const glm::vec3 & direction = glm::vec3(0,0,-1));
    void setDirection(const glm::vec3 & direction);
    glm::vec3 direction() const;
};