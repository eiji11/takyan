//
//  VersusGameData.h
//  Takyan
//
//  Created by bibi-apple on 16/3/15.
//
//

#ifndef __Takyan__VersusGameData__
#define __Takyan__VersusGameData__

#include "cocos2d.h"

#include "Defines.h"

#include "VersusGameConfig.h"
#include "VersusPlayerGameData.h"

class VersusGameData : public cocos2d::Ref
{
public:
	static VersusGameData *create(VersusGameConfig *config);
	VersusGameData();

    VersusPlayerGameData* getGame1();
	VersusPlayerGameData* getGame2();
    
    VersusPlayerGameData* getGame(int index);
    VersusPlayerGameData* getCurrentGame();

	std::string getBackground() const;
	void setBackground(std::string background);

	int getCurrentPlayerIndex() const;
	void setCurrentPlayerIndex(int currentPlayerIndex);

	int getHitsPerRound() const;
	void setHitsPerRound(int hitsPerRound);

	int getSets() const;
	void setSets(int sets);

	int getCurrentHitsForRound() const;
	void setCurrentHitsForRound(int currentHitsForRound);
    void increaseCurrentHitsForRound(int value = 1);

	int getCurrentSet() const;
	void setCurrentSet(int currentSet);
    void increaseCurrentSet(int value = 1);
    
    bool isGameOver();
    void setGameOver(bool isGameOver);

private:
    bool init(VersusGameConfig* config);
    void registerPlayers(PlayerData* first, PlayerData* second);

protected:
    std::string _background;
    int _currentPlayerIndex;
    int _sets;
    int _hitsPerRound;
    int _currentSet;
    int _currentHitsForRound;
    bool _isGameOver;

	VersusPlayerGameData *_game1;
	VersusPlayerGameData *_game2;

};

#endif /* defined(__Takyan__VersusGameData__) */
