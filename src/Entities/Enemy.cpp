#include "Enemy.hpp"

Enemy::Enemy(glm::vec3 initialPosition, glm::vec3 scale, ENEMY_TYPE type)
  : GameObject(initialPosition, scale)
{
  this->enemyType = type;

  direction = glm::vec3(0.0f, 0.0f, 0.0f);
  speed = 200.0f;

  if (type == FOLLOWER)
    mesh = new Mesh("../src/Assets/Models/cube.obj");
  else if (type == CHARGER)
    mesh = new Mesh("../src/Assets/Models/cone.obj");
  else
    mesh = new Mesh("../src/Assets/Models/sphere.obj");

  collider = new SphereCollider(this->position, scale.x * 0.7f);

  maxHealth = 100;
  currentHealth = maxHealth;
}

Enemy::~Enemy()
{
  delete mesh;
  delete collider;
}

void Enemy::update(glm::vec3 playerPosition)
{
  const float targetY = 25.0f;
  direction = playerPosition - position;
  direction.y = targetY;
  direction = glm::normalize(direction);

  handleEnemyTypes();

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

void Enemy::handleEnemyTypes()
{
  switch(enemyType)
  {
    case FOLLOWER:
      position += direction * speed * Game::deltaTime;
      break;
    case CHARGER:
      handleCharger();
      break;
    default:
      break;
  }
}

void Enemy::handleCharger()
{
  if (!isCharging && !isSprinting)
  {
    this->position += direction * speed * Game::deltaTime;

    chargeTimer += 0.1f;

    if (chargeTimer >= chargeDuration)
    {
      isCharging = true;
      chargeTimer = 0.0f;
    }
  }

  if (isCharging)
  {
    this->position += 0.0f;

    chargingTimer += 0.1f;
    if (chargingTimer >= chargingDuration)
    {
      sprintDirection = direction;
      isSprinting = true;
      isCharging = false;
      chargingTimer = 0.0f;
    }
  }

  if (isSprinting)
  {
    this->position += sprintDirection * speed * sprintForce * Game::deltaTime;

    sprintTimer += 0.1f;
    if (sprintTimer >= sprintDuration)
    {
      isSprinting = false;
      sprintTimer = 0.0f;
      chargeTimer = 0.0f;
    }
  }
}

void Enemy::setPosition(glm::vec3 position)
{
  this->position = position;
  collider->setPosition(position);
}