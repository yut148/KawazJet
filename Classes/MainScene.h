//
//  MainScene.h
//  KawazJet
//
//  Created by giginet on 2014/7/9.
//
//

#ifndef __KawazJet__MainScene__
#define __KawazJet__MainScene__

#include <iostream>
#include "cocos2d.h"
#include "MapLayer.h"

class MainScene :public cocos2d::Layer
{
public:
    
    enum class State {
        READY,
        MAIN,
        CLEAR,
        GAMEOVER
    };
    
    static cocos2d::Scene* createScene();
    
    void onEnterTransitionDidFinish() override;
    
    CC_SYNTHESIZE(bool, _isPress, IsPress);
    CC_SYNTHESIZE(int, _coin, Coin);
    CC_SYNTHESIZE(State, _state, State);
    CC_SYNTHESIZE_RETAIN(MapLayer *, _map, Map);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _coinLabel, CoinLabel);
    CC_SYNTHESIZE_RETAIN(cocos2d::ParallaxNode *, _parallaxNode, ParallaxNode);
    CREATE_FUNC(MainScene);
    
CC_CONSTRUCTOR_ACCESS:
    MainScene();
    virtual ~MainScene();
    bool init() override;
    void update(float dt) override;
    
private:
    void onGameOver();
    void onClear();
};

#endif /* defined(__KawazJet__MainScene__) */
