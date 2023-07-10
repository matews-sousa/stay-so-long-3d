#pragma once

#include <glm/mat4x4.hpp>
#include "GameObject.hpp"
#include "../Core/Game.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/Texture.hpp"
#include "../Core/World.hpp"

class Boss : public GameObject
{
public:
  Boss(glm::vec3 position, glm::vec3 size);
  ~Boss();

  void update();
  void draw();

private:
  Mesh *mesh;

  float speed;
  float shootTimer;
  float shootInterval;
  float health;
  float maxHealth;
  float damage;
  float score;

  void shoot();
};