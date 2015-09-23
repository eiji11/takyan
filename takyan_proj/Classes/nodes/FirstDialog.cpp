#include "FirstDialog.h"


USE_NS

FirstDialog *FirstDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("FirstDialog", FirstDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<FirstDialog*>(ccbReader->readNodeGraphFromFile("FirstDialog.ccbi"));
}

FirstDialog::FirstDialog() : cocos2d::Layer()
, _labelTitle(NULL)
, _labelSet(NULL)
, _buttonPlay(NULL)
, _labelFirstTitle(NULL)
{

}

FirstDialog::~FirstDialog()
{
    CC_SAFE_RELEASE(_labelTitle);
    CC_SAFE_RELEASE(_labelSet);
	CC_SAFE_RELEASE(_buttonPlay);
	CC_SAFE_RELEASE(_labelFirstTitle);
}

void FirstDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);

	UI_LOCK_MANAGER_INCREASE();
}

void FirstDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

	UI_LOCK_MANAGER_DECREASE();
}

void FirstDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		this->removeFromParent();
    	}));
    }
}

void FirstDialog::setGameData(VersusGameData *gameData)
{
    m_gameData = gameData;
    m_gameData->retain();
    
    PlayerData *player = m_gameData->getCurrentGame()->getPlayer();
    _labelFirstTitle->setString(player->getName());
    
    int sets = m_gameData->getSets();
    int currentSet = m_gameData->getCurrentSet();
    
    std::string text = StringUtils::format("Set %d of %d", currentSet + 1, sets);
    _labelSet->setString(text);
}

void FirstDialog::onPressPlay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool FirstDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelSet", cocos2d::Label*, _labelSet);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlay", cocos2d::extension::ControlButton*, _buttonPlay);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelFirstTitle", cocos2d::Label*, _labelFirstTitle);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler FirstDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPlay", FirstDialog::onPressPlay);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void FirstDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void FirstDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


