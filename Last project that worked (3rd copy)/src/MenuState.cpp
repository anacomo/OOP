#include "../include/MenuState.h"

void MenuState::initializeText(std::string text, sf::Color color, int charSize)
{
    this->text.setFont(this->font);
    this->text.setString(text);
    this->text.setFillColor(color);
    this->text.setCharacterSize(charSize);
    this->text.setPosition(
        this->window->getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
        this->window->getSize().y / 3.f - this->text.getGlobalBounds().height);
}

void MenuState::initializeButtons()
{
    this->buttons["NEW_GAME"] = new Button(230, 460, 100, 100,
                                           "res/playbutton.png", "res/playbuttonhover.png", "res/playbuttonhover.png");
    this->buttons["EXIT_GAME"] = new Button(470, 460, 100, 100,
                                            "res/quitbutton.png", "res/quitbuttonjover.png", "res/quitbuttonjover.png");
}

void MenuState::initializeBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
                                          static_cast<float>(this->window->getSize().y)));

    try
    {
        if (!this->bgTexture.loadFromFile("res/table2.png"))
            throw Exception("Error: failed to load background from file");
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    this->background.setTexture(&this->bgTexture);
}

MenuState::MenuState(sf::RenderWindow *window, std::stack<State *> *states)
    : State(window, states)
{
    this->initializeButtons();
    this->initializeBackground();
    this->initializeText("Nonogram", sf::Color(52, 72, 97), 50);
}

MenuState::~MenuState()
{
    for (auto i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}

void MenuState::updateButtons()
{
    for (auto &i : this->buttons)
    {
        i.second->update(this->mousePositionView);
    }
    // make new game
    if (this->buttons["NEW_GAME"]->isPressed())
    {
        this->states->push(new NonogramState(this->window, this->states));
        //this->states->push(std::make_shared<NonogramState>(this->window, this->states));
    }
    // quit the game
    if (this->buttons["EXIT_GAME"]->isPressed())
    {
        this->endState();
    }
}

void MenuState::update()
{
    this->updateMousePositions();
    this->updateButtons();
}

void MenuState::renderButtons(sf::RenderTarget *target)
{
    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }
}

void MenuState::render(sf::RenderTarget *target)
{
    if (!target)
        target = this->window;

    target->draw(this->background);
    target->draw(this->text);
    this->renderButtons(target);
}
