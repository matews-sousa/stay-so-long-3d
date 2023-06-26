#include "Terrain.hpp"

Terrain::Terrain(int gridX, int gridZ)
{
  size = 2000;
  tileSize = 200;
  vertexCount = 128;

  x = gridX * size;
  z = gridZ * size;

  generateTerrain();
}

Terrain::~Terrain()
{
}

void Terrain::draw()
{
  Texture::bindByName("rock");
  glm::mat4 modelMatrix = glm::mat4(1.0f);

  if (Game::GLightsEnabled)
  {
    tileSize = 50;
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
    tileSize = 200;
    for (int i = -size; i < size; i += tileSize)
    {
      for (int j = -size; j < size; j += tileSize)
      {
        glBegin(GL_TRIANGLE_STRIP);

        glm::vec3 illum = Light::calculateIllumination(Game::lights, glm::vec3(i, 0.0f, j), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(0.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0, j);

        illum = Light::calculateIllumination(Game::lights, glm::vec3(i, 0.0f, j + tileSize), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(0.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0, j + tileSize);

        illum = Light::calculateIllumination(Game::lights, glm::vec3(i + tileSize, 0.0f, j), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(1.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0, j);
        
        illum = Light::calculateIllumination(Game::lights, glm::vec3(i + tileSize, 0.0f, j + tileSize), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
        glColor3fv(glm::value_ptr(illum)); glTexCoord2f(1.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0, j + tileSize);
        
        glEnd();
      }
    }
  }
}

void Terrain::generateTerrain()
{
  displayList = glGenLists(1);
  glNewList(displayList, GL_COMPILE);
  Texture::bindByName("wall");
  
  for (int i = -size; i < size; i += tileSize)
  {
    for (int j = -size; j < size; j += tileSize)
    {
      glBegin(GL_TRIANGLE_STRIP);
      glTexCoord2f(0.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0, j);
      glTexCoord2f(1.0f, 0.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0, j);
      glTexCoord2f(0.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i, 0, j + tileSize);
      glTexCoord2f(1.0f, 1.0f); glNormal3f(0.0f, 1.0f, 0.0f); glVertex3f(i + tileSize, 0, j + tileSize);
      glEnd();
    }
  }

  glEndList();
}