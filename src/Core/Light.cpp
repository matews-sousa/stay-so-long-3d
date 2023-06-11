#include "Light.hpp"

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
  this->position = position;
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
}

Light::~Light()
{
}

glm::vec3 Light::calculateIllumination(const glm::vec3 &vertexPosition, const glm::vec3 &normal, const glm::mat4 &modelMatrix)
{
  if (!isOn)
    return glm::vec3(0.0f);

  glm::vec3 transformedNormal = glm::vec3(modelMatrix * glm::vec4(normal, 0.0f)); // Transform normal to world space
  transformedNormal = glm::normalize(transformedNormal); // Normalize normal
  glm::vec3 transformedPosition = glm::vec3(modelMatrix * glm::vec4(vertexPosition, 1.0f)); // Transform position to world space

  // Calculate light direction
  glm::vec3 lightDirection = glm::normalize(this->position - transformedPosition);

  // diffuse
  float nDot1 = glm::dot(transformedNormal, lightDirection);
  float brightness = glm::max(nDot1, 0.0f);
  glm::vec3 diff = this->diffuse * brightness;
  
  // specular
  glm::vec3 toCameraVector = glm::vec3(glm::inverse(viewMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) - transformedPosition;
  toCameraVector = glm::normalize(toCameraVector);
  glm::vec3 reflectionVector = glm::reflect(-lightDirection, transformedNormal);
  float specularFactor = glm::max(glm::dot(toCameraVector, reflectionVector), 0.0f);
  specularFactor = glm::pow(specularFactor, 32.0f);
  glm::vec3 spec = this->specular * specularFactor;

  return ambient + diff + spec;
}

glm::vec3 Light::calculateIllumination(std::vector<Light *> lights, const glm::vec3 &position, const glm::vec3 &normal, const glm::mat4 &modelMatrix)
{
  glm::vec3 illumination = glm::vec3(0.0f);
  for (auto &light : lights)
  {
    illumination += light->calculateIllumination(position, normal, modelMatrix);
  }
  return illumination;
}

void Light::draw()
{
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(position.x, position.y, position.z);
  glEnd();
}