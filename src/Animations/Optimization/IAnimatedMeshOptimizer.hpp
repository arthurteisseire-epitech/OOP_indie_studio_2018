/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Created by Taz
*/

namespace ind {
    namespace animations {
        namespace optimization {
            class IAnimatedMeshOptimizer
            {
                public:
                    virtual void serialize() = 0;
                    virtual void deserialize() = 0;
            };
        }
    }
}