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

  void loadTextures();
  void init();
  void update();
  void render();
  void processEvents();

public:
  Game();
  virtual ~Game();

  void run();

  static sf::RenderWindow *window;
  static Camera *camera;
  static float deltaTime;
};