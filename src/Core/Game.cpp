#include "Game.hpp"

sf::RenderWindow *Game::window;
Camera *Game::camera;
MousePicker *Game::picker;
glm::mat4 Game::projectionMatrix;
glm::mat4 Game::viewMatrix;
float Game::deltaTime;
Terrain *Game::terrain;
std::map<std::string, Mesh *> Game::models;
std::map<std::string, sf::Text> Game::uiTexts;
bool Game::debugMode = false;
World *Game::world;
bool Game::paused = false;

void Game::pause()
{
  paused = true;
}

void Game::resume()
{
  paused = false;
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
  window->setActive(true);

  GLenum err = glewInit();
  if (GLEW_OK != err)
  {
    std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    exit(1);
  }

  backgroundTexture = new sf::Texture();
  if (!backgroundTexture->loadFromFile("../src/Assets/Textures/Purple_01.png"))
  {
    std::cout << "Failed to load background texture" << std::endl;
  }
  backgroundSprite = new sf::Sprite(*backgroundTexture);
  float scaleX = (float)window->getSize().x / (float)backgroundTexture->getSize().x;
  float scaleY = (float)window->getSize().y / (float)backgroundTexture->getSize().y;
  backgroundSprite->setScale(scaleX, scaleY);

  font = new sf::Font();
  if (!font->loadFromFile("../src/Assets/Fonts/roboto.ttf"))
  {
    std::cout << "Failed to load font" << std::endl;
  }

  initUiTexts();

  init();
  initLights();
  initTextures();
  initObjModels();

  world = new World();

  terrain = new Terrain(0, 0);

  picker = new MousePicker(projectionMatrix, viewMatrix, *window, *terrain);
}

Game::~Game()
{
  delete window;
  delete world;
  delete camera;
  delete terrain;
  delete picker;
  delete backgroundTexture;
  delete backgroundSprite;
  models.clear();
}

void Game::initUiTexts()
{
  auto addText = [](std::string name)
  {
    uiTexts.insert(std::pair<std::string, sf::Text>(name, sf::Text()));
  };

  addText("fps");
  addText("waveTimer");
  addText("score");
  addText("level");

  for (auto &text : uiTexts)
  {
    text.second.setFont(*font);
    text.second.setCharacterSize(24);
    text.second.setFillColor(sf::Color::White);
  }

  uiTexts["fps"].setPosition(0.0f, 0.0f);
  uiTexts["waveTimer"].setPosition(0.0f, 30.0f);
  uiTexts["score"].setPosition(0.0f, 60.0f);
  uiTexts["level"].setPosition(0.0f, 90.0f);
}

void Game::initTextures()
{
  Texture *texture = new Texture("../src/Assets/Textures/container.jpg", "container");
  texture = new Texture("../src/Assets/Textures/stone.jpg", "stone");
  texture = new Texture("../src/Assets/Textures/stone2.png", "stone2");
  texture = new Texture("../src/Assets/Textures/stone3.png", "stone3");
  texture = new Texture("../src/Assets/Textures/rock.jpg", "rock");
  texture = new Texture("../src/Assets/Textures/wall.jpg", "wall");
  texture = new Texture("../src/Assets/Textures/awesomeface.png", "awesomeface");
  texture = new Texture("../src/Assets/Textures/Mecha01.png", "mecha");
  texture = new Texture("../src/Assets/Textures/TallBuilding01.png", "building");
  texture = new Texture("../src/Assets/Textures/MicroRecon.png", "micro_recon");
  texture = new Texture("../src/Assets/Textures/InterstellarRunner.png", "runner");
  texture = new Texture("../src/Assets/Textures/Transtellar.png", "stellar");
  texture = new Texture("../src/Assets/Textures/second color.png", "giant");
}

void Game::initObjModels()
{
  models["cube"] = new Mesh("../src/Assets/Models/cube.obj");
  models["sphere"] = new Mesh("../src/Assets/Models/sphere.obj");
  models["mecha"] = new Mesh("../src/Assets/Models/mecha.obj");
  models["giant"] = new Mesh("../src/Assets/Models/giant.obj");
  models["building"] = new Mesh("../src/Assets/Models/building.obj");
  models["micro_recon"] = new Mesh("../src/Assets/Models/MicroRecon.obj");
  models["runner"] = new Mesh("../src/Assets/Models/InterstellarRunner.obj");
  models["stellar"] = new Mesh("../src/Assets/Models/Transtellar.obj");
}

void Game::initLights()
{
  new Light(glm::vec3(200.0f, 500.0f, 200.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), LightType::SPOT_LIGHT);
  new Light(glm::vec3(0.0f), glm::vec3(0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
  
  for (auto &light : Light::lights)
    light->setViewMatrix(viewMatrix);
}

void Game::init()
{
  glViewport(0, 0, window->getSize().x, window->getSize().y);

  float halfWidth = window->getSize().x / 2.0f;
  float halfHeight = window->getSize().y / 2.0f;

  projectionMatrix = glm::perspective(glm::radians(45.0f), (float)window->getSize().x / (float)window->getSize().y, 0.1f, 3000.0f);
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

  std::ostringstream out;
  out.precision(2);
  out << std::fixed << 1.0f / deltaTime;
  uiTexts["fps"].setString("FPS: " + out.str());

  viewMatrix = camera->getViewMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(viewMatrix));

  picker->update(projectionMatrix, viewMatrix);

  world->update();

  lightAngle += 0.1f;
  for (auto &light : Light::lights)
  {
    light->setViewMatrix(viewMatrix);
    light->setProjectionMatrix(projectionMatrix);
  }
  if (!paused)
    Light::lights[0]->setLightPosition(glm::vec3(200.0f * cos(lightAngle), 500.0f, 200.0f * sin(lightAngle)));

  if (Input::isKeyPressed(sf::Keyboard::Escape))
  {
    paused = !paused;
    Input::setKeyPressed(sf::Keyboard::Escape, false);
  }

  if (Input::isKeyPressed(sf::Keyboard::M))
  {
    debugMode = !debugMode;
    Input::setKeyPressed(sf::Keyboard::M, false);
  }

  if (Input::isKeyPressed(sf::Keyboard::Num1))
  {
    Light::lights[0]->toggle();
    Input::setKeyPressed(sf::Keyboard::Num1, false);
  }
  else if (Input::isKeyPressed(sf::Keyboard::Num2))
  {
    Light::lights[1]->toggle();
    Input::setKeyPressed(sf::Keyboard::Num2, false);
  }
  Light::lights[1]->setLightPosition(world->player->getPosition() + glm::vec3(0.0f, 150.0f, 0.0f));

  deltaTime = clock.restart().asSeconds();
}

void Game::render()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  window->pushGLStates();
  window->draw(*backgroundSprite);
  window->popGLStates();

  if (debugMode)
  {
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
  }

  glColor3f(1.0f, 1.0f, 1.0f);

  terrain->draw();

  world->render();

  if (debugMode)
  {
    for (auto &light : Light::lights)
      light->draw();
  }

  window->pushGLStates();

  for (auto &text : uiTexts)
  {
    window->draw(text.second);
  }

  window->popGLStates();

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