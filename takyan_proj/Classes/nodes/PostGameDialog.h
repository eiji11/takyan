#ifndef __Cleaning__PostGameDialog__
#define __Cleaning__PostGameDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/SingleGameData.h"

#include "managers_caches/UILockManager.h"


class PostGameDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PostGameDialog);
	static PostGameDialog* createFromCCB();

	PostGameDialog();
	virtual ~PostGameDialog();

	virtual void onEnter();
	virtual void onExit();

    SingleGameData* getGameData();
    void setGameData(SingleGameData* game);

private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    CREATE_HANDLER(onPressRestart);
    CREATE_HANDLER(onPressHome);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::Label *_titleName;
    cocos2d::Label *_labelHits;
    cocos2d::Label *_labelScore;
    cocos2d::Label *_labelRewards;
    
    cocos2d::extension::ControlButton *_buttonRestart;
    cocos2d::extension::ControlButton *_buttonHome;
    
    SingleGameData *m_game;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(PostGameDialog, spritebuilder::LayerLoader);


#endif /* defined(__Cleaning__PostGameDialog__) */
