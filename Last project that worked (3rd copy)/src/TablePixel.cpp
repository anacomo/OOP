#include "../include/TablePixel.h"

void TablePixel::initializeShape(float x, float y, float dim)
{
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(dim, dim));
}

void TablePixel::initializeTexture(std::string unclickedSource, std::string markedSource, std::string emptySource)
{
    try
    {
        if (!this->unclickedTexture.loadFromFile(unclickedSource))
            throw "Error: Could not load Table Pixel texture from file";
        if (!this->markedTexture.loadFromFile(markedSource))
            throw "Error: Could not load Table Pixel texture from file";
        if (!this->emptyTexture.loadFromFile(emptySource))
            throw "Error: Could not load Table Pixel texture from file";
        this->shape.setTexture(&this->unclickedTexture);
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

// constructor and destructor
TablePixel::TablePixel(float x, float y, float dim,
                       std::string unclickedSource, std::string markedSource, std::string emptySource, pixelStates puzzleState)
{
    this->pixelState = UNCLICKED;
    this->initializeShape(x, y, dim);
    this->initializeTexture(unclickedSource, markedSource, emptySource);
    this->puzzleState = puzzleState;
}

TablePixel::~TablePixel()
{
}

// getters
bool TablePixel::isCorrectlyClicked()
{
    auto lambda = [](pixelStates pixelState, pixelStates puzzleState) {
        return pixelState == puzzleState;
    };
    return lambda(this->pixelState, this->puzzleState);
}

bool TablePixel::isClicked()
{
    if (this->pixelState == EMPTY || this->pixelState == MARKED)
    {
        this->pixelState = this->puzzleState;
        return true;
    }
    return false;
}

void TablePixel::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}

void TablePixel::update(sf::Vector2f mousePosition)
{
    if (this->shape.getGlobalBounds().contains(mousePosition))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->puzzleState == MARKED)
        {
            this->pixelState = MARKED;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->puzzleState == MARKED)
        {
            this->pixelState = EMPTY;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->puzzleState == EMPTY)
        {
            this->pixelState = EMPTY;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->puzzleState == EMPTY)
        {
            this->pixelState = MARKED;
        }
    }
    switch (this->pixelState)
    {
    case UNCLICKED:
        this->shape.setTexture(&this->unclickedTexture);
        break;
    case MARKED:
        this->shape.setTexture(&this->markedTexture);
        break;
    case EMPTY:
        this->shape.setTexture(&this->emptyTexture);
        break;
    default:
        break;
    }
}
