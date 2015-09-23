#ifndef _SB_CCEDITBOXLOADER_H_
#define _SB_CCEDITBOXLOADER_H_

#include "CCControlLoader.h"
#include "ui/UIEditBox/UIEditBox.h"

namespace spritebuilder {
    
/* Forward declaration. */
class CCBReader;


class EditBoxLoader : public spritebuilder::NodeLoader {
public:
    //EditBoxLoader() {}
    /**
     * @js NA
     * @lua NA
     */
    virtual ~EditBoxLoader() {};
    /**
     * @js NA
     * @lua NA
     */
   
    SB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EditBoxLoader, loader);
    
protected:
    
    virtual void onHandlePropTypeCheck(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, bool pCheck, CCBReader * ccbReader);
    
//    virtual cocos2d::extension::ControlButton * createNode(cocos2d::Node * pParent, CCBReader * ccbReader);
    virtual cocos2d::ui::EditBox * createNode(cocos2d::Node * pParent, CCBReader * ccbReader);

    /**
     * @js NA
     * @lua NA
     */
    
    virtual void onHandlePropTypeSize(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, cocos2d::Size pSize, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeSpriteFrame(cocos2d::Node * pNode, cocos2d::Node * pParent, const char * pPropertyName, cocos2d::SpriteFrame * pSpriteFrame, CCBReader * ccbReader);
    /**
     * @js NA
     * @lua NA
     */
    virtual void onHandlePropTypeFloatScale(cocos2d::Node * pNode, cocos2d::Node * pParent, const char* pPropertyName, float pFloatScale, CCBReader * ccbReader);

};


};

#endif
