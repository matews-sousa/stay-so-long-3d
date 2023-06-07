#include "Game.hpp"
#include "Input.hpp"
#include <iostream>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../primitives.hpp"
#include "Texture.hpp"
#include "Model.hpp"

float angle = 0.0f;

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

  player = new Player(glm::vec3(0.0f, 35.0f, 0.0f), glm::vec3(30.0f, 70.0f, 30.0f));

  init();
  initTextures();
  initObjModels();
}

Game::~Game()
{
  delete window;
  delete player;
  delete camera;
}

void Game::initTextures()
{
  Texture *texture = new Texture("../src/Assets/Textures/container.jpg", "container");
  texture = new Texture("../src/Assets/Textures/wall.jpg", "wall");
  texture = new Texture("../src/Assets/Textures/awesomeface.png", "awesomeface");
  texture = new Texture("../src/Assets/Textures/Mecha01.png", "mecha");
  texture = new Texture("../src/Assets/Textures/TallBuilding01.png", "building");
  texture = new Texture("../src/Assets/Textures/AncientTreasure.png", "ancient_treasure");
}

void Game::initObjModels()
{
  models["mecha"] = new Model("../src/Assets/Models/mecha.obj");
  models["cube"] = new Model("../src/Assets/Models/cube.obj");
  models["building"] = new Model("../src/Assets/Models/building.obj");
  models["ancient_treasure"] = new Model("../src/Assets/Models/AncientTreasure.obj");
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

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
  GLfloat lightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
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

  glColor3f(1.0f, 1.0f, 1.0f);

  Texture::bindByName("wall");
  glPushMatrix();
  glTranslatef(0.0f, -100.0f, 0.0f);
  glScalef(200.0f, 200.0f, 200.0f);
  glCallList(models["cube"]->getDisplayList());
  glPopMatrix();

  Texture::bindByName("container");
  player->draw();

  angle += 1.0f;

  glColor3f(1.0f, 1.0f, 1.0f);
  Texture::bindByName("mecha");
  glPushMatrix();
  glTranslatef(0.0f, 25.0f, 0.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glScalef(50.0f, 50.0f, 50.0f);
  glCallList(models["mecha"]->getDisplayList());
  glPopMatrix();

  Texture::bindByName("building");
  glPushMatrix();
  glTranslatef(100.0f, 25.0f, 100.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glScalef(25.0f, 25.0f, 25.0f);
  glCallList(models["building"]->getDisplayList());
  glPopMatrix();

  Texture::bindByName("ancient_treasure");
  glPushMatrix();
  glTranslatef(200.0f, 25.0f, 200.0f);
  glRotatef(angle, 0.0f, 1.0f, 0.0f);
  glScalef(25.0f, 25.0f, 25.0f);
  glCallList(models["ancient_treasure"]->getDisplayList());
  glPopMatrix();

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