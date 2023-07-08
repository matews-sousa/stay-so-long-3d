#pragma once

#include "GameObject.hpp"
#include "../Core/Game.hpp"
#include "../Core/Mesh.hpp"
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

class Enemy : public GameObject
{
public:
  Enemy(glm::vec3 initialPosition, glm::vec3 scale);
  virtual ~Enemy();
  
  void update(glm::vec3 playerPosition);
  void draw();

  void setDirection(glm::vec3 direction) { this->direction = direction;}
  void setSpeed(float speed) { this->speed = speed; }

  glm::vec3 getDirection() { return this->direction; }
  float getSpeed() { return this->speed; }

private:
  Mesh *mesh;

  glm::vec3 direction;
  float speed;
};