#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Graphics.hpp>

void rect(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, sf::Color c);

void drawCube(float s);