//
//  AssortedUtils.cpp
//  WaterQuiz
//
//  Created by bibi-apple on 15/1/15.
//
//

#include "AssortedUtils.h"

USING_NS_CC;
USING_NS_CC_EXT;


std::string AssortedUtils::getRandomString(ssize_t len)
{
    static std::string characters = "abscdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    int characterCount = characters.length();
    
    std::string retVal = "";
    
    for (int x = 0; x < len; x++)
    {
        retVal += characters.at((int)(CCRANDOM_0_1() * characterCount));
    }
    
    return retVal;
}

std::string AssortedUtils::getRandomNumber(ssize_t len)
{
    std::string retVal = "";
    
    for (int x = 0; x < len; x++)
    {
        retVal += (int)(random01() * 10);
    }
    
    return retVal;
}

void AssortedUtils::fixFontSize(cocos2d::Label *label)
{
    Size dimensions = label->getDimensions();
    if (!(dimensions.width == 0 || dimensions.height == 0))
    {
        Rect bounds = label->getBoundingBox();
        Size boundsSize = bounds.size;
        TTFConfig config = label->getTTFConfig();
        float fontSize = config.fontSize;
        float widthAllowance = dimensions.width * 1.1f;
        float heightAllowance = dimensions.height * 1.1f;
        if (boundsSize.width > widthAllowance && boundsSize.height < heightAllowance)
        {
            float newScale = widthAllowance / boundsSize.width;
            fontSize *= newScale;
        }
        else if (boundsSize.width < widthAllowance && boundsSize.height > heightAllowance)
        {
            float newScale = heightAllowance / boundsSize.height;
            fontSize *= newScale;
        }
        else if (boundsSize.width > widthAllowance && boundsSize.height > heightAllowance)
        {
            float boundsH = sqrtf((boundsSize.width * boundsSize.width) + (boundsSize.height * boundsSize.height));
            float dimensionsH = sqrtf((widthAllowance * widthAllowance) + (heightAllowance * heightAllowance));
            float newScale = dimensionsH / boundsH;
            fontSize *= newScale;
        }
        
        config.fontSize = fontSize;
        label->setTTFConfig(config);
    }
}

std::string AssortedUtils::makeSpace(int spaces)
{
    std::stringstream stream;
    for (int x = 0; x < spaces; x++)
    {
        stream << "\t";
    }
    return stream.str();
}

std::string AssortedUtils::readValue(cocos2d::Value value, int spaces)
{
    std::string retVal;
    
    std::string spacer = makeSpace(spaces);
    
    
    Value::Type type = value.getType();
    if (type == Value::Type::MAP)
    {
        retVal += "{\n";
        
        std::string spacer2 = makeSpace(spaces + 1);
        
        auto map = value.asValueMap();
        for (auto it : map)
        {
            retVal += spacer2;
            retVal += "\"" + it.first + "\" : ";
            retVal += readValue(it.second, spaces + 1);
            retVal += ", \n";
        }
        
        retVal += spacer;
        retVal += "}";
    }
    else if (type == Value::Type::INT_KEY_MAP)
    {
        retVal += "{\n";
        
        std::string spacer2 = makeSpace(spaces + 1);
        
        auto map = value.asIntKeyMap();
        for (auto it : map)
        {
            retVal += spacer2;
            retVal += StringUtils::format("%d : ", it.first);
            retVal += readValue(it.second, spaces + 1);
            retVal += ", \n";
        }
        
        retVal += spacer;
        retVal += "}";
    }
    else if (type == Value::Type::VECTOR)
    {
        retVal += "[\n";
        
        std::string spacer2 = makeSpace(spaces + 1);
        
        auto vector = value.asValueVector();
        for (auto it : vector)
        {
            retVal += spacer2;
            retVal += readValue(it, spaces + 1);
            retVal += ",\n";
        }
        
        retVal += spacer;
        retVal += "]";
    }
    else if (type == Value::Type::STRING)
    {
        retVal += "\"" + value.asString() + "\"";
    }
    else
    {
        retVal += value.asString();
    }
    
    return retVal;
}

void AssortedUtils::setNodeAncestryGlobalZOrder(cocos2d::Node *node, int zOrder)
{
    node->setGlobalZOrder(zOrder);
    for (auto child : node->getChildren())
    {
        setNodeAncestryGlobalZOrder(child, zOrder);
    }
}

void AssortedUtils::setNodeChildrenLocalZOrder(cocos2d::Node *node, int zOrder)
{
    for (auto child : node->getChildren())
    {
        child->setLocalZOrder(zOrder);
    }
}

void AssortedUtils::unifyButtonSprites(cocos2d::extension::ControlButton *button, std::string frameName)
{
    SpriteFrame *bg = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
    button->setBackgroundSpriteFrameForState(bg, Control::State::NORMAL);
    button->setBackgroundSpriteFrameForState(bg, Control::State::DISABLED);
    button->setBackgroundSpriteFrameForState(bg, Control::State::HIGH_LIGHTED);
    button->setBackgroundSpriteFrameForState(bg, Control::State::SELECTED);
}

float AssortedUtils::random01()
{
    auto randomer = [&](){
        std::srand(std::time(nullptr));
        return CCRANDOM_0_1();
    };
    return randomer();
}
