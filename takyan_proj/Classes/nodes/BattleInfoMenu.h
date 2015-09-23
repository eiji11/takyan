#ifndef __TakyanBattle__BattleInfoMenu__
#define __TakyanBattle__BattleInfoMenu__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "ui/UIEditBox/UIEditBox.h"
#include "ui/CocosGUI.h"

#include "Defines.h"

#include "objects/VersusGameConfig.h"

#include "managers_caches/UILockManager.h"


class BattleInfoMenu : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(BattleInfoMenu);
	static BattleInfoMenu* createFromCCB();

	BattleInfoMenu();
	virtual ~BattleInfoMenu();

	virtual void onEnter();
    virtual void onExit();
    
    VersusGameConfig* getConfig()
    {
        return _versusConfig;
    }
    
    void setVersusGameConfig(VersusGameConfig* config)
    {
        if (_versusConfig != nullptr)
        {
            _versusConfig->release();
        }
        
        _versusConfig = config;
        
        if (_versusConfig != nullptr)
        {
            _versusConfig->retain();
        }
    }


private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressOk);
    CREATE_HANDLER(onPressBack);
    CREATE_HANDLER(onPressHome);
    CREATE_HANDLER(onPressBestOf);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::Label *_labelTitle;
    cocos2d::extension::ControlButton *_buttonOk;
    cocos2d::extension::ControlButton *_buttonBack;
    cocos2d::extension::ControlButton *_buttonHome;
    cocos2d::Label *_labelRounds;
    cocos2d::extension::ControlButton *_buttonBestOf1;
    cocos2d::extension::ControlButton *_buttonBestOf3;
    cocos2d::extension::ControlButton *_buttonBestOf5;
    cocos2d::Label *_labelHits;
    cocos2d::Node *_placeHolderInputHits;
    cocos2d::LayerColor *_textfieldBG;
    
	cocos2d::ui::TextField *_inputHits;
    
    VersusGameConfig *_versusConfig;
    
    int _sets;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);
};

CREATE_CLASS_LOADER(BattleInfoMenu, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__BattleInfoMenu__) */
