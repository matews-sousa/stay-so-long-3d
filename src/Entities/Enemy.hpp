#pragma once

#include "GameObject.hpp"
#include "../Core/Game.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/CubeCollider.hpp"
#include "../Core/SphereCollider.hpp"
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

enum ENEMY_TYPE
{
  FOLLOWER,
  CHARGER,
  SHOOTER
};

class SphereCollider;
class CubeCollider;

class Enemy : public GameObject
{
public:
  Enemy(glm::vec3 initialPosition, glm::vec3 scale, ENEMY_TYPE type);
  virtual ~Enemy();

  SphereCollider *collider;
  
  void update(glm::vec3 playerPosition);
  void draw();

  void setDirection(glm::vec3 direction) { this->direction = direction;}
  void setSpeed(float speed) { this->speed = speed; }

  glm::vec3 getDirection() { return this->direction; }
  float getSpeed() { return this->speed; }

  int getCurrentHealth() { return this->currentHealth; }
  int getMaxHealth() { return this->maxHealth; }

  void takeDamage(int damage) { this->currentHealth -= damage; }

  bool isDead() { return this->currentHealth <= 0; }

  void setPosition(glm::vec3 position);

private:
  ENEMY_TYPE enemyType;

  Mesh *mesh;

  glm::vec3 direction;
  float speed;

  int currentHealth;
  int maxHealth;

  void handleEnemyTypes();

  // charger variables 
  void handleCharger();
  bool isCharging = false;
  float chargeTimer = 0.0f;
  float chargeDuration = 5.0f;

  float chargingTimer = 0.0f;
  float chargingDuration = 5.0f;

  glm::vec3 sprintDirection;
  bool isSprinting = false;
  float sprintForce = 5.0f;
  float sprintTimer = 0.0f;
  float sprintDuration = 3.0f;
};
