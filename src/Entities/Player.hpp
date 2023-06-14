#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include "GameObject.hpp"
#include "../Core/Game.hpp"
#include "../Core/Input.hpp"
#include "../Core/MousePicker.hpp"

class Player : public GameObject
{
private:
  glm::vec3 velocity;
  glm::vec3 forward;
  glm::vec3 right;
  glm::vec3 up;
  glm::mat4 localMatrix;
  float speed;
  float rotation;

public:
  Player(glm::vec3 position, glm::vec3 scale);
  virtual ~Player();

  void update();
  void move(glm::vec3 direction);
  void look(glm::vec3 direction);
  void draw();

  glm::vec3 getVelocity() { return this->velocity; }
  glm::vec3 getForward() { return this->forward; }

  void setVelocity(glm::vec3 velocity) { this->velocity = velocity; }
  void setForward(glm::vec3 forward) { this->forward = forward; }

  void updateLocalMatrix();
};