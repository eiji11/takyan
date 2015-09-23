#ifndef __TakyanBattle__PlayerCreate__
#define __TakyanBattle__PlayerCreate__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "ui/UIEditBox/UIEditBox.h"
#include "ui/CocosGUI.h"

#include "Defines.h"

#include "objects/PlayerManager.h"
#include "objects/PlayerData.h"

#include "managers_caches/UILockManager.h"


class PlayerCreate : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
, public cocos2d::ui::EditBoxDelegate
{
public:
	CREATE_FUNC(PlayerCreate);
	static PlayerCreate* createFromCCB();

	PlayerCreate();
	virtual ~PlayerCreate();

	virtual void onEnter();
	virtual void onExit();

    PlayerData *getPlayer()
    {
        return _player;
    }
    
    void setPlayer(PlayerData *player);

private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressOk);
	CREATE_HANDLER(onPressBack);
	CREATE_HANDLER(onPressGender);
	CREATE_HANDLER(onPressDelete);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

private:
	cocos2d::Label *_labelTitle;
	cocos2d::extension::ControlButton *_buttonOk;
	cocos2d::extension::ControlButton *_buttonBack;
	cocos2d::Label *_labelName;
    cocos2d::Node *_placeHolderInputName;
    cocos2d::LayerColor *_textfieldBG;
	cocos2d::Label *_labelGender;
	cocos2d::extension::ControlButton *_buttonMale;
	cocos2d::extension::ControlButton *_buttonFemale;
	cocos2d::extension::ControlButton *_buttonDelete;
    
    cocos2d::ui::TextField *_inputName;

    PlayerData* _player;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(3);

};

CREATE_CLASS_LOADER(PlayerCreate, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__PlayerCreate__) */
