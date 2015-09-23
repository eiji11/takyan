#ifndef __TakyanBattle__PlayerSelect__
#define __TakyanBattle__PlayerSelect__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/VersusGameConfig.h"
#include "objects/SingleGameData.h"

#include "managers_caches/UILockManager.h"


class PlayerSelect : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener

, public cocos2d::extension::TableViewDataSource
, public cocos2d::extension::TableViewDelegate
{
public:
	CREATE_FUNC(PlayerSelect);
	static PlayerSelect* createFromCCB();

	PlayerSelect();
	virtual ~PlayerSelect();

	virtual void onEnter();
	virtual void onExit();

    VersusGameConfig* getConfig()
    {
        return _versusConfig;
    }
    
    void setVersusGameConfig(VersusGameConfig* config)
    {
        _versusConfig = config;
        
        if (_versusConfig != nullptr)
        {
            _versusConfig->retain();
        }
    }
    
    bool isForVersus()
    {
        return _versusConfig != nullptr;
    }
    
    void setForVersus(bool versus)
    {
        if (versus)
        {
            setVersusGameConfig(VersusGameConfig::create());
        }
        else
        {
            setVersusGameConfig(nullptr);
        }
    }
    
    bool isForPractice()
    {
        return _forPractice;
    }
    
    void setForPractice(bool practice)
    {
        _forPractice = practice;
    }
    
    
protected:
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
    virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) ;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    

private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressNew);
	CREATE_HANDLER(onPressOk);
	CREATE_HANDLER(onPressBack);
	CREATE_HANDLER(onPressHome);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);

    void loadPlayers();

private:
	cocos2d::Label *_labelTitle;
	cocos2d::Node *_containerPlayerSelectTable;
	cocos2d::extension::ControlButton *_buttonNew;
	cocos2d::extension::ControlButton *_buttonOk;
	cocos2d::extension::ControlButton *_buttonBack;
	cocos2d::extension::ControlButton *_buttonHome;
    
    cocos2d::extension::TableView *_tableView;
    
    cocos2d::Vector<PlayerData *> _players;
    PlayerData *_selectedPlayer;
    
    VersusGameConfig *_versusConfig;
    
    bool _forPractice;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);
    
};

CREATE_CLASS_LOADER(PlayerSelect, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__PlayerSelect__) */
