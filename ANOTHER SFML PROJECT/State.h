#ifndef __STATE_H__
#define __STATE_H__

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>


class State
{
private:
    sf::RenderWindow* window;
    std::vector<sf::Texture> textures;

public:
    State(sf::RenderWindow* window);
    virtual ~State();

    // Functions
    virtual void endState() = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};




#endif // __STATE_H__