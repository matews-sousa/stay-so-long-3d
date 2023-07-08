#include "Enemy.hpp"

Enemy::Enemy(glm::vec3 initialPosition, glm::vec3 scale)
  : GameObject(initialPosition, scale)
{
  direction = glm::vec3(0.0f, 0.0f, 0.0f);
  speed = 200.0f;

  mesh = new Mesh("../src/Assets/Models/cube.obj");

  collider = new CubeCollider(this->position, scale);

  maxHealth = 100;
  currentHealth = maxHealth;
}

Enemy::~Enemy()
{
}

void Enemy::update(glm::vec3 playerPosition)
{
  const float targetY = 25.0f;
  direction = playerPosition - position;
  direction.y = targetY;
  direction = glm::normalize(direction);

  position += direction * speed * Game::deltaTime;
  position.y = targetY;

  collider->setPosition(position);
}

void Enemy::draw()
{
  // get rotation angle from direction vector
  glm::vec3 axis = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction);
  float angle = glm::acos(glm::dot(glm::vec3(0.0f, 1.0f, 0.0f), direction));

  this->setRotation(axis * angle);

  glBindTexture(GL_TEXTURE_2D, 0);
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(getModelMatrix()));
  mesh->render(getModelMatrix(), CALCULATE_ILLUMINATION);
  glPopMatrix();

  collider->debug();
}