#include "InstructionsDialog.h"


USE_NS

InstructionsDialog *InstructionsDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("InstructionsDialog", InstructionsDialogLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<InstructionsDialog*>(ccbReader->readNodeGraphFromFile("InstructionsDialog.ccbi"));
}

InstructionsDialog::InstructionsDialog() : cocos2d::Layer()
, _labelTitle(NULL)
, _buttonOk(NULL)
, _scrollView(NULL)
{

}

InstructionsDialog::~InstructionsDialog()
{
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_buttonOk);
	CC_SAFE_RELEASE(_scrollView);
}

void InstructionsDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	auto viewSize = _scrollView->getViewSize();
	auto contentSize = _scrollView->getContentSize();
	_scrollView->setContentOffset(Vec2(0, -(contentSize.height - viewSize.height)), false);

	setKeyboardEnabled(true);

	UI_LOCK_MANAGER_INCREASE();
}

void InstructionsDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

	UI_LOCK_MANAGER_DECREASE();
}

void InstructionsDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		this->removeFromParent();
    	}));
    }
}

void InstructionsDialog::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool InstructionsDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_scrollView", cocos2d::extension::ScrollView*, _scrollView);


	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler InstructionsDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", InstructionsDialog::onPressOk);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void InstructionsDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	_scrollView->setDirection(ScrollView::Direction::VERTICAL);
	_scrollView->setBounceable(false);
}


#pragma mark - CCBAnimationManagerDelegate functions

void InstructionsDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


