#ifndef __TakyanBattle__MainMenuScene__
#define __TakyanBattle__MainMenuScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "managers_caches/UILockManager.h"


class MainMenuScene : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(MainMenuScene);
	static MainMenuScene* createFromCCB();

	MainMenuScene();
	virtual ~MainMenuScene();

	virtual void onEnter();
	virtual void onExit();


private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressSingle);
	CREATE_HANDLER(onPressVersus);
    CREATE_HANDLER(onPressPractice);
    CREATE_HANDLER(onPressBattleRecords);
    CREATE_HANDLER(onPressInstructions);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::extension::ControlButton *_buttonSingle;
    cocos2d::extension::ControlButton *_buttonVersus;
    cocos2d::extension::ControlButton *_buttonPractice;
    cocos2d::extension::ControlButton *_buttonRecords;
    cocos2d::extension::ControlButton *_buttonInstructions;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);

};

CREATE_CLASS_LOADER(MainMenuScene, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__MainMenuScene__) */
