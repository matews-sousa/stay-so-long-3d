#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/gl.h>
#include <vector>
#include "Utils.hpp"

enum LightType
{
  POINT_LIGHT,
  DIRECTIONAL_LIGHT,
  SPOT_LIGHT
};

class Light
{
private:
  glm::vec3 position;
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;

  glm::mat4 projectionMatrix;
  glm::mat4 viewMatrix;

  bool isOn = true;
  LightType type = POINT_LIGHT;

public:
  Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
  Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, LightType type);
  virtual ~Light();

  glm::vec3 calculateIllumination(const glm::vec3 &position, const glm::vec3 &normal, const glm::mat4 &modelMatrix);
  static glm::vec3 calculateIllumination(std::vector<Light *> lights, const glm::vec3 &position, const glm::vec3 &normal, const glm::mat4 &modelMatrix);
  void draw();

  void toggle() { isOn = !isOn; }

  glm::vec3 getPosition() { return position; }
  glm::vec3 getAmbient() { return ambient; }
  glm::vec3 getDiffuse() { return diffuse; }
  glm::vec3 getSpecular() { return specular; }

  void setPosition(glm::vec3 position) { this->position = position; }
  void setAmbient(glm::vec3 ambient) { this->ambient = ambient; }
  void setDiffuse(glm::vec3 diffuse) { this->diffuse = diffuse; }
  void setSpecular(glm::vec3 specular) { this->specular = specular; }
  void setViewMatrix(glm::mat4 viewMatrix) { this->viewMatrix = viewMatrix; }
  void setProjectionMatrix(glm::mat4 projectionMatrix) { this->projectionMatrix = projectionMatrix; }
};