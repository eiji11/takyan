#ifndef __Takyan__TriviaContents__
#define __Takyan__TriviaContents__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "spritebuilder/SpriteBuilder.h"

#include "Defines.h"


class TriviaContents : public cocos2d::Layer
, public spritebuilder::CCBMemberVariableAssigner
, public spritebuilder::CCBSelectorResolver
, public spritebuilder::CCBAnimationManagerDelegate
, public spritebuilder::NodeLoaderListener
{
public:
	CREATE_FUNC(TriviaContents);
	static TriviaContents* createFromCCB();

	TriviaContents();
	virtual ~TriviaContents();

	virtual void onEnter();
	virtual void onExit();


private:
	CCBMEMBER_FUNCTIONS 
	CCBSELECTOR_FUNCTIONS 

	virtual void onNodeLoaded(cocos2d::Node * pNode, spritebuilder::NodeLoader * pNodeLoader);

	virtual void completedAnimationSequenceNamed(const char *name);


private:
	cocos2d::Label *_labelTrivia;
	cocos2d::Sprite *_imageTrivia;

};

CREATE_CLASS_LOADER(TriviaContents, spritebuilder::LayerLoader);


#endif /* defined(__Takyan__TriviaContents__) */
