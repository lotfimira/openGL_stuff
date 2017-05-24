#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>


//-----------------------------------------------------------------------------
glm::vec3 triangleNormal(const glm::vec3 & p0,
                         const glm::vec3 & p1,
                         const glm::vec3 & p2);

// Finds quaternion representing the rotation from vector v0 to vector v1
glm::quat quatFrom2Vect(const glm::vec3 & v0,
                        const glm::vec3 & v1);