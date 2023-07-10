#include "Player.hpp"

Player::Player(glm::vec3 position, glm::vec3 scale) : GameObject(position, scale)
{
  this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  this->speed = 400.0f;

  this->shootCooldown = 0.0f;
  this->maxShootCooldown = 0.5f;

  setRotation(glm::vec3(0.0f, -90.0f, 0.0f));
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
  this->look();
  this->handleShots();

  updateLocalMatrix();

  position.y -= 9.8f * Game::deltaTime;
  if (position.y <= 0.0f)
    position.y = 0.0f;
}

void Player::move(glm::vec3 direction)
{
  if (glm::length(direction) == 0.0f)
    return;

  this->velocity = direction * speed * Game::deltaTime;
  this->position += this->velocity;
  
  Game::camera->move(position);
}

void Player::look()
{
  glm::vec3 dir = Game::picker->getCurrentTerrainPoint() - this->position;
  dir.y = 0.0f;
  dir = glm::normalize(dir);

  glm::vec3 right = glm::normalize(glm::cross(dir, up));

  this->forward = dir;
  this->right = right;
}

void Player::shoot()
{
  Bullet* bullet = new Bullet(25, 1000.0f, this->forward, this->position + glm::vec3(0.0f, 30.0f, 0.0f), glm::vec3(15.0f, 15.0f, 15.0f));
  bullets.push_back(bullet);
}

void Player::handleShots()
{
  shootCooldown += Game::deltaTime;
  if (shootCooldown >= maxShootCooldown && Input::isMouseButtonDown(sf::Mouse::Left))
  {
    shoot();
    shootCooldown = 0.0f;
  }

  for (auto &bullet : bullets)
  {
    bullet->update();

    if (World::boss != nullptr)
    {
      if (bullet->collider->testCollision(*World::boss->collider))
      {
        World::boss->takeDamage(bullet->getDamage());
        bullet->setLifeTime(bullet->getMaxLifeTime());
      }
    }

    for (auto &enemy : World::enemies)
    {
      if (bullet->collider->testCollision(*enemy->collider))
      {
        enemy->takeDamage(bullet->getDamage());
        bullet->setLifeTime(bullet->getMaxLifeTime());
      }
    }
  }

  if (bullets.size() > 0)
  {
    auto i = std::remove_if(bullets.begin(), bullets.end(), [](Bullet* bullet) {
      return bullet->getLifeTime() >= bullet->getMaxLifeTime();
    });

    if (i != bullets.end())
      bullets.erase(i, bullets.end());
  }
}

void Player::draw()
{
  for (auto &bullet : bullets)
    bullet->draw();
  
  // body
  Texture::bindByName("mecha");
  glPushMatrix();
    glMultMatrixf(glm::value_ptr(getModelMatrix()));
    Game::models["mecha"]->render(getModelMatrix());
  glPopMatrix();

  this->debug();
}