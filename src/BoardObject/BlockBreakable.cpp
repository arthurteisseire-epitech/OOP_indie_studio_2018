/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** BlockBreakable.cpp
*/

#include "BlockBreakable.hpp"
#include "Ground.hpp"

ind::BlockBreakable::BlockBreakable(Position position) :
    BoardObject(position, "assets/wood.png")
{
    createGraphicalCube();
}

ind::Tile ind::BlockBreakable::getTile() const
{
    return BLOCKBREAKABLE;
}

std::string ind::BlockBreakable::toString() const
{
    return BoardObject::toString() + BLOCKBREAKABLE_NAME;
}
