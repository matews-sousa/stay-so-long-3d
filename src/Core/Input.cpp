#include "Input.hpp"

void Input::setKeyPressed(sf::Keyboard::Key key, bool value)
{
  keys[key] = value;
}

void Input::setMousePos(glm::vec2 pos)
{
  mouse_pos = pos;
}

void Input::setMouseButtonDown(sf::Mouse::Button button, bool value)
{
  mouse_buttons[button] = value;
}

std::map<sf::Keyboard::Key, bool> Input::keys;

glm::vec2 Input::mouse_pos;

std::map<sf::Mouse::Button, bool> Input::mouse_buttons;