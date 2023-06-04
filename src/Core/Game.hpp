#pragma once

#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include "../Entities/Player.hpp"

class Game
{
private:
  sf::Clock clock;
  sf::Event event;
  Player *player;

public:
  Game();
  virtual ~Game();

  void init();
  void run();
  void update();
  void render();
  void processEvents();

  static sf::RenderWindow *window;
  static Camera *camera;
  static float deltaTime;
};