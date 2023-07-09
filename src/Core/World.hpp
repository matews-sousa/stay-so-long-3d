#pragma once

#include <iostream>
#include <vector>
#include "../Entities/Player.hpp"
#include "../Entities/Enemy.hpp"

class Player;
class Enemy;

class World
{
public:
  World();
  virtual ~World();

  void update();
  void render();

  static Player *player;
  static std::vector<Enemy *> enemies;

private:
  void handleEnemies();
  void handleWaves();

  std::vector<glm::vec3> spawnPoints;

  int currentWave;
  float timeBetweenWaves;
  float waveTimer;
  std::vector<Enemy *> enemiesToSpawn;
};