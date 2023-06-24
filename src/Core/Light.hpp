#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

enum LIGHT_TYPE
{
  LIGHT_POINT,
  LIGHT_SPOT,
  LIGHT_DIRECTIONAL
};

class Light
{
public:
  static void initLights();
  Light(LIGHT_TYPE type);
  ~Light();

  void setVisible(bool visible = true);
  void toggleVisible() { setVisible(!visible); }

  LIGHT_TYPE getLightType() { return lightType; }

  void setPosition(glm::vec4 position);
  void setAmbient(glm::vec4 ambient);
  void setDiffuse(glm::vec4 diffuse);
  void setSpecular(glm::vec4 specular);

  void setLightType(LIGHT_TYPE type);

  // spotlight type specific functions
  void setSpotDirection(glm::vec4 spotDirection);
  void setCutoff(float cutoff);
  void setExponent(float exponent);

  void setAttenuation(float constant, float linear, float quadratic);

  int getLightNum() { return lightNum; }

  void updateLight();
  void drawLight();

  static int numLights;
  static std::vector<int> availableLights;
  static std::vector<Light *> lights;

private:
  glm::vec4 position;
  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 specular;
  glm::vec4 spotDirection;

  LIGHT_TYPE lightType;

  float cutoff;
  float exponent;

  bool visible;
  int lightNum;
};