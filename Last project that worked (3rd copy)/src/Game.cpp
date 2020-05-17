#include "../include/Game.h"

// initializer functions
void Game::initializeWindow()
{
    sf::VideoMode windowDimensions(800, 800);
    std::string title = "Nonogram";

    this->window = new sf::RenderWindow(windowDimensions, title, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(120);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initializeStates()
{
    this->states.push(new MenuState(this->window, &this->states));
}

// constructor
Game::Game()
{
    this->initializeWindow();
    this->initializeStates();
}

// destructor
Game::~Game()
{
    delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

// functions
void Game::updateEvents()
{

    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateEvents();

    if (!this->states.empty())
    {
        this->states.top()->update();

        if (dynamic_cast<MenuState*>(this->states.top()) && this->states.top()->getGameOver() != NOT_FINISHED)
            {
                if (this->states.top()->getGameOver() == WON)
                    this->states.push(GameOverState::getInstance(this->window, &this->states, "win"));
                if (this->states.top()->getGameOver() == LOST)
                    this->states.push(GameOverState::getInstance(this->window, &this->states, "loss"));
            }

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
    {
        this->window->close();
    }
}

void Game::render()
{
    this->window->clear();

    // render items
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->update();
        this->render();
    }
}
