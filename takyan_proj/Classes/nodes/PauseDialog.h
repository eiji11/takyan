#ifndef __TakyanBattle__PauseDialog__
#define __TakyanBattle__PauseDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class PauseDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PauseDialog);
	static PauseDialog* createFromCCB();

	PauseDialog();
	virtual ~PauseDialog();

	virtual void onEnter();
	virtual void onExit();


private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressRestart);
	CREATE_HANDLER(onPressPlay);
	CREATE_HANDLER(onPressHome);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Label *_labelTitle;
	cocos2d::extension::ControlButton *_buttonRestart;
	cocos2d::extension::ControlButton *_buttonPlay;
	cocos2d::extension::ControlButton *_buttonHome;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(PauseDialog, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__PauseDialog__) */
