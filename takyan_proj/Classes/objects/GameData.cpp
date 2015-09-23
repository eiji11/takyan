/*
 * GameData.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: mac-user1
 */

#include "GameData.h"

USING_NS_CC;

GameData* GameData::create(PlayerData* player)
{
    GameData* retVal = new GameData();
    retVal->setPlayer(player);
    retVal->autorelease();
    return retVal;
}

GameData::GameData() : Ref()
, _hits(0)
, _score(0)
, _isOver(false)
, _player(NULL)
{

}

int GameData::getHits()
{
    return _hits;
}

void GameData::setHits(int hits)
{
    _hits = hits;
}

void GameData::addHits(int value)
{
    setHits(_hits + value);
}

int GameData::getScore()
{
    return _score;
}

void GameData::setScore(int score)
{
    _score = score;
}

void GameData::addScore(int value)
{
    setScore(_score + value);
}

bool GameData::isOver()
{
    return _isOver;
}

void GameData::setOver(bool over)
{
    _isOver = over;
}

PlayerData *GameData::getPlayer()
{
    return _player;
}

void GameData::setPlayer(PlayerData *player)
{
    _player = player;
    _player->retain();
}
