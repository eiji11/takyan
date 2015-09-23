/*
 * VersusGameBuilder.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: mac-user1
 */

#include "VersusGameConfig.h"

USING_NS_CC;


VersusGameConfig *VersusGameConfig::create()
{
	VersusGameConfig *retVal = new VersusGameConfig();

	retVal->autorelease();

	return retVal;
}

VersusGameConfig::VersusGameConfig() : Ref()
, _player1(NULL)
, _player2(NULL)
, _background()
, _sets(3)
, _hitsPerRound(3)
{
    
}

int VersusGameConfig::getHitsPerRound() const {
	return _hitsPerRound;
}

void VersusGameConfig::setHitsPerRound(int hitsPerRound) {
	_hitsPerRound = hitsPerRound;
}

PlayerData* VersusGameConfig::getPlayer1() {
	return _player1;
}

void VersusGameConfig::setPlayer1(PlayerData* player1) {
	_player1 = player1;
    
    CC_SAFE_RETAIN(_player1);
}

PlayerData* VersusGameConfig::getPlayer2() {
	return _player2;
}

void VersusGameConfig::setPlayer2(PlayerData* player2)
{
    _player2 = player2;
    CC_SAFE_RETAIN(_player2);
}

int VersusGameConfig::getHighestLevel()
{
    return MAX(_player1->getLevel(), _player2->getLevel());
}

int VersusGameConfig::getSets() const {
	return _sets;
}

void VersusGameConfig::setSets(int sets) {
	_sets = sets;
}

std::string VersusGameConfig::getBackground() const {
	return _background;
}

void VersusGameConfig::setBackground(std::string background) {
	_background = background;
}
