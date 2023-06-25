#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>
#include <GL/glew.h>
#include "../Vertex.hpp"

namespace OBJLoader
{
  std::vector<Vertex> loadFromFile(std::string fileName);
}