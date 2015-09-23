//
//  PlayerData.h
//  Takyan
//
//  Created by bibi-apple on 9/3/15.
//
//

#ifndef __Takyan__PlayerData__
#define __Takyan__PlayerData__

#include "cocos2d.h"


class PlayerData : public cocos2d::Ref
{
public:
    static PlayerData *create();
    static PlayerData* create(cocos2d::ValueMap data);
    
    bool init(cocos2d::ValueMap data);
    
    cocos2d::ValueMap getData();
    void setData(cocos2d::ValueMap data);
    
    std::string getID();
    void setID(std::string pID);
    
    int getLevel();
    void setLevel(int level);
    
    std::string getName();
    void setName(std::string name);
    
    int getGender();
    void setGender(int gender);
    
    int getMaxHits();
    void setMaxHits(int maxHits);
    
    int getHighScore();
    void setHighScore(int highScore);
    
    int getPoints();
    void setPoints(int points);
    
    int getPlays();
    void setPlays(int plays);
    void addPlays(int value);
    
    int getWins();
    void setWins(int wins);
    void addWins(int value);
    
    int getLosses();
    void setLosses(int losses);
    void addLosses(int value);
    
    int getConsecutiveWins();
    void setConsecutiveWins(int cWins);
    void addConsecutiveWins(int value);

    void reset();
    
private:
    cocos2d::ValueMap _data;
    
};

#endif /* defined(__Takyan__PlayerData__) */
