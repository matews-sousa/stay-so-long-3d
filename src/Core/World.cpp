#include "World.hpp"

int World::score;
Player *World::player;
Spaceship *World::spaceship;
Boss *World::boss;
std::vector<Enemy *> World::enemies;

World::World()
{
  score = 0.0f;
  bossScoreStep = 200;

  player = new Player(glm::vec3(50.0f, 35.0f, 50.0f), glm::vec3(15.0f, 15.0f, 15.0f));
  spaceship = new Spaceship(glm::vec3(0.0f, -25.0f, 0.0f), glm::vec3(50.0f, 50.0f, 50.0f));

  currentWave = 0;
  timeBetweenWaves = 5.0f;
  waveTimer = 0.0f;

  spawnPoints.push_back(glm::vec3(0.0f, 0.0f, 2000.0f));
  spawnPoints.push_back(glm::vec3(-2000.0f, 0.0f, 0.0f));
  spawnPoints.push_back(glm::vec3(-2000.0f, 0.0f, 2000.0f));

  boss = nullptr;
}

World::~World()
{
  delete player;
  enemies.clear();
  enemiesToSpawn.clear();
}

void World::update()
{
  Game::uiTexts["score"].setString("Score: " + std::to_string(score));

  if (waveTimer > 0.0f)
  {
    std::ostringstream out;
    out.precision(2);
    out << std::fixed << timeBetweenWaves - waveTimer;
    Game::uiTexts["waveTimer"].setString("Next wave in: " + out.str());
  }
  else
  {
    Game::uiTexts["waveTimer"].setString("Wave: " + std::to_string(currentWave));
  }

  player->update();
  spaceship->update();

  if (boss == nullptr)
  {
    handleEnemies();
    handleWaves();

    if (score >= bossScoreStep)
    {
      enemies.clear();
      enemiesToSpawn.clear();

      glm::vec3 spawnPoint = spawnPoints[Utils::genRandomNumberInRange(0, spawnPoints.size())];
      boss = new Boss(spawnPoint, glm::vec3(50.0f, 50.0f, 50.0f));

      bossScoreStep += 200 * (currentWave + 1);
    }
  }
  else
  {
    boss->update();

    if (boss->getIsDead())
    {
      delete boss;
      boss = nullptr;
      waveTimer = 0.0f;
    }
  }
}

void World::render()
{
  player->draw();

  if (boss == nullptr)
  {
    for (auto &enemy : enemies)
      enemy->draw();
  }
  else
  {
    boss->draw();
  }

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

    if (enemy->collider->testCollision(*player->collider))
    {
      std::cout << "Player hit: " << player->getCurrentHealth() << std::endl;
      player->takeDamage(10);
      enemy->takeDamage(enemy->getMaxHealth());
    }

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
    {
      Enemy *enemy = *i;
      score += enemy->getEnemyType() == FOLLOWER ? 50 : enemy->getEnemyType() == SHOOTER ? 75 : 100;
      enemies.erase(i);
    }
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
      int totalEnemies = Utils::genRandomNumberInRange(3, 5) * currentWave;

      for (int i = 0; i < totalEnemies; i++)
      {
        glm::vec3 spawnPoint = spawnPoints[Utils::genRandomNumberInRange(0, spawnPoints.size())];
        ENEMY_TYPE type = static_cast<ENEMY_TYPE>(Utils::genRandomNumberInRange(0, 2));
        Enemy *enemy = new Enemy(spawnPoint, glm::vec3(25.0f, 25.0f, 25.0f), type);
        enemiesToSpawn.push_back(enemy);
      }

      waveTimer = 0.0f;
    }
  }

  if (!enemiesToSpawn.empty() && enemies.empty())
  {
    int totalEnemiesToSpawn = Utils::genRandomNumberInRange(1, 3) * currentWave / 2.0f;

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
