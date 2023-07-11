#pragma once

#include <iostream>
#include <vector>
#include "../Entities/Player.hpp"
#include "../Entities/Enemy.hpp"
#include "../Entities/Spaceship.hpp"
#include "../Entities/Boss.hpp"

class Player;
class Enemy;
class Spaceship;
class Boss;

class World
{
public:
  World();
  virtual ~World();

  void update();
  void render();

  static int score;
  static Player *player;
  static Spaceship *spaceship;
  static Boss *boss;
  static std::vector<Enemy *> enemies;

private:
  void resetWorld();

  void handleEnemies();
  void handleWaves();

  std::vector<glm::vec3> spawnPoints;

  int currentWave;
  float timeBetweenWaves;
  float waveTimer;
  std::vector<Enemy *> enemiesToSpawn;

  int bossScoreStep;
};