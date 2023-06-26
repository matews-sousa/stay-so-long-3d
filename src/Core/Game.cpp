#include "Game.hpp"

sf::RenderWindow *Game::window;
Camera *Game::camera;
MousePicker *Game::picker;
float Game::deltaTime;
Terrain *Game::terrain;
std::map<std::string, Mesh *> Game::models;
std::vector<Light *> Game::lights;
std::vector<GLight *> Game::glights;

bool Game::GLightsEnabled = false;

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

  player = new Player(glm::vec3(0.0f, 35.0f, 0.0f), glm::vec3(15.0f, 15.0f, 15.0f));

  init();
  GLight::initLights();
  initLights();
  initTextures();
  initObjModels();

  terrain = new Terrain(0, 0);
  picker = new MousePicker(projectionMatrix, viewMatrix, *window, *terrain);
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
  texture = new Texture("../src/Assets/Textures/stone.jpg", "stone");
  texture = new Texture("../src/Assets/Textures/rock.jpg", "rock");
  texture = new Texture("../src/Assets/Textures/wall.jpg", "wall");
  texture = new Texture("../src/Assets/Textures/awesomeface.png", "awesomeface");
  texture = new Texture("../src/Assets/Textures/Mecha01.png", "mecha");
  texture = new Texture("../src/Assets/Textures/MechaGolem.png", "golem");
  texture = new Texture("../src/Assets/Textures/TallBuilding01.png", "building");
  texture = new Texture("../src/Assets/Textures/spaceship6_normal_tangent_bevel.png", "spaceship");
  texture = new Texture("../src/Assets/Textures/T_Weapons.png", "weapons");
  texture = new Texture("../src/Assets/Textures/MicroRecon.png", "micro_recon");
  texture = new Texture("../src/Assets/Textures/InterstellarRunner.png", "runner");
  texture = new Texture("../src/Assets/Textures/Transtellar.png", "stellar");

  // scenary textures
  texture = new Texture("../src/Assets/Textures/MountainRocks-0.png", "mountain");
}

void Game::initObjModels()
{
  models["cube"] = new Mesh("../src/Assets/Models/cube.obj");
  models["mecha"] = new Mesh("../src/Assets/Models/mecha.obj");
  models["golem"] = new Mesh("../src/Assets/Models/MechaGolem.obj");
  models["spaceship"] = new Mesh("../src/Assets/Models/Spaceship6.obj");
  models["building"] = new Mesh("../src/Assets/Models/building.obj");
  models["micro_recon"] = new Mesh("../src/Assets/Models/MicroRecon.obj");
  models["runner"] = new Mesh("../src/Assets/Models/InterstellarRunner.obj");
  models["stellar"] = new Mesh("../src/Assets/Models/Transtellar.obj");

  // scenary models
  models["mountain"] = new Mesh("../src/Assets/Models/MountainRocks-0.obj");
}

void Game::initLights()
{
  // init our own lights
  lights.push_back(new Light(glm::vec3(200.0f, 500.0f, 200.0f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), LightType::SPOT_LIGHT));
  lights.push_back(new Light(player->getPosition(), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
  
  for (auto &light : lights)
    light->setViewMatrix(viewMatrix);

  // init OpenGL lights
  GLight *mainLight = new GLight(LIGHT_SPOT);
  mainLight->setPosition(glm::vec4(100.0f, 200.0f, 100.0f, 1.0f));
  mainLight->setDiffuse(glm::vec4(1.0f, 0.235f, 0.654f, 1.0f));

  GLight *secondLight = new GLight(LIGHT_SPOT);
  secondLight->setPosition(glm::vec4(-100.0f, 200.0f, -100.0f, 1.0f));
  secondLight->setDiffuse(glm::vec4(0.0f, 0.235f, 1.0f, 1.0f));

  GLight *thirdLight = new GLight(LIGHT_POINT);
  thirdLight->setPosition(glm::vec4(player->getPosition(), 1.0f));
  thirdLight->setDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

  glights.push_back(mainLight);
  glights.push_back(secondLight);
  glights.push_back(thirdLight);
}

void Game::init()
{
  glViewport(0, 0, window->getSize().x, window->getSize().y);

  float halfWidth = window->getSize().x / 2.0f;
  float halfHeight = window->getSize().y / 2.0f;

  //glm::mat4 projectionMatrix = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 2000.0f);
  projectionMatrix = glm::perspective(glm::radians(45.0f), (float)window->getSize().x / (float)window->getSize().y, 0.1f, 2000.0f);
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

  std::cout << "FPS: " << 1.0f / deltaTime << std::endl;

  viewMatrix = camera->getViewMatrix();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(glm::value_ptr(viewMatrix));

  picker->update(projectionMatrix, viewMatrix);
  player->update();

  if (Input::isKeyPressed(sf::Keyboard::G))
  {
    GLightsEnabled = !GLightsEnabled;

    if (GLightsEnabled)
    {
      glEnable(GL_LIGHTING);
      glEnable(GL_COLOR_MATERIAL);
    }
    else
    {
      glDisable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);
    }

    Input::setKeyPressed(sf::Keyboard::G, false);
  }

  lightAngle += 0.1f;
  if (!GLightsEnabled)
  {
    for (auto &light : lights)
    {
      light->setViewMatrix(viewMatrix);
      light->setProjectionMatrix(projectionMatrix);
    }
    lights[0]->setLightPosition(glm::vec3(200.0f * cos(lightAngle), 1000.0f, 200.0f * sin(lightAngle)));

    if (Input::isKeyPressed(sf::Keyboard::Num1))
    {
      lights[0]->toggle();
      Input::setKeyPressed(sf::Keyboard::Num1, false);
    }
    else if (Input::isKeyPressed(sf::Keyboard::Num2))
    {
      lights[1]->toggle();
      Input::setKeyPressed(sf::Keyboard::Num2, false);
    }
    lights[1]->setLightPosition(player->getPosition() + glm::vec3(0.0f, 100.0f, 0.0f));
  }
  else
  {
    glights[0]->setPosition(glm::vec4(200.0f * cos(lightAngle), 500.0f, 200.0f * sin(lightAngle), 1.0f));
    glights[1]->setPosition(glm::vec4(-200.0f * cos(lightAngle), 500.0f, -200.0f * sin(lightAngle), 1.0f));

    if (Input::isKeyPressed(sf::Keyboard::Num1))
    {
      glights[0]->toggleVisible();
      Input::setKeyPressed(sf::Keyboard::Num1, false);
    }
    else if (Input::isKeyPressed(sf::Keyboard::Num2))
    {
      glights[1]->toggleVisible();
      Input::setKeyPressed(sf::Keyboard::Num2, false);
    }
    glights[2]->setPosition(glm::vec4(player->getPosition() + glm::vec3(0.0f, 100.0f, 0.0f), 1.0f));
  }

  deltaTime = clock.restart().asSeconds();
}

void Game::render()
{
  Mesh &runner1 = *models["runner"];
  Mesh &runner2 = *models["runner"];

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

  terrain->draw();

  glm::mat4 modelMatrix = glm::mat4(1.0f);

/*   Texture::bindByName("stellar");
  glPushMatrix();
  modelMatrix = glm::translate(modelMatrix, glm::vec3(250.0f, 50.0f, 250.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
  glMultMatrixf(glm::value_ptr(modelMatrix));
  models["stellar"]->render(modelMatrix);
  glPopMatrix();

  Texture::bindByName("building");
  glPushMatrix();
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(150.0f, 0.0f, 150.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(25.0f, 25.0f, 25.0f));
  glMultMatrixf(glm::value_ptr(modelMatrix));
  models["building"]->render(modelMatrix);
  glPopMatrix(); */

  Texture::bindByName("wall");
  glPushMatrix();
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-150.0f, 50.0f, -150.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
  glMultMatrixf(glm::value_ptr(modelMatrix));
  models["cube"]->render(modelMatrix);
  glPopMatrix();

  Texture::bindByName("runner");
  glPushMatrix();
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(-150.0f, -25.0f, -150.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
  glMultMatrixf(glm::value_ptr(modelMatrix));
  runner1.render(modelMatrix);
  glPopMatrix();

  Texture::bindByName("runner");
  glPushMatrix();
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, glm::vec3(250.0f, -25.0f, 250.0f));
  modelMatrix = glm::scale(modelMatrix, glm::vec3(50.0f, 50.0f, 50.0f));
  glMultMatrixf(glm::value_ptr(modelMatrix));
  runner2.render(modelMatrix);
  glPopMatrix();

  player->draw();

  if (GLightsEnabled)
    for (auto &light : glights)
      light->drawLight();
  else
    for (auto &light : lights)
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
