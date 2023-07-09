#include "Spaceship.hpp"

Spaceship::Spaceship(glm::vec3 position, glm::vec3 scale) : GameObject(position, scale)
{
  setRotation(glm::vec3(0.0f, 90.0f, 0.0f));

  mesh = new Mesh("../src/Assets/Models/Runner.obj");

  collider = new SphereCollider(position, scale.x);
}

Spaceship::~Spaceship()
{
  delete mesh;
  delete collider;
}

void Spaceship::update()
{
  collider->setPosition(position);
}

void Spaceship::draw()
{
  Texture::bindByName("runner");
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(getModelMatrix()));
  mesh->render(getModelMatrix());
  glPopMatrix();

  collider->debug();
}