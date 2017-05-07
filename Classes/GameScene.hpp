//
//  GameScene.hpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 4. 26..
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include "cocos2d.h"


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    
};

#endif /* GameScene_hpp */
