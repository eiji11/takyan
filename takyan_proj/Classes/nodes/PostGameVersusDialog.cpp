#include "PostGameVersusDialog.h"

#include "MainMenuScene.h"
#include "objects/PlayerManager.h"

#include "plugins/AnimatingNumber.h"


USE_NS

PostGameVersusDialog *PostGameVersusDialog::createFromCCB()
{
    NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    
    ccNodeLoaderLibrary->registerNodeLoader("PostGameVersusDialog", PostGameVersusDialogLoader::loader());
    
    spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);
    
    return dynamic_cast<PostGameVersusDialog*>(ccbReader->readNodeGraphFromFile("PostGameVersusDialog.ccbi"));
}

PostGameVersusDialog::PostGameVersusDialog() : cocos2d::Layer()
, _titleName(NULL)
, _labelRemarks(NULL)
, _badge(NULL)
, _progressBarContainer(NULL)
, _progressBarFill(NULL)
, _buttonRestart(NULL)
, _buttonHome(NULL)

, m_gameData(NULL)
, _progressBar(NULL)
{
    
}

PostGameVersusDialog::~PostGameVersusDialog()
{
    CC_SAFE_RELEASE(_titleName);
    CC_SAFE_RELEASE(_labelRemarks);
    CC_SAFE_RELEASE(_badge);
    CC_SAFE_RELEASE(_progressBarContainer);
    CC_SAFE_RELEASE(_progressBarFill);
    CC_SAFE_RELEASE(_buttonRestart);
    CC_SAFE_RELEASE(_buttonHome);
}

void PostGameVersusDialog::onEnter()
{
    cocos2d::Node::onEnter();
    
    CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void PostGameVersusDialog::onExit()
{
    cocos2d::Node::onExit();
    
    CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(NULL);
 
    UI_LOCK_MANAGER_DECREASE();
}

void PostGameVersusDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressHome(_buttonHome, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void PostGameVersusDialog::setGameData(VersusGameData *game)
{
    m_gameData = game;
    m_gameData->retain();
    
    VersusPlayerGameData *game1 = m_gameData->getGame1();
    PlayerData *player1 = game1->getPlayer();
    
    int setsWon1 = game1->getSetsWon();
    
    VersusPlayerGameData *game2 = m_gameData->getGame2();
    PlayerData *player2 = game2->getPlayer();
    
    int setsWon2 = game2->getSetsWon();
    
    int winner = 0;
    
    if (setsWon1 < setsWon2) {
        winner = 2;
    }
    else if (setsWon1 > setsWon2)
    {
        winner = 1;
    }
    
    if (winner == 1)
    {
        _titleName->setString(player1->getName());
        
        int previousWins = player1->getWins();
        int currentPoints = player1->getPoints();
        
        if (currentPoints >= 3)
        {
            _badge->setSpriteFrame("versus/badge_gold_big.png");
        }
        else if (currentPoints == 2)
        {
            _badge->setSpriteFrame("versus/badge_silver_big.png");
        }
        else if (currentPoints == 1)
        {
            _badge->setSpriteFrame("versus/badge_bronze_big.png");
        }
        else if (currentPoints == 0)
        {
            _badge->setSpriteFrame("versus/badge_blank_big.png");
        }
        
        float previousPercentage = getPercentage(previousWins, currentPoints);
        _progressBar->setPercentage(previousPercentage);
        
        player1->addConsecutiveWins(1);
        player2->setConsecutiveWins(0);

        player1->addWins(1);
        player2->addLosses(1);

        int wins = player1->getWins();
        
        if (wins >= 10)
        {
        	player1->setPoints(3);
        }
        else if (wins >= 6)
        {
        	player1->setPoints(2);
        }
        else if (wins >= 3)
        {
        	player1->setPoints(1);
        }
        else
        {
        	player1->setPoints(0);
        }
        
        int newPoints = player1->getPoints();
        
        float newPercentage = getPercentage(wins, currentPoints);
        
        Sequence *sequence = Sequence::create(AnimatingNumber::create(2.f, previousPercentage, newPercentage, [&](float current){
            _progressBar->setPercentage(current);
        }), CallFunc::create([&, newPoints](){
            if (newPoints == 1) {
                _badge->setSpriteFrame("versus/badge_bronze_big.png");
            }
            else if (newPoints == 2)
            {
                _badge->setSpriteFrame("versus/badge_silver_big.png");
            }
            else if (newPoints >= 3)
            {
                _badge->setSpriteFrame("versus/badge_gold_big.png");
            }
        }), NULL);
        
        this->runAction(sequence);
    }
    else if (winner == 2)
    {
        _titleName->setString(player2->getName());
        
        
        int previousWins = player2->getWins();
        int currentPoints = player2->getPoints();
        
        if (currentPoints >= 3)
        {
            _badge->setSpriteFrame("versus/badge_gold_big.png");
        }
        else if (currentPoints == 2)
        {
            _badge->setSpriteFrame("versus/badge_silver_big.png");
        }
        else if (currentPoints == 1)
        {
            _badge->setSpriteFrame("versus/badge_bronze_big.png");
        }
        else if (currentPoints == 0)
        {
            _badge->setSpriteFrame("versus/badge_blank_big.png");
        }
        
        float previousPercentage = getPercentage(previousWins, currentPoints);
        _progressBar->setPercentage(previousPercentage);
        
        player2->addConsecutiveWins(1);
        player1->setConsecutiveWins(0);

        player2->addWins(1);
        player1->addLosses(1);
        
        int wins = player2->getWins();
        
        if (wins >= 10)
        {
            player2->setPoints(3);
        }
        else if (wins >= 6)
        {
            player2->setPoints(2);
        }
        else if (wins >= 3)
        {
            player2->setPoints(1);
        }
        else
        {
            player2->setPoints(0);
        }
        
        int newPoints = player2->getPoints();
        
        float newPercentage = getPercentage(wins, currentPoints);
        
        Sequence *sequence = Sequence::create(AnimatingNumber::create(2.f, previousPercentage, newPercentage, [&](float current){
            _progressBar->setPercentage(current);
        }), CallFunc::create([&, newPoints](){
            if (newPoints == 1) {
                _badge->setSpriteFrame("versus/badge_bronze_big.png");
            }
            else if (newPoints == 2)
            {
                _badge->setSpriteFrame("versus/badge_silver_big.png");
            }
            else if (newPoints >= 3)
            {
                _badge->setSpriteFrame("versus/badge_gold_big.png");
            }
        }), NULL);
        
        this->runAction(sequence);
    }
    
    PlayerManager::getInstance()->save();
}

void PostGameVersusDialog::onPressRestart(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        this->removeFromParent();
        
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RESTART_GAME);
    }
}

void PostGameVersusDialog::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        MainMenuScene *layer = MainMenuScene::createFromCCB();
        Scene *scene = Scene::create();
        
        scene->addChild(layer);
        
        Director::getInstance()->replaceScene(scene);
    }
}

float PostGameVersusDialog::getPercentage(int wins, int points)
{
    float retVal = 0.f;
    
    if (points >= 3)
    {
        retVal = 100.f;
    }
    else
    {
        float min = 0;
        float max = 3;
        if (points == 0) {
            min = 0;
            max = 3;
        }
        else if (points == 1)
        {
            min = 3;
            max = 6;
        }
        else if (points == 2)
        {
            min = 6;
            max = 10;
        }
        retVal = ((wins - min) / (max - min)) * 100.f;
    }
    return retVal;
}


#pragma mark - CCBMemberVariableAssigner functions

bool PostGameVersusDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_titleName", cocos2d::Label*, _titleName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelRemarks", cocos2d::Label*, _labelRemarks);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_badge", cocos2d::Sprite*, _badge);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_progressBarContainer", cocos2d::Sprite*, _progressBarContainer);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_progressBarFill", cocos2d::Sprite*, _progressBarFill);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRestart", cocos2d::extension::ControlButton*, _buttonRestart);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHome", cocos2d::extension::ControlButton*, _buttonHome);
    
    return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PostGameVersusDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressRestart", PostGameVersusDialog::onPressRestart);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", PostGameVersusDialog::onPressHome);
    
    return NULL;
}


#pragma mark - NodeLoaderListener functions

void PostGameVersusDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    _progressBar = ProgressTimer::create(_progressBarFill);
    _progressBar->setMidpoint(Vec2::ANCHOR_MIDDLE_LEFT);
    _progressBar->setType(ProgressTimer::Type::BAR);
    _progressBar->setBarChangeRate(Vec2(1.f, 0));
    
    Size barContainerSize = _progressBarContainer->getContentSize();
    _progressBar->setPosition(Vec2(barContainerSize.width * 0.5f, barContainerSize.height * 0.5f));
    
    _progressBarFill->setLocalZOrder(-1);
    _progressBarContainer->addChild(_progressBar, 1);
}


#pragma mark - CCBAnimationManagerDelegate functions

void PostGameVersusDialog::completedAnimationSequenceNamed(const char *name)
{
    if (strcmp(name, "Default Timeline") == 0)
    {
        
    }
    
}


