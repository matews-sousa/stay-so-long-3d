#include "MousePicker.hpp"

MousePicker::MousePicker(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, sf::RenderWindow &window, Terrain &terrain)
{
  this->projectionMatrix = projectionMatrix;
  this->viewMatrix = viewMatrix;
  this->window = &window;
  this->terrain = &terrain;
}

MousePicker::~MousePicker()
{
}

void MousePicker::update(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
  this->projectionMatrix = projectionMatrix;
  this->viewMatrix = viewMatrix;

  currentRay = calculateMouseRay();

  if (intersectionInRange(0, RAY_RANGE, currentRay))
  {
    currentTerrainPoint = binarySearch(0, 0, RAY_RANGE, currentRay);
  }
  else
  {
    currentTerrainPoint = glm::vec3(0.0f, 0.0f, 0.0f);
  }
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

// Binary search algorithm to find the point on the ray closest to the terrain
glm::vec3 MousePicker::getPointOnRay(glm::vec3 ray, float distance)
{
  glm::vec3 camPos = Game::camera->getPosition();
  glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
  glm::vec3 scaledRay = glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
  return start + scaledRay;
}

glm::vec3 MousePicker::binarySearch(int count, float start, float finish, glm::vec3 ray)
{
  float half = start + ((finish - start) / 2.0f);
  if (count >= RECURSION_COUNT)
  {
    glm::vec3 endPoint = getPointOnRay(ray, half);
    Terrain *terrain = Game::terrain;
    if (terrain != NULL)
      return endPoint;
    else
      return glm::vec3(0.0f, 0.0f, 0.0f);
  }

  if (intersectionInRange(start, half, ray))
    return binarySearch(count + 1, start, half, ray);
  else
    return binarySearch(count + 1, half, finish, ray);
}

bool MousePicker::intersectionInRange(float start, float finish, glm::vec3 ray)
{
  glm::vec3 startPoint = getPointOnRay(ray, start);
  glm::vec3 endPoint = getPointOnRay(ray, finish);

  if (!isUnderGround(startPoint) && isUnderGround(endPoint))
    return true;
  else
    return false;
}

bool MousePicker::isUnderGround(glm::vec3 testPoint)
{
  Terrain *terrain = Game::terrain;
  float height = 0.0f;
  if (terrain != NULL)
    height = 0.0f; // use terrain->getHeightOfTerrain(testPoint.x, testPoint.z); when implemented different terrain heights 
  if (testPoint.y < height)
    return true;
  else
    return false;
}