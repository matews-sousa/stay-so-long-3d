#pragma once

#include <GL/glew.h>
#include "Collider.hpp"
#include "SphereCollider.hpp"
#include "Utils.hpp"
#include "Game.hpp"
#include "Mesh.hpp"

class SphereCollider;
class Mesh;

class CubeCollider : public Collider
{
public:
  CubeCollider(glm::vec3 position, glm::vec3 size);
  virtual ~CubeCollider();

  void debug();

  bool testCollision(Collider &other);
  bool testCollision(CubeCollider &other);
  bool testCollision(SphereCollider &other);

  glm::vec3 getMinBB() const { return minBB; }
  glm::vec3 getMaxBB() const { return maxBB; }

  void setMinBB(glm::vec3 minBB) { this->minBB = minBB; }
  void setMaxBB(glm::vec3 maxBB) { this->maxBB = maxBB; }

  void setPosition(glm::vec3 position);

private:
  glm::vec3 minBB;
  glm::vec3 maxBB;

  Mesh *mesh;
};