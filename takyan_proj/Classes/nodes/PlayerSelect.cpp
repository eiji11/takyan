#include "PlayerSelect.h"

#include "objects/PlayerManager.h"
#include "objects/PlayerData.h"

#include "MainMenuScene.h"
#include "PlayerCreate.h"
#include "PlaceSelect.h"
#include "PlayerSelectEntry.h"

#include "managers_caches/AssortedUtils.h"
#include "managers_caches/ObserverManager.h"


USE_NS

static Size CELL_SIZE(210, 20);

PlayerSelect *PlayerSelect::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PlayerSelect", PlayerSelectLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PlayerSelect*>(ccbReader->readNodeGraphFromFile("PlayerSelect.ccbi"));
}

PlayerSelect::PlayerSelect() : cocos2d::Layer()
, _labelTitle(NULL)
, _containerPlayerSelectTable(NULL)
, _buttonNew(NULL)
, _buttonOk(NULL)
, _buttonBack(NULL)
, _buttonHome(NULL)

, _forPractice(false)
, _versusConfig(nullptr)
{

}

PlayerSelect::~PlayerSelect()
{
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_containerPlayerSelectTable);
	CC_SAFE_RELEASE(_buttonNew);
	CC_SAFE_RELEASE(_buttonOk);
	CC_SAFE_RELEASE(_buttonBack);
	CC_SAFE_RELEASE(_buttonHome);
}

void PlayerSelect::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);

	cocos2d::log("loading players");
    loadPlayers();
	cocos2d::log("loaded players");
    
    OBSERVE(this, EVENT_PLAYERS_RELOAD, [&](EventCustom *event){
        this->loadPlayers();
        _tableView->reloadData();
    });

	cocos2d::log("loading _tableView");
    _tableView = TableView::create(this, _containerPlayerSelectTable->getContentSize());
    _tableView->setDelegate(this);
    
    _containerPlayerSelectTable->addChild(_tableView);
	cocos2d::log("loaded _tableView");

	setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void PlayerSelect::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

	_tableView->setDelegate(nullptr);
	_tableView->setDataSource(nullptr);
    
    UNOBSERVE(this);
    
    UI_LOCK_MANAGER_DECREASE();
}

void PlayerSelect::loadPlayers()
{
    Map<std::string, PlayerData *> playersMap = PlayerManager::getInstance()->getPlayers();
    
    _players.clear();
	cocos2d::log("loadPlayers()");
    
    PlayerData *player1 = nullptr;
    
    std::function<void(PlayerData* player)> insertFunc = [&](PlayerData *player)
    {
    	cocos2d::log("basic insert: %s", player->getName().c_str());
        _players.pushBack(player);
    };

	cocos2d::log("check versus");
    if (isForVersus())
    {
        player1 = _versusConfig->getPlayer1();
        if (player1 != nullptr)
        {
        	cocos2d::log("player1 insert: %s", player1->getName().c_str());
            insertFunc = [&, player1](PlayerData *player)
            {
                if (player != player1) {
                	cocos2d::log("filtered insert: %s", player->getName().c_str());
                    _players.pushBack(player);
                }
            };
        }
    }

	cocos2d::log("looping");
    for (auto itr : playersMap)
    {
    	cocos2d::log("test insert: %s", itr.second->getName().c_str());
        insertFunc(itr.second);
    }
    
    std::sort(_players.begin(), _players.end(), [&](PlayerData *first, PlayerData *second){
    	cocos2d::log("sorting 1: %s - %d", first->getName().c_str(), first->getLevel());
    	cocos2d::log("sorting 2: %s - %d", second->getName().c_str(), second->getLevel());
        return first->getLevel() < second->getLevel();
    });
}

void PlayerSelect::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void PlayerSelect::onPressNew(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        PlayerCreate *d = PlayerCreate::createFromCCB();
        d->setPlayer(PlayerData::create());
        
        this->getScene()->addChild(d, 1000);
	}
}

void PlayerSelect::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        if (_selectedPlayer != nullptr)
        {
            if (isForVersus())
            {
                PlayerData *player1 = _versusConfig->getPlayer1();
                if (player1 == nullptr)
                {
                    _versusConfig->setPlayer1(_selectedPlayer);
                    
                    PlayerSelect *d = PlayerSelect::createFromCCB();
                    d->setVersusGameConfig(_versusConfig);
                    
                    this->removeFromParent();
                    Director::getInstance()->getRunningScene()->addChild(d, 1000);
                }
                else
                {
                    _versusConfig->setPlayer2(_selectedPlayer);
                    
                    PlaceSelect *d = PlaceSelect::createFromCCB();
                    d->setVersusGameConfig(_versusConfig);
                    
                    this->removeFromParent();
                    Director::getInstance()->getRunningScene()->addChild(d, 1000);
                }
            }
            else
            {
                PlaceSelect *d = PlaceSelect::createFromCCB();
                SingleGameData *game = SingleGameData::create(_selectedPlayer);
                game->setPracticeMode(_forPractice);
                d->setSingleGameData(game);
                
                this->removeFromParent();
                Director::getInstance()->getRunningScene()->addChild(d, 1000);
            }
        }
	}
}

void PlayerSelect::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        if (isForVersus())
        {
            PlayerData *player1 = _versusConfig->getPlayer1();
            if (player1 != nullptr)
            {
                _versusConfig->setPlayer1(nullptr);
                PlayerSelect *d = PlayerSelect::createFromCCB();
                d->setVersusGameConfig(_versusConfig);
                
                this->removeFromParent();
                Director::getInstance()->getRunningScene()->addChild(d, 1000);
            }
            else
            {
                this->removeFromParent();
            }
            
        }
        else
        {
            this->removeFromParent();
        }
	}
}

void PlayerSelect::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        this->removeFromParent();
	}
}


#pragma mark - CCTableView methods

void PlayerSelect::tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell)
{
    PlayerSelectEntry *entry = dynamic_cast<PlayerSelectEntry *>(cell->getChildren().front());
    if (entry && !IS_LOCKED)
    {
        PlayerData *player = entry->getPlayer();
        
        EventCustom *event = nullptr;
        
        if (_selectedPlayer == nullptr) {
            _selectedPlayer = player;
            event = new EventCustom(EVENT_PLAYER_SELECTED);
        }
        else if (_selectedPlayer != player)
        {
            _selectedPlayer = player;
            event = new EventCustom(EVENT_PLAYER_SELECTED);
        }
        else
        {
            PlayerCreate *c = PlayerCreate::createFromCCB();
            c->setPlayer(player);
            
            Director::getInstance()->getRunningScene()->addChild(c, 1000);
        }
        
        if (event != nullptr)
        {
            event->setUserData(player);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(event);
        }
    }
}

Size PlayerSelect::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return CELL_SIZE;
}

TableViewCell* PlayerSelect::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    PlayerData *player = _players.at(idx);
    
    TableViewCell *cell = TableViewCell::create();
    
    PlayerSelectEntry *entry = PlayerSelectEntry::createFromCCB();
    
    entry->setPlayer(player);
    
    if (_selectedPlayer == player)
    {
        entry->setSelected(true);
    }
    
    cell->addChild(entry);
    
    return cell;
}

ssize_t PlayerSelect::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return _players.size();
}


#pragma mark - CCBMemberVariableAssigner functions

bool PlayerSelect::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerPlayerSelectTable", cocos2d::Node*, _containerPlayerSelectTable);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonNew", cocos2d::extension::ControlButton*, _buttonNew);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHome", cocos2d::extension::ControlButton*, _buttonHome);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PlayerSelect::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressNew", PlayerSelect::onPressNew);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", PlayerSelect::onPressOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", PlayerSelect::onPressBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", PlayerSelect::onPressHome);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PlayerSelect::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
//    auto children = this->getChildren().front()->getChildren();
//    for (auto child : children)
//    {
//        child->setLocalZOrder(1);
//    }
    
    AssortedUtils::unifyButtonSprites(_buttonNew, "single_player/btn_add.png");
    AssortedUtils::unifyButtonSprites(_buttonOk, "single_player/btn_ok.png");
    AssortedUtils::unifyButtonSprites(_buttonBack, "single_player/btn_back.png");
    AssortedUtils::unifyButtonSprites(_buttonHome, "single_player/btn_home.png");
}


#pragma mark - CCBAnimationManagerDelegate functions

void PlayerSelect::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
    {
	}
	
}


