#ifndef __Takyan__RecordsDialog__
#define __Takyan__RecordsDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/PlayerData.h"
#include "objects/PlayerManager.h"

#include "managers_caches/UILockManager.h"


class RecordsDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
, public cocos2d::extension::TableViewDataSource
{
public:
	CREATE_FUNC(RecordsDialog);
	static RecordsDialog* createFromCCB();

	RecordsDialog();
	virtual ~RecordsDialog();

	virtual void onEnter();
	virtual void onExit();


private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    virtual cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) ;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
	CREATE_HANDLER(onPressOk);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);

    void loadPlayers();

private:
	cocos2d::Node *_containerRecordsTable;
	cocos2d::Label *_labelTitle;
	cocos2d::extension::ControlButton *_buttonOk;
    
    cocos2d::extension::TableView *_tableView;
    
    cocos2d::Vector<PlayerData *> _players;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(RecordsDialog, spritebuilder::LayerLoader);


#endif /* defined(__Takyan__RecordsDialog__) */
