//
//  PlayerManager.h
//  Takyan
//
//  Created by bibi-apple on 9/3/15.
//
//

#ifndef __Takyan__PlayerManager__
#define __Takyan__PlayerManager__

#include "cocos2d.h"

class PlayerData;

class PlayerManager
{
public:
    static PlayerManager *getInstance();
    
    cocos2d::Map<std::string, PlayerData *> getPlayers();
    
    bool load();
    
    bool save();
    
    PlayerData *loadPlayer(std::string playerId);
    bool hasPlayer(std::string playerId);
    
    bool addPlayer(PlayerData *player);
    bool removePlayer(std::string key);
    
private:
    cocos2d::Map<std::string, PlayerData *> _data;
};

#endif /* defined(__Takyan__PlayerManager__) */
