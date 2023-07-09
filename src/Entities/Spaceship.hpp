#pragma once

#include "GameObject.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/Texture.hpp"
#include "../Core/CubeCollider.hpp"
#include "../Core/SphereCollider.hpp"

class CubeCollider;
class SphereCollider;

class Spaceship : public GameObject
{
public:
  Spaceship(glm::vec3 position, glm::vec3 scale);
  virtual ~Spaceship();

  void update();
  void draw();

  SphereCollider *collider;

private:
  Mesh *mesh;
};