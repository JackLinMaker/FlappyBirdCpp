//
//  WelcomeScene.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "WelcomeScene.h"
#include "WelcomeLayer.h"

WelcomeScene::WelcomeScene()
{

}

WelcomeScene::~WelcomeScene()
{

}

bool WelcomeScene::init()
{
    if(Scene::init()) {
        auto _welcomeLayer = WelcomeLayer::create();
		this->addChild(_welcomeLayer);
        return true;
    }
    
    return false;
}