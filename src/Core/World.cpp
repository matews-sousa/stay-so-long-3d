#include "World.hpp"

Player *World::player;
std::vector<Enemy *> World::enemies;

World::World()
{
  player = new Player(glm::vec3(0.0f, 35.0f, 0.0f), glm::vec3(15.0f, 15.0f, 15.0f));

  Enemy *enemy = new Enemy(glm::vec3(0.0f, 25.0f, 0.0f), glm::vec3(25.0f, 25.0f, 25.0f));
  enemies.push_back(enemy);
}

World::~World()
{
  delete player;
  enemies.clear();
}

void World::update()
{
  player->update();

  handleEnemies();
}

void World::render()
{
  player->draw();
  for (auto &enemy : enemies)
    enemy->draw();
}

void World::handleEnemies()
{
  for (auto &enemy : enemies)
    enemy->update(player->getPosition());

  if (enemies.size() > 0)
  {
    auto i = std::remove_if(enemies.begin(), enemies.end(), [](Enemy *enemy) { return enemy->isDead(); });

    if (i != enemies.end())
      enemies.erase(i);
  }
}
