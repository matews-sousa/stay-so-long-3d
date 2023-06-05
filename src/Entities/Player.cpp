#include "Player.hpp"
#include "../Core/Input.hpp"
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../primitives.hpp"
#include <iostream>
#include "../Core/Game.hpp"
#include "../Core/Input.hpp"

Player::Player(glm::vec3 position, glm::vec3 scale) : GameObject(position, scale)
{
  this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  this->speed = 400.0f;

  this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
  this->right = glm::vec3(1.0f, 0.0f, 0.0f);
  this->up = glm::vec3(0.0f, 1.0f, 0.0f);

  updateLocalMatrix();
}

Player::~Player()
{
}

void Player::update()
{
  float moveZ = 0.0f;
  float moveX = 0.0f;

  bool up = Input::isKeyPressed(sf::Keyboard::W);
  bool down = Input::isKeyPressed(sf::Keyboard::S);
  bool left = Input::isKeyPressed(sf::Keyboard::A);
  bool right = Input::isKeyPressed(sf::Keyboard::D);

  glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
  
  if (up)
  {
    // make a vector diagonally up and right
    if (right)
      direction = glm::vec3(-1.0f, 0.0f, 0.0f);

    // make a vector diagonally up and left
    else if (left)
      direction = glm::vec3(0.0f, 0.0f, 1.0f);
    
    // make a vector pointing up
    else
      direction = glm::vec3(-1.0f, 0.0f, 1.0f);
  }
  else if (down)
  {
    // make a vector diagonally down and right
    if (right)
      direction = glm::vec3(0.0f, 0.0f, -1.0f);

    // make a vector diagonally down and left
    else if (left)
      direction = glm::vec3(1.0f, 0.0f, 0.0f);
    
    // make a vector pointing down
    else
      direction = glm::vec3(1.0f, 0.0f, -1.0f);
  }
  else if (left)
  {
    // make a vector pointing left
    direction = glm::vec3( 1.0f, 0.0f, 1.0f);
  }
  else if (right)
  {
    // make a vector pointing right
    direction = glm::vec3(-1.0f, 0.0f, -1.0f);
  }

  if (glm::length(direction) > 0.0f)
    direction = glm::normalize(direction);

  this->move(direction);
  this->look(direction);

  updateLocalMatrix();
}

void Player::move(glm::vec3 direction)
{
  if (glm::length(direction) == 0.0f)
    return;

  this->velocity = direction * speed * Game::deltaTime;
  this->position += this->velocity;
  
  Game::camera->move(velocity);
}

void Player::look(glm::vec3 direction)
{
  if (glm::length(direction) == 0.0f)
    return;

  glm::vec3 lookDirection = glm::normalize(direction);
  glm::vec3 right = glm::normalize(glm::cross(lookDirection, up));

  this->forward = lookDirection;
  this->right = right;
}

void Player::draw()
{
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, this->position);
  model = glm::scale(model, this->scale);
  
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // body
  glPushMatrix();
    glMultMatrixf(glm::value_ptr(localMatrix));
    glScalef(scale.x, scale.y, scale.z);
    drawCube(1.0f);
  glPopMatrix();

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

void Player::updateLocalMatrix()
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