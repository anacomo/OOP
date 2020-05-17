#ifndef __GAME_H__
#define __GAME_H__

#include "MenuState.h"

class Game
{
private:
    // variables
    sf::RenderWindow *window;
    sf::Event event;

    // States stack
    std::stack<State *> states;

    // initializer functions
    void initializeWindow();
    void initializeStates();

public:
    Game();
    virtual ~Game();

    // functions
    void updateEvents();
    void update();
    void render();
    void run();
};

#endif // __GAME_H__