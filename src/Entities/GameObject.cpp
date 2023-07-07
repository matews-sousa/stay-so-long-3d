#include "GameObject.hpp"

GameObject::GameObject()
{
  this->position = glm::vec3(0.0f, 0.0f, 0.0f);
  this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

GameObject::GameObject(glm::vec3 position, glm::vec3 scale)
{
  this->position = position;
  this->scale = scale;
}

GameObject::~GameObject()
{
}

glm::mat4 GameObject::getModelMatrix()
{
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, this->position);
  modelMatrix = glm::scale(modelMatrix, this->scale);
  return modelMatrix;
}
