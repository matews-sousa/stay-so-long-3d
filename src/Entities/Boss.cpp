#include "Boss.hpp"

Boss::Boss(glm::vec3 position, glm::vec3 size) : GameObject(position, size)
{
  speed = 200.0f;
  shootTimer = 0.0f;
  shootInterval = 0.5f;
  health = 100.0f;
  maxHealth = 100.0f;
  damage = 10.0f;
  score = 100.0f;

  mesh = new Mesh("../src/Assets/Models/giant.obj");

  //setRotation(glm::vec3(0.0f, 90.0f, 0.0f));
  forward = glm::vec3(0.0f, 0.0f, 1.0f);
  right = glm::vec3(1.0f, 0.0f, 0.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
  updateLocalMatrix();
}

Boss::~Boss()
{
}

void Boss::update()
{
  glm::vec3 direction = World::player->getPosition() - position;
  direction = glm::normalize(direction);
  position += direction * speed * Game::deltaTime;

  glm::vec3 right = glm::cross(direction, up);
  forward = direction;
  this->right = right;

  updateLocalMatrix();
}

void Boss::draw()
{
  glm::mat4 matrix = glm::mat4(1.0f);
  matrix = glm::scale(matrix, scale);

  Texture::bindByName("giant");
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(localMatrix * matrix));
  mesh->render(localMatrix * matrix);
  glPopMatrix();
}

void Boss::shoot()
{
  
}

void Boss::updateLocalMatrix()
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