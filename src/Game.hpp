/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Created by abel,
*/

#pragma once

#include <irrlicht/irrlicht.h>
#include <string>
#include "Board.hpp"
#include "Player.hpp"
#include "DeviceService.hpp"

namespace ind {
    class Game {
        public:
        explicit Game();

        ~Game() = default;

        void run();
    private:
        void startMenu() const;

        DeviceService *deviceService;
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        irr::scene::ISceneManager *manager;
    };
}
