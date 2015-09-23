#ifndef __Takyan__InstructionsDialog__
#define __Takyan__InstructionsDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class InstructionsDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(InstructionsDialog);
	static InstructionsDialog* createFromCCB();

	InstructionsDialog();
	virtual ~InstructionsDialog();

	virtual void onEnter();
	virtual void onExit();


private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressOk);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Label *_labelTitle;
	cocos2d::extension::ControlButton *_buttonOk;
	cocos2d::extension::ScrollView *_scrollView;

	MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
	MAKE_LOCK_LEVEL(2);
};

CREATE_CLASS_LOADER(InstructionsDialog, spritebuilder::LayerLoader);


#endif /* defined(__Takyan__InstructionsDialog__) */
