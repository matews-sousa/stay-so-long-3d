#pragma once

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.hpp"
#include "Bullet.hpp"
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

  float angle;

  float speed;
  float currentHealth;
  float maxHealth;
  bool isDead;
  float damage;
  float score;

  void shoot();
  void handleShots();
  float shootTimer;
  float shootInterval;
  std::vector<Bullet *> bullets;

  void drawHealthBar();
};