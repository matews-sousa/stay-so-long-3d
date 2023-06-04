#include "primitives.hpp"

void rect(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, sf::Color c) {
  glColor3f(c.r, c.g, c.b);
  glBegin(GL_QUADS);
    glVertex3fv(glm::value_ptr(p1));
    glVertex3fv(glm::value_ptr(p2));
    glVertex3fv(glm::value_ptr(p3));
    glVertex3fv(glm::value_ptr(p4));
  glEnd();
}

void drawCube(float s) {
  float d = s / 2.0;

  glm::vec3 v1(-d,  d,  d );
  glm::vec3 v2(-d, -d,  d );
  glm::vec3 v3( d, -d,  d );
  glm::vec3 v4( d,  d,  d );

  glm::vec3 v5( d,  d, -d );
  glm::vec3 v6( d, -d, -d );
  glm::vec3 v7(-d, -d, -d );
  glm::vec3 v8(-d,  d, -d );

  rect(v1, v2, v3, v4, sf::Color::Red); // front
  rect(v4, v3, v6, v5, sf::Color::Green); // right
  rect(v5, v8, v7, v6, sf::Color::Blue); // back
  rect(v1, v8, v7, v2, sf::Color::Yellow); // left
  rect(v1, v4, v5, v8, sf::Color::Magenta); // top
  rect(v2, v7, v6, v3, sf::Color::Cyan); // bottom
}