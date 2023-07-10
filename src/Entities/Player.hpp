#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include "GameObject.hpp"
#include "../Core/Game.hpp"
#include "../Core/World.hpp"
#include "../Core/Input.hpp"
#include "../Core/MousePicker.hpp"
#include "Bullet.hpp"

class Bullet;

class Player : public GameObject
{
private:
  glm::vec3 velocity;
  float speed;
  float rotation;

  float shootCooldown;
  float maxShootCooldown;
  std::vector<Bullet*> bullets;

  void handleDash(glm::vec3 movingDirection);
  void dash(glm::vec3 direction);
  glm::vec3 dashDirection;
  float dashCooldown;
  float maxDashCooldown;
  float dashSpeed;
  float dashDuration;
  float dashTimer;
  bool isDashing;

  void shoot();
  void handleShots();

public:
  Player(glm::vec3 position, glm::vec3 scale);
  virtual ~Player();

  void update();
  void move(glm::vec3 direction);
  void look();
  void draw();

  glm::vec3 getVelocity() { return this->velocity; }

  void setVelocity(glm::vec3 velocity) { this->velocity = velocity; }

  std::vector<Bullet*> getBullets() { return this->bullets; }
};