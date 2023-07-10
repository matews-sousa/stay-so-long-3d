#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class GameObject
{
protected:
  glm::vec3 position;
  glm::vec3 scale;
  glm::vec3 rotation;

  glm::vec3 forward;
  glm::vec3 right;
  glm::vec3 up;
  glm::mat4 localMatrix;

  glm::mat4 modelMatrix;

public:
  GameObject();
  GameObject(glm::vec3 position, glm::vec3 scale);
  virtual ~GameObject();

  void debug();

  glm::mat4 getModelMatrix();
  void updateLocalMatrix();

  glm::vec3 getPosition() { return this->position; }
  glm::vec3 getScale() { return this->scale; }
  glm::vec3 getRotation() { return this->rotation; }  
  glm::vec3 getForward() { return this->forward; }
  glm::vec3 getRight() { return this->right; }
  glm::vec3 getUp() { return this->up; }

  void setPosition(glm::vec3 position) { this->position = position; }
  void setScale(glm::vec3 scale) { this->scale = scale; }
  void setRotation(glm::vec3 rotation) { this->rotation = rotation; }
  void setForward(glm::vec3 forward) { this->forward = forward; }
  void setRight(glm::vec3 right) { this->right = right; }
  void setUp(glm::vec3 up) { this->up = up; }
};