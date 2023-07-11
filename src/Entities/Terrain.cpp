#include "Terrain.hpp"

Terrain::Terrain(int gridX, int gridZ)
{
  size = 2000;
  tileSize = 200;
  vertexCount = 128;

  x = gridX * size;
  z = gridZ * size;
}

Terrain::~Terrain()
{
}

void Terrain::draw()
{
  Texture::bindByName("stone");
  glm::mat4 modelMatrix = glm::mat4(1.0f);

  if (false)
  {
    for (int i = -size; i < size; i += tileSize)
    {
      for (int j = -size; j < size; j += tileSize)
      {
        glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 1.0f, 1.0f); glTexCoord2f(0.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0, j);
        glColor3f(1.0f, 1.0f, 1.0f); glTexCoord2f(0.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0, j + tileSize);
        glColor3f(1.0f, 1.0f, 1.0f); glTexCoord2f(1.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0, j);
        glColor3f(1.0f, 1.0f, 1.0f); glTexCoord2f(1.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0, j + tileSize);
        glEnd();
      }
    }
  }
  else
  {
    for (int i = -size; i < size; i += tileSize)
    {
      for (int j = -size; j < size; j += tileSize)
      {
        glBegin(GL_TRIANGLE_STRIP);

        glm::vec3 illum = Light::calculateAllIllumination(glm::vec3(i, 0.0f, j), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(0.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0.0f, j);

        illum = Light::calculateAllIllumination(glm::vec3(i, 0.0f, j + tileSize), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(0.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0.0f, j + tileSize);

        illum = Light::calculateAllIllumination(glm::vec3(i + tileSize, 0.0f, j), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(1.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0.0f, j);
        
        illum = Light::calculateAllIllumination(glm::vec3(i + tileSize, 0.0f, j + tileSize), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(1.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0.0f, j + tileSize);
        
        glEnd();
      }
    }
  }

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(size / tileSize, size / tileSize); glVertex3f(size, 0, size);
  glTexCoord2f(0.0f, size / tileSize); glVertex3f(size, -size, size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size, -size);
  glTexCoord2f(size / tileSize, 0.0f); glVertex3f(size, 0, -size);
  glEnd();

  glBegin(GL_QUADS);
  glTexCoord2f(size / tileSize, size / tileSize); glVertex3f(size, 0, -size);
  glTexCoord2f(0.0f, size / tileSize); glVertex3f(size, -size, -size);
  glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size, -size);
  glTexCoord2f(size / tileSize, 0.0f); glVertex3f(-size, 0, -size);
  glEnd();
}