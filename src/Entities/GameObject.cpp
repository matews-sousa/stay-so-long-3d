#include "GameObject.hpp"

GameObject::GameObject()
{
  this->position = glm::vec3(0.0f, 0.0f, 0.0f);
  this->scale = glm::vec3(1.0f, 1.0f, 1.0f);

  forward = glm::vec3(0.0f, 0.0f, 1.0f);
  right = glm::vec3(1.0f, 0.0f, 0.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
}

GameObject::GameObject(glm::vec3 position, glm::vec3 scale)
{
  this->position = position;
  this->scale = scale;

  forward = glm::vec3(0.0f, 0.0f, 1.0f);
  right = glm::vec3(1.0f, 0.0f, 0.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
}

GameObject::~GameObject()
{
}

glm::mat4 GameObject::getModelMatrix()
{
  updateLocalMatrix();

  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
  modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
  modelMatrix = glm::scale(modelMatrix, this->scale);
  
  return localMatrix * modelMatrix;
}

void GameObject::updateLocalMatrix()
{
  localMatrix = glm::mat4(1.0f);
  localMatrix[0][0] = right.x;
  localMatrix[1][0] = right.y;
  localMatrix[2][0] = right.z;

  localMatrix[0][1] = up.x;
  localMatrix[1][1] = up.y;
  localMatrix[2][1] = up.z;

  localMatrix[0][2] = forward.x;
  localMatrix[1][2] = forward.y;
  localMatrix[2][2] = forward.z;

  localMatrix[0][3] = position.x;
  localMatrix[1][3] = position.y;
  localMatrix[2][3] = position.z;

  localMatrix = glm::transpose(localMatrix);
}

void GameObject::debug()
{
  glPointSize(10.0f);
  glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(this->position.x, this->position.y, this->position.z);
  glEnd();

  glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(this->position.x, this->position.y, this->position.z);
    glVertex3f(this->position.x + this->forward.x * 100.0f, this->position.y + this->forward.y * 100.0f, this->position.z + this->forward.z * 100.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(this->position.x, this->position.y, this->position.z);
    glVertex3f(this->position.x + this->right.x * 100.0f, this->position.y + this->right.y * 100.0f, this->position.z + this->right.z * 100.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(this->position.x, this->position.y, this->position.z);
    glVertex3f(this->position.x + this->up.x * 100.0f, this->position.y + this->up.y * 100.0f, this->position.z + this->up.z * 100.0f);
  glEnd();
}