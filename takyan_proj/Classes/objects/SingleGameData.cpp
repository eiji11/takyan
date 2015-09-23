//
//  SingleGameData.cpp
//  Takyan
//
//  Created by bibi-apple on 8/3/15.
//
//

#include "SingleGameData.h"

USING_NS_CC;

SingleGameData* SingleGameData::create(PlayerData* player)
{
    SingleGameData* retVal = new SingleGameData();
    retVal->setPlayer(player);
    retVal->autorelease();
    return retVal;
}

SingleGameData::SingleGameData() : GameData()
, _background()
, _isPracticeMode(false)
{
    
}

std::string SingleGameData::getBackground()
{
    return _background;
}

void SingleGameData::setBackground(std::string background)
{
    _background = background;
}

bool SingleGameData::isPracticeMode()
{
    return _isPracticeMode;
}

void SingleGameData::setPracticeMode(bool practiceMode)
{
    _isPracticeMode = practiceMode;
}

void SingleGameData::setPlayer(PlayerData *player)
{
    GameData::setPlayer(player);
    
    _previousLevel = player->getLevel();
}
