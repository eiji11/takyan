#include "AppDelegate.h"
#include "nodes/MainMenuScene.h"

#include "objects/PlayerManager.h"

USING_NS_CC;

using namespace spritebuilder;

#define PHYSIC_FACTOR 32

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview)
    {
        glview = GLViewImpl::create("Takyan");
        director->setOpenGLView(glview);
    }
    

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    Size size = director->getWinSize();
    
    float scaleFactor = size.height / 320.0f;
    glview->setDesignResolutionSize(size.width / scaleFactor, 320.0f, ResolutionPolicy::SHOW_ALL);
    
    director->setContentScaleFactor(scaleFactor / (size.height / 640.0f)); //because the current resource is phonehd's
    director->setDisplayStats(false);
    
    CCBReader::setupSpriteBuilder("resources-phonehd", PHYSIC_FACTOR);

    
    auto layer = MainMenuScene::createFromCCB();
    
    auto scene = Scene::create();
    scene->addChild(layer);

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
