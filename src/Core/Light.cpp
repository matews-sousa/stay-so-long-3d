#include "Light.hpp"

Light::Light(glm::vec3 lightPosition, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
  this->lightPosition = lightPosition;
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
}

Light::Light(glm::vec3 lightPosition, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, LightType type)
{
  this->lightPosition = lightPosition;
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
  this->type = type;
}

Light::~Light()
{
}

glm::vec3 Light::calculateIllumination(const glm::vec3 &vertexPosition, const glm::vec3 &normal, const glm::mat4 &modelMatrix)
{
  if (!isOn)
    return glm::vec3(0.0f);

  if (type == DIRECTIONAL_LIGHT)
  {
    return diffuse;
  }

  if (!Utils::isInFrustum(projectionMatrix * viewMatrix * modelMatrix, vertexPosition))
    return glm::vec3(0.0f);

  glm::vec3 transformedVertexNormal = glm::vec3(glm::transpose(glm::inverse(viewMatrix * modelMatrix)) * glm::vec4(normal, 0.0f)); // Transform normal to world space
  transformedVertexNormal = glm::normalize(transformedVertexNormal); // Normalize normal
  glm::vec3 transformedVertexPosition = glm::vec3(viewMatrix * modelMatrix * glm::vec4(vertexPosition, 1.0f)); // Transform position to world space

  // Calculate light direction
  glm::vec3 lightPositionView = glm::vec3(viewMatrix * glm::vec4(this->lightPosition, 1.0f));
  glm::vec3 lightDirection = glm::normalize(lightPositionView - transformedVertexPosition);

  float intensity = 1.0f;

  if (type == SPOT_LIGHT)
  {
    float outerCone = 0.90f;
    float innerCone = 0.95f;

    float angle = glm::dot(glm::vec3(0.0f, -1.0f, 0.0f), -lightDirection);
    intensity = glm::clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);
  }

  // diffuse
  float nDot1 = glm::dot(transformedVertexNormal, lightDirection);
  float brightness = glm::max(nDot1, 0.0f);
  glm::vec3 diff = this->diffuse * brightness * intensity;
  
  // specular
  glm::vec3 toCameraVector = glm::vec3(glm::inverse(viewMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) - transformedVertexPosition;
  toCameraVector = glm::normalize(toCameraVector);
  glm::vec3 reflectionVector = glm::reflect(-lightDirection, transformedVertexNormal);
  float specularFactor = glm::max(glm::dot(toCameraVector, reflectionVector), 0.0f);
  specularFactor = glm::pow(specularFactor, 32.0f);
  glm::vec3 spec = this->specular * specularFactor * intensity;

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
  glVertex3f(lightPosition.x, lightPosition.y, lightPosition.z);
  glEnd();
}