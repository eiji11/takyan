#ifndef __Takyan__FirstDialog__
#define __Takyan__FirstDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/VersusGameData.h"
#include "managers_caches/UILockManager.h"


class FirstDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(FirstDialog);
	static FirstDialog* createFromCCB();

	FirstDialog();
	virtual ~FirstDialog();

	virtual void onEnter();
	virtual void onExit();

    void setGameData(VersusGameData *gameData);


private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressPlay);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::Label *_labelTitle;
    cocos2d::Label *_labelSet;
	cocos2d::extension::ControlButton *_buttonPlay;
	cocos2d::Label *_labelFirstTitle;
    
    VersusGameData *m_gameData;

	MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
	MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(FirstDialog, spritebuilder::LayerLoader);


#endif /* defined(__Takyan__FirstDialog__) */
