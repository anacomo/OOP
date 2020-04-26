#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include "State.h"

class GameState : public State
{
private:
    /* data */
public:
    GameState(sf::RenderWindow* window);
    virtual ~GameState();

    // Functions
    void endState();
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};



#endif // __GAMESTATE_H__