#include "Game.hpp"
#include <iostream>
#include <GL/gl.h>

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

  glViewport(0, 0, window->getSize().x, window->getSize().y);
}

Game::~Game()
{
  delete window;
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

  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-0.5f, -0.5f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.5f, -0.5f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 0.5f, 0.0f);
  glEnd();

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
float Game::deltaTime;