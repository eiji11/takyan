#ifndef __Takyan__PostGameVersusDialog__
#define __Takyan__PostGameVersusDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/VersusGameData.h"
#include "managers_caches/UILockManager.h"


class PostGameVersusDialog : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PostGameVersusDialog);
	static PostGameVersusDialog* createFromCCB();

	PostGameVersusDialog();
	virtual ~PostGameVersusDialog();

	virtual void onEnter();
	virtual void onExit();

    void setGameData(VersusGameData *game);

private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    CREATE_HANDLER(onPressRestart);
    CREATE_HANDLER(onPressHome);
    
    
    CCBMEMBER_FUNCTIONS
    CCBSELECTOR_FUNCTIONS
    
    virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);
    
    virtual void completedAnimationSequenceNamed(const char *name);
    
    static float getPercentage(int wins, int points);
    
private:
    cocos2d::Label *_titleName;
    cocos2d::Label *_labelRemarks;
    cocos2d::Sprite *_badge;
    cocos2d::Sprite *_progressBarContainer;
    cocos2d::Sprite *_progressBarFill;
    cocos2d::extension::ControlButton *_buttonRestart;
    cocos2d::extension::ControlButton *_buttonHome;
    
    cocos2d::ProgressTimer *_progressBar;
    
    VersusGameData *m_gameData;

    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);
};

CREATE_CLASS_LOADER(PostGameVersusDialog, spritebuilder::LayerLoader);


#endif /* defined(__com.spotcatstudio.cleaning__PostGameVersusDialog__) */
