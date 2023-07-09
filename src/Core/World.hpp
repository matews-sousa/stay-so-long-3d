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

};