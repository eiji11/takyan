#ifndef __Takyan__TriviaDialog__
#define __Takyan__TriviaDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class TriviaDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
    static bool shown;
	CREATE_FUNC(TriviaDialog);
	static TriviaDialog* createFromCCB();

	TriviaDialog();
	virtual ~TriviaDialog();

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
	cocos2d::extension::ScrollView *_scrollView;
	cocos2d::Label *_labelTitle;
	cocos2d::extension::ControlButton *_buttonOk;
    
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(TriviaDialog, spritebuilder::LayerLoader);


#endif /* defined(__Takyan__TriviaDialog__) */
