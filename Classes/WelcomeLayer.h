//
//  WelcomeLayer.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__WelcomeLayer__
#define __FlappyBirdCpp__WelcomeLayer__


#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCMenuItem.h"
#include "time.h"
#include "BirdSprite.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

const int START_BUTTON_TAG = 100;

class WelcomeLayer : public Layer {
public:
    WelcomeLayer(void);
    ~WelcomeLayer(void);
    virtual bool init();
    CREATE_FUNC(WelcomeLayer);
private:
    void menuStartCallback(Ref *sender);
    void scrollLand(float dt);
    Sprite* land1;
    Sprite* land2;
    BirdSprite* bird;
};

#endif /* defined(__FlappyBirdCpp__WelcomeLayer__) */
