#include "../include/Button.h"

// initializer functions
void Button::initializeShape(float x, float y, float width, float height)
{
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
}

void Button::initializeTexture(std::string defaultSource, std::string hoverSource, std::string activeSource)
{
    try
    {
        if (!this->defaultTexture.loadFromFile(defaultSource))
            throw Exception("Error: failed to load texture from file");
        if (!this->hoverTexture.loadFromFile(hoverSource))
            throw Exception("Error: failed to load texture from file");
        if (!this->activeTexture.loadFromFile(activeSource))
            throw Exception("Error: failed to load texture from file");
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    this->shape.setTexture(&this->defaultTexture);
}
// constructor
Button::Button(float x, float y, float width, float height,
               std::string defaultSource, std::string hoverSource, std::string activeSource)
{
    this->buttonState = DEFAULT;
    this->initializeShape(x, y, width, height);
    this->initializeTexture(defaultSource, hoverSource, activeSource);
}

Button::~Button()
{
}

bool Button::isPressed() const
{
    if (this->buttonState == ACTIVE)
        return true;
    return false;
}

// functions
void Button::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}

void Button::update(const sf::Vector2f mousePosition)
{
    this->buttonState = DEFAULT;
    if (this->shape.getGlobalBounds().contains(mousePosition))
    {
        this->buttonState = HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            this->buttonState = ACTIVE;
    }

    try
    {
        switch (this->buttonState)
        {
        case DEFAULT:
            this->shape.setTexture(&this->defaultTexture);
            break;
        case HOVER:
            this->shape.setTexture(&this->hoverTexture);
            break;
        case ACTIVE:
            this->shape.setTexture(&this->activeTexture);
            break;
        default:
            throw Exception("Error: this button doesn't look good!");
            break;
        }
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
