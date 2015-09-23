#include "RecordsDialogEntry.h"


USE_NS

RecordsDialogEntry *RecordsDialogEntry::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("RecordsDialogEntry", RecordsDialogEntryLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<RecordsDialogEntry*>(ccbReader->readNodeGraphFromFile("RecordsDialogEntry.ccbi"));
}

RecordsDialogEntry::RecordsDialogEntry() : cocos2d::Layer()
, _background(NULL)
, _badge(NULL)
, _labelLosses(NULL)
, _labelWins(NULL)
, _labelPlays(NULL)
, _labelLevel(NULL)
, _labelGender(NULL)
, _labelName(NULL)
{

}

RecordsDialogEntry::~RecordsDialogEntry()
{
	CC_SAFE_RELEASE(_background);
	CC_SAFE_RELEASE(_badge);
	CC_SAFE_RELEASE(_labelLosses);
	CC_SAFE_RELEASE(_labelWins);
	CC_SAFE_RELEASE(_labelPlays);
	CC_SAFE_RELEASE(_labelLevel);
	CC_SAFE_RELEASE(_labelGender);
	CC_SAFE_RELEASE(_labelName);
}

void RecordsDialogEntry::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);
}

void RecordsDialogEntry::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);

}

void RecordsDialogEntry::setPlayer(PlayerData *player)
{
    _player = player;
    
    if (_player != nullptr)
    {
        _player->retain();
        
        _labelName->setString(_player->getName());
        _labelGender->setString(_player->getGender() == GENDER_MALE ? "Male" : "Female");
        _labelLevel->setString(StringUtils::format("%d", _player->getLevel()));
        _labelPlays->setString(StringUtils::format("%d", _player->getPlays()));
        _labelWins->setString(StringUtils::format("%d", _player->getWins()));
        _labelLosses->setString(StringUtils::format("%d", _player->getLosses()));
        
        int points = _player->getPoints();
        if (points == 1) {
            _badge->setSpriteFrame("versus/badge_bronze_small.png");
        }
        else if (points == 2)
        {
            _badge->setSpriteFrame("versus/badge_silver_small.png");
        }
        else if (points >= 3)
        {
            _badge->setSpriteFrame("versus/badge_gold_small.png");
        }
    }
}


#pragma mark - CCBMemberVariableAssigner functions

bool RecordsDialogEntry::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
    CCLOG("pMemberVariableName: %s", pMemberVariableName);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_background", cocos2d::LayerColor*, _background);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_badge", cocos2d::Sprite*, _badge);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelLosses", cocos2d::Label*, _labelLosses);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelWins", cocos2d::Label*, _labelWins);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelPlays", cocos2d::Label*, _labelPlays);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelLevel", cocos2d::Label*, _labelLevel);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelGender", cocos2d::Label*, _labelGender);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelName", cocos2d::Label*, _labelName);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler RecordsDialogEntry::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void RecordsDialogEntry::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	
}


#pragma mark - CCBAnimationManagerDelegate functions

void RecordsDialogEntry::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


