#ifndef __Takyan__ConfirmDialog__
#define __Takyan__ConfirmDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"

#include <functional>


class ConfirmDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(ConfirmDialog);
	static ConfirmDialog* createFromCCB();

	ConfirmDialog();
	virtual ~ConfirmDialog();

	virtual void onEnter();
	virtual void onExit();

	void setOkCallback(std::function<void()> callback)
	{
		_okCallback = callback;
	}

	void setBackCallback(std::function<void()> callback)
	{
		_backCallback = callback;
	}

private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_HANDLER(onPressOk);
	CREATE_HANDLER(onPressBack);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Label *_labelTitle;
	cocos2d::extension::ControlButton *_buttonOk;
	cocos2d::extension::ControlButton *_buttonBack;

	std::function<void()> _okCallback;
	std::function<void()> _backCallback;

    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(ConfirmDialog, spritebuilder::LayerLoader);


#endif /* defined(__Takyan__ConfirmDialog__) */
