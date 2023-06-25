#include "Mesh.hpp"

Mesh::Mesh(std::string fileName)
{
  this->vertices = OBJLoader::loadFromFile(fileName);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
  glDeleteBuffers(1, &vbo);
}

void Mesh::updateColorBuffer()
{
  for (int i = 0; i < vertices.size(); i++)
  {
    vertices[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::render()
{
  updateColorBuffer();

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
  glNormalPointer(GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
  glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));
  glColorPointer(3, GL_FLOAT, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

  glDrawArrays(GL_TRIANGLES, 0, vertices.size());

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}