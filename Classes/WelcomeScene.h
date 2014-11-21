//
//  WelcomeScene.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__WelcomeScene__
#define __FlappyBirdCpp__WelcomeScene__


#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class WelcomeScene : public Scene {
public:
    WelcomeScene(void);
    ~WelcomeScene(void);
    virtual bool init();
    CREATE_FUNC(WelcomeScene);
};

#endif /* defined(__FlappyBirdCpp__WelcomeScene__) */
