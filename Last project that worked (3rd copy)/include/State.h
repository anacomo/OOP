#ifndef __STATE_H__
#define __STATE_H__

#include "Exception.h"
#include <vector>
#include <stack>
#include <map>
#include <vector>
#include <memory>
#include <utility>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Button.h"

enum gameFinality
{
    NOT_FINISHED,
    WON,
    LOST
};

class State
{
protected:
    sf::RenderWindow *window;
    bool quit;
    std::stack<State *> *states;
    //std::shared_ptr<std::stack<State*>> states;
    sf::Font font;

    // mouse positions
    sf::Vector2f mousePositionView;

    // initializer functions
    void initializeFonts();
    static gameFinality gameOver;

public:
    State(sf::RenderWindow *window, std::stack<State *> *states);
    virtual ~State();

    const bool &getQuit() const;
    gameFinality getGameOver() const;
    virtual void updateMousePositions();

    // pure virtual functions
    virtual void update() = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
    void endState();
};

#endif // __STATE_H__