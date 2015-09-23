//
//  AnimatingNumber.cpp
//  Takyan
//
//  Created by bibi-apple on 31/3/15.
//
//

#include "AnimatingNumber.h"

USING_NS_CC;

AnimatingNumber *AnimatingNumber::create(float duration, float from, float to, std::function<void(float current)> callback)
{
    AnimatingNumber *retVal = new AnimatingNumber();
    if (retVal->init(duration, from, to, callback))
    {
        retVal->autorelease();
        return retVal;
    }
    
    delete retVal;
    retVal = nullptr;
    return nullptr;
}

AnimatingNumber::AnimatingNumber() : cocos2d::ActionInterval()
, _from(0)
, _to(100)
, _callback(nullptr)
{
    
}

bool AnimatingNumber::init(float duration, float from, float to, std::function<void (float)> callback)
{
    ActionInterval::initWithDuration(duration);
    
    _from = from;
    _to = to;
    _callback = callback;
    
    return true;
}

void AnimatingNumber::update(float dt)
{
    if (_callback != nullptr)
    {
        float newVal = _from + ((_to - _from) * dt);
        _callback(newVal);
    }
}