#include "CubeCollider.hpp"

CubeCollider::CubeCollider(glm::vec3 position, glm::vec3 size) : Collider(position, size)
{
  this->minBB = position - size / 2.0f;
  this->maxBB = position + size / 2.0f;

  mesh = Game::models["cube"];
}

CubeCollider::~CubeCollider()
{
}

void CubeCollider::debug()
{
  if (!Game::debugMode)
    return;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(1.0f, 0.0f, 0.0f);
  mesh->setVertexColors(glm::vec3(1.0f, 0.0f, 0.0f));
  glPushMatrix();
  glTranslatef(position.x, position.y, position.z);
  glScalef(size.x * 1.1f, size.y * 1.1f, size.z * 1.1f);
  mesh->render(glm::mat4(1.0f));
  glPopMatrix();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // draw line between minBB and maxBB
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(position.x, position.y, position.z);
  glVertex3f(maxBB.x, maxBB.y, maxBB.z);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(position.x, position.y, position.z);
  glVertex3f(minBB.x, minBB.y, minBB.z);
  glEnd();
  
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(minBB.x, minBB.y, minBB.z);
  glVertex3f(maxBB.x, maxBB.y, maxBB.z);
  glEnd();
}

bool CubeCollider::testCollision(Collider &other)
{
  return other.testCollision(*this);
}

bool CubeCollider::testCollision(CubeCollider &other)
{
  return Utils::CubeCubeCollision(this, &other);
}

bool CubeCollider::testCollision(SphereCollider &other)
{
  return Utils::SphereCubeCollision(&other, this);
}

void CubeCollider::setPosition(glm::vec3 position)
{
  this->position = position;
  this->minBB = position - size / 2.0f;
  this->maxBB = position + size / 2.0f;
}