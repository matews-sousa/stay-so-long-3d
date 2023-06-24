#pragma once

#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>

class Texture
{
public:
  GLuint texID;
  std::string name;

  static std::map<std::string, Texture*> textures;

  Texture(std::string fileName, std::string name);
  virtual ~Texture();

  void loadFromFile(std::string filename);
  void bind();
  void unbind();
  
  static void bindByName(std::string name);
};