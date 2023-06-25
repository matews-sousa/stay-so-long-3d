#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>

namespace Utils
{
  static bool isInFrustum(glm::mat4 matrix, glm::vec3 position)
  {
    glm::vec4 pClip = matrix * glm::vec4(position, 1.0f);
    return std::abs(pClip.x) < pClip.w &&
           std::abs(pClip.y) < pClip.w &&
           0 < pClip.z &&
           std::abs(pClip.z) < pClip.w;
  }
};