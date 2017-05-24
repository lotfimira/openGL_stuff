#include "MathUtils.h"

#include <glm/glm.hpp>

//-----------------------------------------------------------------------------
glm::vec3 triangleNormal(const glm::vec3 & p0,
                         const glm::vec3 & p1,
                         const glm::vec3 & p2)
{
    return glm::normalize(glm::cross(p1 - p0, p2 - p0));
}

// Finds quaternion representing the rotation from vector v0 to vector v1
glm::quat quatFrom2Vect(const glm::vec3 & v0,
                        const glm::vec3 & v1)
{
    float dot_v0_v1 = glm::dot(v0, v1);

    if(dot_v0_v1 > 0.999999) // vectors are co-directed
        return glm::quat();  // return identity quaternion

    if(dot_v0_v1 < -0.999999) // vectors are parallels but opposite directions
        return glm::angleAxis(180.0f, glm::vec3(0,0,1)); // return 180 degress rotation

    glm::quat q;
    glm::vec3 a = glm::cross(v0, v1);
    q.x = a.x;
    q.y = a.y;
    q.z = a.z;
    q.w = sqrt((v0.length() ^ 2) * (v1.length() ^ 2)) + dot_v0_v1;

    return q;
}