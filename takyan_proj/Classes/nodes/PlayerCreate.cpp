#include "PlayerCreate.h"

#include "managers_caches/AssortedUtils.h"


USE_NS
using namespace ui;

PlayerCreate *PlayerCreate::createFromCCB()
{
	NodeLoaderLibrary * ccNodeLoaderLibrary = NodeLoaderLibrary::getInstance();

	ccNodeLoaderLibrary->registerNodeLoader("PlayerCreate", PlayerCreateLoader::loader());

	spritebuilder::CCBReader *ccbReader = new spritebuilder::CCBReader(ccNodeLoaderLibrary);

	return dynamic_cast<PlayerCreate*>(ccbReader->readNodeGraphFromFile("PlayerCreate.ccbi"));
}

PlayerCreate::PlayerCreate() : cocos2d::Layer()
, _labelTitle(NULL)
, _buttonOk(NULL)
, _buttonBack(NULL)
, _labelName(NULL)
, _inputName(NULL)
, _placeHolderInputName(NULL)
, _textfieldBG(NULL)
, _labelGender(NULL)
, _buttonMale(NULL)
, _buttonFemale(NULL)
, _buttonDelete(NULL)
{

}

PlayerCreate::~PlayerCreate()
{
	CC_SAFE_RELEASE(_labelTitle);
	CC_SAFE_RELEASE(_buttonOk);
    CC_SAFE_RELEASE(_buttonBack);
    CC_SAFE_RELEASE(_labelName);
    CC_SAFE_RELEASE(_placeHolderInputName);
    CC_SAFE_RELEASE(_textfieldBG);
	CC_SAFE_RELEASE(_labelGender);
	CC_SAFE_RELEASE(_buttonMale);
	CC_SAFE_RELEASE(_buttonFemale);
	CC_SAFE_RELEASE(_buttonDelete);
}

void PlayerCreate::onEnter()
{
	cocos2d::Node::onEnter();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(this);

	setKeyboardEnabled(true);
    
    UI_LOCK_MANAGER_INCREASE();
}

void PlayerCreate::onExit()
{
	cocos2d::Node::onExit();

	CCBAnimationManager *animationManager = dynamic_cast<CCBAnimationManager*>(this->getUserObject());
	animationManager->setDelegate(NULL);
    
    UI_LOCK_MANAGER_DECREASE();
}

void PlayerCreate::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if ((keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) && !IS_LOCKED) {
    	this->runAction(CallFunc::create([&](){
    		onPressBack(_buttonBack, Control::EventType::TOUCH_UP_INSIDE);
    	}));
    }
}

void PlayerCreate::setPlayer(PlayerData *player)
{
    _player = player;
    
    if (_player != nullptr)
    {
        _player->retain();
        
        _inputName->setString(_player->getName());
        int gender = _player->getGender();
        if (gender == GENDER_MALE)
        {
            _buttonMale->setHighlighted(true);
            _buttonFemale->setHighlighted(false);
        }
        else
        {
            _buttonMale->setHighlighted(false);
            _buttonFemale->setHighlighted(true);
        }
    }
}

void PlayerCreate::editBoxReturn(cocos2d::ui::EditBox* editBox)
{
}

void PlayerCreate::onPressOk(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		std::string name = _inputName->getString();
		if (!name.empty())
		{
			_player->setName(_inputName->getString());

			auto players = PlayerManager::getInstance()->getPlayers();

			std::string debug = "";

			for (auto playerIT : players)
			{
				debug += AssortedUtils::readValue(Value(playerIT.second->getData()), 0);\
			}

			CCLOG("debug: %s", debug.c_str());


			std::string pId = _player->getID();
			bool hasPlayer = PlayerManager::getInstance()->hasPlayer(pId);
			if (!hasPlayer)
			{
				if (PlayerManager::getInstance()->addPlayer(_player))
				{
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYERS_RELOAD);
					PlayerManager::getInstance()->save();
				}
			}
			else
			{
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYERS_RELOAD);
				PlayerManager::getInstance()->save();
			}

			this->removeFromParent();
		}
	}
}

void PlayerCreate::onPressBack(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
        this->removeFromParent();
	}
}

void PlayerCreate::onPressGender(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
    {
        if (sender == _buttonMale)
        {
            _buttonMale->setHighlighted(true);
            _buttonFemale->setHighlighted(false);
            
            _player->setGender(GENDER_MALE);
        }
        else if (sender == _buttonFemale)
        {
            _buttonMale->setHighlighted(false);
            _buttonFemale->setHighlighted(true);
            
            _player->setGender(GENDER_FEMALE);
        }
	}
}

void PlayerCreate::onPressDelete(cocos2d::Ref *sender, cocos2d::extension::Control::EventType pControlEvent)
{
	if (pControlEvent == Control::EventType::TOUCH_UP_INSIDE)
	{
		if (_player != nullptr)
		{
			std::string playerId = _player->getID();
			PlayerManager::getInstance()->removePlayer(playerId);
			PlayerManager::getInstance()->save();

			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_PLAYERS_RELOAD);
		}

        this->removeFromParent();
	}
}


#pragma mark - CCBMemberVariableAssigner functions

bool PlayerCreate::onAssignCCBMemberVariable(cocos2d::Ref *pTarget, const char *pMemberVariableName, cocos2d::Node *pNode)
{
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelTitle", cocos2d::Label*, _labelTitle);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonOk", cocos2d::extension::ControlButton*, _buttonOk);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonBack", cocos2d::extension::ControlButton*, _buttonBack);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelName", cocos2d::Label*, _labelName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_placeHolderInputName", cocos2d::Node*, _placeHolderInputName);
    SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_textfieldBG", cocos2d::LayerColor*, _textfieldBG);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_labelGender", cocos2d::Label*, _labelGender);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonMale", cocos2d::extension::ControlButton*, _buttonMale);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonFemale", cocos2d::extension::ControlButton*, _buttonFemale);
	SB_MEMBERVARIABLEASSIGNER_GLUE(this, "_buttonDelete", cocos2d::extension::ControlButton*, _buttonDelete);

	return false;
}


#pragma mark - CCBSelectorResolver functions

Control::Handler PlayerCreate::onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressOk", PlayerCreate::onPressOk);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressBack", PlayerCreate::onPressBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressGender", PlayerCreate::onPressGender);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onPressDelete", PlayerCreate::onPressDelete);

	return NULL;
}


#pragma mark - NodeLoaderListener functions

void PlayerCreate::onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader)
{
	/*
    _inputName = EditBox::create(_placeHolderInputName->getContentSize(), "ccbResources/ccbTextField.png", Widget::TextureResType::PLIST);
    _inputName->setFontColor(Color3B::BLACK);
    _inputName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _inputName->setReturnType(EditBox::KeyboardReturnType::DONE);
    _inputName->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _inputName->setDelegate(this);
    */
	_inputName = TextField::create();
	_inputName->setColor(Color3B::BLACK);
	_inputName->setMaxLengthEnabled(true);
	_inputName->setMaxLength(15);

	Size tSize = _textfieldBG->getContentSize();
	_inputName->setPosition(Vec2(tSize.width * 0.5f, tSize.height * 0.5f));
	_inputName->setSize(tSize);



    _textfieldBG->addChild(_inputName);
    
    
    AssortedUtils::unifyButtonSprites(_buttonOk, "single_player/btn_ok.png");
    AssortedUtils::unifyButtonSprites(_buttonBack, "single_player/btn_back.png");
}


#pragma mark - CCBAnimationManagerDelegate functions

void PlayerCreate::completedAnimationSequenceNamed(const char *name)
{
	if (strcmp(name, "Default Timeline") == 0)
	{
		
	}
	
}


