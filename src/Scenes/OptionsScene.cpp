/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Created by Arthamios
*/

#include <climits>
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/IGUIButton.h>
#include "Path.hpp"
#include "OptionsScene.hpp"
#include "PlayersSettingsSave.hpp"
#include "PlaceRectangle.hpp"

ind::OptionsScene::OptionsScene() :
        AScene(),
        gui(_manager->getGUIEnvironment())
{
    irr::video::IVideoDriver *driver = gui->getVideoDriver();
    const irr::core::dimension2d<irr::u32> size = gui->getVideoDriver()->getScreenSize();

    initButtons({(const irr::s32) size.Width, (const irr::s32) size.Height});
    background = driver->getTexture(Path::realpath("assets/bomb_background.png").c_str());
    gui->getSkin()->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255, 180, 180, 180));
}

ind::OptionsScene::~OptionsScene()
{
    for (auto &button : buttonsPlace)
        button.first->remove();
}

void ind::OptionsScene::initButtons(const irr::core::dimension2d<irr::s32> &size)
{
    irr::core::dimension2df signSize = {1.0f / 20, 1.0f / 30};

    returnButton = initButton({1.0f / 2, 11.0f / 12}, {1.0f / 10, 1.0f / 20}, size, "assets/return.png", nullptr);
    initMaxBombsButtons(size, signSize);
    initBombsPowerButtons(size, signSize);
    initSpeedButtons(size, signSize);
    initPlayerNumber(size, signSize);
    initAINumber(size, signSize);
    setTexts();
}

void ind::OptionsScene::initMaxBombsButtons(const irr::core::dimension2d<irr::s32> &size,
                                            const irr::core::dimension2df &signSize)
{
    float bombsHeight = 0.6f / 4;

    maxBombsPlacedButton = initButton({1.0f / 5, bombsHeight}, {1.0f / 10, 1.0f / 15}, size,
                                      "assets/settings/bombs_placed_max.png", nullptr);
    bombsPlacedDown = initButton({3.0f / 5, bombsHeight}, signSize, size, "assets/settings/minus.png",
                                 &ind::OptionsScene::decrementMaxBombsPlaced);
    bombsPlacedUp = initButton({4.0f / 5, bombsHeight}, signSize, size, "assets/settings/plus.png",
                               &ind::OptionsScene::incrementMaxBombsPlaced);
    bombsPlacedNumber = initButton({3.5f / 5, bombsHeight}, signSize, size, "assets/settings/empty.png",
                                   nullptr);
}

void ind::OptionsScene::initSpeedButtons(const irr::core::dimension2d<irr::s32> &size,
                                         const irr::core::dimension2df &signSize)
{
    float speedHeight = 1.6f / 5;

    speedButton = initButton({1.0f / 5, speedHeight}, {1.0f / 10, 1.0f / 20}, size,
                             "assets/settings/movement_speed.png", nullptr);
    speedDownButton = initButton({3.0f / 5, speedHeight}, signSize, size, "assets/settings/minus.png",
                                 &ind::OptionsScene::decrementSpeed);
    speedUpButton = initButton({4.0f / 5, speedHeight}, signSize, size, "assets/settings/plus.png",
                               &ind::OptionsScene::incrementSpeed);
    speedNumberButton = initButton({3.5f / 5, speedHeight}, signSize, size, "assets/settings/empty.png",
                                   nullptr);
}

void ind::OptionsScene::initBombsPowerButtons(const irr::core::dimension2d<irr::s32> &size,
                                              const irr::core::dimension2df &signSize)
{
    float bombPowerHeight = 2.3f / 5;

    bombsPowerButton = initButton({1.0f / 5, bombPowerHeight}, {1.0f / 10, 1.0f / 20}, size,
                                  "assets/settings/bombs_power.png", nullptr);
    bombsPowerDownButton = initButton({3.0f / 5, bombPowerHeight}, signSize, size, "assets/settings/minus.png",
                                      &ind::OptionsScene::decrementBombsPower);
    bombsPowerUpButton = initButton({4.0f / 5, bombPowerHeight}, signSize, size, "assets/settings/plus.png",
                                    &ind::OptionsScene::incrementBombsPower);
    bombsPowerNumberButton = initButton({3.5f / 5, bombPowerHeight}, signSize, size, "assets/settings/empty.png",
                                        nullptr);
}

void ind::OptionsScene::initPlayerNumber(const irr::core::dimension2d<irr::s32> &size,
                                         const irr::core::dimension2df &signSize)
{
    float playerNumberHeight = 3.2f / 5;

    playerNumberButton = initButton({1.0f / 5, playerNumberHeight}, {1.0f / 10, 1.0f / 15}, size,
                                    "assets/settings/players_number.png", nullptr);
    playerNumberDown = initButton({3.0f / 5, playerNumberHeight}, signSize, size, "assets/settings/minus.png",
                                  &ind::OptionsScene::decrementPlayerNumber);
    playerNumberUp = initButton({4.0f / 5, playerNumberHeight}, signSize, size, "assets/settings/plus.png",
                                &ind::OptionsScene::incrementPlayerNumber);
    playerNumberValue = initButton({3.5f / 5, playerNumberHeight}, signSize, size, "assets/settings/empty.png",
                                   nullptr);
}

void ind::OptionsScene::initAINumber(const irr::core::dimension2d<irr::s32> &size,
                                     const irr::core::dimension2df &signSize)
{
    float AINumberHeight = 4.0 / 5;

    AINumberButton = initButton({1.0f / 5, AINumberHeight}, {1.0f / 10, 1.0f / 15}, size,
                                "assets/settings/ai_number.png", nullptr);
    AINumberDown = initButton({3.0f / 5, AINumberHeight}, signSize, size, "assets/settings/minus.png",
                              &ind::OptionsScene::decrementAINumber);
    AINumberUp = initButton({4.0f / 5, AINumberHeight}, signSize, size, "assets/settings/plus.png",
                            &ind::OptionsScene::incrementAINumber);
    AINumberValue = initButton({3.5f / 5, AINumberHeight}, signSize, size, "assets/settings/empty.png",
                               nullptr);
}

void ind::OptionsScene::setTexts() const
{
    irr::gui::IGUIFont *font = gui->getFont(Path::realpath("assets/settings/fonts/32px/myfont.xml").c_str());

    const std::string maxBombsPlacedStr = std::to_string(
            ind::PlayersSettingsSave::defaultSettings().maxBombsPlaced);
    bombsPlacedNumber->setText(std::wstring(maxBombsPlacedStr.begin(), maxBombsPlacedStr.end()).c_str());
    bombsPlacedNumber->setOverrideFont(font);

    const std::string speedStr = std::to_string((int) ind::PlayersSettingsSave::defaultSettings().speed);
    speedNumberButton->setText(std::wstring(speedStr.begin(), speedStr.end()).c_str());
    speedNumberButton->setOverrideFont(font);

    const std::string powerStr = std::to_string(ind::PlayersSettingsSave::defaultSettings().bombPower);
    bombsPowerNumberButton->setText(std::wstring(powerStr.begin(), powerStr.end()).c_str());
    bombsPowerNumberButton->setOverrideFont(font);

    const std::string playersNbStr = std::to_string(ind::PlayersSettingsSave::getPlayerNumber());
    playerNumberValue->setText(std::wstring(playersNbStr.begin(), playersNbStr.end()).c_str());
    playerNumberValue->setOverrideFont(font);

    const std::string AINbStr = std::to_string(ind::PlayersSettingsSave::getAINumber());
    AINumberValue->setText(std::wstring(AINbStr.begin(), AINbStr.end()).c_str());
    AINumberValue->setOverrideFont(font);
}

irr::gui::IGUIButton *ind::OptionsScene::initButton(const irr::core::dimension2df &center,
                                                    const irr::core::dimension2df &size,
                                                    const irr::core::dimension2di &screenDimension, const char *path,
                                                    void (ind::OptionsScene::*function)())
{
    irr::gui::IGUIButton *button = gui->addButton(ind::PlaceRectangle::getRectangle(
            {(int) (center.Width * screenDimension.Width), (int) (center.Height * screenDimension.Height)},
            {(int) (size.Width * screenDimension.Width), (int) (size.Height * screenDimension.Height)}));
    button->setImage(gui->getVideoDriver()->getTexture(Path::realpath(path).c_str()));
    button->setDrawBorder(false);
    buttonsPlace.emplace(button, ButtonPosition(center, size));
    if (function)
        buttonsFunction[button] = function;
    return button;
}

ind::SceneType ind::OptionsScene::execute(irr::f32)
{
    static irr::core::dimension2d<irr::u32> size = gui->getVideoDriver()->getScreenSize();
    const irr::core::dimension2d<irr::u32> currSize = gui->getVideoDriver()->getScreenSize();

    if (currSize != size) {
        resizeButtons(currSize);
        size = currSize;
    }
    if (returnButton->isPressed())
        return MAIN_MENU;
    for (const auto &pair : buttonsFunction)
        if (pair.first->isPressed())
            (this->*pair.second)();
    draw(size);
    return OPTIONS;
}

void ind::OptionsScene::draw(const irr::core::dimension2d<irr::u32> &size) const
{
    gui->getVideoDriver()->draw2DImage(background,
                                       irr::core::position2d<irr::s32>(0, 0),
                                       irr::core::rect<irr::s32>(0, 0, 1920, 1080),
                                       new irr::core::rect<irr::s32>(0, 0, size.Width, size.Height));

    gui->drawAll();
}

void ind::OptionsScene::resizeButtons(const irr::core::dimension2d<irr::u32> &currSize) const
{
    const irr::u32 &x = currSize.Width;
    const irr::u32 &y = currSize.Height;

    for (const auto &buttonPair : buttonsPlace)
        buttonPair.first->setRelativePosition(findPosition(x, y, buttonPair.first));
}

irr::core::rect<irr::s32> ind::OptionsScene::findPosition(const irr::u32 &x, const irr::u32 &y,
                                                          irr::gui::IGUIButton *button) const
{
    const ButtonPosition &buttonPlace = buttonsPlace.at(button);

    return ind::PlaceRectangle::getRectangle(
            {(int) (x * buttonPlace.center.Width), (int) (y * buttonPlace.center.Height)},
            {(int) (x * buttonPlace.size.Width), (int) (y * buttonPlace.size.Height)});
}

ind::SceneType ind::OptionsScene::type()
{
    return OPTIONS;
}

void ind::OptionsScene::incrementMaxBombsPlaced()
{
    if (PlayersSettingsSave::defaultSettings().maxBombsPlaced == SHRT_MAX)
        return;

    ++PlayersSettingsSave::defaultSettings().maxBombsPlaced;

    std::string maxBombsPlacedStr = std::to_string(PlayersSettingsSave::defaultSettings().maxBombsPlaced);
    bombsPlacedNumber->setText(std::wstring(maxBombsPlacedStr.begin(), maxBombsPlacedStr.end()).c_str());
    bombsPlacedUp->setPressed(false);
}

void ind::OptionsScene::decrementMaxBombsPlaced()
{
    if (PlayersSettingsSave::defaultSettings().maxBombsPlaced <= 1)
        return;

    --PlayersSettingsSave::defaultSettings().maxBombsPlaced;

    std::string maxBombsPlacedtr = std::to_string(PlayersSettingsSave::defaultSettings().maxBombsPlaced);
    bombsPlacedNumber->setText(std::wstring(maxBombsPlacedtr.begin(), maxBombsPlacedtr.end()).c_str());
    bombsPlacedDown->setPressed(false);
}

void ind::OptionsScene::incrementSpeed()
{
    if (PlayersSettingsSave::defaultSettings().speed == FLT_MAX)
        return;

    ++PlayersSettingsSave::defaultSettings().speed;
    std::string speedStr = std::to_string((int) PlayersSettingsSave::defaultSettings().speed);
    speedNumberButton->setText(std::wstring(speedStr.begin(), speedStr.end()).c_str());
    speedUpButton->setPressed(false);
}

void ind::OptionsScene::decrementSpeed()
{
    if (PlayersSettingsSave::defaultSettings().speed <= 1)
        return;

    --PlayersSettingsSave::defaultSettings().speed;

    std::string speedStr = std::to_string((int) PlayersSettingsSave::defaultSettings().speed);
    speedNumberButton->setText(std::wstring(speedStr.begin(), speedStr.end()).c_str());
    speedDownButton->setPressed(false);
}

void ind::OptionsScene::decrementBombsPower()
{
    if (PlayersSettingsSave::defaultSettings().bombPower <= 1)
        return;

    --PlayersSettingsSave::defaultSettings().bombPower;

    std::string bombsPowerStr = std::to_string(PlayersSettingsSave::defaultSettings().bombPower);
    bombsPowerNumberButton->setText(std::wstring(bombsPowerStr.begin(), bombsPowerStr.end()).c_str());
    bombsPowerDownButton->setPressed(false);
}

void ind::OptionsScene::incrementBombsPower()
{
    if (PlayersSettingsSave::defaultSettings().bombPower >= USHRT_MAX)
        return;

    ++PlayersSettingsSave::defaultSettings().bombPower;

    std::string bombsPowerStr = std::to_string(PlayersSettingsSave::defaultSettings().bombPower);
    bombsPowerNumberButton->setText(std::wstring(bombsPowerStr.begin(), bombsPowerStr.end()).c_str());
    bombsPowerUpButton->setPressed(false);
}

void ind::OptionsScene::incrementPlayerNumber()
{
    if (PlayersSettingsSave::getPlayerNumber() == PlayersSettingsSave::getMaxPlayers())
        return;

    if (PlayersSettingsSave::getAINumber() == PlayersSettingsSave::getMaxAI())
        decrementAINumber();
    PlayersSettingsSave::addPlayer();

    const std::string playerNumberStr = std::to_string(PlayersSettingsSave::getPlayerNumber());
    playerNumberValue->setText(std::wstring(playerNumberStr.begin(), playerNumberStr.end()).c_str());
    playerNumberUp->setPressed(false);
}

void ind::OptionsScene::decrementPlayerNumber()
{
    if (PlayersSettingsSave::getPlayerNumber() == 1)
        return;

    if (PlayersSettingsSave::getPlayerNumber() == 2 && PlayersSettingsSave::getAINumber() == 0)
        incrementAINumber();
    PlayersSettingsSave::removePlayer();

    const std::string playerNumberStr = std::to_string(PlayersSettingsSave::getPlayerNumber());
    playerNumberValue->setText(std::wstring(playerNumberStr.begin(), playerNumberStr.end()).c_str());
    playerNumberDown->setPressed(false);
}

void ind::OptionsScene::decrementAINumber()
{
    const unsigned short aiNumber = PlayersSettingsSave::getAINumber();

    if (aiNumber == 0)
        return;

    if (PlayersSettingsSave::getPlayerNumber() == 1 && aiNumber == 1)
        incrementPlayerNumber();
    PlayersSettingsSave::removeAI();

    const std::string AINumberStr = std::to_string(aiNumber - 1);
    AINumberValue->setText(std::wstring(AINumberStr.begin(), AINumberStr.end()).c_str());
    AINumberDown->setPressed(false);
}

void ind::OptionsScene::incrementAINumber()
{
    if (PlayersSettingsSave::getAINumber() >= PlayersSettingsSave::getMaxAI())
        return;

    if (PlayersSettingsSave::getPlayerNumber() == PlayersSettingsSave::getMaxPlayers() &&
        PlayersSettingsSave::getMaxAI() == PlayersSettingsSave::getAINumber() + 1)
        decrementPlayerNumber();
    PlayersSettingsSave::addAI();

    const std::string AINumberStr = std::to_string(PlayersSettingsSave::getAINumber());
    AINumberValue->setText(std::wstring(AINumberStr.begin(), AINumberStr.end()).c_str());
    AINumberUp->setPressed(false);
}