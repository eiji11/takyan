#include "VersusScene.h"

#include "MainMenuScene.h"
#include "PauseDialog.h"
#include "PostGameVersusDialog.h"
#include "FirstDialog.h"

#include "objects/PlayerManager.h"

#include "managers_caches/AssortedUtils.h"
#include "managers_caches/ObserverManager.h"

#include <vector>


USE_NS

// n < 1, slower; n > 1 faster
#define GAME_SPEED 1.f
#define ANIMATION_SPEED (1 / GAME_SPEED)

// don't show bounds: PhysicsWorld::DEBUGDRAW_NONE
// show bounds: PhysicsWorld::DEBUGDRAW_ALL
#define DEBUGDRAW_OPTIONS PhysicsWorld::DEBUGDRAW_NONE


VersusScene *VersusScene::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("VersusScene", VersusSceneLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<VersusScene*>(ccbReader->readNodeGraphFromFile("VersusScene.ccbi"));
}

VersusScene::VersusScene() : cocos2d::Layer()
, _background(NULL)
, _leftWallBounds(NULL)
, _rightWallBounds(NULL)
, _floorBounds(NULL)
, _ceilingBounds(NULL)
, _labelSetTitle(NULL)
, _containerPlayerInfo1(NULL)
, _labelPlayerName1(NULL)
, _labelPlayerLevel1(NULL)
, _containerStars1(NULL)
, _badge1(NULL)
, _star1_1(NULL)
, _star1_2(NULL)
, _star1_3(NULL)
, _containerPlayerInfo2(NULL)
, _labelPlayerName2(NULL)
, _labelPlayerLevel2(NULL)
, _containerStars2(NULL)
, _badge2(NULL)
, _star2_1(NULL)
, _star2_2(NULL)
, _star2_3(NULL)
, _buttonPause(NULL)
, _player2(NULL)
, _playerSprite2(NULL)
, _currentPointer2(NULL)
, _labelHitsLeft2(NULL)
, _handHelper2(NULL)
, _kickRotator2(NULL)
, _kicker2(NULL)
, _player1(NULL)
, _playerSprite1(NULL)
, _currentPointer1(NULL)
, _labelHitsLeft1(NULL)
, _handHelper1(NULL)
, _kickRotator1(NULL)
, _kicker1(NULL)
, _takyanTail(NULL)
, _takyan(NULL)
, _takyanSprite(NULL)
, _containerSkills1(NULL)
, _buttonLeft1(NULL)
, _buttonRight1(NULL)
, _buttonSkillFire1(NULL)
, _buttonSkillTeleport1(NULL)
, _buttonSkillSpread1(NULL)
, _containerSkills2(NULL)
, _buttonLeft2(NULL)
, _buttonRight2(NULL)
, _buttonSkillFire2(NULL)
, _buttonSkillTeleport2(NULL)
, _buttonSkillSpread2(NULL)

, m_gameData(NULL)
{

}

VersusScene::~VersusScene()
{
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_leftWallBounds);
    CC_SAFE_RELEASE(_rightWallBounds);
    CC_SAFE_RELEASE(_floorBounds);
    CC_SAFE_RELEASE(_ceilingBounds);
    CC_SAFE_RELEASE(_labelSetTitle);
    CC_SAFE_RELEASE(_containerPlayerInfo1);
    CC_SAFE_RELEASE(_labelPlayerName1);
    CC_SAFE_RELEASE(_labelPlayerLevel1);
    CC_SAFE_RELEASE(_containerStars1);
    CC_SAFE_RELEASE(_badge1);
    CC_SAFE_RELEASE(_star1_1);
    CC_SAFE_RELEASE(_star1_2);
    CC_SAFE_RELEASE(_star1_3);
    CC_SAFE_RELEASE(_containerPlayerInfo2);
    CC_SAFE_RELEASE(_labelPlayerName2);
    CC_SAFE_RELEASE(_labelPlayerLevel2);
    CC_SAFE_RELEASE(_containerStars2);
    CC_SAFE_RELEASE(_badge2);
    CC_SAFE_RELEASE(_star2_1);
    CC_SAFE_RELEASE(_star2_2);
    CC_SAFE_RELEASE(_star2_3);
    CC_SAFE_RELEASE(_buttonPause);
    CC_SAFE_RELEASE(_player2);
    CC_SAFE_RELEASE(_playerSprite2);
    CC_SAFE_RELEASE(_currentPointer2);
    CC_SAFE_RELEASE(_labelHitsLeft2);
    CC_SAFE_RELEASE(_handHelper2);
    CC_SAFE_RELEASE(_kickRotator2);
    CC_SAFE_RELEASE(_kicker2);
    CC_SAFE_RELEASE(_player1);
    CC_SAFE_RELEASE(_playerSprite1);
    CC_SAFE_RELEASE(_currentPointer1);
    CC_SAFE_RELEASE(_labelHitsLeft1);
    CC_SAFE_RELEASE(_handHelper1);
    CC_SAFE_RELEASE(_kickRotator1);
    CC_SAFE_RELEASE(_kicker1);
    CC_SAFE_RELEASE(_takyanTail);
    CC_SAFE_RELEASE(_takyan);
    CC_SAFE_RELEASE(_takyanSprite);
    CC_SAFE_RELEASE(_containerSkills1);
    CC_SAFE_RELEASE(_buttonLeft1);
    CC_SAFE_RELEASE(_buttonRight1);
    CC_SAFE_RELEASE(_buttonSkillFire1);
    CC_SAFE_RELEASE(_buttonSkillTeleport1);
    CC_SAFE_RELEASE(_buttonSkillSpread1);
    CC_SAFE_RELEASE(_containerSkills2);
    CC_SAFE_RELEASE(_buttonLeft2);
    CC_SAFE_RELEASE(_buttonRight2);
    CC_SAFE_RELEASE(_buttonSkillFire2);
    CC_SAFE_RELEASE(_buttonSkillTeleport2);
    CC_SAFE_RELEASE(_buttonSkillSpread2);
}

void VersusScene::onEnter()
{
    CCASSERT(m_gameData != nullptr, "NO GAME DATA");
    
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    if (!m_enterred)
    {
        int sets = m_gameData->getSets();
        int currentSet = m_gameData->getCurrentSet();
        
        std::string text = StringUtils::format("Set %d of %d", currentSet + 1, sets);
        CCLOG("TEXT: %s", text.c_str());
        _labelSetTitle->setString(text);
        
        if (sets < 5)
        {
            _star1_3->setVisible(false);
            _star2_3->setVisible(false);
        }
        if (sets < 3)
        {
            _star1_2->setVisible(false);
            _star2_2->setVisible(false);
        }
        
		this->setupPlayers();
		this->setupPhysics();
		this->setupListeners();

		auto bg = Director::getInstance()->getTextureCache()->addImage(m_gameData->getBackground());
		_background->setTexture(bg);

		this->runAction(CallFunc::create([&]()
		{
			cocos2d::log("SHOWING FIRST");
			FirstDialog *d = FirstDialog::createFromCCB();
            d->setGameData(m_gameData);
			Director::getInstance()->getRunningScene()->addChild(d, 1000);
			this->fixPlayerUI();
		}));
		m_enterred = true;
    }
}

void VersusScene::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    this->unschedule(schedule_selector(VersusScene::updatePhysics));
    
    UNOBSERVE(this);
//    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}

void VersusScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressPause(_buttonPause, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void VersusScene::setGameData(VersusGameData *game)
{
    m_gameData = game;
    m_gameData->retain();
    
    
}
void VersusScene::restart()
{
    PlayerData *player1 = m_gameData->getGame1()->getPlayer();
    PlayerData *player2 = m_gameData->getGame2()->getPlayer();
    
    auto layer = VersusScene::createFromCCB();
    VersusGameConfig *config = VersusGameConfig::create();
    config->setBackground(m_gameData->getBackground());
    
    config->setPlayer1(player1);
    config->setPlayer2(player2);
    config->setSets(m_gameData->getSets());
    config->setHitsPerRound(m_gameData->getHitsPerRound());
    
    VersusGameData *game = VersusGameData::create(config);
    layer->setGameData(game);
    auto scene = Scene::createWithPhysics();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
}

void VersusScene::gotoNextSet()
{
    auto layer = VersusScene::createFromCCB();
    m_gameData->setGameOver(false);
    m_gameData->getGame1()->setOver(false);
    m_gameData->getGame2()->setOver(false);
    layer->setGameData(m_gameData);
    auto scene = Scene::createWithPhysics();
    scene->addChild(layer);
    Director::getInstance()->replaceScene(scene);
}

void VersusScene::updatePhysics(float delta)
{
    Vec2 takyanPos = _takyan->getPosition();
    Vec2 tailPos = _takyanTail->getPosition();
    
    Vec2 deltaPos;
    deltaPos.x = tailPos.x - takyanPos.x;
    deltaPos.y = tailPos.y - takyanPos.y;
    
    float angleInDegrees = atan2f(deltaPos.y, -deltaPos.x) * 180 / PI;
    _takyanSprite->setRotation(angleInDegrees - 90);
}

void VersusScene::setupPlayers()
{
    VersusPlayerGameData *gd1 = m_gameData->getGame1();
    gd1->retain();
    VersusPlayerGameData *gd2 = m_gameData->getGame2();
    gd2->retain();
    
    
    PlayerData *player1 = gd1->getPlayer();
    player1->retain();
    PlayerData *player2 = gd2->getPlayer();
    player2->retain();
    
    int gender1 = player1->getGender();
    int gender2 = player2->getGender();
    
    if (gender1 == GENDER_MALE)
    {
        m_characterPrefixes[PLAYER_1_INDEX] = "boy1_character/boy1_";
        if (gender2 == gender1)
        {
            m_characterPrefixes[PLAYER_2_INDEX] = "boy2_character/boy2_";
        }
        else
        {
            m_characterPrefixes[PLAYER_2_INDEX] = "girl1_character/girl1_";
        }
    }
    else if (gender1 == GENDER_FEMALE)
    {
        m_characterPrefixes[PLAYER_1_INDEX] = "girl1_character/girl1_";
        if (gender2 == gender1)
        {
            m_characterPrefixes[PLAYER_2_INDEX] = "girl2_character/girl2_";
        }
        else
        {
            m_characterPrefixes[PLAYER_2_INDEX] = "boy1_character/boy1_";
        }
    }
    
    _playerSprite1->setSpriteFrame(m_characterPrefixes[PLAYER_1_INDEX] + "steady.png");
    _playerSprite2->setSpriteFrame(m_characterPrefixes[PLAYER_2_INDEX] + "steady.png");
    
    
    _player1->setLocalZOrder(m_gameData->getCurrentPlayerIndex() == 0 ? 3 : 2);
    _player2->setLocalZOrder(m_gameData->getCurrentPlayerIndex() == 0 ? 2 : 3);

    for (int x = 0; x < 2; x++)
    {
        m_moved[x] = false;
        m_isKicking[x] = false;
        m_touchPlayerIndeces[x] = nullptr;
        m_movingSpriteChangerFlag[x] = false;
        m_nextSkill[x] = 0;
    }
    
    
    _labelPlayerName1->setString(player1->getName());
    int level1 = player1->getLevel();
    _labelPlayerLevel1->setString(StringUtils::format("Lvl %d", level1));
    
    ControlButton *buttons1[] = {_buttonSkillFire1, _buttonSkillTeleport1, _buttonSkillSpread1};
    for (int x = 0; x < 3; x++) {
        buttons1[x]->setEnabled(level1 > x);
    }
    
    _labelPlayerName2->setString(player2->getName());
    int level2 = player2->getLevel();
    _labelPlayerLevel2->setString(StringUtils::format("Lvl %d", level2));
    
    ControlButton *buttons2[] = {_buttonSkillFire2, _buttonSkillTeleport2, _buttonSkillSpread2};
    for (int x = 0; x < 3; x++) {
        buttons2[x]->setEnabled(level2 > x);
    }
    
    int points1 = player1->getPoints();
    if (points1 == 1) {
        _badge1->setSpriteFrame("versus/badge_bronze_small.png");
    }
    else if (points1 == 2)
    {
        _badge1->setSpriteFrame("versus/badge_silver_small.png");
    }
    else if (points1 >= 3)
    {
        _badge1->setSpriteFrame("versus/badge_gold_small.png");
    }
    
    int points2 = player2->getPoints();
    if (points2 == 1) {
        _badge2->setSpriteFrame("versus/badge_bronze_small.png");
    }
    else if (points2 == 2)
    {
        _badge2->setSpriteFrame("versus/badge_silver_small.png");
    }
    else if (points2 >= 3)
    {
        _badge2->setSpriteFrame("versus/badge_gold_small.png");
    }
    
    fixPlayerSetsWon();
}

void VersusScene::setupPhysics()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float visibleHeight = visibleSize.height;
    PhysicsWorld* world = this->getScene()->getPhysicsWorld();
    world->setGravity(Vec2(0, (visibleHeight / 320.0f) * -98.0f));
    world->setSpeed(GAME_SPEED);
    
    world->setDebugDrawMask(DEBUGDRAW_OPTIONS);
    
    
    Vec2 takyanPos = _takyan->getPosition();
    PhysicsBody *takyanBody = PhysicsBody::createCircle(_takyan->getContentSize().width * 0.5f, PhysicsMaterial(0.01f, 1.0f, 1.0f)); //_takyan->getPhysicsBody();
    float takyanMass = takyanBody->getMass();
    float velocityLimit = m_velocityLimit = takyanMass * 150.0f;
    takyanBody->setMass(takyanMass * 100.0f);
    takyanBody->setRotationEnable(false);
    takyanBody->setVelocityLimit(velocityLimit);
    _takyan->setPhysicsBody(takyanBody);
    
    PHYSICS_MASK(takyanBody, MASK_TAKYAN, MASK_BOUNDS | MASK_KICKER, MASK_BOUNDS | MASK_KICKER);
    
    Size takyanSize = _takyan->getContentSize();
    takyanSize.height *= 0.8f;
    
    PhysicsMaterial material(0.0025f, 0.0f, 1.0f);
    PhysicsBody *takyanTailBody = PhysicsBody::createCircle(takyanSize.width, material);
    takyanTailBody->setMass(takyanMass * 0.01);
    takyanTailBody->setRotationEnable(false);
    takyanTailBody->setLinearDamping(1.0f);
    takyanTailBody->setVelocityLimit(velocityLimit * 0.5f);
    _takyanTail->setPhysicsBody(takyanTailBody);
    
    PHYSICS_MASK(takyanTailBody, MASK_TAKYAN_TAIL, 0, MASK_FLOOR);
    
    Vec2 diff = _takyanTail->getPosition() - _takyan->getPosition();
    Vec2 anch1 = Vec2::ANCHOR_MIDDLE;
    Vec2 anch2 = Vec2::ANCHOR_MIDDLE;
    auto jointS = PhysicsJointLimit::construct(takyanBody, takyanTailBody, anch1, anch2, 0, diff.y);
    jointS->setCollisionEnable(true);
    world->addJoint(jointS);
    
    this->runAction(CallFunc::create([&](){
        m_tailYDiff = _takyanTail->getPosition().y - _takyan->getPosition().y;
    }));
    
    
    Node *kickers[] = {_kicker1, _kicker2};
    
    for (Node *kicker : kickers)
    {
        PhysicsBody *kickerBody = PhysicsBody::createCircle(kicker->getContentSize().width * KICKER_RADIUS, PhysicsMaterial(1.0f, 1.0f, 1.0f));
        kickerBody->setDynamic(false);
        kickerBody->setEnable(false);
        kicker->setPhysicsBody(kickerBody);
        PHYSICS_MASK(kickerBody, MASK_KICKER, MASK_TAKYAN, MASK_TAKYAN);
    }
    
    int takyans = MASK_TAKYAN | MASK_TAKYAN_TAIL | MASK_TAKYAN_FAKE;
    
    auto floorBody = PhysicsBody::createBox(_floorBounds->getContentSize(), PhysicsMaterial(1.0f, 0.3f, 0.7f));
    floorBody->setDynamic(false);
    _floorBounds->setPhysicsBody(floorBody);
    PHYSICS_MASK(floorBody, MASK_BOUNDS, takyans, takyans);
    
    auto ceilingBody = PhysicsBody::createBox(_ceilingBounds->getContentSize(), PhysicsMaterial(1.0f, 0.3f, 0.7f));
    ceilingBody->setDynamic(false);
    _ceilingBounds->setPhysicsBody(ceilingBody);
    PHYSICS_MASK(ceilingBody, MASK_BOUNDS, 0, MASK_TAKYAN | MASK_TAKYAN_FAKE);
    
    Size wallSize = _leftWallBounds->getContentSize();
    wallSize.height *= 5.0f;
    
    auto leftWallBody = PhysicsBody::createBox(wallSize); //_leftWallBounds->getPhysicsBody();
    leftWallBody->setDynamic(false);
    _leftWallBounds->setPhysicsBody(leftWallBody);
    PHYSICS_MASK(leftWallBody, MASK_WALLS, takyans, MASK_TAKYAN | MASK_TAKYAN_FAKE);
    
    auto rightWallBody = PhysicsBody::createBox(wallSize); //_rightWallBounds->getPhysicsBody();
    rightWallBody->setDynamic(false);
    _rightWallBounds->setPhysicsBody(rightWallBody);
    PHYSICS_MASK(rightWallBody, MASK_WALLS, takyans, MASK_TAKYAN | MASK_TAKYAN_FAKE);
}

void VersusScene::setupListeners()
{
    m_touchPlayerIndeces[PLAYER_1_INDEX] = nullptr;
    m_touchPlayerIndeces[PLAYER_2_INDEX] = nullptr;
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(VersusScene::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_2(VersusScene::onContactPresolve, this);
    contactListener->onContactPostSolve = CC_CALLBACK_2(VersusScene::onContactPostsolve, this);
    contactListener->onContactSeperate = CC_CALLBACK_1(VersusScene::onContactSeparate, this);
//    _eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    // SceneGraphPriority(contactListener, _physicsWorld);
    
    
    EventListenerTouchOneByOne *oneTouch = EventListenerTouchOneByOne::create();
    oneTouch->setSwallowTouches(false);
    oneTouch->onTouchBegan = CC_CALLBACK_2(VersusScene::touchBegan, this);
    oneTouch->onTouchMoved = CC_CALLBACK_2(VersusScene::touchMoved, this);
    oneTouch->onTouchEnded = CC_CALLBACK_2(VersusScene::touchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);
    

    this->schedule(schedule_selector(VersusScene::updatePhysics));
    
    OBSERVE(this, EVENT_LOCK_LEVEL_CHANGED, [&](EventCustom *event){
        this->getScene()->getPhysicsWorld()->setSpeed(IS_LOCKED ? 0 : GAME_SPEED);
        if (IS_LOCKED) {
            _kicker1->pause();
            _kicker2->pause();
        }
        else
        {
            _kicker1->resume();
            _kicker2->resume();
        }
    });
    
    OBSERVE(this, EVENT_RESTART_GAME, [&](EventCustom *event){
        this->restart();
    });
}

void VersusScene::onPressPause(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        PauseDialog *d = PauseDialog::createFromCCB();
        
        Director::getInstance()->getRunningScene()->addChild(d, 1000);
    }
}

void VersusScene::onPressSkillFire(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        if (sender == _buttonSkillFire1)
        {
            m_nextSkill[0] = 1;

            _buttonSkillFire1->setHighlighted(true);
            _buttonSkillTeleport1->setHighlighted(false);
            _buttonSkillSpread1->setHighlighted(false);
        }
        else
        {
            m_nextSkill[1] = 1;

            _buttonSkillFire2->setHighlighted(true);
            _buttonSkillTeleport2->setHighlighted(false);
            _buttonSkillSpread2->setHighlighted(false);
        }
    }
}

void VersusScene::onPressSkillTeleport(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        if (sender == _buttonSkillTeleport1)
        {
            m_nextSkill[0] = 2;

            _buttonSkillFire1->setHighlighted(false);
            _buttonSkillTeleport1->setHighlighted(true);
            _buttonSkillSpread1->setHighlighted(false);
        }
        else
        {
            m_nextSkill[1] = 2;

            _buttonSkillFire2->setHighlighted(false);
            _buttonSkillTeleport2->setHighlighted(true);
            _buttonSkillSpread2->setHighlighted(false);
        }
    }
}

void VersusScene::onPressSkillSpread(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        if (sender == _buttonSkillSpread1)
        {
            m_nextSkill[0] = 3;

            _buttonSkillFire1->setHighlighted(false);
            _buttonSkillTeleport1->setHighlighted(false);
            _buttonSkillSpread1->setHighlighted(true);
        }
        else
        {
            m_nextSkill[1] = 3;

            _buttonSkillFire2->setHighlighted(false);
            _buttonSkillTeleport2->setHighlighted(false);
            _buttonSkillSpread2->setHighlighted(true);
        }
    }
}

void VersusScene::onPressLeft(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if ((pControlEvent == Control::EventType::TOUCH_UP_INSIDE || pControlEvent == Control::EventType::TOUCH_CANCEL)  && !IS_LOCKED)
    {
        int characterIndex = PLAYER_1_INDEX;
        Node *player = _player1;
        Sprite *playerSprite = _playerSprite1;

        if (sender == _buttonLeft1)
        {
        	characterIndex = PLAYER_1_INDEX;
            player = _player1;
            playerSprite = _playerSprite1;
        }
        else
        {
        	characterIndex = PLAYER_2_INDEX;
            player = _player2;
            playerSprite = _playerSprite2;
        }

    	float move = player->getContentSize().width * 0.33f;

        Vec2 playerPos = player->getPosition() + Vec2(-move, 0);
        float playerWidthAllowance = player->getContentSize().width * 0.125f;
        float backgroundWidth = Director::getInstance()->getVisibleSize().width;

        if (playerPos.x >= playerWidthAllowance && playerPos.x <= backgroundWidth - playerWidthAllowance)
        {
            player->setPosition(playerPos);

            if (!m_movingSpriteChangerFlag)
            {
                m_movingSpriteChangerFlag[characterIndex] = true;
                playerSprite->setSpriteFrame(m_characterPrefixes[characterIndex] + "_move.png");
                playerSprite->runAction(Sequence::create(DelayTime::create(0.25f), CallFunc::create([&, playerSprite, characterIndex](){
                    playerSprite->setSpriteFrame(m_characterPrefixes[characterIndex] + "_steady.png");
                }), DelayTime::create(0.25f), CallFunc::create([&, characterIndex](){
                    m_movingSpriteChangerFlag[characterIndex] = false;
                }), NULL));
            }
        }
    }
}

void VersusScene::onPressRight(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if ((pControlEvent == Control::EventType::TOUCH_UP_INSIDE || pControlEvent == Control::EventType::TOUCH_CANCEL)  && !IS_LOCKED)
    {
        int characterIndex = PLAYER_1_INDEX;
        Node *player = _player1;
        Sprite *playerSprite = _playerSprite1;

        if (sender == _buttonRight1)
        {
        	characterIndex = PLAYER_1_INDEX;
            player = _player1;
            playerSprite = _playerSprite1;
        }
        else
        {
        	characterIndex = PLAYER_2_INDEX;
            player = _player2;
            playerSprite = _playerSprite2;
        }

    	float move = player->getContentSize().width * 0.33f;

        Vec2 playerPos = player->getPosition() + Vec2(move, 0);
        float playerWidthAllowance = player->getContentSize().width * 0.125f;
        float backgroundWidth = Director::getInstance()->getVisibleSize().width;

        if (playerPos.x >= playerWidthAllowance && playerPos.x <= backgroundWidth - playerWidthAllowance)
        {
            player->setPosition(playerPos);

            if (!m_movingSpriteChangerFlag)
            {
                m_movingSpriteChangerFlag[characterIndex] = true;
                playerSprite->setSpriteFrame(m_characterPrefixes[characterIndex] + "_move.png");
                playerSprite->runAction(Sequence::create(DelayTime::create(0.25f), CallFunc::create([&, playerSprite, characterIndex](){
                    playerSprite->setSpriteFrame(m_characterPrefixes[characterIndex] + "_steady.png");
                }), DelayTime::create(0.25f), CallFunc::create([&, characterIndex](){
                    m_movingSpriteChangerFlag[characterIndex] = false;
                }), NULL));
            }
        }
    }
}

Sequence *VersusScene::makeHandSequence(int playerIndex, std::string framePrefix, float height, float kickSpeed)
{
    Node *_player = nullptr;
    Sprite *_playerSprite = nullptr;
    Node *_kicker = nullptr;
    Node *_kickRotator = nullptr;
    Node *_handHelper = nullptr;
    
    if (playerIndex == PLAYER_1_INDEX)
    {
        _player = _player1;
        _playerSprite = _playerSprite1;
        _kicker = _kicker1;
        _kickRotator = _kickRotator1;
        _handHelper = _handHelper1;
    }
    else if (playerIndex == PLAYER_2_INDEX)
    {
        _player = _player2;
        _playerSprite = _playerSprite2;
        _kicker = _kicker2;
        _kickRotator = _kickRotator2;
        _handHelper = _handHelper2;
    }
    
    return Sequence::create(CallFunc::create([&, _kicker, playerIndex](){
        _kicker->getPhysicsBody()->setEnable(playerIndex == m_gameData->getCurrentPlayerIndex());
        m_isKicking[playerIndex] = true;
        m_hitWhenKicked = false;
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.6f)), CallFunc::create([&, framePrefix, _playerSprite](){
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_hand.png", framePrefix.c_str()));
        m_scoreCanAcquire = 2;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.4f)), CallFunc::create([&, framePrefix, _playerSprite](){
        m_scoreCanAcquire = 3;
        _playerSprite->setSpriteFrame(StringUtils::format("%shands.png", framePrefix.c_str()));
    }), DelayTime::create(kickSpeed * 2.0f), CallFunc::create([&, framePrefix, _playerSprite](){
        m_scoreCanAcquire = 2;
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_hand.png", framePrefix.c_str()));
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.4f)), CallFunc::create([&](){
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.6f)), CallFunc::create([&, framePrefix, _playerSprite, _kicker, playerIndex](){
        _playerSprite->setSpriteFrame(StringUtils::format("%ssteady.png", framePrefix.c_str()));
        m_scoreCanAcquire = 0;
        _kicker->getPhysicsBody()->setEnable(false);
        m_isKicking[playerIndex] = false;
    }), NULL);
}

Sequence *VersusScene::makeKickSequence(int playerIndex, std::string framePrefix, float height, float kickSpeed)
{
    Node *_player = nullptr;
    Sprite *_playerSprite = nullptr;
    Node *_kicker = nullptr;
    Node *_kickRotator = nullptr;
    Node *_handHelper = nullptr;
    
    if (playerIndex == PLAYER_1_INDEX)
    {
        _player = _player1;
        _playerSprite = _playerSprite1;
        _kicker = _kicker1;
        _kickRotator = _kickRotator1;
        _handHelper = _handHelper1;
    }
    else if (playerIndex == PLAYER_2_INDEX)
    {
        _player = _player2;
        _playerSprite = _playerSprite2;
        _kicker = _kicker2;
        _kickRotator = _kickRotator2;
        _handHelper = _handHelper2;
    }
    
    return Sequence::create(CallFunc::create([&, _kicker, playerIndex](){
        _kicker->getPhysicsBody()->setEnable(playerIndex == m_gameData->getCurrentPlayerIndex());
        m_isKicking[playerIndex] = true;
        m_hitWhenKicked = false;
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.6f)), CallFunc::create([&, framePrefix, _playerSprite](){
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_kick.png", framePrefix.c_str()));
        m_scoreCanAcquire = 2;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.4f)), CallFunc::create([&, framePrefix, _playerSprite](){
        m_scoreCanAcquire = 3;
        _playerSprite->setSpriteFrame(StringUtils::format("%skick.png", framePrefix.c_str()));
    }), DelayTime::create(kickSpeed * 2.0f), CallFunc::create([&, framePrefix, _playerSprite](){
        m_scoreCanAcquire = 2;
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_kick.png", framePrefix.c_str()));
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.4f)), CallFunc::create([&, framePrefix](){
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.6f)), CallFunc::create([&, framePrefix, _kicker, playerIndex, _playerSprite](){
        _playerSprite->setSpriteFrame(StringUtils::format("%ssteady.png", framePrefix.c_str()));
        m_scoreCanAcquire = 0;
        _kicker->getPhysicsBody()->setEnable(false);
        m_isKicking[playerIndex] = false;
    }), NULL);
}

void VersusScene::fixPlayerSetsWon()
{
    int points1 = m_gameData->getGame1()->getSetsWon();
    Sprite *stars1[] = {_star1_1, _star1_2, _star1_3};
    for (int x = 0; x < 3; x++)
    {
        std::string frameName = "versus/small_star_blank.png";
        if (points1 > x) {
            frameName = "versus/small_star.png";
        }
        stars1[x]->setSpriteFrame(frameName);
    }
    
    int points2 = m_gameData->getGame2()->getSetsWon();
    Sprite *stars2[] = {_star2_1, _star2_2, _star2_3};
    for (int x = 0; x < 3; x++)
    {
        std::string frameName = "versus/small_star_blank.png";
        if (points2 > x) {
            frameName = "versus/small_star.png";
        }
        stars2[x]->setSpriteFrame(frameName);
    }
    cocos2d::log("%d & %d", points1, points2);
}

void VersusScene::fixPlayerUI()
{
    int currentPlayer = m_gameData->getCurrentPlayerIndex();
    if (currentPlayer == PLAYER_2_INDEX)
    {
        _player1->setLocalZOrder(1);
        _player2->setLocalZOrder(2);
        _currentPointer1->setVisible(false);
        _currentPointer2->setVisible(true);
        
        _labelHitsLeft2->setString(StringUtils::format("%d", m_gameData->getHitsPerRound()));
    }
    else
    {
        _player1->setLocalZOrder(2);
        _player2->setLocalZOrder(1);
        _currentPointer1->setVisible(true);
        _currentPointer2->setVisible(false);
        
        _labelHitsLeft1->setString(StringUtils::format("%d", m_gameData->getHitsPerRound()));
    }

}

void VersusScene::switchCurrentPlayer()
{
    int currentPlayer = m_gameData->getCurrentPlayerIndex();

    if (currentPlayer == PLAYER_1_INDEX)
    {
        currentPlayer = PLAYER_2_INDEX;
    }
    else
    {
        currentPlayer = PLAYER_1_INDEX;
    }
    
    m_gameData->getGame1()->setHitsForRound(0);
    m_gameData->getGame2()->setHitsForRound(0);
    
    m_gameData->setCurrentPlayerIndex(currentPlayer);

	this->fixPlayerUI();
    
    m_gameData->setCurrentHitsForRound(0);
    
}

void VersusScene::showGameOver()
{
    PostGameVersusDialog *d = PostGameVersusDialog::createFromCCB();
    d->setGameData(m_gameData);
    
    Director::getInstance()->getRunningScene()->addChild(d, 1000);
}

void VersusScene::makeFakeTakyan(cocos2d::Vec2 velocity, std::string frameName)
{
    Node *fakeTakyan = Node::create();
    fakeTakyan->setPosition(_takyan->getPosition());
    fakeTakyan->setAnchorPoint(_takyan->getAnchorPoint());
    fakeTakyan->setRotation(_takyan->getRotation());
    
    Node *fakeTakyanTail = Node::create();
    fakeTakyanTail->setPosition(_takyanTail->getPosition());
    fakeTakyanTail->setAnchorPoint(_takyanTail->getAnchorPoint());
    
    Sprite *fakeTakyanSprite = Sprite::createWithSpriteFrameName(frameName);
    fakeTakyanSprite->setPosition(_takyanSprite->getPosition());
    fakeTakyanSprite->setAnchorPoint(_takyanSprite->getAnchorPoint());
    fakeTakyan->addChild(fakeTakyanSprite);
    
    this->addChild(fakeTakyan, _takyan->getLocalZOrder());
    this->addChild(fakeTakyanTail, _takyanTail->getLocalZOrder());
    
    
    Vec2 takyanPos = _takyan->getPosition();
    PhysicsBody *takyanBody = PhysicsBody::createCircle(_takyan->getContentSize().width * 0.5f, PhysicsMaterial(0.01f, 1.0f, 1.0f));
    float takyanMass = takyanBody->getMass();
    float velocityLimit = m_velocityLimit;
    takyanBody->setMass(takyanMass * 100.0f);
    takyanBody->setRotationEnable(false);
    takyanBody->setVelocityLimit(velocityLimit);
    fakeTakyan->setPhysicsBody(takyanBody);
    
    PHYSICS_MASK(takyanBody, MASK_TAKYAN_FAKE, MASK_FLOOR, MASK_BOUNDS);
    
    Size takyanSize = _takyan->getContentSize();
    takyanSize.height *= 0.8f;
    
    PhysicsMaterial material(0.0025f, 0.0f, 1.0f);
    PhysicsBody *takyanTailBody = PhysicsBody::createCircle(takyanSize.width, material);
    takyanTailBody->setMass(takyanMass * 0.01);
    takyanTailBody->setRotationEnable(false);
    takyanTailBody->setLinearDamping(1.0f);
    takyanTailBody->setVelocityLimit(velocityLimit * 0.5f);
    fakeTakyanTail->setPhysicsBody(takyanTailBody);
    
    PHYSICS_MASK(takyanTailBody, MASK_TAKYAN_FAKE, 0, MASK_FLOOR);
    
    auto jointS = PhysicsJointLimit::construct(takyanBody, takyanTailBody, Vec2::ANCHOR_MIDDLE_BOTTOM, Vec2::ANCHOR_MIDDLE_TOP);
    jointS->setCollisionEnable(true);
    this->getScene()->getPhysicsWorld()->addJoint(jointS);
    
    takyanBody->setVelocity(velocity);
    takyanBody->setAngularVelocity(_takyan->getPhysicsBody()->getAngularVelocity());
    
    takyanTailBody->setVelocity(_takyanTail->getPhysicsBody()->getVelocity());
    
    fakeTakyan->setTag(41);
    
    fakeTakyan->runAction(RepeatForever::create(Sequence::create(CallFunc::create([fakeTakyan, fakeTakyanTail, fakeTakyanSprite](){
        Vec2 takyanPos = fakeTakyan->getPosition();
        Vec2 tailPos = fakeTakyanTail->getPosition();
        
        Vec2 deltaPos;
        deltaPos.x = tailPos.x - takyanPos.x;
        deltaPos.y = tailPos.y - takyanPos.y;
        
        float angleInDegrees = atan2f(deltaPos.y, -deltaPos.x) * 180 / PI;
        fakeTakyanSprite->setRotation(angleInDegrees - 90);
    }), NULL)));
}

bool VersusScene::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    int playerIndex = PLAYER_1_INDEX;
    
    float width = this->getContentSize().width;
    
    float width2 = width / 2;
    
    float touchX = touch->getStartLocation().x;
    
    if (touchX > width2)
    {
        playerIndex = PLAYER_2_INDEX;
    }
    
    m_touchPlayerIndeces[playerIndex] = touch;

    return !m_isKicking[playerIndex] && !IS_LOCKED;
}

void VersusScene::touchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (!IS_LOCKED)
	{
		Node *_player = nullptr;
		Sprite *_playerSprite = nullptr;

		int playerIndex = -1;

		if (m_touchPlayerIndeces[PLAYER_1_INDEX] != nullptr) {
			if (touch == m_touchPlayerIndeces[PLAYER_1_INDEX])
			{
				playerIndex = PLAYER_1_INDEX;

				_player = _player1;
				_playerSprite = _playerSprite1;
			}
		}
		if (m_touchPlayerIndeces[PLAYER_2_INDEX] != nullptr) {
			if (touch == m_touchPlayerIndeces[PLAYER_2_INDEX])
			{
				playerIndex = PLAYER_2_INDEX;

				_player = _player2;
				_playerSprite = _playerSprite2;
			}
		}

		if (playerIndex == -1)
		{
			return;
		}

		if (!m_moved[playerIndex])
		{
			float threshold = Director::getInstance()->getVisibleSize().width * 0.02f;

			Vec2 start = touch->getStartLocation();
			Vec2 current = touch->getLocation();

			if (fabs(start.x - current.x) < threshold)
			{
				return;
			}
		}

		m_moved[playerIndex] = true;

		Vec2 playerPos = _player->getPosition();

		Vec2 delta = touch->getDelta();

		playerPos.x += delta.x;

		float playerWidthAllowance = _player->getContentSize().width * 0.125f;
		float backgroundWidth = Director::getInstance()->getVisibleSize().width;

		if (playerPos.x >= playerWidthAllowance && playerPos.x <= backgroundWidth - playerWidthAllowance)
		{
			_player->setPosition(playerPos);

			if (!m_movingSpriteChangerFlag)
			{
				m_movingSpriteChangerFlag[playerIndex] = true;
				_playerSprite->setSpriteFrame(m_characterPrefixes[playerIndex] + "_move.png");
				_player->runAction(Sequence::create(DelayTime::create(0.25f), CallFunc::create([&](){
					_playerSprite->setSpriteFrame(m_characterPrefixes[playerIndex] + "_steady.png");
				}), DelayTime::create(0.25f), CallFunc::create([&](){
					m_movingSpriteChangerFlag[playerIndex] = false;
				}), NULL));
			}
		}
    }
    
}

void VersusScene::touchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Node *_player = nullptr;
    Sprite *_playerSprite = nullptr;
    Node *_kicker = nullptr;
    Node *_kickRotator = nullptr;
    Node *_handHelper = nullptr;
    
    int playerIndex = -1;
    
    if (m_touchPlayerIndeces[PLAYER_1_INDEX] != nullptr) {
        if (touch == m_touchPlayerIndeces[PLAYER_1_INDEX])
        {
            playerIndex = PLAYER_1_INDEX;
            
            _player = _player1;
            _playerSprite = _playerSprite1;
            _kicker = _kicker1;
            _kickRotator = _kickRotator1;
            _handHelper = _handHelper1;
        }
    }
    if (m_touchPlayerIndeces[PLAYER_2_INDEX] != nullptr) {
        if (touch == m_touchPlayerIndeces[PLAYER_2_INDEX])
        {
            playerIndex = PLAYER_2_INDEX;
            
            _player = _player2;
            _playerSprite = _playerSprite2;
            _kicker = _kicker2;
            _kickRotator = _kickRotator2;
            _handHelper = _handHelper2;
        }
    }
    
    if (playerIndex == -1)
    {
        return;
    }
    
    if (!m_moved[playerIndex]) {
        Size playerSize = _player->getContentSize();
        float frames = 30.0f;
        float framesPerSeconds = 1.0f / frames;
        float kickSpeed = (framesPerSeconds * 2.5f) * ANIMATION_SPEED;
        std::string framePrefix = m_characterPrefixes[playerIndex];
        
        Sequence *sequence;
        
        GameData *gameData = m_gameData->getGame(playerIndex);
        PlayerData *playerData = gameData->getPlayer();
        
        int level = playerData->getLevel();
        
        if (level == 0)
        {
            _kicker->retain();
            _kicker->removeFromParent();
            _handHelper->addChild(_kicker);
            
            float height = _handHelper->getContentSize().height;
            
            sequence = makeHandSequence(playerIndex, framePrefix, height, kickSpeed);
        }
        else if (level == 1)
        {
            _kicker->retain();
            _kicker->removeFromParent();
            _kickRotator->addChild(_kicker);
            
            float height = _kickRotator->getContentSize().height;
            
            sequence = makeKickSequence(playerIndex, framePrefix, height, kickSpeed);
        }
        else if (level >= 2)
        {
            Vec2 takyanPos = _takyan->getPosition();
            //            float xPos = takyanPos.x;
            float yTakyanPos = takyanPos.y;
            
            Vec2 playerPos = _player->getPosition();
            float yPlayerPos = playerPos.y;
            
            Size playerSize = _player->getContentSize();
            float playerHeight = playerSize.height;
            
            float yLimit = yPlayerPos + playerHeight * 0.4f;
            
            if (yLimit <= yTakyanPos)
            {
                _kicker->retain();
                _kicker->removeFromParent();
                _handHelper->addChild(_kicker);
                
                float height = _handHelper->getContentSize().height;
                
                sequence = makeHandSequence(playerIndex, framePrefix, height, kickSpeed);
            }
            else
            {
                _kicker->retain();
                _kicker->removeFromParent();
                _kickRotator->addChild(_kicker);
                
                float height = _kickRotator->getContentSize().height;
                
                sequence = makeKickSequence(playerIndex, framePrefix, height, kickSpeed);
            }
        }
        
        if (sequence != nullptr)
        {
            _kicker->runAction(sequence);
        }
        
        /*
        if (false) {
            sequence = Sequence::create(CallFunc::create([&, playerIndex, _kicker](){
                if (m_gameData->getCurrentPlayerIndex() == playerIndex)
                {
                    _kicker->getPhysicsBody()->setEnable(true);
                    m_hitWhenKicked = false;
                    m_scoreCanAcquire = 1;
                }
                m_isKicking[playerIndex] = true;
            }), RotateBy::create(kickSpeed, -60.0f), CallFunc::create([&, playerIndex, _playerSprite](){
                if (m_gameData->getCurrentPlayerIndex() == playerIndex)
                {
                    m_scoreCanAcquire = 2;
                }
                _playerSprite->setSpriteFrame(m_characterPrefixes[playerIndex] + "_half_kick.png");
            }), RotateBy::create(kickSpeed, -30.0f), CallFunc::create([&, playerIndex, _playerSprite](){
                if (m_gameData->getCurrentPlayerIndex() == playerIndex)
                {
                    m_scoreCanAcquire = 3;
                }
                _playerSprite->setSpriteFrame(m_characterPrefixes[playerIndex] + "_kick.png");
            }), DelayTime::create(kickSpeed * 2.0f), CallFunc::create([&, playerIndex, _playerSprite](){
                if (m_gameData->getCurrentPlayerIndex() == playerIndex)
                {
                    m_scoreCanAcquire = 2;
                }
                _playerSprite->setSpriteFrame(m_characterPrefixes[playerIndex] + "_half_kick.png");
            }), RotateBy::create(kickSpeed, 30.0f), CallFunc::create([&, playerIndex](){
                if (m_gameData->getCurrentPlayerIndex() == playerIndex)
                {
                    m_scoreCanAcquire = 1;
                }
            }), RotateBy::create(kickSpeed, 60.0f), CallFunc::create([&, playerIndex, _kicker, _playerSprite](){
                if (m_gameData->getCurrentPlayerIndex() == playerIndex)
                {
                    m_scoreCanAcquire = 0;
                }
                _playerSprite->setSpriteFrame(m_characterPrefixes[playerIndex] + "_steady.png");
                _kicker->getPhysicsBody()->setEnable(false);
                m_isKicking[playerIndex] = false;
            }), NULL);
            
            _kickRotator->runAction(sequence);
         }
         */
        
        
        
    }
    
    m_moved[playerIndex] = false;
    
    m_touchPlayerIndeces[playerIndex] = nullptr;
}


#pragma mark - collissions

bool VersusScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    bool isPlayer1 = m_gameData->getCurrentPlayerIndex() == PLAYER_1_INDEX;
    
    auto _kicker = isPlayer1 ? _kicker1 : _kicker2;
    //    auto _currentPointer = isPlayer1 ? _currentPointer1 : _currentPointer2;
    auto _hitsLeftLabel = isPlayer1 ? _labelHitsLeft1 : _labelHitsLeft2;
    
    
    VersusPlayerGameData *playerGameData = m_gameData->getCurrentGame();
    VersusPlayerGameData *otherPlayerGameData = isPlayer1 ? m_gameData->getGame2() : m_gameData->getGame1();
    
    if (nodeA == _takyan || nodeB == _takyan) {
        auto otherNode = nodeA == _takyan ? nodeB : nodeA;
        
        if (otherNode == _floorBounds) {
            if (!m_gameData->isGameOver())
            {
                m_gameData->setGameOver(true);
                
                playerGameData->setOver(true);
                
                m_gameData->increaseCurrentSet();
                otherPlayerGameData->addSetsWon(1);
                
                int setsWon = otherPlayerGameData->getSetsWon();
                float setsToWin = m_gameData->getSets() * 0.5f;
                
                cocos2d::log("%d / %d", setsWon, setsToWin);

                Sequence *sequence = Sequence::create(DelayTime::create(2.f), CallFunc::create([&](){
                	cocos2d::log("refresh stars");
                    fixPlayerSetsWon();
                }), DelayTime::create(3.f), CallFunc::create([&, setsWon, setsToWin](){
                    if (setsWon < setsToWin)
                    {
                        gotoNextSet();
                    }
                    else
                    {
                        showGameOver();
                    }
                }), NULL);

                this->runAction(sequence);

            }
        }
        else if (otherNode == _kicker)
        {
            if (!m_hitWhenKicked && !m_gameData->isGameOver())
            {
                m_gameData->increaseCurrentHitsForRound();
                m_hitWhenKicked = true;
                
                
                playerGameData->addHits(1);
                playerGameData->addHitsForRound(1);
                playerGameData->addScore(m_scoreCanAcquire);
                
                int hits = playerGameData->getHitsForRound();
                int hitsRequired = m_gameData->getHitsPerRound();
                int hitsLeft = hitsRequired - hits;
                
                _hitsLeftLabel->setString(StringUtils::format("%d", hitsLeft));
                
                std::string remarks;
                Color4B color;
                if (m_scoreCanAcquire == 1)
                {
                    remarks = "Good";
                    color = Color4B(64, 64, 64, 255);
                }
                else if (m_scoreCanAcquire == 2)
                {
                    remarks = "Great!";
                    color = Color4B::GRAY;
                }
                else if (m_scoreCanAcquire == 3)
                {
                    remarks = "Perfect!";
                    color = Color4B::WHITE;
                }
                
                if (remarks.size() > 0)
                {
                    std::string fontName = _labelSetTitle->getTTFConfig().fontFilePath;
                    Label *remarksLabel = Label::createWithTTF(remarks, fontName, 12.0f, _labelSetTitle->getDimensions());
                    
                    remarksLabel->setPosition(contact.getContactData()->points[0]);
                    
                    remarksLabel->setTextColor(color);
                    remarksLabel->setHorizontalAlignment(TextHAlignment::CENTER);
                    remarksLabel->setVerticalAlignment(TextVAlignment::CENTER);
                    remarksLabel->enableOutline(Color4B::BLACK, 2);
                    this->addChild(remarksLabel, 10);
                    
                    remarksLabel->runAction(Sequence::create(MoveBy::create(1.5f, Vec2(0, remarksLabel->getContentSize().height)), FadeOut::create(2.0f), CallFuncN::create([&](Node* node){
                        node->removeFromParent();
                    }), NULL));
                }
                
                if (m_shouldResetLimits)
                {
                    _takyan->getPhysicsBody()->setVelocityLimit(m_velocityLimit);
                    _takyanTail->getPhysicsBody()->setVelocityLimit(m_velocityLimit * 0.5f);
                    _takyanSprite->setSpriteFrame("game/takyan.png");
                    m_shouldResetLimits = false;
                }
                
            }
            return !m_gameData->isGameOver();
        }
        else
        {
        }
    }
    else if (nodeA->getTag() == 41 || nodeB->getTag() == 41)
    {
        auto otherNode = nodeA->getTag() == 41 ? nodeB : nodeA;
        auto fakeTakyan = nodeA->getTag() == 41 ? nodeA : nodeB;
        
        if (otherNode == _floorBounds) {
            fakeTakyan->stopAllActions();
            PhysicsJoint *joint = fakeTakyan->getPhysicsBody()->getJoints().at(0);
            
            Node *fakeTakyanTail;
            if (joint->getBodyA() == fakeTakyan->getPhysicsBody())
            {
                fakeTakyanTail = joint->getBodyB()->getNode();
            }
            else
            {
                fakeTakyanTail = joint->getBodyA()->getNode();
            }
            fakeTakyan->removeFromParent();
            fakeTakyanTail->removeFromParent();
        }
    }
    
    return true;
}

bool VersusScene::onContactPresolve(cocos2d::PhysicsContact &contact, cocos2d::PhysicsContactPreSolve &solve)
{
    return true;
}

void VersusScene::onContactPostsolve(cocos2d::PhysicsContact &contact, const cocos2d::PhysicsContactPostSolve &solve)
{
    
}

void VersusScene::onContactSeparate(cocos2d::PhysicsContact &contact)
{
    if (m_gameData->isGameOver())
    {
        return;
    }
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    bool isPlayer1 = m_gameData->getCurrentPlayerIndex() == PLAYER_1_INDEX;
    
    auto *_kicker = isPlayer1 ? _kicker1 : _kicker2;
    auto *_player = isPlayer1 ? _player1 : _player2;
    int nextSkill = isPlayer1 ? m_nextSkill[0] : m_nextSkill[1];
    
    if (nodeA == _takyan || nodeB == _takyan) {
        auto otherNode = nodeA == _takyan ? nodeB : nodeA;
        
        if (otherNode == _kicker && !m_gameData->isGameOver())
        {
            _kicker->getPhysicsBody()->setEnable(false);
            
            auto takyanBody = _takyan->getPhysicsBody();
            Vec2 v = takyanBody->getVelocity();
            int hitsForRound = m_gameData->getCurrentGame()->getHitsForRound();
            int hitsPerRound = m_gameData->getHitsPerRound();
            CCLOG("HITS: %d, %d", hitsForRound, hitsPerRound);
            if (hitsForRound < hitsPerRound) {
                CCLOG("NEXT...");
                float limitY = takyanBody->getMass();
                if (v.y < limitY) {
                    v.y = MAX(limitY, v.y * 2.5f);
                }
                float limitX = takyanBody->getMass();
                if (v.x < -limitX || v.x > limitX) {
                    v.x = limitX * (v.x < 0 ? -1 : 1);
                }
                
                if (m_scoreCanAcquire == 3)
                {
                    Vec2 zero;
                    float distance = zero.distance(v);
                    v.x = 0;
                    v.y = distance;
                }
            }
            else
            {
                CCLOG("SWITCH...");
                
                float width = this->getContentSize().width;
                float width2 = width * 0.5f;
                
                float posX = _player->getPosition().x;
                float targetX;
                
                if (posX < width2)
                {
                    targetX = (posX + width2);
                }
                else
                {
                    targetX = -posX; //-(posX - width2);
                }
                
                
                if (nextSkill == 1)
                {
                    v.x = takyanBody->getMass() * (targetX * 0.075);
                    v.y = takyanBody->getMass() * fabs(targetX * 0.075);
                    
                    takyanBody->setVelocityLimit(m_velocityLimit * 1.25);
                    _takyanTail->getPhysicsBody()->setVelocityLimit(m_velocityLimit * 0.625f);
                    
                    _takyanSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game/takyan_fire_red.png"));
                    
                    m_shouldResetLimits = true;
                }
                else if (nextSkill == 2)
                {
                    v = Vec2::ZERO;
                    
                    _takyan->setRotation(0);
                    _takyan->getPhysicsBody()->setAngularVelocity(0);
                    _takyanTail->getPhysicsBody()->setVelocity(Vec2::ZERO);
                    
                    float width = this->getContentSize().width;
                    
                    float xPos = fmodf(arc4random(), width * 0.9f) + width * 0.05f;
                    
                    float yPos = this->getContentSize().height;
                    
                    CCLOG("BEFORE: %.2f, %.2f", _takyan->getPosition().x, _takyan->getPosition().y);
                    
                    _takyan->getPhysicsBody()->setEnable(false);
                    _takyanTail->getPhysicsBody()->setEnable(false);
                    
                    this->runAction(Sequence::create(CallFunc::create([&, xPos, yPos](){
                        _takyan->setPosition(Vec2(xPos, yPos));
                        _takyanTail->setPosition(Vec2(xPos, yPos + m_tailYDiff));
                    }), DelayTime::create(0.25f), CallFunc::create([&](){
                        _takyan->getPhysicsBody()->setEnable(true);
                        _takyanTail->getPhysicsBody()->setEnable(true);
                        
                        CCLOG("AFTER: %.2f, %.2f", _takyan->getPosition().x, _takyan->getPosition().y);
                    }), nullptr));
                }
                else if (nextSkill == 3)
                {
                    v.x = takyanBody->getMass() * (targetX * 0.1);
                    v.y = takyanBody->getMass() * fabs(targetX * 0.1);
                    
                    std::vector<cocos2d::Vec2> velocities;
                    velocities.push_back(v * 0.25f);
                    velocities.push_back(v * 1.75f);
                    velocities.push_back(v);
                    
                    CCLOG("-----BEFORE-----");
                    for (int x = 0; x < velocities.size(); x++)
                    {
                        CCLOG("V [%d] = %.2f", x, velocities[x].x);
                    }
                    
                    for (int x = 0; x < 5; x++) { // shuffle
                        int pos1 = AssortedUtils::random01() * velocities.size();
                        int pos2 = AssortedUtils::random01() * velocities.size();
                        
                        cocos2d::Vec2 v1 = velocities[pos1];
                        velocities[pos1] = velocities[pos2];
                        velocities[pos2] = v1;
                    }
                    
                    CCLOG("-----AFTER-----");
                    for (int x = 0; x < velocities.size(); x++)
                    {
                        CCLOG("V [%d] = %.2f", x, velocities[x].x);
                    }
                    
                    v = velocities[0];
                    
                    CCLOG("V = %.2f", v.x);
                    
                    _takyanSprite->setSpriteFrame("game/takyan_fire_red.png");
                    
                    makeFakeTakyan(velocities[1], "game/takyan_fire_green.png");
                    makeFakeTakyan(velocities[2], "game/takyan_fire_blue.png");
                    
                    m_shouldResetLimits = true;
                }
                else
                {
                    v.x = takyanBody->getMass() * (targetX * 0.075);
                    v.y = takyanBody->getMass() * fabs(targetX * 0.075);
                }
                
                this->switchCurrentPlayer();
            }
            
            this->runAction(CallFunc::create([&, takyanBody, v](){
                takyanBody->setVelocity(v);
            }));
        }
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool VersusScene::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_background", cocos2d::Sprite*, _background);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_leftWallBounds", cocos2d::Node*, _leftWallBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_rightWallBounds", cocos2d::Node*, _rightWallBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_floorBounds", cocos2d::Node*, _floorBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_ceilingBounds", cocos2d::Node*, _ceilingBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelSetTitle", cocos2d::Label*, _labelSetTitle);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerPlayerInfo1", cocos2d::Node*, _containerPlayerInfo1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlayerName1", cocos2d::Label*, _labelPlayerName1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlayerLevel1", cocos2d::Label*, _labelPlayerLevel1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerStars1", cocos2d::Node*, _containerStars1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_badge1", cocos2d::Sprite*, _badge1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star1_1", cocos2d::Sprite*, _star1_1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star1_2", cocos2d::Sprite*, _star1_2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star1_3", cocos2d::Sprite*, _star1_3);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerPlayerInfo2", cocos2d::Node*, _containerPlayerInfo2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlayerName2", cocos2d::Label*, _labelPlayerName2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlayerLevel2", cocos2d::Label*, _labelPlayerLevel2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerStars2", cocos2d::Node*, _containerStars2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_badge2", cocos2d::Sprite*, _badge2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star2_1", cocos2d::Sprite*, _star2_1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star2_2", cocos2d::Sprite*, _star2_2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_star2_3", cocos2d::Sprite*, _star2_3);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPause", cocos2d::extension::ControlButton*, _buttonPause);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_player2", cocos2d::Node*, _player2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_playerSprite2", cocos2d::Sprite*, _playerSprite2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_currentPointer2", cocos2d::Sprite*, _currentPointer2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelHitsLeft2", cocos2d::Label*, _labelHitsLeft2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_handHelper2", cocos2d::Node*, _handHelper2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_kickRotator2", cocos2d::Node*, _kickRotator2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_kicker2", cocos2d::Node*, _kicker2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_player1", cocos2d::Node*, _player1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_playerSprite1", cocos2d::Sprite*, _playerSprite1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_currentPointer1", cocos2d::Sprite*, _currentPointer1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelHitsLeft1", cocos2d::Label*, _labelHitsLeft1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_handHelper1", cocos2d::Node*, _handHelper1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_kickRotator1", cocos2d::Node*, _kickRotator1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_kicker1", cocos2d::Node*, _kicker1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_takyanTail", cocos2d::Node*, _takyanTail);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_takyan", cocos2d::Node*, _takyan);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_takyanSprite", cocos2d::Sprite*, _takyanSprite);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerSkills1", cocos2d::Node*, _containerSkills1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSkillFire1", cocos2d::extension::ControlButton*, _buttonSkillFire1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLeft1", cocos2d::extension::ControlButton*, _buttonLeft1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRight1", cocos2d::extension::ControlButton*, _buttonRight1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSkillTeleport1", cocos2d::extension::ControlButton*, _buttonSkillTeleport1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSkillSpread1", cocos2d::extension::ControlButton*, _buttonSkillSpread1);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_containerSkills2", cocos2d::Node*, _containerSkills2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonLeft2", cocos2d::extension::ControlButton*, _buttonLeft2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRight2", cocos2d::extension::ControlButton*, _buttonRight2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSkillFire2", cocos2d::extension::ControlButton*, _buttonSkillFire2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSkillTeleport2", cocos2d::extension::ControlButton*, _buttonSkillTeleport2);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonSkillSpread2", cocos2d::extension::ControlButton*, _buttonSkillSpread2);
    
    return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler VersusScene::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPause", VersusScene::onPressPause);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSkillFire", VersusScene::onPressSkillFire);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSkillTeleport", VersusScene::onPressSkillTeleport);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressSkillSpread", VersusScene::onPressSkillSpread);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressLeft", VersusScene::onPressLeft);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressRight", VersusScene::onPressRight);
    
    return NULL;
}


#pragma mark - NodeLoaderListener functions

void VersusScene::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    _containerSkills1->setLocalZOrder(6);
    _containerSkills2->setLocalZOrder(6);
    
    _takyan->setLocalZOrder(4);
    _takyanTail->setLocalZOrder(4);
}


#pragma mark - CCBAnimationManagerDelegate functions

void VersusScene::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


