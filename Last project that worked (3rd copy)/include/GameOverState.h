#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "State.h"

class GameOverState
    : public State
{
private:
    // singleton : private constructor
    static GameOverState *instance;
    sf::Text text;

    sf::Clock clock;

    void initializeText(std::string message);
    GameOverState(sf::RenderWindow *window, std::stack<State *> *states, std::string message);

public:
    static GameOverState *getInstance(sf::RenderWindow *window,
                                      std::stack<State *> *states,
                                      std::string message);

    ~GameOverState();

    GameOverState(const GameOverState &) = delete;  // delete the copy constructor
    void operator=(GameOverState const &) = delete; // delete the assignment operator

    void updateKeyInput();
    // overriding functions
    void render(sf::RenderTarget *target = nullptr) override;
    void update() override;
};

#endif // __GAMEOVER_H__