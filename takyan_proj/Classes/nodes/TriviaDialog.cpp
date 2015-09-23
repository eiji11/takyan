#include "TriviaDialog.h"

#include "TriviaContents.h"


USE_NS

bool TriviaDialog::shown = false;

TriviaDialog *TriviaDialog::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    
    ccNodeLoaderLibrary->registerNodeLoader("TriviaDialog", TriviaDialogLoader::loader());
    ccNodeLoaderLibrary->registerNodeLoader("TriviaContents", TriviaContentsLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<TriviaDialog*>(ccbReader->readNodeGraphFromFile("TriviaDialog.ccbi"));
}

TriviaDialog::TriviaDialog() : cocos2d::Layer()
, _scrollView(NULL)
, _labelTitle(NULL)
, _buttonOk(NULL)
{

}

TriviaDialog::~TriviaDialog()
{
	CC_SAFE_RELEASE(_scrollView);
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_buttonOk);
}

void TriviaDialog::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
    animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    auto viewSize = _scrollView->getViewSize();
    auto contentSize = _scrollView->getContentSize();
    _scrollView->setContentOffset(Vec2(0, -(contentSize.height - viewSize.height)), false);

    
    UI_LOCK_MANAGER_INCREASE();
}

void TriviaDialog::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();
}

void TriviaDialog::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
        	this->removeFromParent();
    	}));
    }
}

void TriviaDialog::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool TriviaDialog::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_scrollView", cocos2d::extension::ScrollView*, _scrollView);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler TriviaDialog::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", TriviaDialog::onPressOk);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void TriviaDialog::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
    _scrollView->setDirection(ScrollView::Direction::VERTICAL);
    _scrollView->setBounceable(false);
}


#pragma mark - CCBAnimationManagerDelegate functions

void TriviaDialog::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


