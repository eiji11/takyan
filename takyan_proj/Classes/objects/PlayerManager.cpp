//
//  PlayerManager.cpp
//  Takyan
//
//  Created by bibi-apple on 9/3/15.
//
//

#include "PlayerManager.h"
#include "PlayerData.h"

USING_NS_CC;

#define KEY_PLAYERS "players"

#define SAVE_FILE "takyan_file.plist"

PlayerManager *PlayerManager::getInstance()
{
    static PlayerManager *instance;
    if (instance == nullptr) {
        instance = new PlayerManager();
        instance->load();
    }
    return instance;
}

Map<std::string, PlayerData *> PlayerManager::getPlayers()
{
    return _data;
}

bool PlayerManager::load()
{
    std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE;
    ValueMap data = FileUtils::getInstance()->getValueMapFromFile(path);
    
    if (!data.empty())
    {
        ValueMap players;
        if (data.at(KEY_PLAYERS).getType() == Value::Type::MAP)
        {
            players = data.at(KEY_PLAYERS).asValueMap();
        }
        
        for (auto playerPT : players)
        {
            auto playerId = playerPT.first;
            
            ValueMap playerData = playerPT.second.asValueMap();
            
            PlayerData *data = PlayerData::create(playerData);
            _data.insert(playerId, data);
        }
        
        return true;
    }
    else
    {
        std::srand(std::time(nullptr));
        
    	PlayerData *l1 = PlayerData::create();
    	l1->setName("Level 1");
    	l1->setLevel(1);
    	addPlayer(l1);

    	PlayerData *l2 = PlayerData::create();
    	l2->setName("Level 2");
    	l2->setLevel(2);
    	addPlayer(l2);

    	PlayerData *l3 = PlayerData::create();
    	l3->setName("Level 3");
    	l3->setLevel(3);
    	addPlayer(l3);

        return false;
    }
}

bool PlayerManager::removePlayer(std::string key)
{
	return _data.erase(key) == 1;
}

bool PlayerManager::save()
{
    std::string path = FileUtils::getInstance()->getWritablePath() + SAVE_FILE;
    ValueMap d;
    ValueMap ps;
    for (auto it : _data)
    {
        PlayerData *p = it.second;
        ps[it.first] = Value(p->getData());
    }
    d[KEY_PLAYERS] = ps;
    
    return FileUtils::getInstance()->writeToFile(d, path);
}

PlayerData *PlayerManager::loadPlayer(std::string playerId)
{
    PlayerData *player = _data.at(playerId);
    player->retain();
    return player;
}

bool PlayerManager::hasPlayer(std::string playerId)
{
    return _data.find(playerId) != _data.end();
}

bool PlayerManager::addPlayer(PlayerData *player)
{
    cocos2d::log("ADDING: %s || %s", player->getName().c_str(), player->getID().c_str());
    if (!hasPlayer(player->getID())) {
        _data.insert(player->getID(), player);
        cocos2d::log("ADDED: %s", player->getName().c_str());
        return true;
    }
    
    return false;
}
