#include "../include/NonogramState.h"

int NonogramState::gameNumber = 1;

void NonogramState::initializeBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));
    try
    {
        if (!this->texture.loadFromFile("res/table.png"))
            throw Exception("Error: could not load table background");
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    this->background.setTexture(&this->texture);
}

void NonogramState::initializeText()
{
    this->textColor = sf::Color(85, 118, 145);
    float xpos = 200;
    // this is for columns
    for (int i = 0; i < 10; i++)
    {
        std::stringstream ss;
        for (auto &j : colClues[i])
        {
            ss << j;
            ss << '\n';
        }
        sf::Text text;
        text.setFont(this->font);
        text.setString(ss.str());
        text.setCharacterSize(30);
        text.setFillColor(this->textColor);
        // setting the x position
        xpos += (50 - text.getLocalBounds().width) / 2.f;

        text.setPosition(xpos, 195 - colClues[i].size() * 35);
        // modifying xpos
        xpos += (50 - text.getLocalBounds().width) / 2.f + text.getLocalBounds().width;
        colCluesMap[i] = text;
    }
    // this is for rows
    for (int i = 0; i < 10; i++)
    {
        std::stringstream ss;
        for (auto &j : rowClues[i])
        {
            ss << j;
            ss << ' ';
        }
        sf::Text text;
        text.setFont(this->font);
        text.setString(ss.str());
        text.setCharacterSize(30);
        text.setFillColor(this->textColor);
        text.setPosition(195 - text.getLocalBounds().width, 207 + i * 50);
        rowCluesMap[i] = text;
    }
}

void NonogramState::initializeHearts()
{
   h = std::make_unique<Heart>(sf::Vector2f(50 + 60 * 1, 50), sf::Vector2f(50, 50));
}

void NonogramState::initializeTable()
{

    try
    {
        std::string str = "maps/map";
        str = str + std::to_string(gameNumber) + ".txt";
        std::ifstream fin;
        fin.open(str);

        if (fin.is_open())
        {
            unsigned num;
            for (int i = 0; i < 10; i++)
                for (int j = 0; j < 10; j++)
                {
                    fin >> num;
                    boolMap[i][j] = static_cast<pixelStates>(num);
                }
            std::string line;
            for (int i = -1; i < 10; i++)
            {

                getline(fin, line);
                std::istringstream iss(line);
                int a;
                while (iss >> a)
                {
                    if (i > -1)
                        colClues[i].push_back(a);
                }
            }

            for (int i = 0; i < 10; i++)
            {
                getline(fin, line);
                std::istringstream iss(line);
                int a;
                while (iss >> a)
                {
                    if (i > -1)
                        rowClues[i].push_back(a);
                }
            }
        }
        else
        {
            throw Exception("Error: Could not load map file!");
        }

        fin.close();
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            table[i][j] = new TablePixel(202.5 + 50 * i, 202.5 + 50 * j, 45,
                                         "res/unclickedpixel.png", "res/markedpixel.png", "res/emptypixel.png", boolMap[i][j]);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            inputMap[i][j] = UNCLICKED;
}

NonogramState::NonogramState(sf::RenderWindow *window, std::stack<State *> *states)
    : State(window, states)
{
    this->initializeTable();
    this->initializeBackground();
    this->initializeText();
    this->initializeHearts();
    gameNumber = gameNumber % 13 + 1;
}

NonogramState::~NonogramState()
{
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; j++)
            delete this->table[i][j];
    for (int i = 0; i < 10; i++)
    {
        colClues[i].clear();
        rowClues[i].clear();
    }
    colCluesMap.clear();
    rowCluesMap.clear();
    for (unsigned i = 0; i < boolMap.size(); ++i)
        boolMap[i].clear();
    for (unsigned i = 0; i < inputMap.size(); ++i)
        inputMap[i].clear();
   h.reset();
}

// redefining pure virtual functions
void NonogramState::updateKeyInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        this->endState();
}

void NonogramState::updatePixels()
{
    // todo verify if the pixels were correctly clicked
    for (auto i = 0; i < 10; i++)
    {
        for (auto j = 0; j < 10; j++)
        {
            if (this->table[i][j]->isCorrectlyClicked() && this->inputMap[i][j] == UNCLICKED)
            {
                this->inputMap[i][j] = this->boolMap[i][j];
                ++*h;
            }
            else if (table[i][j]->isClicked() && inputMap[i][j] == UNCLICKED) // aici inseamna ca am apasat gresit
            {

                if (Heart::doIHaveRemainingHearts() == true)
                {
                    this->inputMap[i][j] = this->boolMap[i][j];
                    --*h;
                }
                else
                {
                    if (this->boolMap[i][j] == MARKED)
                        this->inputMap[i][j] = EMPTY;
                    else
                    {
                        this->inputMap[i][j] = MARKED;
                    }
                }
            }
        }
    }
    if (inputMap == boolMap && Heart::doIHaveRemainingHearts() == true)
    {
        this->endState();
        gameOver = WON;
    }

    if (inputMap != boolMap || Heart::doIHaveRemainingHearts() == false)
    {
        gameOver = LOST;
        this->endState();
    }

    // update
    for (auto &i : this->table)
        for (auto &j : i)
            j->update(mousePositionView);
}

void NonogramState::renderPixels(sf::RenderTarget *target)
{
    for (auto &i : this->table)
        for (auto &j : i)
            j->render(target);
}

void NonogramState::renderText(sf::RenderTarget *target)
{
    for (auto &i : this->colCluesMap)
    {
        target->draw(i.second);
    }
    for (auto &i : this->rowCluesMap)
    {
        target->draw(i.second);
    }
}

void NonogramState::renderHeart(sf::RenderTarget *target)
{
    if (Heart::doIHaveRemainingHearts())
        h->render(target);
}

void NonogramState::update()
{
    this->updateMousePositions();
    this->updateKeyInput();
    this->updatePixels();
    this->h->update();
}

void NonogramState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;
    target->draw(this->background);

    this->renderPixels(target);
    this->renderText(target);
    this->renderHeart(target);
}