#include "SphereCollider.hpp"

SphereCollider::SphereCollider(glm::vec3 position, float radius) : Collider(position, glm::vec3(radius * 2))
{
  this->radius = radius;

  mesh = Game::models["sphere"];
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::debug()
{
  if (!Game::debugMode)
    return;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(1.0f, 0.0f, 0.0f);
  mesh->setVertexColors(glm::vec3(1.0f, 0.0f, 0.0f));
  glPushMatrix();
  glTranslatef(position.x, position.y, position.z);
  glScalef(radius * 2 * 1.1f, radius * 2 * 1.1f, radius * 2 * 1.1f);
  mesh->render(glm::mat4(1.0f));
  glPopMatrix();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool SphereCollider::testCollision(Collider &other)
{
  return other.testCollision(*this);
}

bool SphereCollider::testCollision(SphereCollider &other)
{
  return Utils::SphereSphereCollision(this, &other);
}

bool SphereCollider::testCollision(CubeCollider &other)
{
  return Utils::SphereCubeCollision(this, &other);
}