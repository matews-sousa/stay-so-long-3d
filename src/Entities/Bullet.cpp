#include "Bullet.hpp"

Bullet::Bullet(float speed, glm::vec3 direction, glm::vec3 initialPosition, glm::vec3 scale) : GameObject(initialPosition, scale)
{
  this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  this->speed = speed;
  this->direction = direction;

  this->lifeTime = 0.0f;
  this->maxLifeTime = 1.5f;

  mesh = Game::models["sphere"];
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
  this->lifeTime += Game::deltaTime;

  this->velocity = this->direction * this->speed * Game::deltaTime;
  this->position += this->velocity;
}

void Bullet::draw()
{
  glBindTexture(GL_TEXTURE_2D, 0);
  mesh->setVertexColors(glm::vec3(1.0f, 0.0f, 0.0f));
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(this->getModelMatrix()));
  mesh->render(this->getModelMatrix(), CALCULATE_ILLUMINATION);
  glPopMatrix();
}