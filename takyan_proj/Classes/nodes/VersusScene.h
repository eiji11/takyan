#ifndef __TakyanBattle__VersusScene__
#define __TakyanBattle__VersusScene__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"

#include "objects/VersusGameData.h"
#include "managers_caches/UILockManager.h"


class VersusScene : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(VersusScene);
	static VersusScene* createFromCCB();

	VersusScene();
	virtual ~VersusScene();

	virtual void onEnter();
	virtual void onExit();
    
    void setGameData(VersusGameData* game);
    
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
    CREATE_HANDLER(onPressSkillFire);
    CREATE_HANDLER(onPressSkillTeleport);
    CREATE_HANDLER(onPressSkillSpread);
    CREATE_HANDLER(onPressLeft);
    CREATE_HANDLER(onPressRight);


	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);
    
    void restart();
    void gotoNextSet();

    void updatePhysics(float delta);
    
    void setupPlayers();
    void setupPhysics();
    void setupListeners();
    
    void fixPlayerSetsWon();
    void fixPlayerUI();
    void switchCurrentPlayer();
    void showGameOver();
    
    void makeFakeTakyan(cocos2d::Vec2 velocity, std::string frameName);
    cocos2d::Sequence *makeHandSequence(int playerIndex, std::string framePrefix, float height, float kickSpeed);
    cocos2d::Sequence *makeKickSequence(int playerIndex, std::string framePrefix, float height, float kickSpeed);

private:
    cocos2d::Sprite *_background;
    cocos2d::Node *_leftWallBounds;
    cocos2d::Node *_rightWallBounds;
    cocos2d::Node *_floorBounds;
    cocos2d::Node *_ceilingBounds;
    cocos2d::Label *_labelSetTitle;
    cocos2d::Node *_containerPlayerInfo1;
    cocos2d::Label *_labelPlayerName1;
    cocos2d::Label *_labelPlayerLevel1;
    cocos2d::Node *_containerStars1;
    cocos2d::Sprite *_badge1;
    cocos2d::Sprite *_star1_1;
    cocos2d::Sprite *_star1_2;
    cocos2d::Sprite *_star1_3;
    cocos2d::Node *_containerPlayerInfo2;
    cocos2d::Label *_labelPlayerName2;
    cocos2d::Label *_labelPlayerLevel2;
    cocos2d::Node *_containerStars2;
    cocos2d::Sprite *_badge2;
    cocos2d::Sprite *_star2_1;
    cocos2d::Sprite *_star2_2;
    cocos2d::Sprite *_star2_3;
    cocos2d::extension::ControlButton *_buttonPause;
    cocos2d::Node *_player2;
    cocos2d::Sprite *_playerSprite2;
    cocos2d::Sprite *_currentPointer2;
    cocos2d::Label *_labelHitsLeft2;
    cocos2d::Node *_handHelper2;
    cocos2d::Node *_kickRotator2;
    cocos2d::Node *_kicker2;
    cocos2d::Node *_player1;
    cocos2d::Sprite *_playerSprite1;
    cocos2d::Sprite *_currentPointer1;
    cocos2d::Label *_labelHitsLeft1;
    cocos2d::Node *_handHelper1;
    cocos2d::Node *_kickRotator1;
    cocos2d::Node *_kicker1;
    cocos2d::Node *_takyanTail;
    cocos2d::Node *_takyan;
    cocos2d::Sprite *_takyanSprite;
    cocos2d::Node *_containerSkills1;
    cocos2d::extension::ControlButton *_buttonLeft1;
    cocos2d::extension::ControlButton *_buttonRight1;
    cocos2d::extension::ControlButton *_buttonSkillFire1;
    cocos2d::extension::ControlButton *_buttonSkillTeleport1;
    cocos2d::extension::ControlButton *_buttonSkillSpread1;
    cocos2d::Node *_containerSkills2;
    cocos2d::extension::ControlButton *_buttonLeft2;
    cocos2d::extension::ControlButton *_buttonRight2;
    cocos2d::extension::ControlButton *_buttonSkillFire2;
    cocos2d::extension::ControlButton *_buttonSkillTeleport2;
    cocos2d::extension::ControlButton *_buttonSkillSpread2;
    
    float m_velocityLimit;
    
    bool m_moved[2];
    bool m_isKicking[2];
    cocos2d::Touch* m_touchPlayerIndeces[2];
    std::string m_characterPrefixes[2];
    int m_nextSkill[2];
    
    bool m_movingSpriteChangerFlag[2];
    
    bool m_enterred = false;
    
    bool m_shouldResetLimits = false;
    
    int m_scoreCanAcquire = 0;
    bool m_hitWhenKicked = false;
    
    float m_tailYDiff = 0;
    
    VersusGameData* m_gameData;
    
    MAKE_CONTEXT(UI_LOCK_CONTEXT_DEFAULT);
    MAKE_LOCK_LEVEL(1);
    
};

CREATE_CLASS_LOADER(VersusScene, spritebuilder::LayerLoader);


#endif /* defined(__TakyanBattle__VersusScene__) */
