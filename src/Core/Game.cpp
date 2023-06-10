#include "Game.hpp"
#include "Input.hpp"
#include <iostream>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../primitives.hpp"
#include "Texture.hpp"

sf::RenderWindow *Game::window;
Camera *Game::camera;
float Game::deltaTime;
std::map<std::string, Model *> Game::models;
Light *Game::light;

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

  player = new Player(glm::vec3(0.0f, 100.0f, 0.0f), glm::vec3(15.0f, 15.0f, 15.0f));

  light = new Light(glm::vec3(500.0f, 500.0f, 500.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
  
  projectionMatrix = glm::mat4(1.0f);
  viewMatrix = glm::mat4(1.0f);

  init();
  initTextures();
  initObjModels();

}

Game::~Game()
{
  delete window;
  delete player;
  delete camera;
  models.clear();
}

void Game::initTextures()
{
  Texture *texture = new Texture("../src/Assets/Textures/container.jpg", "container");
  texture = new Texture("../src/Assets/Textures/wall.jpg", "wall");
  texture = new Texture("../src/Assets/Textures/awesomeface.png", "awesomeface");
  texture = new Texture("../src/Assets/Textures/Mecha01.png", "mecha");
  texture = new Texture("../src/Assets/Textures/TallBuilding01.png", "building");
  texture = new Texture("../src/Assets/Textures/spaceship6_normal_tangent_bevel.png", "spaceship");
}

void Game::initObjModels()
{
  models["cube"] = new Model("../src/Assets/Models/cube.obj", *light);
  models["mecha"] = new Model("../src/Assets/Models/mecha.obj", *light);
  models["spaceship"] = new Model("../src/Assets/Models/Spaceship6.obj", *light);
  models["building"] = new Model("../src/Assets/Models/building.obj", *light);
}

void Game::init()
{
  glViewport(0, 0, window->getSize().x, window->getSize().y);

  float halfWidth = window->getSize().x / 2.0f;
  float halfHeight = window->getSize().y / 2.0f;

  //projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 2000.0f);
  projectionMatrix = glm::perspective(glm::radians(45.0f), (float)window->getSize().x / (float)window->getSize().y, 0.1f, 2500.0f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(projectionMatrix));

  camera = new Camera(glm::vec3(500.0f, 500.0f, -500.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  viewMatrix = camera->getViewMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(viewMatrix));

  glEnable(GL_DEPTH_TEST);

  glEnable(GL_TEXTURE_2D);

/*   glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  GLfloat lightPosition[] = { 700.0f, 500.0f, -700.0f, 1.0f };
  GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  GLfloat lightDiffuse[] = { 2.0f, 2.0f, 2.0f, 1.0f };
  GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); */
}

void Game::run()
{
  while (window->isOpen())
  {
    update();
    render();
  }
}

float lightAngle = 0.0f;
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

  // make the light position rotate around the origin
  lightAngle += 0.1f;
  GLfloat lightPosition[] = { 500.0f * cosf(lightAngle), 500.0f, 500.0f * sinf(lightAngle), 1.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

  light->setPosition(glm::vec3(lightPosition[0], lightPosition[1], lightPosition[2]));

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

  // terrain generation
  Texture::bindByName("wall");
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  //modelMatrix = glm::translate(modelMatrix, glm::vec3(-1000.0f, 0.0f, -1000.0f));
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(modelMatrix));
  for (int x = -2000; x < 2000; x += 100)
  {
    for (int z = -2000; z < 2000; z += 100)
    {
      glBegin(GL_TRIANGLE_STRIP);

      glm::vec3 illum1 = light->calculateIllumination(glm::vec3(x, 0.0f, z), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
      glColor3fv(glm::value_ptr(illum1));
      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x, 0.0f, z);

      glm::vec3 illum2 = light->calculateIllumination(glm::vec3(x, 0.0f, z + 100), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
      glColor3fv(glm::value_ptr(illum2));
      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x, 0.0f, z + 100);

      glm::vec3 illum3 = light->calculateIllumination(glm::vec3(x + 100, 0.0f, z), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
      glColor3fv(glm::value_ptr(illum3));
      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x + 100, 0.0f, z);

      glm::vec3 illum4 = light->calculateIllumination(glm::vec3(x + 100, 0.0f, z + 100), glm::vec3(0.0f, 1.0f, 0.0f), modelMatrix);
      glColor3fv(glm::value_ptr(illum4));
      glNormal3f(0.0f, 1.0f, 0.0f);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x + 100, 0.0f, z + 100);

      glEnd();
    }
  }
  glPopMatrix();

  glColor3f(1.0f, 1.0f, 1.0f);

  Texture::bindByName("mecha");
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(modelMatrix));
  models["mecha"]->setModelMatrix(modelMatrix);
  models["mecha"]->draw();
  glPopMatrix();

  Texture::bindByName("building");
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(150.0f, 0.0f, 150.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(25.0f, 25.0f, 25.0f));
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(modelMatrix));
  models["building"]->setModelMatrix(modelMatrix);
  models["building"]->draw();
  glPopMatrix();

  Texture::bindByName("spaceship");
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-150.0f, 25.0f, -150.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(25.0f, 25.0f, 25.0f));
  glPushMatrix();
  glMultMatrixf(glm::value_ptr(modelMatrix));
  models["spaceship"]->setModelMatrix(modelMatrix);
  models["spaceship"]->draw();
  glPopMatrix();

  player->draw();

  light->draw();

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
