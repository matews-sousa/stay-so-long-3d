#include "Bullet.hpp"

Bullet::Bullet(int damage, float speed, glm::vec3 direction, glm::vec3 initialPosition, glm::vec3 scale) : GameObject(initialPosition, scale)
{
  this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  this->speed = speed;
  this->direction = direction;

  this->lifeTime = 0.0f;
  this->maxLifeTime = 1.5f;
  this->damage = damage;

  mesh = Game::models["sphere"];

  collider = new SphereCollider(this->position, scale.x / 2);
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
  this->lifeTime += Game::deltaTime;

  this->velocity = this->direction * this->speed * Game::deltaTime;
  this->position += this->velocity;

  collider->setPosition(this->position);
}

void Bullet::draw()
{
  glBindTexture(GL_TEXTURE_2D, 0);
  mesh->setVertexColors(glm::vec3(1.0f, 0.0f, 0.0f));
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(this->getModelMatrix()));
  mesh->render(this->getModelMatrix(), CALCULATE_ILLUMINATION);
  glPopMatrix();

  if (Game::debugMode)
  {
    collider->debug();
    this->debug();
  }
}