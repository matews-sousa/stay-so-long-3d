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
  drawHealthBar();

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