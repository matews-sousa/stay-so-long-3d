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
#include "Light.hpp"
#include "MousePicker.hpp"
#include "OBJLoader.hpp"
#include "Mesh.hpp"
#include "World.hpp"
#include "../primitives.hpp"

class World;
class Terrain;
class MousePicker;
class Mesh;
class Light;

class Game
{
private:
  sf::Clock clock;
  sf::Event event;
  sf::Font *font;
  sf::Texture *backgroundTexture;
  sf::Sprite *backgroundSprite;

  void initUiTexts();
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
  static MousePicker *picker;
  static glm::mat4 projectionMatrix;
  static glm::mat4 viewMatrix;
  static float deltaTime;
  static Terrain *terrain;
  static std::map<std::string, Mesh *> models;
  static bool debugMode;
  static std::map<std::string, sf::Text> uiTexts;
  static World *world;
};