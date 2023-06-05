#include "Game.hpp"
#include "Input.hpp"
#include <iostream>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../primitives.hpp"
#include "Texture.hpp"

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

  player = new Player(glm::vec3(0.0f, 75.0f, 0.0f), glm::vec3(30.0f, 70.0f, 30.0f));

  init();
}

Game::~Game()
{
  delete window;
  delete player;
  delete camera;
}

void Game::loadTextures()
{
  Texture *texture = new Texture("../src/Assets/Textures/container.jpg", "container");
  texture = new Texture("../src/Assets/Textures/wall.jpg", "wall");
  texture = new Texture("../src/Assets/Textures/awesomeface.png", "awesomeface");
}

void Game::init()
{
  glViewport(0, 0, window->getSize().x, window->getSize().y);

  float halfWidth = window->getSize().x / 2.0f;
  float halfHeight = window->getSize().y / 2.0f;

  //glm::mat4 projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 2000.0f);
  glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)window->getSize().x / (float)window->getSize().y, 0.1f, 2000.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(projectionMatrix));

  camera = new Camera(glm::vec3(500.0f, 500.0f, -500.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 viewMatrix = camera->getViewMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(viewMatrix));

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_TEXTURE_2D);

  loadTextures();
}

void Game::run()
{
  while (window->isOpen())
  {
    update();
    render();
  }
}

void Game::update()
{
  while (window->pollEvent(event))
  {
    processEvents();
  }

  glm::mat4 viewMatrix = camera->getViewMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(viewMatrix));

  player->update();
  deltaTime = clock.restart().asSeconds();
}

void Game::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw axis
  glBegin(GL_LINES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-1000.0f, 0.0f, 0.0f);
  glVertex3f(1000.0f, 0.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, -1000.0f, 0.0f);
  glVertex3f(0.0f, 1000.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.0f, -1000.0f);
  glVertex3f(0.0f, 0.0f, 1000.0f);
  glEnd();

  Texture::bindByName("wall");
  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.0f);
  glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
  glScalef(500.0f, 50.0f, 500.0f);
  drawCube(1.0f);
  glPopMatrix();

  Texture::bindByName("awesomeface");
  glPushMatrix();
  glTranslatef(50.0f, 50.0f, 50.0f);
  glScalef(50.0f, 50.0f, 50.0f);
  drawCube(1.0f);
  glPopMatrix();

  Texture::bindByName("container");
  player->draw();

  window->display();
}

void Game::processEvents()
{
  if (event.type == sf::Event::Closed)
    window->close();

  // handle keyboard input
  if (event.type == sf::Event::KeyPressed)
  {
    Input::setKeyPressed(event.key.code, true);
    if (event.key.code == sf::Keyboard::Q)
      window->close();
  }
  if (event.type == sf::Event::KeyReleased)
    Input::setKeyPressed(event.key.code, false);

  // handle mouse input
  if (event.type == sf::Event::MouseButtonPressed)
    Input::setMouseButtonDown(event.mouseButton.button, true);
  if (event.type == sf::Event::MouseButtonReleased)
    Input::setMouseButtonDown(event.mouseButton.button, false);

  // handle mouse movement
  if (event.type == sf::Event::MouseMoved)
    Input::setMousePos(glm::vec2(event.mouseMove.x, event.mouseMove.y));
}

sf::RenderWindow *Game::window;
Camera *Game::camera;
float Game::deltaTime;