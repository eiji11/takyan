//
//  AssortedUtils.h
//  WaterQuiz
//
//  Created by bibi-apple on 15/1/15.
//
//

#ifndef __WaterQuiz__AssortedUtils__
#define __WaterQuiz__AssortedUtils__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

#include "Defines.h"

class AssortedUtils
{
public:
    static std::string getRandomString(ssize_t len);
    static std::string getRandomNumber(ssize_t len);
    
    static void fixFontSize(cocos2d::Label* label);
    
    static std::string makeSpace(int spaces);
    static std::string readValue(cocos2d::Value value, int spaces);
    
    static void setNodeAncestryGlobalZOrder(cocos2d::Node *node, int zOrder);
    static void setNodeChildrenLocalZOrder(cocos2d::Node *node, int zOrder);
    
    static void unifyButtonSprites(cocos2d::extension::ControlButton *button, std::string frameName);
    
    static float random01();
    
};

#endif /* defined(__WaterQuiz__AssortedUtils__) */
