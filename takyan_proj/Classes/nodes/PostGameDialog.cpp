#include "PostGameDialog.h"

#include "MainMenuScene.h"
#include "SinglePlayerScene.h"

#include "objects/PlayerManager.h"
#include "objects/PlayerData.h"


USE_NS

PostGameDialog *PostGameDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PostGameDialog", PostGameDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PostGameDialog*>(ccbReader->readNodeGraphFromFile("PostGameDialog.ccbi"));
}

PostGameDialog::PostGameDialog() : cocos2d::Layer()
, _titleName(NULL)
, _labelHits(NULL)
, _labelScore(NULL)
, _labelRewards(NULL)
, _buttonRestart(NULL)
, _buttonHome(NULL)

, m_game(NULL)
{

}

PostGameDialog::~PostGameDialog()
{
    CC_SAFE_RELEASE(_titleName);
    CC_SAFE_RELEASE(_labelHits);
    CC_SAFE_RELEASE(_labelScore);
    CC_SAFE_RELEASE(_labelRewards);
    CC_SAFE_RELEASE(_buttonRestart);
    CC_SAFE_RELEASE(_buttonHome);
}

void PostGameDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER->changeLockLevel(VAR_LOCK_CONTEXT, 1);
}

void PostGameDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER->changeLockLevel(VAR_LOCK_CONTEXT, -1);
}

SingleGameData* PostGameDialog::getGameData()
{
    return m_game;
}

void PostGameDialog::setGameData(SingleGameData *game)
{
    m_game = game;
    m_game->retain();
    
    _labelHits->setString(StringUtils::format("%d", m_game->getHits()));
    _labelScore->setString(StringUtils::format("%d", m_game->getScore()));
    
    PlayerData *player = m_game->getPlayer();
    
    int level = player->getLevel();
    
    int skillsAcquired = 0;
    int backgroundsAcquired = 0;
    int powersAcquired = 0;
    
    if (level < 1 && (m_game->getHits() >= 10 || m_game->getScore() >= 15) && player->getPoints() >= 1)
    {
        skillsAcquired++;
        backgroundsAcquired++;
        powersAcquired++;
        player->setLevel(1);
    }
    
    if (level < 2 && (m_game->getHits() >= 20 || m_game->getScore() >= 30) && player->getPoints() >= 2)
    {
        skillsAcquired++;
        backgroundsAcquired++;
        powersAcquired++;
        player->setLevel(2);
    }
    
    if (level < 3 && (m_game->getHits() >= 30 || m_game->getScore() >= 50) && player->getPoints() >= 3)
    {
        powersAcquired++;
        player->setLevel(3);
    }
    
    std::string reward = "";
    if (m_game->getPreviousLevel() < player->getLevel()) {
        reward += "- Level Up!";
    }
    
    if (skillsAcquired > 1) {
        if (!reward.empty()) {
            reward += "\n";
        }
        reward += "- New Skills";
    }
    else if (skillsAcquired == 1)
    {
        if (!reward.empty()) {
            reward += "\n";
        }
        reward += "- New Skill";
    }
    
    if (powersAcquired > 1) {
        if (!reward.empty()) {
            reward += "\n";
        }
        reward += "- New Powers";
    }
    else if (powersAcquired == 1)
    {
        if (!reward.empty()) {
            reward += "\n";
        }
        reward += "- New Power";
    }
    
    if (backgroundsAcquired > 1) {
        if (!reward.empty()) {
            reward += "\n";
        }
        reward += "- New Battle Places";
    }
    else if (backgroundsAcquired == 1)
    {
        if (!reward.empty()) {
            reward += "\n";
        }
        reward += "- New Battle Place";
    }
    
    if (reward.empty())
    {
        if (level == 3) {
            reward = "- None. Max level.";
        }
        else
        {
            reward = "- None. Please try again.";
        }
    }
    
    _labelRewards->setString(reward);
    
    PlayerManager::getInstance()->save();
}

void PostGameDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressHome(_buttonHome, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void PostGameDialog::onPressRestart(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        this->removeFromParent();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RESTART_GAME);
    }
}

void PostGameDialog::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
    if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        MainMenuScene *layer = MainMenuScene::createFromCCB();
        Scene *scene = Scene::create();
        
        scene->addChild(layer);
        
        Director::getInstance()->replaceScene(scene);
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool PostGameDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_titleName", cocos2d::Label*, _titleName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelHits", cocos2d::Label*, _labelHits);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelScore", cocos2d::Label*, _labelScore);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelRewards", cocos2d::Label*, _labelRewards);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRestart", cocos2d::extension::ControlButton*, _buttonRestart);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHome", cocos2d::extension::ControlButton*, _buttonHome);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PostGameDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressRestart", PostGameDialog::onPressRestart);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", PostGameDialog::onPressHome);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PostGameDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    Vector<Node*> children = this->getChildren().front()->getChildren();
    
    for (Node *n : children)
    {
        n->setLocalZOrder(10);
    }
}


#pragma mark - CCBAnimationManagerDelegate functions

void PostGameDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


