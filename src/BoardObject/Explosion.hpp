/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** Explosion.hpp
*/

#ifndef BOMBERMAN_EXPLOSION_HPP
#define BOMBERMAN_EXPLOSION_HPP

#include "BoardObject.hpp"
#include "TimeoutObject.hpp"

namespace ind {
    class Explosion : public BoardObject, public TimeoutObject {
    public:
        explicit Explosion(Position position);
        ~Explosion() override;
        Tile getTile() const override;

        private:
            irr::scene::IParticleSystemSceneNode *particleSystem = nullptr;
    };
}

#endif
