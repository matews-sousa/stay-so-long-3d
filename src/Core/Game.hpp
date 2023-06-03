#pragma once

#include <SFML/Graphics.hpp>

class Game
{
private:
  sf::Clock clock;

public:
  Game();
  virtual ~Game();

  void run();
  void update();
  void render();
  void processEvents();

  static sf::RenderWindow *window;
  static float deltaTime;
};