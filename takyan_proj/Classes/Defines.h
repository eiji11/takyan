//
//  Defines.h
//  WaterQuiz
//
//  Created by bibi-apple on 26/12/14.
//
//

#ifndef WaterQuiz_Defines_h
#define WaterQuiz_Defines_h

#define CREATE_CLASS_LOADER(nodeType, baseLoader) \
class nodeType##Loader : public baseLoader \
{ \
public: \
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(nodeType##Loader, loader); \
private: \
    SB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(nodeType); \
}

#define USE_NS \
USING_NS_CC; \
USING_NS_CC_EXT; \
using namespace spritebuilder;

#define CREATE_HANDLER(funcName) \
void funcName(cocos2d::Ref * sender, cocos2d::extension::Control::EventType pControlEvent)

#define CCBMEMBER_FUNCTIONS \
virtual bool onAssignCCBMemberVariable(cocos2d::Ref* pTarget, const char* pMemberVariableName, cocos2d::Node* pNode); \
virtual bool onAssignCCBCustomProperty(cocos2d::Ref* target, const char* memberVariableName, const cocos2d::Value& value){ return false; };

#define CCBSELECTOR_FUNCTIONS \
virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::Ref * pTarget, const char* pSelectorName){ return NULL; } \
virtual cocos2d::SEL_CallFuncN onResolveCCBCCCallFuncSelector(cocos2d::Ref * pTarget, const char* pSelectorName) { return NULL; } \
virtual cocos2d::extension::Control::Handler onResolveCCBCCControlSelector(cocos2d::Ref * pTarget, const char* pSelectorName);

typedef std::vector<cocos2d::ValueMap> ValueMapList;

#define PHYSICS_MASK(body, category, contact, collision) \
body->setCategoryBitmask(category); \
body->setContactTestBitmask(contact); \
body->setCollisionBitmask(collision);

#define PHYSICS_SET_FRICTION(body, friction) \
for (auto shape : body->getShapes()) \
{ \
shape->setFriction(friction); \
}

#define PHYSICS_SET_DENSITY(body, density) \
for (auto shape : body->getShapes()) \
{ \
shape->setDensity(density); \
}

#define PHYSICS_SET_RESTITUTION(body, restitution) \
for (auto shape : body->getShapes()) \
{ \
shape->setRestitution(restitution); \
}

#define BALL_RADIUS 0.625f
#define KICKER_RADIUS 0.85f

#define MASK_FLOOR 1
#define MASK_WALLS 2
#define MASK_BOUNDS (MASK_FLOOR | MASK_WALLS)
#define MASK_TAKYAN 4
#define MASK_KICKER 8
#define MASK_TAKYAN_TAIL 16
#define MASK_TAKYAN_FAKE 32

#define PI 3.14159265358979323846f

#define PLAYER_1_INDEX 0
#define PLAYER_2_INDEX 1

#define GENDER_MALE 0
#define GENDER_FEMALE 1


#define EVENT_RESTART_GAME "restart_game"

#define EVENT_PLAYER_ADDED "player_added"
#define EVENT_PLAYERS_RELOAD "players_reload"
#define EVENT_PLAYER_SELECTED "player_selected"

#endif
