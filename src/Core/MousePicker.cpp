#include "MousePicker.hpp"

MousePicker::MousePicker(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, sf::RenderWindow &window)
{
  this->projectionMatrix = projectionMatrix;
  this->viewMatrix = viewMatrix;
  this->window = &window;
}

MousePicker::~MousePicker()
{
}

void MousePicker::update()
{
  currentRay = calculateMouseRay();
}

glm::vec3 MousePicker::calculateMouseRay()
{
  float mouseX = Input::getMousePos().x;
  float mouseY = Input::getMousePos().y;

  glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY);
  glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
  glm::vec4 eyeCoords = toEyeCoords(clipCoords);
  glm::vec4 worldRay = toWorldCoords(eyeCoords);

  return glm::vec3(worldRay.x, worldRay.y, worldRay.z);
}

glm::vec2 MousePicker::getNormalizedDeviceCoords(float mouseX, float mouseY)
{
  float x = (2.0f * mouseX) / window->getSize().x - 1.0f;
  float y = (2.0f * mouseY) / window->getSize().y - 1.0f;

  return glm::vec2(x, -y);
}

glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords)
{
  glm::mat4 invertedProjection = glm::inverse(projectionMatrix);
  glm::vec4 eyeCoords = invertedProjection * clipCoords;

  return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
}

glm::vec4 MousePicker::toWorldCoords(glm::vec4 eyeCoords)
{
  glm::mat4 invertedView = glm::inverse(viewMatrix);
  glm::vec4 rayWorld = invertedView * eyeCoords;

  glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
  mouseRay = glm::normalize(mouseRay);

  return glm::vec4(mouseRay.x, mouseRay.y, mouseRay.z, 0.0f);
}