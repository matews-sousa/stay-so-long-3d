#include "Boss.hpp"

Boss::Boss(glm::vec3 position, glm::vec3 size) : GameObject(position, size)
{
  speed = 200.0f;
  shootTimer = 0.0f;
  shootInterval = 0.5f;
  maxHealth = 100.0f;
  currentHealth = maxHealth;
  isDead = false;
  damage = 10.0f;
  score = 100.0f;

  mesh = new Mesh("../src/Assets/Models/giant.obj");

  collider = new CubeCollider(position + glm::vec3(0.0f, size.y, 0.0f), size);
}

Boss::~Boss()
{
}

void Boss::update()
{
  std::cout << "Boss health: " << currentHealth << std::endl;
  isDead = currentHealth <= 0.0f;
  if (isDead)
    return;

  glm::vec3 direction = World::player->getPosition() - position;
  direction = glm::normalize(direction);
  position += direction * speed * Game::deltaTime;

  glm::vec3 right = glm::cross(direction, up);
  forward = direction;
  this->right = right;

  updateLocalMatrix();

  collider->setPosition(position + glm::vec3(0.0f, scale.y, 0.0f));
}

void Boss::draw()
{
  Texture::bindByName("giant");
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(getModelMatrix()));
  mesh->render(getModelMatrix());
  glPopMatrix();

  collider->debug();
  this->debug();
}

void Boss::shoot()
{
  
}