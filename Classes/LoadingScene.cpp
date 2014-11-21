//
//  LoadingScene.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "LoadingScene.h"
#include "WelcomeScene.h"

LoadingScene::LoadingScene()
{

}

LoadingScene::~LoadingScene()
{

}

bool LoadingScene::init() {
    if(Scene::init()) {
        Sprite* background = Sprite::create("splash.png");
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Point origin = Director::getInstance()->getVisibleOrigin();
        background->setPosition(origin.x + visibleSize.width * 0.5f, origin.y + visibleSize.height * 0.5f);
        this->addChild(background);

        return true;
    }else {
        return false;
    }
}

void LoadingScene::onEnter() {
    
    Director::getInstance()->getTextureCache()->addImageAsync("atlas.png", CC_CALLBACK_1(LoadingScene::loadingCallBack, this));
}

void LoadingScene::loadingCallBack(cocos2d::Texture2D *texture)
{
    AtlasLoader::getInstance()->loadAtlas("atlas.txt", texture);
    
    // After loading the texture , preload all the sound
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_die.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_hit.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_point.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_swooshing.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("sfx_wing.ogg");
    
    // After load all the things, change the scene to new one
    auto scene = WelcomeScene::create();
    TransitionScene* transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
    
}