#include "Terrain.hpp"

Terrain::Terrain(int gridX, int gridZ)
{
  size = 800;
  tileSize = 80;
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
  glCallList(displayList);
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