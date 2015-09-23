//
//  GameData.h
//  Takyan
//
//  Created by bibi-apple on 8/3/15.
//
//

#ifndef __Takyan__GameData__
#define __Takyan__GameData__

#include "cocos2d.h"

#include "Defines.h"

#include "GameData.h"

class SingleGameData : public GameData
{
public:
    static SingleGameData* create(PlayerData* player);
    SingleGameData();
    
    std::string getBackground();
    void setBackground(std::string background);
    
    bool isPracticeMode();
    void setPracticeMode(bool practiceMode);
    
    virtual void setPlayer(PlayerData *player);
    
    int getPreviousLevel()
    {
        return _previousLevel;
    }
    
protected:
    std::string _background;
    bool _isPracticeMode;
    int _previousLevel;
};

#endif /* defined(__Takyan__GameData__) */
