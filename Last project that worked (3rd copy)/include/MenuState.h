#ifndef __MENUSTATE_H__
#define __MENUSTATE_H__

#include "NonogramState.h"
#include "Button.h"

class MenuState
    : public State
{
private:
    sf::RectangleShape background;
    sf::Texture bgTexture;

    sf::Text text;

    std::map<std::string, Button *> buttons;

    // initializer functions
    void initializeText(std::string text, sf::Color color, int charSize);
    void initializeButtons();
    void initializeBackground();

public:
    MenuState(sf::RenderWindow *window, std::stack<State *> *states);
    virtual ~MenuState();

    // redefining pure virtual functions
    void updateButtons();

    void update() override;
    void renderButtons(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target = nullptr) override;
};

#endif // __MENUSTATE_H__