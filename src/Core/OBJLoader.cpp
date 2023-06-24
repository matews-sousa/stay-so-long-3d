#include "OBJLoader.hpp"

std::vector<Vertex> OBJLoader::loadFromFile(std::string fileName)
{
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  std::vector<int> indexPositions;
  std::vector<int> indexNormals;
  std::vector<int> indexTexCoords;

  std::vector<Vertex> vertices;

  std::ifstream file(fileName);

  if (!file.is_open())
  {
    std::cout << "Error opening file" << std::endl;
    return vertices;
  }

  std::string line = "";
  std::string prefix;
  int vertexCounter = 0;
  
  while (std::getline(file, line))
  {
    std::stringstream ss(line);
    ss >> prefix;

    if (prefix == "v")
    {
      glm::vec3 vertex;
      ss >> vertex.x >> vertex.y >> vertex.z;
      positions.push_back(vertex);
    }
    else if (prefix == "vt")
    {
      glm::vec2 texCoord;
      ss >> texCoord.x >> texCoord.y;
      texCoords.push_back(texCoord);
    }
    else if (prefix == "vn")
    {
      glm::vec3 normal;
      ss >> normal.x >> normal.y >> normal.z;
      normals.push_back(normal);
    }
    else if (prefix == "f")
    {
      // Count the number of positions in the face (3 or 4) to determine if it's a quad or a triangle
      std::stringstream ssVertexCounter(line);
      vertexCounter = 0;
      while (std::getline(ssVertexCounter, line, ' '))
        vertexCounter++;
      vertexCounter -= 1; // Remove the "f" prefix from the count

      int tempInt = 0;
      int counter = 0;
      while (ss >> tempInt)
      {
        if (counter == 0)
          indexPositions.push_back(tempInt);
        else if (counter == 1)
          indexTexCoords.push_back(tempInt);
        else if (counter == 2)
          indexNormals.push_back(tempInt);

        if (ss.peek() == '/')
        {
          ++counter;
          ss.ignore(1, '/');
        }
        else if (ss.peek() == ' ')
        {
          ++counter;
          ss.ignore(1, ' ');
        }

        if (counter > 2)
        {
          counter = 0;
        }
      }
    }
  }

  vertices.resize(indexPositions.size(), Vertex());

  for (int i = 0; i < indexPositions.size(); ++i)
  {
    vertices[i].position = positions[indexPositions[i] - 1];
    vertices[i].texCoords = texCoords[indexTexCoords[i] - 1];
    vertices[i].normal = normals[indexNormals[i] - 1];
    vertices[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
  }

  std::cout << "Loaded " << fileName << std::endl;

  return vertices;
}