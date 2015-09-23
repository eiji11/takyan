//
//  VersusGameData.cpp
//  Takyan
//
//  Created by bibi-apple on 16/3/15.
//
//

#include "VersusGameData.h"

USING_NS_CC;


VersusGameData* VersusGameData::create(VersusGameConfig *config)
{
    VersusGameData *retVal = new VersusGameData();
    retVal->init(config);
    retVal->autorelease();
    
    return retVal;
}

VersusGameData::VersusGameData() : Ref()
, _background()
, _currentPlayerIndex(0)
, _sets(1)
, _hitsPerRound(3)
, _currentSet(0)
, _currentHitsForRound(0)
, _isGameOver(false)
, _game1(nullptr)
, _game2(nullptr)
{
    
}

bool VersusGameData::init(VersusGameConfig *config)
{
    setBackground(config->getBackground());
    setSets(config->getSets());
    setHitsPerRound(config->getHitsPerRound());
    
    registerPlayers(config->getPlayer1(), config->getPlayer2());
    
    return true;
}

void VersusGameData::registerPlayers(PlayerData *first, PlayerData *second)
{
    _game1 = VersusPlayerGameData::create(first);
    _game2 = VersusPlayerGameData::create(second);
}

VersusPlayerGameData* VersusGameData::getGame1() {
    return _game1;
}

VersusPlayerGameData* VersusGameData::getGame2() {
    return _game2;
}

VersusPlayerGameData* VersusGameData::getGame(int index)
{
    return index == PLAYER_1_INDEX ? getGame1() : getGame2();
}

VersusPlayerGameData* VersusGameData::getCurrentGame()
{
    return getGame(getCurrentPlayerIndex());
}

std::string VersusGameData::getBackground() const {
	return _background;
}

void VersusGameData::setBackground(std::string background) {
	_background = background;
}

int VersusGameData::getCurrentHitsForRound() const {
	return _currentHitsForRound;
}

void VersusGameData::setCurrentHitsForRound(int currentHitsForRound) {
	_currentHitsForRound = currentHitsForRound;
}

void VersusGameData::increaseCurrentHitsForRound(int value)
{
    setCurrentHitsForRound(_currentHitsForRound + value);
}

int VersusGameData::getCurrentSet() const {
    return _currentSet;
}

void VersusGameData::setCurrentSet(int currentSet) {
    _currentSet = currentSet;
}

void VersusGameData::increaseCurrentSet(int value)
{
    setCurrentSet(getCurrentSet() + value);
}

int VersusGameData::getHitsPerRound() const {
	return _hitsPerRound;
}

void VersusGameData::setHitsPerRound(int hitsPerRound) {
	_hitsPerRound = hitsPerRound;
}

int VersusGameData::getSets() const {
	return _sets;
}

void VersusGameData::setSets(int sets) {
	_sets = sets;
}

int VersusGameData::getCurrentPlayerIndex() const {
	return _currentPlayerIndex;
}

void VersusGameData::setCurrentPlayerIndex(int currentPlayerIndex) {
	_currentPlayerIndex = currentPlayerIndex;
}

bool VersusGameData::isGameOver()
{
    return _isGameOver;
}

void VersusGameData::setGameOver(bool isGameOver)
{
    _isGameOver = isGameOver;
}
