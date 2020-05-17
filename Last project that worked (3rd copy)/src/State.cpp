#include "../include/State.h"

// static
gameFinality State::gameOver = NOT_FINISHED;

// intitializer functions
void State::initializeFonts() 
{
    try
    {
        if(!this->font.loadFromFile("fonts/ProductSansBold.ttf"))
            throw Exception("Error: could not load font from file");
    }
    catch(Exception e)
    {
        std::cerr << e.what() << '\n';
    }
}
State::State(sf::RenderWindow* window, std::stack <State*>* states)
{
    this->initializeFonts();
    this->states = states;
    this->window = window;
    this->quit = false;
}

State::~State()
{
}


const bool& State::getQuit() const
{
    return this->quit;
}


gameFinality State::getGameOver() const
{
    return gameOver;
}

void State::updateMousePositions() 
{
    this->mousePositionView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}


void State::endState() 
{
    this->quit = true;
}
