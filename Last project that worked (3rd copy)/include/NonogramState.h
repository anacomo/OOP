#ifndef __NONOGRAMSTATE_H__
#define __NONOGRAMSTATE_H__

#include "State.h"
#include "TablePixel.h"
#include <fstream>
#include "GameOverState.h"
#include "Heart.h"
#include <iostream>

template <typename T>
bool operator!=(std::map<T, std::map<T, pixelStates>> &firstMap, std::map<T, std::map<T, pixelStates>> &secondMap)
{
    for (auto &i : firstMap)
    {
        for (auto &j : i.second)
        {
            if (auto it = secondMap.find(j.first); it == secondMap.end())
            {
                return true;
            }
            else
            {
                if (secondMap[i.first][j.first] == EMPTY and j.second == MARKED)
                {
                    return true;
                }
                if (secondMap[i.first][j.first] == MARKED and j.second == EMPTY)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

template <typename T>
bool operator==(std::map<T, std::map<T, pixelStates>> &firstMap, std::map<T, std::map<T, pixelStates>> &secondMap)
{
    for (auto &i : firstMap)
    {
        for (auto &j : i.second)
        {
            if (auto it = secondMap.find(j.first); it == secondMap.end())
            {
                return false;
            }
            else
            {
                if (secondMap[i.first][j.first] != j.second)
                {

                    if (!(secondMap[i.first][j.first] == EMPTY and j.second == UNCLICKED) &&
                        !(secondMap[i.first][j.first] == MARKED and j.second == EMPTY))
                        return false;
                }
            }
        }
    }
    return true;
}



class NonogramState
    : public State
{
private:
    static int gameNumber;
    sf::RectangleShape background;
    sf::Texture texture;

    TablePixel *table[10][10];
    std::vector<int> colClues[10];
    std::vector<int> rowClues[10];

    std::map<int, sf::Text> colCluesMap;
    std::map<int, sf::Text> rowCluesMap;
    sf::Color textColor;

    std::unique_ptr<Heart> h;
    sf::Texture heartTexture;
    
    std::map<int, std::map<int, pixelStates>> boolMap;
    std::map<int, std::map<int, pixelStates>> inputMap;

    // initializer functions
    void initializeTable();
    void initializeBackground();
    void initializeText();
    void initializeHearts();

public:
    NonogramState(sf::RenderWindow *window, std::stack<State *> *states);
    virtual ~NonogramState();

    void updateKeyInput();
    void updatePixels();

    void renderPixels(sf::RenderTarget *target = nullptr);
    void renderText(sf::RenderTarget *target = nullptr);
    void renderHeart(sf::RenderTarget * target = nullptr);
    // overrides the pure virtual functions from state class
    void update() override;
    void render(sf::RenderTarget *target = nullptr) override;

    // pentru moment
};

#endif // __NONOGRAMSTATE_H__