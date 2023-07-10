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
  delete mesh;
  delete collider;
  for (auto &bullet : bullets)
  {
    delete bullet;
  }
}

void Boss::update()
{
  isDead = currentHealth <= 0.0f;
  if (isDead)
    return;

  glm::vec3 direction = World::player->getPosition() - position;
  direction = glm::normalize(direction);
  position += direction * speed * Game::deltaTime;

  glm::vec3 right = glm::cross(direction, up);
  forward = direction;
  this->right = right;

  handleShots();

  updateLocalMatrix();

  collider->setPosition(position + glm::vec3(0.0f, scale.y, 0.0f));
}

void Boss::draw()
{
  drawHealthBar();
  for (auto &bullet : bullets)
  {
    bullet->draw();
  }

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
  glm::vec3 initialPosition = position + glm::vec3(0.0f, scale.y, 0.0f);

  Bullet *bullet = new Bullet(damage, 1000.0f, forward, initialPosition, glm::vec3(30.0f, 30.0f, 30.0f));
  bullets.push_back(bullet);
}

void Boss::handleShots()
{
  shootTimer += Game::deltaTime;
  if (shootTimer >= shootInterval)
  {
    shoot();
    shootTimer = 0.0f;
  }

  for (auto &bullet : bullets)
  {
    bullet->update();
  }

  if (bullets.size() > 0)
  {
    auto i = std::remove_if(bullets.begin(), bullets.end(), [](Bullet *bullet) {
      return bullet->getLifeTime() >= bullet->getMaxLifeTime();
    });

    if (i != bullets.end())
      bullets.erase(i);
  }
}

void Boss::drawHealthBar()
{
  float healthPercentage = currentHealth / maxHealth;
  float barWidth = 500.0f;
  float barHeight = 25.0f;
  float barX = Game::window->getSize().x / 2.0f - barWidth / 2.0f;
  float barY = Game::window->getSize().y - barHeight - 10.0f;

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