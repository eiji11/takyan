#include "TriviaContents.h"


USE_NS

TriviaContents *TriviaContents::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("TriviaContents", TriviaContentsLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<TriviaContents*>(ccbReader->readNodeGraphFromFile("TriviaContents.ccbi"));
}

TriviaContents::TriviaContents() : cocos2d::Layer()
, _labelTrivia(NULL)
, _imageTrivia(NULL)
{

}

TriviaContents::~TriviaContents()
{
	CC_SAFE_RELEASE(_labelTrivia);
	CC_SAFE_RELEASE(_imageTrivia);
}

void TriviaContents::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);
}

void TriviaContents::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}


#pragma mark - CCBMemberVariableAssigner functions

bool TriviaContents::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTrivia", cocos2d::Label*, _labelTrivia);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_imageTrivia", cocos2d::Sprite*, _imageTrivia);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler TriviaContents::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void TriviaContents::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void TriviaContents::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


