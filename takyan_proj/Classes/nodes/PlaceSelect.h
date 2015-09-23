#ifndef __TakyanBattle__PlaceSelect__
#define __TakyanBattle__PlaceSelect__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/VersusGameConfig.h"
#include "objects/SingleGameData.h"

#include "managers_caches/UILockManager.h"


class PlaceSelect : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PlaceSelect);
	static PlaceSelect* createFromCCB();

	PlaceSelect();
	virtual ~PlaceSelect();

	virtual void onEnter();
	virtual void onExit();
    
    VersusGameConfig* getConfig()
    {
        return _versusConfig;
    }
    
    void setVersusGameConfig(VersusGameConfig* config)
    {
        _versusConfig = config;
    }
    
    bool isForVersus()
    {
        return _versusConfig != nullptr;
    }
    
    void setForVersus(bool versus)
    {
        if (versus)
        {
            setVersusGameConfig(VersusGameConfig::create());
            setSingleGameData(nullptr);
        }
        else
        {
            setVersusGameConfig(nullptr);
        }
    }
    
    SingleGameData *getSingleGameData()
    {
        return _singleGameData;
    }
    
    void setSingleGameData(SingleGameData* gameData)
    {
        _singleGameData = gameData;
        _singleGameData->retain();
    }
    

private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
	CREATE_HANDLER(onPressPlace);
	CREATE_HANDLER(onPressOk);
	CREATE_HANDLER(onPressBack);
	CREATE_HANDLER(onPressHome);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);

    void clearSelection();

private:
	cocos2d::Label *_labelTitle;
	cocos2d::LayerColor *_borderPlace1;
	cocos2d::extension::ControlButton *_buttonPlace1;
	cocos2d::Label *_labelPlaceName1;
	cocos2d::LayerColor *_borderPlace2;
	cocos2d::extension::ControlButton *_buttonPlace2;
	cocos2d::Label *_labelPlaceName2;
	cocos2d::LayerColor *_borderPlace3;
	cocos2d::extension::ControlButton *_buttonPlace3;
	cocos2d::Label *_labelPlaceName3;
	cocos2d::extension::ControlButton *_buttonOk;
	cocos2d::extension::ControlButton *_buttonBack;
	cocos2d::extension::ControlButton *_buttonHome;
    
    VersusGameConfig *_versusConfig;
    SingleGameData *_singleGameData;
    
    std::string _selectedBackground;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(2);

};

CREATE_CLASS_LOADER(PlaceSelect, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__PlaceSelect__) */
