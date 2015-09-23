#include "PauseDialog.h"

#include "MainMenuScene.h"


USE_NS

PauseDialog *PauseDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PauseDialog", PauseDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PauseDialog*>(ccbReader->readNodeGraphFromFile("PauseDialog.ccbi"));
}

PauseDialog::PauseDialog() : cocos2d::Layer()
, _labelTitle(NULL)
, _buttonRestart(NULL)
, _buttonPlay(NULL)
, _buttonHome(NULL)
{

}

PauseDialog::~PauseDialog()
{
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_buttonRestart);
	CC_SAFE_RELEASE(_buttonPlay);
	CC_SAFE_RELEASE(_buttonHome);
}

void PauseDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void PauseDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();
}

void PauseDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		this->removeFromParent();
    	}));
    }
}

void PauseDialog::onPressRestart(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        this->removeFromParent();
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_RESTART_GAME);
	}
}

void PauseDialog::onPressPlay(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        this->removeFromParent();
	}
}

void PauseDialog::onPressHome(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
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

bool PauseDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonRestart", cocos2d::extension::ControlButton*, _buttonRestart);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonPlay", cocos2d::extension::ControlButton*, _buttonPlay);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonHome", cocos2d::extension::ControlButton*, _buttonHome);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PauseDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressRestart", PauseDialog::onPressRestart);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressPlay", PauseDialog::onPressPlay);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressHome", PauseDialog::onPressHome);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PauseDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void PauseDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


