#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <glm/glm.hpp>
#include "World.hpp"
#include "Game.hpp"
#include "Input.hpp"
#include "../Entities/Terrain.hpp"

class Terrain;

const int RECURSION_COUNT = 200;
const float RAY_RANGE = 2000;

class MousePicker
{
public:
  MousePicker(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, sf::RenderWindow &window, Terrain &terrain);
  virtual ~MousePicker();

  void update(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
  glm::vec3 getCurrentRay() const { return currentRay; }
  glm::vec3 getCurrentTerrainPoint() { return currentTerrainPoint; }

  void setProjectionMatrix(glm::mat4 projectionMatrix) { this->projectionMatrix = projectionMatrix; }
  void setViewMatrix(glm::mat4 viewMatrix) { this->viewMatrix = viewMatrix; }
  
private:
  sf::RenderWindow *window;
  glm::vec3 currentRay;
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;

  Terrain *terrain;
  glm::vec3 currentTerrainPoint;

  glm::vec3 calculateMouseRay();
  glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
  glm::vec4 toEyeCoords(glm::vec4 clipCoords);
  glm::vec4 toWorldCoords(glm::vec4 eyeCoords);

  // Binary search algorithm to find the point on the ray closest to the terrain
  glm::vec3 getPointOnRay(glm::vec3 ray, float distance);
  glm::vec3 binarySearch(int count, float start, float finish, glm::vec3 ray);
  bool intersectionInRange(float start, float finish, glm::vec3 ray);
  bool isUnderGround(glm::vec3 testPoint);
};