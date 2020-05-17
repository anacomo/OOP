#ifndef __TABLEPIXEL_H__
#define __TABLEPIXEL_H__

#include "State.h"

enum pixelStates
{
    UNCLICKED,
    MARKED,
    EMPTY
};

class TablePixel
{
private:
    pixelStates pixelState;
    pixelStates puzzleState;
    sf::RectangleShape shape;

    sf::Texture unclickedTexture;
    sf::Texture markedTexture;
    sf::Texture emptyTexture;

    //initializer functions
    void initializeShape(float x, float y, float dim);
    void initializeTexture(std::string unclickedSource, std::string markedSource, std::string emptySource);

public:
    TablePixel(float x, float y, float dim,
               std::string unclickedSource, std::string markedSource, std::string emptySource, pixelStates puzzleState);
    virtual ~TablePixel();

    // getters
    bool isCorrectlyClicked();
    bool isClicked();

    // utility functions
    void render(sf::RenderTarget *target);
    void update(sf::Vector2f mousePosition);
};

#endif // __TABLEPIXEL_H__