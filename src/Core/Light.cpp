#include "Light.hpp"

int Light::numLights;
std::vector<int> Light::availableLights;
std::vector<Light *> Light::lights;

void Light::initLights()
{
  glGetIntegerv(GL_MAX_LIGHTS, &numLights);

  for (int i = 0; i < numLights; i++)
  {
    availableLights.push_back(GL_LIGHT0 + i);
  }
}

Light::Light(LIGHT_TYPE type)
{
  lights.push_back(this);

  if ((int)availableLights.size() > 0)
  {
    lightNum = availableLights[0];

    availableLights.erase(availableLights.begin());
  
    setVisible(true);

    setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    setAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    setDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    setSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    setSpotDirection(glm::vec4(0.0f, -1.0f, 0.0f, 1.0f));
    setCutoff(45.0f);
    setExponent(12.0f);

    setLightType(type);
    
    updateLight();
  }
  else
  {
    lightNum = 0;
    setVisible(false);
    std::cout << "No more lights available" << std::endl;
  }
}

Light::~Light()
{
  if (lightNum != 0)
  {
    availableLights.push_back(lightNum);
  }

  lights.erase(std::find(lights.begin(), lights.end(), this));
}

void Light::setVisible(bool visible)
{
  this->visible = visible;

  if (visible)
    glEnable(lightNum);
  else
    glDisable(lightNum);
}

void Light::setPosition(glm::vec4 position)
{
  this->position = position;
  glLightfv(lightNum, GL_POSITION, glm::value_ptr(position));
}

void Light::setAmbient(glm::vec4 ambient) 
{ 
  this->ambient = ambient;
  glLightfv(lightNum, GL_AMBIENT, glm::value_ptr(ambient));
}

void Light::setDiffuse(glm::vec4 diffuse) 
{ 
  this->diffuse = diffuse;
  glLightfv(lightNum, GL_DIFFUSE, glm::value_ptr(diffuse));
}

void Light::setSpecular(glm::vec4 specular)
{ 
  this->specular = specular; 
  glLightfv(lightNum, GL_SPECULAR, glm::value_ptr(specular));
}

void Light::setLightType(LIGHT_TYPE type)
{
  this->lightType = type;

  if (type == LIGHT_SPOT)
  {
    position.w = 1.0f;
    setCutoff(45.0f);
  }
  else if (type == LIGHT_POINT)
  {
    position.w = 1.0f;
    setCutoff(180.0f);
  }
  else if (type == LIGHT_DIRECTIONAL)
  {
    position.w = 0.0f;
    setCutoff(180.0f);
  }

  updateLight();
}

void Light::setSpotDirection(glm::vec4 spotDirection) 
{ 
  this->spotDirection = spotDirection; 
  glLightfv(lightNum, GL_SPOT_DIRECTION, glm::value_ptr(spotDirection));
}

void Light::setCutoff(float cutoff) 
{ 
  this->cutoff = cutoff;
  glLightf(lightNum, GL_SPOT_CUTOFF, cutoff);
}

void Light::setExponent(float exponent)
{ 
  this->exponent = exponent; 
  glLightf(lightNum, GL_SPOT_EXPONENT, exponent);
}

void Light::setAttenuation(float constant, float linear, float quadratic)
{
  glLightfv(lightNum, GL_CONSTANT_ATTENUATION, &constant);
  glLightfv(lightNum, GL_LINEAR_ATTENUATION, &linear);
  glLightfv(lightNum, GL_QUADRATIC_ATTENUATION, &quadratic);
}

void Light::updateLight()
{
  glLightfv(lightNum, GL_POSITION, glm::value_ptr(position));
  glLightfv(lightNum, GL_AMBIENT, glm::value_ptr(ambient));
  glLightfv(lightNum, GL_DIFFUSE, glm::value_ptr(diffuse));
  glLightfv(lightNum, GL_SPECULAR, glm::value_ptr(specular));
  glLightfv(lightNum, GL_SPOT_DIRECTION, glm::value_ptr(spotDirection));
  glLightf(lightNum, GL_SPOT_CUTOFF, cutoff);
  glLightf(lightNum, GL_SPOT_EXPONENT, exponent);
}

void Light::drawLight()
{
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  glColor3f(1.0f, 1.0f, 0.0f);
  glVertex3f(position.x, position.y, position.z);
  glEnd();
}