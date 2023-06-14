#pragma once

#include <SFML/Graphics.hpp>
#include "Camera.hpp"
#include <vector>
#include <map>
#include <string>
#include "Texture.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Terrain.hpp"

class Game
{
private:
  sf::Clock clock;
  sf::Event event;
  Player *player;

  void initTextures();
  void initObjModels();
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
  static Terrain *terrain;
  static std::map<std::string, Model *> models;
};