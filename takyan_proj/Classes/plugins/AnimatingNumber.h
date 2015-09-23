//
//  AnimatingNumber.h
//  Takyan
//
//  Created by bibi-apple on 31/3/15.
//
//

#ifndef __Takyan__AnimatingNumber__
#define __Takyan__AnimatingNumber__

#include "cocos2d.h"

#include <functional>

class AnimatingNumber : public cocos2d::ActionInterval
{
public:
    static AnimatingNumber* create(float duration, float from, float to, std::function<void(float current)> callback);
    
    AnimatingNumber();
    
    bool init(float duration, float from, float to, std::function<void(float current)> callback);
    
    virtual void update(float dt);
    
    float getFrom()
    {
        return _from;
    }
    
    float getTo()
    {
        return _to;
    }
    
protected:
    float _from;
    float _to;
    std::function<void(float current)> _callback;
};

#endif /* defined(__Takyan__AnimatingNumber__) */
