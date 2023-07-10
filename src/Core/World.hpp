#pragma once

#include <iostream>
#include <vector>
#include "../Entities/Player.hpp"
#include "../Entities/Enemy.hpp"
#include "../Entities/Spaceship.hpp"

class Player;
class Enemy;
class Spaceship;

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