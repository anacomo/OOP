#include "../include/Heart.h"

int Heart::numberOfHearts = 11;

void Heart::initializeShape(sf::Vector2f v, sf::Vector2f s)
{
    this->heartTexture.loadFromFile("res/heart.png");
    this->shape.setPosition(v);
    this->shape.setSize(s);
    this->shape.setPosition(v);
    this->shape.setTexture(&this->heartTexture);
}

void Heart::initializeText()
{
    //std::string str = static_cast<std::string>(numberOfHearts);
    this->font.loadFromFile("fonts/ProductSansBold.ttf");
    this->text.setFont(this->font);
    std::ostringstream os;
    os << numberOfHearts;
    this->text.setString(os.str());
    this->text.setFillColor(sf::Color(52, 72, 97));
    this->text.setCharacterSize(35);
    this->text.setPosition(50, 50);
}

// default constructor
Heart::Heart()
{
    numberOfHearts++;
}

Heart::Heart(sf::Vector2f v, sf::Vector2f s)
{
    this->initializeShape(v, s);
    this->initializeText();
    if(numberOfHearts <= 0)
        numberOfHearts = 10;
}


// destructor
Heart::~Heart()
{
}

void Heart::operator++()
{
    Heart::numberOfHearts = Heart::numberOfHearts + 1;
}

void Heart::operator--()
{
    Heart::numberOfHearts = Heart::numberOfHearts - 1;
}

bool Heart::doIHaveRemainingHearts()
{
    if (numberOfHearts > 0)
        return true;
    return false;
}

void Heart::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
    target->draw(this->text);
}

void Heart::update()
{
    std::ostringstream os;
    os << numberOfHearts;
    this->text.setString(os.str());
}