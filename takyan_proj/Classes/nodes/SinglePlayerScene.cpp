#include "SinglePlayerScene.h"

#include "MainMenuScene.h"
#include "PostGameDialog.h"
#include "PauseDialog.h"

#include "managers_caches/ObserverManager.h"

USE_NS

// n < 1, slower; n > 1 faster
#define GAME_SPEED 1.0f
#define ANIMATION_SPEED (1 / GAME_SPEED)

// don't show bounds: PhysicsWorld::DEBUGDRAW_NONE
// show bounds: PhysicsWorld::DEBUGDRAW_ALL
#define DEBUGDRAW_OPTIONS PhysicsWorld::DEBUGDRAW_NONE


SinglePlayerScene *SinglePlayerScene::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("SinglePlayerScene", SinglePlayerSceneLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<SinglePlayerScene*>(ccbReader->readNodeGraphFromFile("SinglePlayerScene.ccbi"));
}

SinglePlayerScene::SinglePlayerScene() : cocos2d::Layer()
, _background(NULL)
, _leftWallBounds(NULL)
, _rightWallBounds(NULL)
, _floorBounds(NULL)
, _ceilingBounds(NULL)
, _labelName(NULL)
, _labelLevel(NULL)
, _labelScore(NULL)
, _player(NULL)
, _playerSprite(NULL)
, _handHelper(NULL)
, _kickRotator(NULL)
, _kicker(NULL)
, _takyanTail(NULL)
, _takyan(NULL)
, _takyanSprite(NULL)
, _buttonPause(NULL)
{
    
}

SinglePlayerScene::~SinglePlayerScene()
{
    CC_SAFE_RELEASE(_background);
    CC_SAFE_RELEASE(_leftWallBounds);
    CC_SAFE_RELEASE(_rightWallBounds);
    CC_SAFE_RELEASE(_floorBounds);
    CC_SAFE_RELEASE(_ceilingBounds);
    CC_SAFE_RELEASE(_labelName);
    CC_SAFE_RELEASE(_labelLevel);
    CC_SAFE_RELEASE(_labelScore);
    CC_SAFE_RELEASE(_player);
    CC_SAFE_RELEASE(_playerSprite);
    CC_SAFE_RELEASE(_handHelper);
    CC_SAFE_RELEASE(_kickRotator);
    CC_SAFE_RELEASE(_kicker);
    CC_SAFE_RELEASE(_takyanTail);
    CC_SAFE_RELEASE(_takyan);
    CC_SAFE_RELEASE(_takyanSprite);
    CC_SAFE_RELEASE(_buttonPause);
}

void SinglePlayerScene::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    if (!m_enterred)
    {
        _playerSprite->setSpriteFrame(StringUtils::format("%ssteady.png", m_framePrefix.c_str()));
        auto bg = Director::getInstance()->getTextureCache()->addImage(m_game->getBackground());
        _background->setTexture(bg);
        
        this->setupPhysics();
        
        this->setupListeners();
        
        if (!m_game->isPracticeMode())
        {
            m_game->getPlayer()->addPlays(1);
        }
    }
    
    m_enterred = true;
}

void SinglePlayerScene::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UNOBSERVE(this);
}

void SinglePlayerScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressPause(_buttonPause, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

SingleGameData *SinglePlayerScene::getGameData()
{
    return m_game;
}

void SinglePlayerScene::setGameData(SingleGameData* game)
{
    m_game = game;
    m_game->retain();
    
    PlayerData *player = m_game->getPlayer();
    
    
    if (player->getGender() == GENDER_MALE)
    {
        m_framePrefix = "boy1_character/boy1_";
    }
    else
    {
        m_framePrefix = "girl1_character/girl1_";
    }
    
    _labelName->setString(player->getName());
    _labelScore->setString("0");
    _labelLevel->setString(StringUtils::format("Lvl %d", player->getLevel()));
}

void SinglePlayerScene::onPressPause(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE && !IS_LOCKED)
    {
        PauseDialog *d = PauseDialog::createFromCCB();
        
        Director::getInstance()->getRunningScene()->addChild(d, 1000);
	}
}

void SinglePlayerScene::updatePhysics(float delta)
{
    Vec2 takyanPos = _takyan->getPosition();
    Vec2 tailPos = _takyanTail->getPosition();
    
    Vec2 deltaPos;
    deltaPos.x = tailPos.x - takyanPos.x;
    deltaPos.y = tailPos.y - takyanPos.y;
    
    float angleInDegrees = atan2f(deltaPos.y, -deltaPos.x) * 180 / PI;
    _takyanSprite->setRotation(angleInDegrees - 90);
}

void SinglePlayerScene::setupPhysics()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float visibleHeight = visibleSize.height;
    PhysicsWorld* world = this->getScene()->getPhysicsWorld();
    world->setGravity(Vec2(0, (visibleHeight / 320.0f) * -98.0f));
    world->setSpeed(GAME_SPEED);
    
    world->setDebugDrawMask(DEBUGDRAW_OPTIONS);
    
    
    Vec2 takyanPos = _takyan->getPosition();
    PhysicsBody *takyanBody = PhysicsBody::createCircle(_takyan->getContentSize().width * BALL_RADIUS, PhysicsMaterial(0.01f, 1.0f, 1.0f)); //_takyan->getPhysicsBody();
    float takyanMass = takyanBody->getMass();
    float velocityLimit = takyanMass * 150.0f;
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
    jointS->setCollisionEnable(false);
    world->addJoint(jointS);
    
    
    PhysicsBody *kickerBody = PhysicsBody::createCircle(_kicker->getContentSize().width * KICKER_RADIUS, PhysicsMaterial(1.0f, 1.0f, 1.0f)); //_kicker->getPhysicsBody();
    kickerBody->setDynamic(false);
    kickerBody->setEnable(false);
    _kicker->setPhysicsBody(kickerBody);
    
    PHYSICS_MASK(kickerBody, MASK_KICKER, MASK_TAKYAN, MASK_TAKYAN);
    
    int takyans = MASK_TAKYAN | MASK_TAKYAN_TAIL;
    
    auto floorBody = PhysicsBody::createBox(_floorBounds->getContentSize(), PhysicsMaterial(1.0f, 0.3f, 0.7f)); //_floorBounds->getPhysicsBody();
    floorBody->setDynamic(false);
    _floorBounds->setPhysicsBody(floorBody);
    PHYSICS_MASK(floorBody, MASK_BOUNDS, takyans, takyans);
    
    auto ceilingBody = PhysicsBody::createBox(_ceilingBounds->getContentSize(), PhysicsMaterial(1.0f, 0.3f, 0.7f));
    ceilingBody->setDynamic(false);
    _ceilingBounds->setPhysicsBody(ceilingBody);
    PHYSICS_MASK(ceilingBody, MASK_BOUNDS, MASK_TAKYAN, MASK_TAKYAN);
    
    Size wallSize = _leftWallBounds->getContentSize();
    wallSize.height *= 5.0f;
    
    auto leftWallBody = PhysicsBody::createBox(wallSize); //_leftWallBounds->getPhysicsBody();
    leftWallBody->setDynamic(false);
    _leftWallBounds->setPhysicsBody(leftWallBody);
    PHYSICS_MASK(leftWallBody, MASK_WALLS, takyans, MASK_TAKYAN);
    
    auto rightWallBody = PhysicsBody::createBox(wallSize); //_rightWallBounds->getPhysicsBody();
    rightWallBody->setDynamic(false);
    _rightWallBounds->setPhysicsBody(rightWallBody);
    PHYSICS_MASK(rightWallBody, MASK_WALLS, takyans, MASK_TAKYAN);
}

void SinglePlayerScene::setupListeners()
{
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(SinglePlayerScene::onContactBegin, this);
    contactListener->onContactPreSolve = CC_CALLBACK_2(SinglePlayerScene::onContactPresolve, this);
    contactListener->onContactPostSolve = CC_CALLBACK_2(SinglePlayerScene::onContactPostsolve, this);
    contactListener->onContactSeperate = CC_CALLBACK_1(SinglePlayerScene::onContactSeparate, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this->getScene());
    
    
    EventListenerTouchOneByOne *oneTouch = EventListenerTouchOneByOne::create();
    oneTouch->onTouchBegan = CC_CALLBACK_2(SinglePlayerScene::touchBegan, this);
    oneTouch->onTouchMoved = CC_CALLBACK_2(SinglePlayerScene::touchMoved, this);
    oneTouch->onTouchEnded = CC_CALLBACK_2(SinglePlayerScene::touchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);
    
    
    this->schedule(schedule_selector(SinglePlayerScene::updatePhysics));
    
    OBSERVE(this, EVENT_LOCK_LEVEL_CHANGED, [&](EventCustom *event){
        this->getScene()->getPhysicsWorld()->setSpeed(IS_LOCKED ? 0 : GAME_SPEED);
        if (IS_LOCKED) {
            _kicker->pause();
        }
        else
        {
            _kicker->resume();
        }
    });
    
    OBSERVE(this, EVENT_RESTART_GAME, [&](EventCustom *event){
        CCLOG("RESTART GAME");
        PlayerData *player = m_game->getPlayer();
        std::string background = m_game->getBackground();
        
        SingleGameData *gameData = SingleGameData::create(player);
        gameData->setBackground(background);
        gameData->setPracticeMode(m_game->isPracticeMode());
        
        SinglePlayerScene *layer = SinglePlayerScene::createFromCCB();
        layer->setGameData(gameData);
        
        Scene *scene = Scene::createWithPhysics();
        scene->addChild(layer);
        
        Director::getInstance()->replaceScene(scene);
    });
}

Sequence *SinglePlayerScene::makeHandSequence(std::string framePrefix, float height, float kickSpeed)
{
    return Sequence::create(CallFunc::create([&](){
        _kicker->getPhysicsBody()->setEnable(true);
        m_isKicking = true;
        m_hitWhenKicked = false;
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.6f)), CallFunc::create([&, framePrefix](){
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_hand.png", framePrefix.c_str()));
        m_scoreCanAcquire = 2;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.4f)), CallFunc::create([&, framePrefix](){
        m_scoreCanAcquire = 3;
        _playerSprite->setSpriteFrame(StringUtils::format("%shands.png", framePrefix.c_str()));
    }), DelayTime::create(kickSpeed * 2.0f), CallFunc::create([&, framePrefix](){
        m_scoreCanAcquire = 2;
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_hand.png", framePrefix.c_str()));
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.4f)), CallFunc::create([&](){
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.6f)), CallFunc::create([&, framePrefix](){
        _playerSprite->setSpriteFrame(StringUtils::format("%ssteady.png", framePrefix.c_str()));
        m_scoreCanAcquire = 0;
        _kicker->getPhysicsBody()->setEnable(false);
        m_isKicking = false;
    }), NULL);
}

Sequence *SinglePlayerScene::makeKickSequence(std::string framePrefix, float height, float kickSpeed)
{
    return Sequence::create(CallFunc::create([&](){
        _kicker->getPhysicsBody()->setEnable(true);
        m_isKicking = true;
        m_hitWhenKicked = false;
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.6f)), CallFunc::create([&, framePrefix](){
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_kick.png", framePrefix.c_str()));
        m_scoreCanAcquire = 2;
    }), MoveBy::create(kickSpeed, Vec2(0, height * 0.4f)), CallFunc::create([&, framePrefix](){
        m_scoreCanAcquire = 3;
        _playerSprite->setSpriteFrame(StringUtils::format("%skick.png", framePrefix.c_str()));
    }), DelayTime::create(kickSpeed * 2.0f), CallFunc::create([&, framePrefix](){
        m_scoreCanAcquire = 2;
        _playerSprite->setSpriteFrame(StringUtils::format("%shalf_kick.png", framePrefix.c_str()));
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.4f)), CallFunc::create([&, framePrefix](){
        m_scoreCanAcquire = 1;
    }), MoveBy::create(kickSpeed, Vec2(0, -height * 0.6f)), CallFunc::create([&, framePrefix](){
        _playerSprite->setSpriteFrame(StringUtils::format("%ssteady.png", framePrefix.c_str()));
        m_scoreCanAcquire = 0;
        _kicker->getPhysicsBody()->setEnable(false);
        m_isKicking = false;
    }), NULL);
}

bool SinglePlayerScene::touchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return !m_isKicking && !IS_LOCKED;
}

void SinglePlayerScene::touchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!m_moved)
    {
        float threshold = Director::getInstance()->getVisibleSize().width * 0.02f;
        
        Vec2 start = touch->getStartLocation();
        Vec2 current = touch->getLocation();
        
        if (fabs(start.x - current.x) < threshold)
        {
            return;
        }
    }
    
    m_moved = true;
    
    Vec2 playerPos = _player->getPosition();
    Vec2 kickerPos = _kicker->getPosition();
    
    Vec2 delta = touch->getDelta();
    
    playerPos.x += delta.x;
    
    float playerWidthAllowance = _player->getContentSize().width * 0.125f;
    float backgroundWidth = Director::getInstance()->getVisibleSize().width;
    
    if (playerPos.x >= playerWidthAllowance && playerPos.x <= backgroundWidth - playerWidthAllowance)
    {
        _player->setPosition(playerPos);
        
        if (!m_movingSpriteChangerFlag)
        {
            m_movingSpriteChangerFlag = true;
            _playerSprite->setSpriteFrame(StringUtils::format("%smove.png", m_framePrefix.c_str()));
            _player->runAction(Sequence::create(DelayTime::create(0.25f), CallFunc::create([&](){
                _playerSprite->setSpriteFrame(StringUtils::format("%ssteady.png", m_framePrefix.c_str()));
            }), DelayTime::create(0.25f), CallFunc::create([&](){
                m_movingSpriteChangerFlag = false;
            }), NULL));
        }
    }
    
}

void SinglePlayerScene::touchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (!m_moved) {
        Size playerSize = _player->getContentSize();
        float frames = 30.0f;
        float framesPerSeconds = 1.0f / frames;
        float kickSpeed = (framesPerSeconds * 2.5f) * ANIMATION_SPEED;
        
        int level = m_game->getPlayer()->getLevel();
        
        Sequence *sequence = NULL;
        
        if (level == 0)
        {
            _kicker->retain();
            _kicker->removeFromParent();
            _handHelper->addChild(_kicker);
            
            float height = _handHelper->getContentSize().height;
            
            sequence = makeHandSequence(m_framePrefix, height, kickSpeed);
        }
        else if (level == 1)
        {
            _kicker->retain();
            _kicker->removeFromParent();
            _kickRotator->addChild(_kicker);
            
            float height = _kickRotator->getContentSize().height;
            
            sequence = makeKickSequence(m_framePrefix, height, kickSpeed);
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
                
                sequence = makeHandSequence(m_framePrefix, height, kickSpeed);
            }
            else
            {
                _kicker->retain();
                _kicker->removeFromParent();
                _kickRotator->addChild(_kicker);
                
                float height = _kickRotator->getContentSize().height;
                
                sequence = makeKickSequence(m_framePrefix, height, kickSpeed);
            }
        }
        
        if (sequence != nullptr)
        {
            _kicker->runAction(sequence);
        }
    }
    
    m_moved = false;
}

#pragma mark - collissions

bool SinglePlayerScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA == _takyan || nodeB == _takyan) {
        auto otherNode = nodeA == _takyan ? nodeB : nodeA;
        
        if (otherNode == _floorBounds) {
            if (!m_game->isPracticeMode())
            {
                m_game->setOver(true);
                
                _kicker->getPhysicsBody()->setEnable(false);
                
                PostGameDialog *dialog = PostGameDialog::createFromCCB();
                dialog->setGameData(m_game);
                Director::getInstance()->getRunningScene()->addChild(dialog, 1001);
            }
        }
        else if (otherNode == _kicker)
        {
            if (!m_hitWhenKicked && !m_game->isOver())
            {
                m_hitWhenKicked = true;
                m_game->addScore(m_scoreCanAcquire);
                
                _labelScore->setString(StringUtils::format("%d", m_game->getScore()));
                
                m_game->addHits(1);
                
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
                    std::string fontName = _labelScore->getTTFConfig().fontFilePath;
                    Label *remarksLabel = Label::createWithTTF(remarks, fontName, 12.0f, _labelScore->getDimensions()); //createWithSystemFont(remarks, fontName, 12.0f, _scoreLabel->getDimensions());
                    
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
                
            }
            return !m_game->isOver();
        }
        else
        {
            
        }
    }
    
    return true;
}

bool SinglePlayerScene::onContactPresolve(cocos2d::PhysicsContact &contact, cocos2d::PhysicsContactPreSolve &solve)
{
    return true;
}

void SinglePlayerScene::onContactPostsolve(cocos2d::PhysicsContact &contact, const cocos2d::PhysicsContactPostSolve &solve)
{
    
}

void SinglePlayerScene::onContactSeparate(cocos2d::PhysicsContact &contact)
{
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA == _takyan || nodeB == _takyan) {
        auto otherNode = nodeA == _takyan ? nodeB : nodeA;
        
        if (otherNode == _kicker && !m_game->isOver())
        {
            auto takyanBody = _takyan->getPhysicsBody();
            Vec2 v = takyanBody->getVelocity();
            float limitY = takyanBody->getMass() * 1.0f;
            if (v.y < limitY) {
                v.y = MAX(limitY, v.y * 2.5f);
            }
            float limitX = takyanBody->getMass() * 1.0f;
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
            
            takyanBody->setVelocity(v);
        }
        else if (otherNode == _floorBounds && m_game->isPracticeMode())
        {
            m_game->setScore(0);
            
            auto takyanBody = _takyan->getPhysicsBody();
            Vec2 velocity;
            
            velocity.y = takyanBody->getMass() * 2.50f;
            takyanBody->setVelocity(velocity);
        }
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool SinglePlayerScene::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_background", cocos2d::Sprite*, _background);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_leftWallBounds", cocos2d::Node*, _leftWallBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_rightWallBounds", cocos2d::Node*, _rightWallBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_floorBounds", cocos2d::Node*, _floorBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_ceilingBounds", cocos2d::Node*, _ceilingBounds);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelName", cocos2d::Label*, _labelName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelLevel", cocos2d::Label*, _labelLevel);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelScore", cocos2d::Label*, _labelScore);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_player", cocos2d::Node*, _player);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_playerSprite", cocos2d::Sprite*, _playerSprite);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_handHelper", cocos2d::Node*, _handHelper);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_kickRotator", cocos2d::Node*, _kickRotator);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_kicker", cocos2d::Node*, _kicker);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_takyanTail", cocos2d::Node*, _takyanTail);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_takyan", cocos2d::Node*, _takyan);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_takyanSprite", cocos2d::Sprite*, _takyanSprite);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPause", cocos2d::extension::ControlButton*, _buttonPause);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler SinglePlayerScene::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPause", SinglePlayerScene::onPressPause);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void SinglePlayerScene::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void SinglePlayerScene::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


