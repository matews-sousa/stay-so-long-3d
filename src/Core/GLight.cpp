#include "GLight.hpp"

int GLight::numLights;
std::vector<int> GLight::availableLights;
std::vector<GLight *> GLight::lights;

void GLight::initLights()
{
  glGetIntegerv(GL_MAX_LIGHTS, &numLights);

  for (int i = 0; i < numLights; i++)
  {
    availableLights.push_back(GL_LIGHT0 + i);
  }
}

GLight::GLight(LIGHT_TYPE type)
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

GLight::~GLight()
{
  if (lightNum != 0)
  {
    availableLights.push_back(lightNum);
  }

  lights.erase(std::find(lights.begin(), lights.end(), this));
}

void GLight::setVisible(bool visible)
{
  this->visible = visible;

  if (visible)
    glEnable(lightNum);
  else
    glDisable(lightNum);
}

void GLight::setPosition(glm::vec4 position)
{
  this->position = position;
  glLightfv(lightNum, GL_POSITION, glm::value_ptr(position));
}

void GLight::setAmbient(glm::vec4 ambient) 
{ 
  this->ambient = ambient;
  glLightfv(lightNum, GL_AMBIENT, glm::value_ptr(ambient));
}

void GLight::setDiffuse(glm::vec4 diffuse) 
{ 
  this->diffuse = diffuse;
  glLightfv(lightNum, GL_DIFFUSE, glm::value_ptr(diffuse));
}

void GLight::setSpecular(glm::vec4 specular)
{ 
  this->specular = specular; 
  glLightfv(lightNum, GL_SPECULAR, glm::value_ptr(specular));
}

void GLight::setLightType(LIGHT_TYPE type)
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

void GLight::setSpotDirection(glm::vec4 spotDirection) 
{ 
  this->spotDirection = spotDirection; 
  glLightfv(lightNum, GL_SPOT_DIRECTION, glm::value_ptr(spotDirection));
}

void GLight::setCutoff(float cutoff) 
{ 
  this->cutoff = cutoff;
  glLightf(lightNum, GL_SPOT_CUTOFF, cutoff);
}

void GLight::setExponent(float exponent)
{ 
  this->exponent = exponent; 
  glLightf(lightNum, GL_SPOT_EXPONENT, exponent);
}

void GLight::setAttenuation(float constant, float linear, float quadratic)
{
  glLightfv(lightNum, GL_CONSTANT_ATTENUATION, &constant);
  glLightfv(lightNum, GL_LINEAR_ATTENUATION, &linear);
  glLightfv(lightNum, GL_QUADRATIC_ATTENUATION, &quadratic);
}

void GLight::updateLight()
{
  glLightfv(lightNum, GL_POSITION, glm::value_ptr(position));
  glLightfv(lightNum, GL_AMBIENT, glm::value_ptr(ambient));
  glLightfv(lightNum, GL_DIFFUSE, glm::value_ptr(diffuse));
  glLightfv(lightNum, GL_SPECULAR, glm::value_ptr(specular));
  glLightfv(lightNum, GL_SPOT_DIRECTION, glm::value_ptr(spotDirection));
  glLightf(lightNum, GL_SPOT_CUTOFF, cutoff);
  glLightf(lightNum, GL_SPOT_EXPONENT, exponent);
}

void GLight::drawLight()
{
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  glColor3f(1.0f, 1.0f, 0.0f);
  glVertex3f(position.x, position.y, position.z);
  glEnd();
}