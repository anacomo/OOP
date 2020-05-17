#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <sstream>
#include <vector>
#include <iostream>
#include <stack>
#include <map>
#include <vector>
#include <string>
#include "Exception.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

enum buttonStates
{
    DEFAULT,
    HOVER,
    ACTIVE
};

class Button
{
private:
    buttonStates buttonState;
    sf::RectangleShape shape;

    sf::Texture defaultTexture;
    sf::Texture hoverTexture;
    sf::Texture activeTexture;

    // initializer functions
    void initializeShape(float x, float y, float width, float height);
    void initializeTexture(std::string defaultSource, std::string hoverSource, std::string activeSource);

public:
    Button(float x, float y, float width, float height,
           std::string defaultSource, std::string hoverSource, std::string activeSource);
    virtual ~Button();

    // getter
    bool isPressed() const;

    // functions
    void render(sf::RenderTarget *target);
    void update(const sf::Vector2f mousePosition);
};

#endif // __BUTTON_H__