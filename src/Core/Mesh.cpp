#include "Mesh.hpp"
#include <vector>
#include <thread>

Mesh::Mesh(std::string fileName)
{
  modelMatrix = glm::mat4(1.0f);
  this->vertices = OBJLoader::loadFromFile(fileName);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh()
{
  glDeleteBuffers(1, &vbo);
}

void Mesh::updateColorBufferThread(int start, int end)
{
  for (int i = start; i < end; i++)
  {
    glm::vec3 illum = Light::calculateIllumination(Game::lights, vertices[i].position, vertices[i].normal, modelMatrix);
    vertices[i].color = illum;
  }
}

void Mesh::updateColorBuffer()
{
  int numThreads = std::thread::hardware_concurrency();
  int verticesPerThread = vertices.size() / numThreads;

  std::vector<std::thread> threads;
  for (int i = 0; i < numThreads; i++)
  {
    int start = i * verticesPerThread;
    int end = (i == numThreads - 1) ? vertices.size() : start + verticesPerThread;
    threads.emplace_back(&Mesh::updateColorBufferThread, this, start, end);
  }

  for (auto& thread : threads)
  {
    thread.join();
  }

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::render(glm::mat4 modelMatrix)
{
  this->modelMatrix = modelMatrix;
  updateColorBuffer();

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

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
