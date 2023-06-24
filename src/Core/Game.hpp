#pragma once

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.hpp"
#include "Texture.hpp"
#include "Input.hpp"
#include "Model.hpp"
#include "Light.hpp"
#include "MousePicker.hpp"
#include "../Entities/Player.hpp"
#include "../Entities/Terrain.hpp"
#include "../primitives.hpp"

class Player;

class MousePicker;

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
  static MousePicker *picker;
  static float deltaTime;
  static Terrain *terrain;
  static std::map<std::string, Model *> models;
};