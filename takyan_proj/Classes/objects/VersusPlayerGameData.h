//
//  VersusPlayerGameData.h
//  Takyan
//
//  Created by bibi-apple on 23/3/15.
//
//

#ifndef __Takyan__VersusPlayerGameData__
#define __Takyan__VersusPlayerGameData__

#include "cocos2d.h"

#include "GameData.h"

class VersusPlayerGameData : public GameData
{
public:
    static VersusPlayerGameData* create(PlayerData* player);
    VersusPlayerGameData();
    
    int getHitsForRound()
    {
        return _hitsForRound;
    }
    
    void setHitsForRound(int hits)
    {
        _hitsForRound = hits;
    }
    
    void addHitsForRound(int hit)
    {
        setHitsForRound(_hitsForRound + hit);
    }
    
    int getSetsWon()
    {
        return _setsWon;
    }
    
    void setSetsWon(int setsWon)
    {
        _setsWon = setsWon;
    }
    
    void addSetsWon(int value)
    {
        setSetsWon(getSetsWon() + value);
    }
    
private:
    int _hitsForRound;
    int _setsWon;
};

#endif /* defined(__Takyan__VersusPlayerGameData__) */
