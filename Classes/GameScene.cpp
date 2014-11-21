//
//  GameScene.cpp
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#include "GameScene.h"
#include "BackgroundLayer.h"
#include "OptionLayer.h"
#include "GameLayer.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

bool GameScene::init()
{
    if(Scene::initWithPhysics()) {
        this->getPhysicsWorld()->setGravity(Vect(0, -900));
        
        auto backgroundLayer = BackgroundLayer::create();
        if(backgroundLayer) {
            this->addChild(backgroundLayer);
        }
        
        auto statusLayer = StatusLayer::create();
        
        auto gameLayer = GameLayer::create();
        if(gameLayer) {
            gameLayer->setPhyWorld(this->getPhysicsWorld());
            gameLayer->setDelegator(statusLayer);
            this->addChild(gameLayer);
        }
        
        // Add the game status layer to show the score and game status
        if(statusLayer) {
            this->addChild(statusLayer);
        }
        
        // add operation layer to control
        auto optionLayer = OptionLayer::create();
        if(optionLayer) {
            optionLayer->setDelegator(gameLayer);
            this->addChild(optionLayer);
        }
        return true;
    }else {
        return false;
    }
}

void GameScene::restart()
{
    this->removeAllChildrenWithCleanup(true);
    this->init();
}