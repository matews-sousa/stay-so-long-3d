#pragma once

#include <GL/glew.h>
#include "Collider.hpp"
#include "CubeCollider.hpp"
#include "Utils.hpp"
#include "Game.hpp"
#include "Mesh.hpp"

class CubeCollider;
class Mesh;

class SphereCollider : public Collider
{
public:
  SphereCollider(glm::vec3 position, float radius);
  virtual ~SphereCollider();
  
  void debug();
  
  bool testCollision(Collider &other);
  bool testCollision(SphereCollider &other);
  bool testCollision(CubeCollider &other);

  float getRadius() const { return radius; }

  void setRadius(float radius) { this->radius = radius; }

private:
  float radius;

  Mesh *mesh;
};