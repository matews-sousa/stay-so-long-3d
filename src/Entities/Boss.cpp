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

  forward = glm::vec3(0.0f, 0.0f, 1.0f);
  right = glm::vec3(1.0f, 0.0f, 0.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
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
  glMultMatrixf(glm::value_ptr(getModelMatrix()));
  mesh->render(getModelMatrix());
  glPopMatrix();

  this->debug();
}

void Boss::shoot()
{
  
}