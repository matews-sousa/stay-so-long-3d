#include "World.hpp"

Player *World::player;
Spaceship *World::spaceship;
std::vector<Enemy *> World::enemies;

World::World()
{
  player = new Player(glm::vec3(50.0f, 35.0f, 50.0f), glm::vec3(15.0f, 15.0f, 15.0f));
  spaceship = new Spaceship(glm::vec3(0.0f, -25.0f, 0.0f), glm::vec3(50.0f, 50.0f, 50.0f));

  currentWave = 2;
  timeBetweenWaves = 10.0f;
  waveTimer = 0.0f;

  spawnPoints.push_back(glm::vec3(2000.0f, 0.0f, 0.0f));
  spawnPoints.push_back(glm::vec3(-2000.0f, 0.0f, 0.0f));
  spawnPoints.push_back(glm::vec3(0.0f, 0.0f, 2000.0f));
  spawnPoints.push_back(glm::vec3(0.0f, 0.0f, -2000.0f));
  spawnPoints.push_back(glm::vec3(2000.0f, 0.0f, 2000.0f));
  spawnPoints.push_back(glm::vec3(2000.0f, 0.0f, -2000.0f));
  spawnPoints.push_back(glm::vec3(-2000.0f, 0.0f, 2000.0f));
  spawnPoints.push_back(glm::vec3(-2000.0f, 0.0f, -2000.0f));
}

World::~World()
{
  delete player;
  enemies.clear();
}

void World::update()
{
  player->update();
  spaceship->update();

  handleEnemies();
  handleWaves();
}

void World::render()
{
  player->draw();
  for (auto &enemy : enemies)
    enemy->draw();

  spaceship->draw();

  for (auto &spawn : spawnPoints)
  {
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(spawn.x, spawn.y, spawn.z);
    glEnd();
  }
}

void World::handleEnemies()
{
  for (auto &enemy : enemies)
  {
    enemy->update(player->getPosition());

    if (enemy->collider->testCollision(*spaceship->collider))
    {
      enemy->takeDamage(enemy->getMaxHealth());
    }

    for (auto &targetEnemy : enemies)
    {
      if (enemy != targetEnemy)
      {
        if (enemy->collider->testCollision(*targetEnemy->collider))
        {
          float distance = glm::distance(enemy->getPosition(), targetEnemy->getPosition());
          float overlap = 0.1f * (distance - enemy->collider->getRadius() - targetEnemy->collider->getRadius());
          glm::vec3 direction = glm::normalize(enemy->getPosition() - targetEnemy->getPosition());
          enemy->setPosition(overlap * direction + enemy->getPosition());
          targetEnemy->setPosition(overlap * -direction + targetEnemy->getPosition());
        } 
      }
    }
  }

  if (enemies.size() > 0)
  {
    auto i = std::remove_if(enemies.begin(), enemies.end(), [](Enemy *enemy) { return enemy->isDead(); });

    if (i != enemies.end())
      enemies.erase(i);
  }
}

void World::handleWaves()
{
  if (enemiesToSpawn.empty() && enemies.empty())
  {
    waveTimer += 1.0f / 60.0f;
    if (waveTimer >= timeBetweenWaves)
    {
      currentWave++;
      int totalEnemies = 5 * currentWave;

      for (int i = 0; i < totalEnemies; i++)
      {
        int random = rand() % spawnPoints.size();
        glm::vec3 spawnPoint = spawnPoints[random];
        Enemy *enemy = new Enemy(spawnPoint, glm::vec3(25.0f, 25.0f, 25.0f));
        enemiesToSpawn.push_back(enemy);
      }

      waveTimer = 0.0f;
    }
  }

  if (!enemiesToSpawn.empty() && enemies.empty())
  {
    int random = rand() % spawnPoints.size();
    
    int totalEnemiesToSpawn = random * currentWave / 2;

    if (totalEnemiesToSpawn > enemiesToSpawn.size())
      totalEnemiesToSpawn = enemiesToSpawn.size();

    for (int i = 0; i < totalEnemiesToSpawn; i++)
    {
      Enemy *enemy = enemiesToSpawn.back();
      enemiesToSpawn.pop_back();
      enemies.push_back(enemy);
    }
  }
}
