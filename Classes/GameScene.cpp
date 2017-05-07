//
//  GameScene.cpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 4. 26..
//
//

#include "GameScene.hpp"
#include "GameLayer.hpp"
#include "Defines.hpp"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    GameLayer *game = GameLayer::create();
    this->addChild(game);
    
    return true;
}

