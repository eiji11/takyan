//
//  CBClassBuilderMacros.h
//  WaterQuiz
//
//  Created by bibi-apple on 10/1/15.
//
//

#ifndef WaterQuiz_CBClassBuilderMacros_h
#define WaterQuiz_CBClassBuilderMacros_h

#include "AssortedUtils.h"

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


#define CCB_FIX_Z(children) \
for (int x = 0; x < children.size(); x++) { \
Node *node = children.at(x); \
node->setLocalZOrder(x); \
}

#define CCB_DETACH_CHILDREN(node) \
{ \
auto children = node->getChildren(); \
for (auto node : children) { \
node->removeFromParent(); \
} \
}

#define CCB_TRANSFER_CHILDREN(origin, destination) \
{ \
auto originChildren = origin->getChildren(); \
for (auto node : originChildren) { \
node->removeFromParent(); \
destination->addChild(node, node->getLocalZOrder()); \
} \
}

#define CCB_TRANSFER_NODES(nodes, destination) \
{ \
for (auto node : nodes) { \
destination->addChild(node, node->getLocalZOrder()); \
} \
}

#endif
