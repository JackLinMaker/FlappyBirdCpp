//
//  LoadingScene.h
//  FlappyBirdCpp
//
//  Created by 林光海 on 14-11-21.
//
//

#ifndef __FlappyBirdCpp__LoadingScene__
#define __FlappyBirdCpp__LoadingScene__

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class LoadingScene : public Scene {
public:
    LoadingScene();
    
    ~LoadingScene();
    
    virtual bool init();
    
    CREATE_FUNC(LoadingScene);
    
    void onEnter() override;
    
private:
    void loadingCallBack(Texture2D* texture);
};

#endif /* defined(__FlappyBirdCpp__LoadingScene__) */
