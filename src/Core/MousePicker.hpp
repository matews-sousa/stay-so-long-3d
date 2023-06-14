#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <glm/glm.hpp>
#include "Input.hpp"

class MousePicker
{
public:
  MousePicker(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, sf::RenderWindow &window);
  virtual ~MousePicker();

  void update();
  glm::vec3 getCurrentRay() const { return currentRay; }

  void setProjectionMatrix(glm::mat4 projectionMatrix) { this->projectionMatrix = projectionMatrix; }
  void setViewMatrix(glm::mat4 viewMatrix) { this->viewMatrix = viewMatrix; }

private:
  sf::RenderWindow *window;
  glm::vec3 currentRay;
  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;

  glm::vec3 calculateMouseRay();
  glm::vec2 getNormalizedDeviceCoords(float mouseX, float mouseY);
  glm::vec4 toEyeCoords(glm::vec4 clipCoords);
  glm::vec4 toWorldCoords(glm::vec4 eyeCoords);
};