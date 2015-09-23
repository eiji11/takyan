#ifndef __TakyanBattle__SinglePlayerScene__
#define __TakyanBattle__SinglePlayerScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/SingleGameData.h"

#include "managers_caches/UILockManager.h"


class SinglePlayerScene : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(SinglePlayerScene);
	static SinglePlayerScene* createFromCCB();

	SinglePlayerScene();
	virtual ~SinglePlayerScene();

	virtual void onEnter();
	virtual void onExit();
    
    SingleGameData *getGameData();
    void setGameData(SingleGameData* game);
    
    
protected:
    virtual bool touchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void touchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    bool onContactPresolve(cocos2d::PhysicsContact& contact, cocos2d::PhysicsContactPreSolve& solve);
    void onContactPostsolve(cocos2d::PhysicsContact& contact, const cocos2d::PhysicsContactPostSolve& solve);
    void onContactSeparate(cocos2d::PhysicsContact& contact);

    
private:
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    
    CREATE_HANDLER(onPressPause);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);
    
    
    void updatePhysics(float delta);
    
    void setupPhysics();
    void setupListeners();
    cocos2d::Sequence *makeHandSequence(std::string framePrefix, float height, float kickSpeed);
    cocos2d::Sequence *makeKickSequence(std::string framePrefix, float height, float kickSpeed);
    

private:
    cocos2d::Sprite *_background;
    cocos2d::Node *_leftWallBounds;
    cocos2d::Node *_rightWallBounds;
    cocos2d::Node *_floorBounds;
    cocos2d::Node *_ceilingBounds;
    cocos2d::Label *_labelName;
    cocos2d::Label *_labelLevel;
    cocos2d::Label *_labelScore;
    cocos2d::Node *_player;
    cocos2d::Sprite *_playerSprite;
    cocos2d::Node *_handHelper;
    cocos2d::Node *_kickRotator;
    cocos2d::Node *_kicker;
    cocos2d::Node *_takyanTail;
    cocos2d::Node *_takyan;
    cocos2d::Sprite *_takyanSprite;
    cocos2d::extension::ControlButton *_buttonPause;
    
    SingleGameData *m_game;
    
    std::string m_framePrefix;
    bool m_isKicking = false;
    int m_scoreCanAcquire = 0;
    bool m_moved = false;
    bool m_hitWhenKicked = false;
    bool m_enterred = false;
    
    bool m_movingSpriteChangerFlag = false;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);
};

CREATE_CLASS_LOADER(SinglePlayerScene, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__SinglePlayerScene__) */
