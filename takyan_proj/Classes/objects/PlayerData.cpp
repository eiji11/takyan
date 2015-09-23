//
//  PlayerData.cpp
//  Takyan
//
//  Created by bibi-apple on 9/3/15.
//
//

#include "PlayerData.h"

#include "Defines.h"

#include "managers_caches/AssortedUtils.h"

USING_NS_CC;


#define KEY_ID "id"
#define KEY_LEVEL "level"
#define KEY_NAME "name"
#define KEY_GENDER "gender"
#define KEY_MAX_HITS "max_hits"
#define KEY_HIGH_SCORE "high_score"
#define KEY_POINTS "points"
#define KEY_PLAYS "plays"
#define KEY_WINS "wins"
#define KEY_LOSSES "losses"
#define KEY_CONSECUTIVE_WINS "consecutive_wins"

PlayerData *PlayerData::create()
{
    ValueMap data;
    data[KEY_ID] = AssortedUtils::getRandomString(8);
    data[KEY_LEVEL] = 0;
    data[KEY_NAME] = "Player";
    data[KEY_GENDER] = GENDER_MALE;
    data[KEY_MAX_HITS] = 0;
    data[KEY_HIGH_SCORE] = 0;
    data[KEY_POINTS] = 0;
    
    return create(data);
}

PlayerData *PlayerData::create(cocos2d::ValueMap data)
{
    PlayerData *retVal = new PlayerData();
    if (retVal->init(data)) {
        retVal->autorelease();
        return retVal;
    }
    
    delete retVal;
    retVal = NULL;
    return NULL;
}

bool PlayerData::init(cocos2d::ValueMap data)
{
    this->setData(data);
    
    return true;
}

cocos2d::ValueMap PlayerData::getData()
{
    return _data;
}

void PlayerData::setData(cocos2d::ValueMap data)
{
    _data = data;
}

std::string PlayerData::getID()
{
    return _data.at(KEY_ID).asString();
}

void PlayerData::setID(std::string pID)
{
    _data[KEY_ID] = pID;
}

int PlayerData::getLevel()
{
    return _data.at(KEY_LEVEL).asInt();
}

void PlayerData::setLevel(int level)
{
    _data[KEY_LEVEL] = level;
}

std::string PlayerData::getName()
{
    return _data[KEY_NAME].asString();
}

void PlayerData::setName(std::string name)
{
    _data[KEY_NAME] = name;
}

int PlayerData::getGender()
{
    return _data[KEY_GENDER].asInt();
}

void PlayerData::setGender(int gender)
{
    _data[KEY_GENDER] = gender;
}

int PlayerData::getMaxHits()
{
    return _data[KEY_MAX_HITS].asInt();
}

void PlayerData::setMaxHits(int maxHits)
{
    _data[KEY_MAX_HITS] = maxHits;
}

int PlayerData::getHighScore()
{
    return _data[KEY_HIGH_SCORE].asInt();
}

void PlayerData::setHighScore(int highScore)
{
    _data[KEY_HIGH_SCORE] = highScore;
}

int PlayerData::getPoints()
{
    return _data[KEY_POINTS].asInt();
}

void PlayerData::setPoints(int points)
{
    _data[KEY_POINTS] = MIN(4, MAX(0, points));
}

int PlayerData::getPlays()
{
    return _data[KEY_PLAYS].asInt();
}

void PlayerData::setPlays(int plays)
{
    _data[KEY_PLAYS] = plays;
}

void PlayerData::addPlays(int value)
{
    setPlays(getPlays() + value);
}

int PlayerData::getWins()
{
    return _data[KEY_WINS].asInt();
}

void PlayerData::setWins(int wins)
{
    _data[KEY_WINS] = wins;
}

void PlayerData::addWins(int value)
{
    setWins(getWins() + value);
}

int PlayerData::getLosses()
{
    return _data[KEY_LOSSES].asInt();
}

void PlayerData::setLosses(int losses)
{
    _data[KEY_LOSSES] = losses;
}

void PlayerData::addLosses(int value)
{
    setLosses(getLosses() + value);
}
int PlayerData::getConsecutiveWins()
{
    return _data[KEY_CONSECUTIVE_WINS].asInt();
}

void PlayerData::setConsecutiveWins(int cWins)
{
    _data[KEY_CONSECUTIVE_WINS] = cWins;
}

void PlayerData::addConsecutiveWins(int value)
{
    setConsecutiveWins(getConsecutiveWins() + value);
}

void PlayerData::reset()
{
    this->setLevel(0);
    this->setMaxHits(0);
    this->setHighScore(0);
    this->setName("Player");
    this->setGender(0);
    this->setPoints(0);
    this->setPlays(0);
    this->setWins(0);
    this->setLosses(0);
}
