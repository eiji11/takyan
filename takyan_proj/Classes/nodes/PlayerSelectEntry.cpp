#include "PlayerSelectEntry.h"

#include "managers_caches/ObserverManager.h"


USE_NS

PlayerSelectEntry *PlayerSelectEntry::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PlayerSelectEntry", PlayerSelectEntryLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PlayerSelectEntry*>(ccbReader->readNodeGraphFromFile("PlayerSelectEntry.ccbi"));
}

PlayerSelectEntry::PlayerSelectEntry() : cocos2d::Layer()
, _background(NULL)
, _labelName(NULL)
, _labelGender(NULL)
, _labelLevel(NULL)
{

}

PlayerSelectEntry::~PlayerSelectEntry()
{
    CC_SAFE_RELEASE(_background);
	CC_SAFE_RELEASE(_labelName);
	CC_SAFE_RELEASE(_labelGender);
	CC_SAFE_RELEASE(_labelLevel);
}

void PlayerSelectEntry::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);
    
    OBSERVE(this, EVENT_PLAYER_SELECTED, [&](EventCustom *event){
        PlayerData *selectedPlayer = (PlayerData*)(event->getUserData());
        this->setSelected(selectedPlayer == _player);
    });
}

void PlayerSelectEntry::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UNOBSERVE(this);
}

void PlayerSelectEntry::setPlayer(PlayerData *player)
{
    _player = player;
    
    if (_player != nullptr)
    {
        _player->retain();
        
        _labelName->setString(_player->getName());
        _labelGender->setString(_player->getGender() == GENDER_MALE ? "Male" : "Female");
        _labelLevel->setString(StringUtils::format("%d", _player->getLevel()));
    }
}

void PlayerSelectEntry::setSelected(bool selected)
{
    Color3B color = Color3B(180, 120, 45);
    if (selected)
    {
        color = Color3B::WHITE;
    }
    _background->setColor(color);
}


#pragma mark - CCBMemberVariableAssigner functions

bool PlayerSelectEntry::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_background", cocos2d::LayerColor*, _background);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelName", cocos2d::Label*, _labelName);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelGender", cocos2d::Label*, _labelGender);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelLevel", cocos2d::Label*, _labelLevel);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PlayerSelectEntry::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PlayerSelectEntry::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void PlayerSelectEntry::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


