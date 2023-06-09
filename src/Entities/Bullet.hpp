#pragma once

#include "GameObject.hpp"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../Core/Game.hpp"
#include "../Core/Mesh.hpp"
#include "../Core/SphereCollider.hpp"

class Mesh;
class SphereCollider;

class Bullet : public GameObject
{
public:
  Bullet(int damage, float speed, glm::vec3 direction, glm::vec3 initialPosition, glm::vec3 scale);
  ~Bullet();

  void update();
  void draw();

  void setVelocity(glm::vec3 velocity) { this->velocity = velocity; }
  glm::vec3 getVelocity() { return this->velocity; }

  void setSpeed(float speed) { this->speed = speed; }
  float getSpeed() { return this->speed; }

  void setLifeTime(float lifeTime) { this->lifeTime = lifeTime; }
  float getLifeTime() { return this->lifeTime; }

  void setMaxLifeTime(float maxLifeTime) { this->maxLifeTime = maxLifeTime; }
  float getMaxLifeTime() { return this->maxLifeTime; }

  void setDamage(int damage) { this->damage = damage; }
  int getDamage() { return this->damage; }

  SphereCollider *collider;
  
private:
  int damage;
  glm::vec3 velocity;
  glm::vec3 direction;
  float speed;
  float lifeTime;
  float maxLifeTime;

  Mesh* mesh;
};