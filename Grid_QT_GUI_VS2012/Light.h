#pragma once

#include <glm/glm.hpp>

class Light
{
protected:
    glm::vec3 _direction;

public:
    glm::vec3 direction() const;
};