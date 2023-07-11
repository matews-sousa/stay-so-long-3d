#include "Player.hpp"

Player::Player(glm::vec3 position, glm::vec3 scale) : GameObject(position, scale)
{
  velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  speed = 400.0f;

  maxHealth = 100.0f;
  currentHealth = maxHealth;

  shootCooldown = 0.0f;
  maxShootCooldown = 0.5f;

  dashCooldown = 0.0f;
  maxDashCooldown = 0.5f;
  dashSpeed = 1000.0f;
  dashDuration = 0.1f;
  dashTimer = 0.0f;
  isDashing = false;

  setRotation(glm::vec3(0.0f, -90.0f, 0.0f));

  collider = new SphereCollider(position + glm::vec3(0.0f, scale.y + 10.0f, 0.0f), scale.x);
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
  this->handleDash(direction);

  updateLocalMatrix();

  position.y -= 9.8f * Game::deltaTime;
  if (position.y <= 0.0f)
    position.y = 0.0f;

  // limit player to the terrain
  if (position.x < -Game::terrain->getWidth())
    position.x = -Game::terrain->getWidth();
  else if (position.x > Game::terrain->getWidth())
    position.x = Game::terrain->getWidth();
  else if (position.z < -Game::terrain->getHeight())
    position.z = -Game::terrain->getHeight();
  else if (position.z > Game::terrain->getHeight())
    position.z = Game::terrain->getHeight();


  collider->setPosition(position + glm::vec3(0.0f, scale.y + 10.0f, 0.0f));
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

void Player::handleDash(glm::vec3 movingDirection)
{
  dashCooldown -= Game::deltaTime;
  if (Input::isKeyPressed(sf::Keyboard::Space))
  {
    if (dashCooldown < 0.0f)
    {
      isDashing = true;
      dashDirection = movingDirection;
      dashCooldown = maxDashCooldown;
    }
  }

  if (isDashing)
  {
    dashTimer += Game::deltaTime;
    dash(dashDirection);
    if (dashTimer >= dashDuration)
    {
      isDashing = false;
      dashTimer = 0.0f;
    }
  }
}

void Player::dash(glm::vec3 direction)
{
  this->velocity = direction * dashSpeed * Game::deltaTime;
  this->position += this->velocity;

  Game::camera->move(position);
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
  drawHealthBar();
  
  for (auto &bullet : bullets)
    bullet->draw();

  // body
  Texture::bindByName("mecha");
  glPushMatrix();
    glMultMatrixf(glm::value_ptr(getModelMatrix()));
    Game::models["mecha"]->render(getModelMatrix());
  glPopMatrix();

  this->debug();
  collider->debug();
}

void Player::drawHealthBar()
{
  float healthPercentage = currentHealth / maxHealth;
  float barWidth = 250.0f;
  float barHeight = 25.0f;
  float barX = Game::window->getSize().x / 2.0f - barWidth / 2.0f;
  float barY = 30.0f;

  // remove projection and modelview matrices
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glm::mat4 ortho = glm::ortho(0.0f, (float)Game::window->getSize().x, 0.0f, (float)Game::window->getSize().y);
  glLoadMatrixf(glm::value_ptr(ortho));
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glPushMatrix();
  glTranslatef(barX, barY, 0.0f);

  // current health bar
  glColor3f(0.0f, 1.0f, 0.0f);
  glBegin(GL_QUADS);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(barWidth * healthPercentage, 0.0f);
  glVertex2f(barWidth * healthPercentage, barHeight);
  glVertex2f(0.0f, barHeight);
  glEnd();

  // total health bar
  glColor3f(1.0f, 0.0f, 0.0f);
  glBegin(GL_QUADS);
  glVertex2f(0.0f, 0.0f);
  glVertex2f(barWidth, 0.0f);
  glVertex2f(barWidth, barHeight);
  glVertex2f(0.0f, barHeight);
  glEnd();

  glPopMatrix();

  // reset projection and modelview matrices
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(glm::value_ptr(Game::projectionMatrix));
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixf(glm::value_ptr(Game::viewMatrix));
}