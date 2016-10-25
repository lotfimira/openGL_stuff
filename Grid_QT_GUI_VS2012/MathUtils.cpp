#include "MathUtils.h"

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------
glm::vec3 triangleNormal(const glm::vec3 & p0,
                         const glm::vec3 & p1,
                         const glm::vec3 & p2)
{
    return glm::normalize(glm::cross(p2 - p0, p1 - p0));
}