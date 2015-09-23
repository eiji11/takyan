/*
 * VersusGameBuilder.h
 *
 *  Created on: Mar 18, 2015
 *      Author: mac-user1
 */

#ifndef VERSUSGAMECONFIG_H_
#define VERSUSGAMECONFIG_H_

#include "cocos2d.h"

#include "Defines.h"

#include "PlayerData.h"


class VersusGameConfig : public cocos2d::Ref {
public:
	static VersusGameConfig *create();
	VersusGameConfig();

    PlayerData* getPlayer1();
	void setPlayer1(PlayerData* player1);
	PlayerData* getPlayer2();
	void setPlayer2(PlayerData* player2);
    
    int getHighestLevel();

	int getHitsPerRound() const;
	void setHitsPerRound(int hitsPerRound);

	int getSets() const;
	void setSets(int sets);
	std::string getBackground() const;
	void setBackground(std::string background);

private:
	PlayerData* _player1;
	PlayerData* _player2;

	std::string _background;
	int _sets;
	int _hitsPerRound;

};

#endif /* VERSUSGAMEBUILDER_H_ */
