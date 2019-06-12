/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** SpeedUp.hpp
*/

#ifndef BOMBERMAN_SPEEDUP_HPP
#define BOMBERMAN_SPEEDUP_HPP

#include "PowerUp.hpp"

namespace ind {
    class SpeedUp : public PowerUp {
    public:
        explicit SpeedUp(ind::Position position);
        ~SpeedUp() override = default;
        void upgrade(Player &player) override;
    };
}

#endif