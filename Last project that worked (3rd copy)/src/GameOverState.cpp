#include "../include/GameOverState.h"

// static variable
GameOverState *GameOverState::instance = nullptr;

// private functions
void GameOverState::initializeText(std::string message)
{
    this->text.setFont(font);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(50);
    this->text.setPosition(
        this->window->getSize().x / 2.f - 200,
        this->window->getSize().y / 2.f - 60);

    try
    {
        if (message == "loss")
        {
            this->text.setString("You lost. Try again!");
        }
        else if (message == "win")
        {
            this->text.setString("You won! Great job");
        }
        else
        {
            throw Exception("Error: the type of the game finality is wrong");
        }
        
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

GameOverState::GameOverState(sf::RenderWindow *window,
                             std::stack<State *> *states,
                             std::string message)
    : State(window, states)
{
    this->initializeText(message);
}

// public functions
GameOverState *GameOverState::getInstance(sf::RenderWindow *window,
                                          std::stack<State *> *states,
                                          std::string message)
{
    if (instance == nullptr)
        instance = new GameOverState(window, states, message);
    return instance;
}

GameOverState::~GameOverState()
{
    instance = nullptr;
}

void GameOverState::updateKeyInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        gameOver = NOT_FINISHED;
        this->endState();
    }
}

void GameOverState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;
    target->draw(this->text);
}

void GameOverState::update()
{
    this->updateKeyInput();
}