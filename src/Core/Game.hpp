#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include <glm/mat4x4.hpp>
#include "Camera.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "../Entities/Player.hpp"

class Game
{
private:
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;
  sf::Clock clock;
  sf::Event event;
  Player *player;

  void initTextures();
  void initObjModels();
  void initLights();
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
  static std::map<std::string, Model *> models;
  static std::vector<Light *> lights;
};