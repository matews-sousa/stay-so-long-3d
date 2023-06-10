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
  glm::vec3 transformedNormal = glm::vec3(modelMatrix * glm::vec4(normal, 0.0f)); // Transform normal to world space
  transformedNormal = glm::normalize(transformedNormal); // Normalize normal
  glm::vec3 transformedPosition = glm::vec3(modelMatrix * glm::vec4(vertexPosition, 1.0f)); // Transform position to world space

  // Calculate light direction
  glm::vec3 lightDirection = glm::normalize(position - transformedPosition);

  float ambientIntensity = 0.1f; // Default ambient intensity

  // Calculate diffuse intensity
  float diffuseIntensity = glm::max(glm::dot(transformedNormal, lightDirection), 0.0f);

  // Calculate specular intensity
  glm::vec3 viewDirection = glm::normalize(-transformedPosition);
  glm::vec3 reflectDirection = glm::reflect(-lightDirection, transformedNormal);
  float specularIntensity = glm::pow(glm::max(glm::dot(viewDirection, reflectDirection), 0.0f), 32.0f);

  // Calculate final illumination using Phong lighting model
  glm::vec3 illumination = ambient * ambientIntensity + diffuse * diffuseIntensity + specular * specularIntensity;

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