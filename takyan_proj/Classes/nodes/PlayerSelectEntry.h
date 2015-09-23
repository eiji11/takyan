#ifndef __TakyanBattle__PlayerSelectEntry__
#define __TakyanBattle__PlayerSelectEntry__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/PlayerData.h"


class PlayerSelectEntry : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(PlayerSelectEntry);
	static PlayerSelectEntry* createFromCCB();

	PlayerSelectEntry();
	virtual ~PlayerSelectEntry();

	virtual void onEnter();
	virtual void onExit();
    
    PlayerData *getPlayer()
    {
        return _player;
    }
    
    void setPlayer(PlayerData *player);
    
    void setSelected(bool selected);


private:
	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
    cocos2d::LayerColor *_background;
	cocos2d::Label *_labelName;
	cocos2d::Label *_labelGender;
	cocos2d::Label *_labelLevel;
    
    PlayerData *_player;

};

CREATE_CLASS_LOADER(PlayerSelectEntry, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__PlayerSelectEntry__) */
