//
//  GameScene.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__GameScene__
#define __FlappyBirdCpp__GameScene__

#include "cocos2d.h"
using namespace cocos2d;

class GameScene : public Scene {
public:
    GameScene();
    
    ~GameScene();
    
    virtual bool init();
    
    void restart();
    
    CREATE_FUNC(GameScene);
    
};

#endif /* defined(__FlappyBirdCpp__GameScene__) */
