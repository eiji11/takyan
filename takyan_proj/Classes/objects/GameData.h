/*
 * GameData.h
 *
 *  Created on: Mar 18, 2015
 *      Author: mac-user1
 */

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include "cocos2d.h"

#include "Defines.h"

#include "PlayerData.h"

class GameData: public cocos2d::Ref {
public:
	static GameData* create(PlayerData* player);
	GameData();

    int getHits();
    void setHits(int hits);
    void addHits(int value = 1);

    int getScore();
    void setScore(int score);
    void addScore(int value);

    bool isOver();
    void setOver(bool over);

    PlayerData *getPlayer();
    virtual void setPlayer(PlayerData *player);

protected:
    int _hits;
    int _score;
    bool _isOver;

    PlayerData *_player;
};

#endif /* GAMEDATA_H_ */
