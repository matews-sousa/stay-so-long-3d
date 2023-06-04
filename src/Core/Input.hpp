#pragma once

#include <glm/glm.hpp>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

class Input
{
  public:
    static std::map<sf::Keyboard::Key, bool> keys;
    static glm::vec2 mouse_pos;
    static std::map<sf::Mouse::Button, bool> mouse_buttons;

    static void setKeyPressed(sf::Keyboard::Key key, bool value);
    static void setMousePos(glm::vec2 pos);
    static void setMouseButtonDown(sf::Mouse::Button button, bool value);

    static bool isKeyPressed(sf::Keyboard::Key key) { return keys[key]; };
    static glm::vec2 getMousePos() { return mouse_pos; };
    static bool isMouseButtonDown(sf::Mouse::Button button) { return mouse_buttons[button]; };
};