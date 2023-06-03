#include "Game.hpp"
#include <iostream>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef float color[3];

color white = { 1.0f, 1.0f, 1.0f };
color red = { 1.0f, 0.0f, 0.0f };
color green = { 0.0f, 1.0f, 0.0f };
color blue = { 0.0f, 0.0f, 1.0f };
color yellow = { 1.0f, 1.0f, 0.0f };
color magenta = { 1.0f, 0.0f, 1.0f };
color cyan = { 0.0f, 1.0f, 1.0f };

void rect(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec3 p4, color c) {
  glColor3fv(c);
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

  rect(v1, v2, v3, v4, red); // front
  rect(v4, v3, v6, v5, green); // right
  rect(v5, v8, v7, v6, blue); // back
  rect(v1, v8, v7, v2, yellow); // left
  rect(v1, v4, v5, v8, magenta); // top
  rect(v2, v7, v6, v3, cyan); // bottom
}

Game::Game()
{
  sf::ContextSettings settings;
  settings.depthBits = 24;
  settings.stencilBits = 8;
  settings.antialiasingLevel = 2;
  
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

  window = new sf::RenderWindow(sf::VideoMode(1280, 920), "SFML Game", sf::Style::Close, settings);
  window->setFramerateLimit(60);
  window->setPosition(sf::Vector2i((desktop.width - window->getSize().x) / 2, (desktop.height - window->getSize().y) / 2));

  init();
}

Game::~Game()
{
  delete window;
}

void Game::init()
{
  glViewport(0, 0, window->getSize().x, window->getSize().y);

  camera = new Camera(glm::vec3(100.0f, 100.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 viewMatrix = camera->getViewMatrix();
  glm::mat4 projectionMatrix = glm::perspective(45.0f, (float)window->getSize().x / (float)window->getSize().y, 0.1f, 500.0f);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(projectionMatrix));

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(viewMatrix));

  glEnable(GL_DEPTH_TEST);
}

void Game::run()
{
  while (window->isOpen())
  {
    processEvents();
    update();
    render();
  }
}

void Game::update()
{
  deltaTime = clock.restart().asSeconds();
}

void Game::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.0f);
  glScalef(10.0f, 10.0f, 10.0f);
  drawCube(1.0f);
  glPopMatrix();

  window->display();
}

void Game::processEvents()
{
  sf::Event event;

  while (window->pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      window->close();
    }
  }
}

sf::RenderWindow *Game::window;
Camera *Game::camera;
float Game::deltaTime;