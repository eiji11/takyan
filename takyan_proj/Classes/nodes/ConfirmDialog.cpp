#include "ConfirmDialog.h"


USE_NS

ConfirmDialog *ConfirmDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("ConfirmDialog", ConfirmDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<ConfirmDialog*>(ccbReader->readNodeGraphFromFile("ConfirmDialog.ccbi"));
}

ConfirmDialog::ConfirmDialog() : cocos2d::Layer()
, _labelTitle(NULL)
, _buttonOk(NULL)
, _buttonBack(NULL)
{

}

ConfirmDialog::~ConfirmDialog()
{
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_buttonOk);
	CC_SAFE_RELEASE(_buttonBack);
}

void ConfirmDialog::onEnter()
{
	cocos2d::Layer::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);

    UI_LOCK_MANAGER_INCREASE();
}

void ConfirmDialog::onExit()
{
	cocos2d::Layer::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

    UI_LOCK_MANAGER_DECREASE();
}

void ConfirmDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	cocos2d::log("CONFIRM DIALOG BACK: %d", UI_LOCK_MANAGER->getLockLevel(VAR_LOCK_CONTEXT));
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
            onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void ConfirmDialog::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		if (_okCallback != nullptr)
		{
			_okCallback();
		}

		this->removeFromParent();
	}
}

void ConfirmDialog::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		if (_backCallback != nullptr)
		{
			_backCallback();
		}

		this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool ConfirmDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler ConfirmDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", ConfirmDialog::onPressOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", ConfirmDialog::onPressBack);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void ConfirmDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void ConfirmDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


