#include "Texture.hpp"
#include <iostream>

Texture::Texture(std::string fileName, std::string name)
{
  this->name = name;

  textures[name] = this;

  loadFromFile(fileName);
}

Texture::~Texture()
{
  textures.erase(name);

  glDeleteTextures(1, &texID);
}

void Texture::loadFromFile(std::string filename)
{
  sf::Image image;
  if (!image.loadFromFile(filename))
  {
    std::cout << "Failed to load image: " << filename << std::endl;
    return;
  }
  image.flipVertically();

  glGenTextures(1, &texID);

  glBindTexture(GL_TEXTURE_2D, texID);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bindByName(std::string name)
{  
  textures[name]->bind();
}

void Texture::bind()
{
  glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::unbind()
{
  glBindTexture(GL_TEXTURE_2D, 0);
}

std::map<std::string, Texture*> Texture::textures;