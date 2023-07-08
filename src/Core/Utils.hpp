#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <iostream>
#include "CubeCollider.hpp"
#include "SphereCollider.hpp"

class CubeCollider;
class SphereCollider;

namespace Utils
{
  bool isInFrustum(glm::mat4 matrix, glm::vec3 position);

  bool SphereSphereCollision(const SphereCollider *a, const SphereCollider *b);
  bool CubeCubeCollision(const CubeCollider *a, const CubeCollider *b);
  bool SphereCubeCollision(const SphereCollider *a, const CubeCollider *b);
};