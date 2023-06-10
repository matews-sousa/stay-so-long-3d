#include "Model.hpp"

Model::Model(std::string fileName, std::vector<Light *> lights, glm::mat4 modelMatrix)
{
  this->fileName = fileName;
  this->lights = lights;
  this->modelMatrix = modelMatrix;

  objectLoaded = false;

  displayList = 0;

  objectLoaded = loadObject(fileName);

  if (objectLoaded)
    createDisplayList();
  else
    std::cout << "Error loading object " << fileName << std::endl;
}

Model::~Model()
{
  glDeleteLists(displayList, 1);
}

void Model::draw()
{
  glCallList(displayList);
}

void Model::createDisplayList()
{
  if (objectLoaded)
  {
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE_AND_EXECUTE);
    for (auto face : faces)
    {
      drawFace(face);
    }
    glEndList();
  }
}

void Model::drawFace(Face &face)
{
  if (face.isQuad)
    glBegin(GL_POLYGON);
  else
    glBegin(GL_TRIANGLES);

  for (int v = 0; v < face.vertices.size(); v++)
  {
    glm::vec3 illum = Light::calculateIllumination(lights, face.vertices[v], face.normals[v], modelMatrix);
    glColor3f(illum.x, illum.y, illum.z);
    
    if (face.texCoords.size() > 0)
      glTexCoord2f(face.texCoords[v].x, face.texCoords[v].y);
    if (face.normals.size() > 0)
      glNormal3f(face.normals[v].x, face.normals[v].y, face.normals[v].z);
    if (face.vertices.size() > 0)
      glVertex3f(face.vertices[v].x, face.vertices[v].y, face.vertices[v].z);
  }

  glEnd();
}

bool Model::loadObject(std::string fileName)
{
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> texCoords;

  std::vector<int> indexVertices;
  std::vector<int> indexNormals;
  std::vector<int> indexTexCoords;

  std::ifstream file(fileName);

  if (!file.is_open())
  {
    std::cout << "Error opening file" << std::endl;
    return false;
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
      vertices.push_back(vertex);
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
      // Count the number of vertices in the face (3 or 4) to determine if it's a quad or a triangle
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
          indexVertices.push_back(tempInt);
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

  Face newFace;
  if (vertexCounter >= 4)
    newFace.isQuad = true;
    
  vertices.resize(indexVertices.size(), glm::vec3(0.0f));

  for (size_t i = 0; i < vertices.size(); i++)
  {
    newFace.vertices.push_back(vertices[indexVertices[i] - 1]);
    newFace.normals.push_back(normals[indexNormals[i] - 1]);
    newFace.texCoords.push_back(texCoords[indexTexCoords[i] - 1]);
  }

  faces.push_back(newFace);

  return true;
}