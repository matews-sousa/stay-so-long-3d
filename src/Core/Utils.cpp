#include "Utils.hpp"

float Utils::genRandomNumberInRange(float min, float max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(min, max);
  return dis(gen);
}

int Utils::genRandomNumberInRange(int min, int max)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}

bool Utils::isInFrustum(glm::mat4 matrix, glm::vec3 position)
{
  glm::vec4 pClip = matrix * glm::vec4(position, 1.0f);
  return std::abs(pClip.x) < pClip.w &&
          std::abs(pClip.y) < pClip.w &&
          0 < pClip.z &&
          std::abs(pClip.z) < pClip.w;
}

bool Utils::SphereSphereCollision(const SphereCollider *a, const SphereCollider *b)
{
  float distance = glm::distance(a->getPosition(), b->getPosition());

  float radiusSum = a->getRadius() + b->getRadius();

  return (distance - radiusSum) < radiusSum;
}

bool Utils::SphereCubeCollision(const SphereCollider *a, const CubeCollider *b)
{
  glm::vec3 closestPoint = glm::clamp(a->getPosition(), b->getPosition() - b->getSize(), b->getPosition() + b->getSize());

  float distance = glm::distance(a->getPosition(), closestPoint);

  return distance < a->getRadius();
}

bool Utils::CubeCubeCollision(const CubeCollider *a, const CubeCollider *b)
{
  glm::vec3 aMin = a->getMinBB();
  glm::vec3 aMax = a->getMaxBB();

  glm::vec3 bMin = b->getMinBB();
  glm::vec3 bMax = b->getMaxBB();

  return (aMin.x <= bMax.x && aMax.x >= bMin.x) &&
         (aMin.y <= bMax.y && aMax.y >= bMin.y) &&
         (aMin.z <= bMax.z && aMax.z >= bMin.z);
}