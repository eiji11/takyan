//
//  VersusPlayerGameData.cpp
//  Takyan
//
//  Created by bibi-apple on 23/3/15.
//
//

#include "VersusPlayerGameData.h"

VersusPlayerGameData *VersusPlayerGameData::create(PlayerData *player)
{
    VersusPlayerGameData* retVal = new VersusPlayerGameData();
    retVal->setPlayer(player);
    retVal->autorelease();
    return retVal;
}


VersusPlayerGameData::VersusPlayerGameData() : GameData()
, _hitsForRound(0)
, _setsWon(0)
{
    
}
