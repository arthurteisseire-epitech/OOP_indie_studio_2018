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
    state(FIND_BLOCKBREACKABLE),
    prevDir(NORTH),
    deltaTime(0)
{
    alterStateMap = {
        {DODGE,                [this]() { alterDodge(); }},
        {MOVE_TO_PLAYER,       [this]() { alterMoveToPlayer(); }},
        {FIND_BLOCKBREACKABLE, [this]() { alterFindBlockBreakable(); }},
        {PLACE_BOMB,           [this]() { alterPlaceBomb(); }},
        {PICK_POWERUP,         [this]() { alterPickPowerUp(); }},
    };

    actionStateMap = {
        {DODGE,                [this]() { actionDodge(); }},
        {MOVE_TO_PLAYER,       [this]() { actionMoveToPlayer(); }},
        {FIND_BLOCKBREACKABLE, [this]() { actionFindBlockBreakable(); }},
        {PLACE_BOMB,           [this]() { actionPlaceBomb(); }},
        {PICK_POWERUP,         [this]() { actionPickPowerUp(); }},
    };
}

void ind::AIBehaviour::update(float dt)
{
    deltaTime = dt;
    player.disableWallPass();
    player.checkDeath();

    if (!AIUtils::contain(board.getAllExplosionsPositions(),
                          AIUtils::getPositionsAroundWalkable(board, player.getPosition()))) {
        action();
    } else {
        stopWalking();
    }
}

void ind::AIBehaviour::action()
{
    execFromMap(alterStateMap);
    execFromMap(actionStateMap);
}

void ind::AIBehaviour::execFromMap(const std::map<State, std::function<void()>> &map)
{
    for (auto &pair : map)
        if (pair.first == state) {
            pair.second();
            break;
        }
}

void ind::AIBehaviour::alterDodge()
{
    auto positionsWithoutExplosions = AIUtils::getPositionsAroundWithoutFutureExplosion(board, player.getPosition());
    auto positionsWalkable = AIUtils::getPositionsAroundWalkable(board, player.getPosition());

    if (!AIUtils::isOnFutureExplosion(board, player.getPosition())) {
        if (positionsWalkable.size() == positionsWithoutExplosions.size())
            state = FIND_BLOCKBREACKABLE;
    }
}

void ind::AIBehaviour::alterMoveToPlayer()
{
    auto posToTarget = AIUtils::findNearestPlayerPositions(board, player.getPosition());
    if (AIUtils::isOnFutureExplosion(board, player.getPosition()))
        state = DODGE;
    else if (posToTarget.size() < 3)
        state = PLACE_BOMB;
}

void ind::AIBehaviour::alterFindBlockBreakable()
{
    auto posToTarget = AIUtils::findNearestPlayerPositions(board, player.getPosition());

    if (AIUtils::isOnFutureExplosion(board, player.getPosition()))
        state = DODGE;
    else if (AIUtils::isBlockBreakableAround(board, player.getPosition()))
        state = PLACE_BOMB;
    else if (AIUtils::findAvailablePowerUpAround(board, player.getPosition()) != player.getPosition())
        state = PICK_POWERUP;
    else if (!posToTarget.empty())
        state = MOVE_TO_PLAYER;
}

void ind::AIBehaviour::alterPlaceBomb()
{
    if (AIUtils::isOnFutureExplosion(board, player.getPosition()))
        state = DODGE;
}

void ind::AIBehaviour::alterPickPowerUp()
{
    if (AIUtils::findAvailablePowerUpAround(board, player.getPosition()) == player.getPosition())
        state = FIND_BLOCKBREACKABLE;
}

void ind::AIBehaviour::actionDodge()
{
    if (!AIUtils::isOnFutureExplosion(board, player.getPosition())) {
        stopWalking();
        return;
    }
    const Position &pos = AIUtils::findAvailablePositionAround(board, player.getPosition());
    if (player.getPosition() != pos)
        move(AIUtils::posToDir(player.getPosition(), pos));
    else
        stopWalking();
}

void ind::AIBehaviour::actionMoveToPlayer()
{
    auto posToTarget = AIUtils::findNearestPlayerPositions(board, player.getPosition());

    if (posToTarget.size() > 2)
        move(AIUtils::posToDir(player.getPosition(), posToTarget.at(1)));
}

void ind::AIBehaviour::actionFindBlockBreakable()
{
    auto positions = AIUtils::findBlockBreakable(board, player.getPosition());

    if (!positions.empty())
        move(AIUtils::posToDir(player.getPosition(), positions.at(0)));
}

void ind::AIBehaviour::actionPlaceBomb()
{
    player.placeBomb();
}

void ind::AIBehaviour::actionPickPowerUp()
{
    auto pos = AIUtils::findAvailablePowerUpAround(board, player.getPosition());
    auto positions = SingleTon<PathfindingService>::getInstance().searchPath(board, player.getPosition(), pos);

    if (positions.size() > 1)
        move(AIUtils::posToDir(player.getPosition(), positions.at(1)));
    else
        stopWalking();
}

void ind::AIBehaviour::move(Orientation dir)
{
    player.updateForce(dir, deltaTime, player.getSpeed());
    if (to2d(player.nextPos()) == to2d(player.getAnimator().getPosition()) && !isTurnAround(dir))
        dir = prevDir;
    if (player.getAction() != Actions::Walking) {
        player.getAnimator().setCurrentAnimation("walk").playAnimation();
        player.setAction(Actions::Walking);
    }
    player.setDirection(dir);
    player.getAnimator().setAnimationsRotation(DirectionMap::directionAngles.at(dir));
    player.updateForce(dir, deltaTime, player.getSpeed());
    player.draw();
    prevDir = dir;
}

void ind::AIBehaviour::stopWalking()
{
    if (player.getAction() == ind::Walking) {
        player.getAnimator().setCurrentAnimation("idle").playAnimation();
        player.setAction(ind::Down);
    }
}

bool ind::AIBehaviour::isTurnAround(ind::Orientation orientation)
{
    return (prevDir == NORTH && orientation == SOUTH) ||
           (prevDir == SOUTH && orientation == NORTH) ||
           (prevDir == WEST && orientation == EAST) ||
           (prevDir == EAST && orientation == WEST);
}
