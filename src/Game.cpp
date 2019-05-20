/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Created by abel,
*/

#include <iostream>
#include "Game.hpp"
#include "crossPlatform.hpp"

Game::Game(char *exec)
{
    std::string ex = exec;
    std::size_t last_slash = ex.find_last_of('/');
    if (last_slash == std::string::npos) {
        this->rootPath = ".";
        this->rootPath += '/';
    } else {
        this->rootPath = ex.substr(0, last_slash);
        this->rootPath += '/';
    }
    this->device = irr::createDevice(irr::video::EDT_OPENGL);
    if (!this->device)
        throw std::runtime_error("Can't create device");
    this->environment = this->device->getGUIEnvironment();
    this->driver = this->device->getVideoDriver();
    this->manager = this->device->getSceneManager();
}

void Game::run()
{

}
