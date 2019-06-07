/*
** EPITECH PROJECT, 2018
** bomberman
** File description:
** AiBehaviour.cpp
*/

#include "to2d.hpp"
#include "DirectionMap.hpp"
#include "PathfindingService.hpp"
#include "Singleton.hpp"
#include "AIBehaviour.hpp"

ind::AIBehaviour::AIBehaviour(ind::Player &player, Board &board) :
    player(player),
    board(board),
    prevDir(Up)
{
}

void ind::AIBehaviour::update(float deltaTime)
{
    player.checkDeath();
    const Position &targetPos = board.getPlayers()[0]->getPosition();
    auto posToTarget = SingleTon<PathfindingService>::getInstance().searchPath(board, player.getPosition(), targetPos);

    if (!posToTarget.empty() && !contain(board.getAllExplosionsPositions(), getPositionsAroundWalkable())) {
        moveToPlayerOne(deltaTime, posToTarget);
    } else {
        if (player.getAction() == Actions::Walking) {
            player.getAnimator().setCurrentAnimation("idle").playAnimation();
            player.setAction(Actions::Down);
        }
    }
}

void ind::AIBehaviour::moveToPlayerOne(float deltaTime, std::vector<ind::Position> &posToTarget)
{
    if (isOnFutureExplosion(player.getPosition()))
        dodgeExplosions(deltaTime);
    else if (posToTarget.size() > 2)
        move(deltaTime, posToDir(posToTarget.at(1)));
}

void ind::AIBehaviour::dodgeExplosions(float deltaTime)
{
    std::vector<Position> pos = getPositionsAroundWithoutExplosion();

    if (!pos.empty())
        move(deltaTime, posToDir(pos.at(0)));
}

void ind::AIBehaviour::move(float deltaTime, Actions direction)
{
    Actions &dir = direction;

    player.updateForce(ind::DirectionMap::keyDirections.at(dir), deltaTime, player.getSpeed());
    if (to2d(player.nextPos()) == to2d(player.getAnimator().getPosition()))
        dir = prevDir;
    if (player.getAction() != Actions::Walking) {
        player.getAnimator().setCurrentAnimation("walk").playAnimation();
        player.setAction(Actions::Walking);
    }
    player.setDirection(DirectionMap::keyDirections.at(dir));
    player.getAnimator().setAnimationsRotation(DirectionMap::directionAngles.at(DirectionMap::keyDirections.at(dir)));
    player.updateForce(DirectionMap::keyDirections.at(dir), deltaTime, player.getSpeed());
    player.draw();
    prevDir = dir;
}

std::vector<ind::Position> ind::AIBehaviour::getAllFutureExplosionsPositions() const
{
    auto bombs = board.getAllBombs();
    std::vector<Position> positions;

    for (const auto &bomb : bombs) {
        auto row = bomb->getExplosionsPositions();
        positions.insert(positions.end(), row.begin(), row.end());
    }
    return positions;
}

std::vector<ind::Position> ind::AIBehaviour::getPositionsAroundWalkable() const
{
    const auto &pos = player.getPosition();
    std::vector<Position> positions;

    addPosIfWalkable(positions, pos.x + 1, pos.y);
    addPosIfWalkable(positions, pos.x - 1, pos.y);
    addPosIfWalkable(positions, pos.x, pos.y + 1);
    addPosIfWalkable(positions, pos.x, pos.y - 1);
    addPosIfWalkable(positions, pos.x + 1, pos.y + 1);
    addPosIfWalkable(positions, pos.x - 1, pos.y - 1);
    addPosIfWalkable(positions, pos.x + 1, pos.y - 1);
    addPosIfWalkable(positions, pos.x - 1, pos.y + 1);
    return positions;
}

void ind::AIBehaviour::addPosIfWalkable(std::vector<ind::Position> &positions, int x, int y) const
{
    if (!board.in(Position(x, y)))
        return;

    const auto &type = board.getInfoAtCoord(x, y);

    if (type != BLOCKBREAKABLE && type != WALL && type != BOMB)
        positions.emplace_back(x, y);
}

ind::Actions ind::AIBehaviour::posToDir(const ind::Position &pos) const
{
    const auto &playerPos = player.getPosition();

    if (pos.y > playerPos.y)
        return Left;
    else if (pos.y < playerPos.y)
        return Right;
    if (pos.x > playerPos.x)
        return Up;
    else if (pos.x < playerPos.x)
        return Down;
    return Up;
}

bool ind::AIBehaviour::contain(const std::vector<ind::Position> &pos1, const std::vector<ind::Position> &pos2) const
{
    for (auto &i : pos1)
        for (auto &j : pos2)
            if (i == j)
                return true;
    return false;
}

std::vector<ind::Position> ind::AIBehaviour::getPositionsAroundWithoutExplosion() const
{
    std::vector<Position> positions;
    auto positionsAround = getPositionsAroundWalkable();
    auto futureExplosions = getAllFutureExplosionsPositions();

    for (auto &pos : positionsAround)
        if (std::find(futureExplosions.begin(), futureExplosions.end(), pos) == futureExplosions.end())
            positions.push_back(pos);
    return positions;
}

bool ind::AIBehaviour::isOnFutureExplosion(const ind::Position &pos) const
{
    auto futureExplosions = getAllFutureExplosionsPositions();
    auto it = std::find(futureExplosions.begin(), futureExplosions.end(), pos);

    return it != futureExplosions.end();
}
