#ifndef __Takyan__RecordsDialogEntry__
#define __Takyan__RecordsDialogEntry__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/PlayerData.h"


class RecordsDialogEntry : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(RecordsDialogEntry);
	static RecordsDialogEntry* createFromCCB();

	RecordsDialogEntry();
	virtual ~RecordsDialogEntry();

	virtual void onEnter();
    virtual void onExit();
    
    PlayerData *getPlayer()
    {
        return _player;
    }
    
    void setPlayer(PlayerData *player);


private:
	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);
    

private:
	cocos2d::LayerColor *_background;
	cocos2d::Sprite *_badge;
	cocos2d::Label *_labelLosses;
	cocos2d::Label *_labelWins;
	cocos2d::Label *_labelPlays;
	cocos2d::Label *_labelLevel;
	cocos2d::Label *_labelGender;
	cocos2d::Label *_labelName;

    PlayerData *_player;
};

CREATE_CLASS_LOADER(RecordsDialogEntry, spritebuilder::LayerLoader);


#endif /* defined(__Takyan__RecordsDialogEntry__) */
