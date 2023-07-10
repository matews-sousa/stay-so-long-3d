#pragma once

#include <glm/mat4x4.hpp>
#include "GameObject.hpp"
#include "../Core/Game.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/Texture.hpp"
#include "../Core/World.hpp"
#include "../Core/CubeCollider.hpp"

class CubeCollider;

class Boss : public GameObject
{
public:
  Boss(glm::vec3 position, glm::vec3 size);
  ~Boss();

  void update();
  void draw();
  void takeDamage(float damage) { currentHealth -= damage; }
  bool getIsDead() { return isDead; }

  CubeCollider *collider;

private:
  Mesh *mesh;

  float speed;
  float shootTimer;
  float shootInterval;
  float currentHealth;
  float maxHealth;
  bool isDead;
  float damage;
  float score;

  void shoot();
  void drawHealthBar();
};