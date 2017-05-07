//
//  GameLayer.cpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 3..
//
//

#include "GameLayer.hpp"

USING_NS_CC;


bool GameLayer::init(){
    
    if (!Layer::init() ){
        
        CCLOG("you should not see this");
        return false;
    }
    
    mVulcanCoolTime = mCannonCoolTime = mMissileCoolTime = 0;
    mIsShoot = false;
    
    auto winSize = Director::getInstance()->getWinSize();
    log("winSize(%.2f, %.2f)", winSize.width, winSize.height);
    
    
#if BATCHMODE
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Surface.plist");
    auto spriteBatchNodeSurface = SpriteBatchNode::create("Surface.png");
    addChild(spriteBatchNodeSurface, ZORDER_SPRITE_BATCH_NODE_SURFACE, TAG_SPRITE_BATCH_NODE_SURFACE);
    
    // Explostion SpriteBatchNode
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Explosion.plist");
    BlendFunc bfExplosion = {GL_ONE, GL_ONE};
    
    // 지상 폭발용 SpriteBatchNode
    auto spriteBatchNodeExplosionS = SpriteBatchNode::create("Explosion.png");
    spriteBatchNodeExplosionS->setBlendFunc(bfExplosion);
    addChild(spriteBatchNodeExplosionS, ZORDER_SPRITE_BATCH_NODE_EXPLOSION_S, TAG_SPRITE_BATCH_NODE_EXPLOSION_S);
    
    // 공중 폭발용 SpriteBatchNode
    auto spriteBatchNodeExplosionA = SpriteBatchNode::create("Explosion.png");
    spriteBatchNodeExplosionA->setBlendFunc(bfExplosion);
    addChild(spriteBatchNodeExplosionA, ZORDER_SPRITE_BATCH_NODE_EXPLOSION_A, TAG_SPRITE_BATCH_NODE_EXPLOSION_A);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Air.plist");
    auto spriteBatchNodeAir = SpriteBatchNode::create("Air.png");
    addChild(spriteBatchNodeAir, ZORDER_SPRITE_BATCH_NODE_AIR, TAG_SPRITE_BATCH_NODE_AIR);
    
    // 인터페이스용
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Interface.plist");
    auto spriteBatchNodeInterface = SpriteBatchNode::create("Interface.png");
    addChild(spriteBatchNodeInterface, ZORDER_SPRITE_BATCH_NODE_INTERFACE, TAG_SPRITE_BATCH_NODE_INTERFACE);
    
    //auto scoreBoard = (ScoreBoard*)ScoreBoard::createWithSpriteFrameName("score_board.png");
    auto scoreBoard = ScoreBoard::create();
    scoreBoard->setTag(TAG_INTERFACE_SCOREBOARD);
    scoreBoard->setAnchorPoint(Point(0.5, 1));
    scoreBoard->setPosition(winSize.width/2, winSize.height);
    scoreBoard->setScale(winSize.width / scoreBoard->getContentSize().width);
    spriteBatchNodeInterface->addChild(scoreBoard);
    
    log("\n\nBatch Mode!..\n\n");
#else
    log("\n\nNormal Mode!..\n\n");
#endif
    
    
    
    
    
    addWeaponInterface("controller_img_cannon.png",
                       "controller_text_cannon.png",
                       Point(winSize.width*0.21, 0),
                       TAG_INTERFACE_CANNON);
    
    addWeaponInterface("controller_img_vulcan.png",
                       "controller_text_vulcan.png",
                       Point(winSize.width*0.5, 0),
                       TAG_INTERFACE_VULCAN);
    
    addWeaponInterface("controller_img_missile.png",
                       "controller_text_missile.png",
                       Point(winSize.width*0.79, 0),
                       TAG_INTERFACE_MISSILE);
    

    
    // 배경
    auto spriteSEA = Sprite::create("SEA.png");
    spriteSEA->setPosition(Point(winSize.width/2, winSize.height/2));
    float scaleX = winSize.width / spriteSEA->getContentSize().width;
    float scaleY = winSize.height / spriteSEA->getContentSize().height;
    spriteSEA->setScale(scaleX, scaleY);
    this->addChild(spriteSEA, ZORDER_SEA);
    
    // 섬
#if BATCHMODE
    auto spriteDOKDO = Sprite::createWithSpriteFrameName("DOKDO.png");
    spriteBatchNodeSurface->addChild(spriteDOKDO, ZORDER_DOKDO);
#else
    auto spriteDOKDO = Sprite::create("DOKDO.png");
    this->addChild(spriteDOKDO, ZORDER_DOKDO);
#endif
    mPtDokdo = Point(winSize.width * 0.5, winSize.height * 0.25);
    spriteDOKDO->setPosition(mPtDokdo);
    

    
    
    
    // 회전하는 레이더 생성
#if BATCHMODE
    auto spriteRotateRadar = Sprite::createWithSpriteFrameName("radar_01.png");
    spriteBatchNodeSurface->addChild(spriteRotateRadar, ZORDER_RADAR);
#else
    auto spriteRotateRadar = Sprite::create("radar_01.png");
    this->addChild(spriteRotateRadar, ZORDER_RADAR);
#endif
    
    spriteRotateRadar->setAnchorPoint(Point(1, 0));
    spriteRotateRadar->setPosition(Point(winSize.width * 0.5, winSize.height * 0.25));
    float scale = winSize.height / spriteRotateRadar->getContentSize().height;
    spriteRotateRadar->setScale(scale);
    auto rotateBy = RotateBy::create(10, 360);
    auto repeatForever = RepeatForever::create(rotateBy);
    spriteRotateRadar->runAction(repeatForever);
    
    // 원형 레이더 생성
#if BATCHMODE
    auto spriteScaleRadar = Sprite::createWithSpriteFrameName("radar_00.png");
    spriteBatchNodeSurface->addChild(spriteScaleRadar);
#else
    auto spriteScaleRadar = Sprite::create("radar_00.png");
    this->addChild(spriteScaleRadar);
#endif
    
    spriteScaleRadar->setPosition(Point(winSize.width * 0.5, winSize.height * 0.25));
    spriteScaleRadar->setScale(0);
    scale = winSize.height / spriteScaleRadar->getContentSize().height;
    auto scaleTo = ScaleTo::create(4, scale);
    auto scaleToZero = ScaleTo::create(0, 0);
    auto sequence = Sequence::create(scaleTo, scaleToZero, NULL);
    repeatForever = RepeatForever::create(sequence);
    spriteScaleRadar->runAction(repeatForever);
    
    // 사라지는 레이더 생성
#if BATCHMODE
    auto spriteFadeRadar = Sprite::createWithSpriteFrameName("radar_00.png");
    spriteBatchNodeSurface->addChild(spriteFadeRadar);
#else
    auto spriteFadeRadar = Sprite::create("radar_00.png");
    this->addChild(spriteFadeRadar);
#endif
    
    spriteFadeRadar->setPosition(Point(winSize.width * 0.5, winSize.height * 0.25));
    spriteFadeRadar->setScale(scale);
    auto fadeOut = FadeOut::create(4);
    auto fadeInZero = FadeIn::create(0);
    sequence = Sequence::create(fadeOut, fadeInZero, NULL);
    auto fadeForever = RepeatForever::create(sequence);
    spriteFadeRadar->runAction(fadeForever);
    
    // 폭발효과
    auto spriteExplosion = Sprite::create("explosion_effect_18.png");
    spriteExplosion->setPosition(Point(winSize.width / 2, winSize.height / 2));
    spriteExplosion->setScale(winSize.width / spriteExplosion->getContentSize().width);
    //addChild(spriteExplosion, ZORDER_EXPLOSION_S);
    
    //BlendFunc bfLinearDodge = {GL_ONE, GL_ONE};
    BlendFunc bfLinearDodge = {GL_ONE_MINUS_DST_COLOR, GL_ONE};
    spriteExplosion->setBlendFunc(bfLinearDodge);
    
    
    
    // 폭탄투하
    //schedule(schedule_selector(GameLayer::dropNuclearBomb), 4.0f);
    
    // 배
    schedule(schedule_selector(GameLayer::addPatrol), ADD_PATROL_TERM);
    schedule(schedule_selector(GameLayer::addDestroyer), ADD_DESTROYER_TERM);
    schedule(schedule_selector(GameLayer::addCruiser), ADD_CRUISER_TERM);
    schedule(schedule_selector(GameLayer::addCarrier), ADD_CARRIER_TERM);
    
    // 비행기
    schedule(schedule_selector(GameLayer::addHelicopter), ADD_HELICOPTER_TERM);
    schedule(schedule_selector(GameLayer::addFighter), ADD_FIGHTER_TERM);
    schedule(schedule_selector(GameLayer::addBomber), ADD_BOMBER_TERM);
    schedule(schedule_selector(GameLayer::addStrategyBomber), ADD_STRATEGY_BOMBER_TERM);
    
    
    schedule(schedule_selector(GameLayer::updateWeaponInterface));
    schedule(schedule_selector(GameLayer::checkCollision));
    schedule(schedule_selector(GameLayer::addCloud), 1.5f);

    //setTouchEnabled(true);
    
    return true;
}

void GameLayer::addCloud(float dt)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    // 3가지 이미지중 랜덤하게 선택한다.
    int cloudNum = rand() % 3;
    char szFileName[16] = {0, };
    sprintf(szFileName, "cloud_%02d.png", cloudNum);
    auto spriteCloud = Sprite::create(szFileName);
    
    // 구름의 크기를 랜덤하게 적용한다.
    float frand = ((rand() % 4) + 6) / 10.f;
    float scale = (winSize.width * frand) / spriteCloud->getContentSize().width;
    spriteCloud->setScale(scale);
    spriteCloud->setAnchorPoint(Point(1, 0.5));
    
    // 구름의 y 좌표를 랜덤하게 생성한다.
    float xPos = 0;
    float yPos = (rand() % (int)winSize.height);
    spriteCloud->setPosition(Point(xPos, yPos));
    
    // Multiply Blending을 적용한다.
    BlendFunc bf = {GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA};
    spriteCloud->setBlendFunc(bf);
    
    // 구름의 이동 속도를 랜덤하게 선택하여 MoveBy Action을 생성한다.
    float moveTime = 8 + (rand() % 3);
    auto moveBy = MoveBy::create(moveTime, Point(winSize.width + spriteCloud->getBoundingBox().size.width, 0));
    
    auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::selfRemover, this));
    auto sequence = Sequence::create(moveBy, callfunc, NULL);
    
    spriteCloud->runAction(sequence);
    
    addChild(spriteCloud, ZORDER_CLOUD);
}

void GameLayer::dropNuclearBomb(float dt)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    // 폭탄생성
    auto spriteBomb = Sprite::create("MISSILE.png");
    float bombHeight = spriteBomb->getContentSize().height;
    
    // 시작사이즈와 종료 사이즈 결정
    float beginScale = (winSize.height / 6) / bombHeight;
    float finishScale = (winSize.height / 40) / bombHeight;
    
    spriteBomb->setScale(beginScale);
    float visibleHeight = spriteBomb->getBoundingBox().size.height;
    spriteBomb->setPosition(Point(winSize.width/2, 0-(visibleHeight/2)));
    //addChild(spriteBomb);
    addChild(spriteBomb, ZORDER_NUCLEAR, TAG_NUCLEAR);
    
    //이동 Action 생성
    auto moveBy = MoveBy::create(1.5, Point(0, winSize.height * 0.66));
    
    // 가속도 운동 생성
    auto actionInterval = EaseOut::create(moveBy, 1.8);
    
    // 크기변경 Action 생성
    auto scaleTo = ScaleTo::create(1.5, finishScale);
    
    // 가속도 운동과 크기 변경 Action을 동시에 수행
    auto spawn = Spawn::create(actionInterval, scaleTo, NULL);
    
    auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::selfRemover, this));
    
    auto sequence = Sequence::create(spawn, callfunc, NULL);
    
    spriteBomb->runAction(sequence);
    
}



void GameLayer::setFirstPosition(Sprite* sprite)
{
    auto winSize = Director::getInstance()->getWinSize();
    float xPos = rand() % (int)winSize.width;
    float yPos = winSize.height;
    sprite->setPosition(Point(xPos, yPos));
    sprite->setAnchorPoint(Point(0.5, 0));
}

void GameLayer::bezierToDokdo(Sprite* sprite, float moveTime)
{
    auto winSize = Director::getInstance()->getWinSize();
    Point position = sprite->getPosition();
    float xDistance = (winSize.width/2) - position.x;
    
    ccBezierConfig bezierConfig;
    bezierConfig.controlPoint_1 = Point(position.x, winSize.height * 0.6f);
    bezierConfig.controlPoint_2 = Point(position.x + (xDistance / 3), winSize.height * 0.4f);
    bezierConfig.endPosition = Point(winSize.width * 0.5, winSize.height * 0.25);
    auto bezierTo = BezierTo::create(moveTime, bezierConfig);
    auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::unitRemover, this));
    auto sequence = Sequence::create(bezierTo, callfunc, NULL);
    sprite->runAction(sequence);
}

void GameLayer::addPatrol(float dt)
{
    Unit* patrol = new Unit();
    patrol->body = Sprite::createWithSpriteFrameName("patrolship.png");
    patrol->body->setTag(TAG_UNIT_E);
    patrol->isEnemy = true;
    patrol->eUnitType = SHIP;
    patrol->setEnergy(HP_PATROL);
    setFirstPosition(patrol->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE)->addChild(patrol->body, ZORDER_SHIP);
    bezierToDokdo(patrol->body, PATROL_MOVE_TIME);
    
    addUnit(patrol);
}

void GameLayer::addDestroyer(float dt)
{
    Unit* destroyer = new Unit();
    destroyer->body = Sprite::createWithSpriteFrameName("destroyer.png");
    destroyer->body->setTag(TAG_UNIT_E);
    destroyer->isEnemy = true;
    destroyer->eUnitType = SHIP;
    destroyer->setEnergy(HP_DESTROYER);
    setFirstPosition(destroyer->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE)->addChild(destroyer->body, ZORDER_SHIP);
    bezierToDokdo(destroyer->body, DESTROYER_MOVE_TIME);
    
    addUnit(destroyer);
}

void GameLayer::addCruiser(float dt)
{
    Unit* cruiser = new Unit();
    cruiser->body = Sprite::createWithSpriteFrameName("cruiser.png");
    cruiser->body->setTag(TAG_UNIT_E);
    cruiser->isEnemy = true;
    cruiser->eUnitType = SHIP;
    cruiser->setEnergy(HP_CRUISER);
    setFirstPosition(cruiser->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE)->addChild(cruiser->body, ZORDER_SHIP);
    bezierToDokdo(cruiser->body, CRUISER_MOVE_TIME);
    
    addUnit(cruiser);
}

void GameLayer::addCarrier(float dt)
{
    Unit* carrier = new Unit();
    carrier->body = Sprite::createWithSpriteFrameName("aircraftcarrier.png");
    carrier->body->setTag(TAG_UNIT_E);
    carrier->isEnemy = true;
    carrier->eUnitType = SHIP;
    carrier->setEnergy(HP_CARRIER);
    setFirstPosition(carrier->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE)->addChild(carrier->body, ZORDER_SHIP);
    bezierToDokdo(carrier->body, CARRIER_MOVE_TIME);
    
    addUnit(carrier);
}

void GameLayer::addHelicopter(float dt)
{
    /*
    auto spriteHelicopter = Sprite::createWithSpriteFrameName("helicopter.png");
    
    auto spritePropeller = Sprite::createWithSpriteFrameName("helicopter_propeller.png");
    spritePropeller->setPosition(Point(spriteHelicopter->getContentSize().width/2, spriteHelicopter->getContentSize().height/2)); //18, 28));
    auto rotateBy = RotateBy::create(0.6, 360);
    auto repeatForever = RepeatForever::create(rotateBy);
    spritePropeller->runAction(repeatForever);
    spriteHelicopter->addChild(spritePropeller);
    
    setFirstPosition(spriteHelicopter);
    log(" x:%f, y:%f", spriteHelicopter->getContentSize().width, spriteHelicopter->getContentSize().height);
    
    
    getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE)->addChild(spriteHelicopter, ZORDER_HELICOPTER);
    bezierToDokdo(spriteHelicopter, HELICOPTER_MOVE_TIME);
    */
    
    
    Unit* helicopter = new Unit();
    helicopter->body = Sprite::createWithSpriteFrameName("helicopter.png");
    helicopter->body->setTag(TAG_UNIT_E);
    helicopter->isEnemy = true;
    helicopter->eUnitType = AIRCRAFT;
    helicopter->setEnergy(HP_HELICOPTER);
    setFirstPosition(helicopter->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE)->addChild(helicopter->body, ZORDER_HELICOPTER);
    bezierToDokdo(helicopter->body, HELICOPTER_MOVE_TIME);
    
    auto spritePropeller = Sprite::createWithSpriteFrameName("helicopter_propeller.png");
    spritePropeller->setPosition(Point(helicopter->body->getContentSize().width/2, helicopter->body->getContentSize().height/2)); //18, 28));
    auto rotateBy = RotateBy::create(0.6, 360);
    auto repeatForever = RepeatForever::create(rotateBy);
    spritePropeller->runAction(repeatForever);
    helicopter->body->addChild(spritePropeller);
    
    addUnit(helicopter);
}

void GameLayer::addFighter(float dt)
{
    /*
    auto spriteFighter = Sprite::createWithSpriteFrameName("fighter.png");
    
    auto spriteFire = Sprite::createWithSpriteFrameName("bullet.png");
    spriteFire->setOpacity(180);
    spriteFire->setAnchorPoint(Point(0.5, 0.1));
    spriteFire->setPosition(Point(spriteFighter->getContentSize().width/2,spriteFighter->getContentSize().height));
    
    auto scaleToSmall = ScaleTo::create(0.15, 0.85);
    auto scaleToBig = ScaleTo::create(0.15, 1.15);
    auto sequence = Sequence::create(scaleToSmall, scaleToBig, NULL);
    auto repeatForever = RepeatForever::create(sequence);
    spriteFire->runAction(repeatForever);
    spriteFighter->addChild(spriteFire);
    
    auto spriteContrailL = Sprite::createWithSpriteFrameName("tail.png");
    spriteContrailL->setAnchorPoint(Point(0.5, 0));
    spriteContrailL->setPosition(Point(0, spriteFighter->getContentSize().height/1.5));
    spriteFighter->addChild(spriteContrailL);
    
    auto spriteContrailR = Sprite::createWithSpriteFrameName("tail.png");
    spriteContrailR->setAnchorPoint(Point(0.5, 0));
    spriteContrailR->setPosition(Point(spriteFighter->getContentSize().width, spriteFighter->getContentSize().height/1.5));
    spriteFighter->addChild(spriteContrailR);
    
    setFirstPosition(spriteFighter);
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(spriteFighter, ZORDER_FIGHTER);
    bezierToDokdo(spriteFighter, FIGHTER_MOVE_TIME);
    */
    
    
    Unit* fighter = new Unit();
    fighter->body = Sprite::createWithSpriteFrameName("fighter.png");
    fighter->body->setTag(TAG_UNIT_E);
    fighter->isEnemy = true;
    fighter->eUnitType = AIRCRAFT;
    fighter->setEnergy(HP_FIGHTER);
    setFirstPosition(fighter->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(fighter->body, ZORDER_FIGHTER);
    bezierToDokdo(fighter->body, FIGHTER_MOVE_TIME);
    
    auto spriteFire = Sprite::createWithSpriteFrameName("bullet.png");
    spriteFire->setOpacity(180);
    spriteFire->setAnchorPoint(Point(0.5, 0.1));
    spriteFire->setPosition(Point(fighter->body->getContentSize().width/2,fighter->body->getContentSize().height));
    
    auto scaleToSmall = ScaleTo::create(0.15, 0.85);
    auto scaleToBig = ScaleTo::create(0.15, 1.15);
    auto sequence = Sequence::create(scaleToSmall, scaleToBig, NULL);
    auto repeatForever = RepeatForever::create(sequence);
    spriteFire->runAction(repeatForever);
    fighter->body->addChild(spriteFire);
    
    auto spriteContrailL = Sprite::createWithSpriteFrameName("tail.png");
    spriteContrailL->setAnchorPoint(Point(0.5, 0));
    spriteContrailL->setPosition(Point(0, fighter->body->getContentSize().height/1.5));
    fighter->body->addChild(spriteContrailL);
    
    auto spriteContrailR = Sprite::createWithSpriteFrameName("tail.png");
    spriteContrailR->setAnchorPoint(Point(0.5, 0));
    spriteContrailR->setPosition(Point(fighter->body->getContentSize().width, fighter->body->getContentSize().height/1.5));
    fighter->body->addChild(spriteContrailR);
    
    addUnit(fighter);
}

void GameLayer::addBomber(float dt)
{
    /*
    auto spriteBomber = Sprite::createWithSpriteFrameName("bomber.png");
    setFirstPosition(spriteBomber);
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(spriteBomber, ZORDER_BOMBER);
    bezierToDokdo(spriteBomber, BOMBER_MOVE_TIME);
    */
    
    Unit* bomber = new Unit();
    bomber->body = Sprite::createWithSpriteFrameName("bomber.png");
    bomber->body->setTag(TAG_UNIT_E);
    bomber->isEnemy = true;
    bomber->eUnitType = AIRCRAFT;
    bomber->setEnergy(HP_BOMBER);
    setFirstPosition(bomber->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(bomber->body, ZORDER_BOMBER);
    bezierToDokdo(bomber->body, BOMBER_MOVE_TIME);

    addUnit(bomber);
}

void GameLayer::addStrategyBomber(float dt)
{
    /*
    auto spriteStrategyBomber = Sprite::createWithSpriteFrameName("b52h.png");
    setFirstPosition(spriteStrategyBomber);
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(spriteStrategyBomber, ZORDER_STRATEGYBOMBER);
    bezierToDokdo(spriteStrategyBomber, STRATEGY_BOMBER_MOVE_TIME);
    */
    
    Unit* strategyBomber = new Unit();
    strategyBomber->body = Sprite::createWithSpriteFrameName("b52h.png");
    strategyBomber->body->setTag(TAG_UNIT_E);
    strategyBomber->isEnemy = true;
    strategyBomber->eUnitType = AIRCRAFT;
    strategyBomber->setEnergy(HP_STRATEGYBOMBER);
    setFirstPosition(strategyBomber->body);
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(strategyBomber->body, ZORDER_BOMBER);
    bezierToDokdo(strategyBomber->body, STRATEGY_BOMBER_MOVE_TIME);
    
    addUnit(strategyBomber);
}



 void GameLayer::addWaterColumn(Point pt, float hRatio, float delayPerUnit)
 {
     auto winSize = Director::getInstance()->getWinSize();
 
 #if BATCHMODE
     auto spriteWater = Sprite::createWithSpriteFrameName("water_column_00.png");
     getChildByTag(TAG_SPRITE_BATCH_NODE_SURFACE)->addChild(spriteWater, ZORDER_WATERCOLUMN);
 #else
     auto spriteWater = Sprite::create("water_column_00.png");
     if(spriteWater == NULL) return;
     addChild(spriteWater, ZORDER_WATERCOLUMN);
 #endif
 
     spriteWater->setPosition(pt);
     spriteWater->setScale((winSize.height * hRatio) / spriteWater->getContentSize().height);
 
 
     auto frameCache = SpriteFrameCache::getInstance();
     auto animation = Animation::create();
     char szFile[64] = {0, };
     for(int i=0 ; i<12 ; i++){
         sprintf(szFile, "water_column_%02d.png", i);
         animation->addSpriteFrame(frameCache->getSpriteFrameByName(szFile));
     }
     animation->setDelayPerUnit(delayPerUnit);
 
     auto animate = Animate::create(animation);
     auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::selfRemover, this));
     auto sequence = Sequence::create(animate, callfunc, NULL);
     spriteWater->runAction(sequence);
 }

void GameLayer::addExplosion(Point pt,              // 폭발위치
                             float wRatio,          // 폭발크기 계산할 화면 넓이 대한 비율
                             float delayPerUnit,    // 애니메이션 속도
                             bool surface)          // 지상 / 공중 여부
{
    auto winSize = Director::getInstance()->getWinSize();
    
    auto spriteExplosion = Sprite::createWithSpriteFrameName("explosion_effect_00.png");
    spriteExplosion->setPosition(pt);
    
    spriteExplosion->setScale((winSize.width * wRatio) /spriteExplosion->getContentSize().width );
    if(true == surface)
    {
        getChildByTag(TAG_SPRITE_BATCH_NODE_EXPLOSION_S)->addChild(spriteExplosion);
    }
    else
    {
        getChildByTag(TAG_SPRITE_BATCH_NODE_EXPLOSION_A)->addChild(spriteExplosion);
    }
    
    auto frameCache = SpriteFrameCache::getInstance();
    auto animation = Animation::create();
    char szFile[64] = {0, };
    for(int i=0 ;i<36; i++)
    {
        sprintf(szFile, "explosion_effect_%02d.png", i);
        animation->addSpriteFrame(frameCache->getSpriteFrameByName(szFile));
    }
    animation->setDelayPerUnit(delayPerUnit);
    
    auto animate = Animate::create(animation);
    auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::selfRemover, this));
    auto sequence = Sequence::create(animate, callfunc, NULL);
    spriteExplosion->runAction(sequence);
}

void GameLayer::addShootFire(Point pt, float hRatio, float delayPerUnit, bool surface, float angle)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    auto spriteShootFire = Sprite::createWithSpriteFrameName("dok_01.png");
    spriteShootFire->setPosition(pt);
    spriteShootFire->setScale((winSize.height * hRatio) / spriteShootFire->getContentSize().height);
    spriteShootFire->setRotation(angle);
    spriteShootFire->setAnchorPoint(Point(0.5, 0.2));
    
    if(true == surface)
        getChildByTag(TAG_SPRITE_BATCH_NODE_EXPLOSION_S)->addChild(spriteShootFire);
    else
        getChildByTag(TAG_SPRITE_BATCH_NODE_EXPLOSION_A)->addChild(spriteShootFire);
    
    // 애니메이션 생성
    auto frameCache = SpriteFrameCache::getInstance();
    auto animation = Animation::create();
    char szFile[64] = {0, };
    for(int i=1;i<=6;i++){
        sprintf(szFile, "dok_%02d.png", i);
        animation->addSpriteFrame(frameCache->getSpriteFrameByName(szFile));
    }
    animation->setDelayPerUnit(delayPerUnit);
    
    Animate* animate = Animate::create(animation);
    auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::selfRemover, this));
    auto sequence = Sequence::create(animate, callfunc, NULL);
    
    spriteShootFire->runAction(sequence);
}



void GameLayer::addWeaponInterface(const char* imgPath, const char* txtPath, Point pt, int tag)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    // 버튼의 배경이미지
    auto spriteBK = Sprite::createWithSpriteFrameName("controller_back.png");
    spriteBK->setAnchorPoint(Point(0.5, 0));
    spriteBK->setPosition(pt);
    spriteBK->setTag(tag);
    getChildByTag(TAG_SPRITE_BATCH_NODE_INTERFACE)->addChild(spriteBK);
    
    // 버튼 하단 텍스트
    auto spriteText = Sprite::createWithSpriteFrameName(txtPath);
    spriteText->setAnchorPoint(Point(0.5, 0));
    spriteText->setPosition(Point(winSize.width * 0.07, pt.y));   // 67, 0));
    spriteBK->addChild(spriteText);
    
    // 쿨타임 표현 녹색 원
    auto spriteActivity = Sprite::createWithSpriteFrameName("controller_active.png");
    spriteActivity->setAnchorPoint(Point(0.5, 0.5));
    spriteActivity->setPosition(Point(winSize.width * 0.07, winSize.height * 0.05)); // 67, 98));
    spriteActivity->setOpacity(120);
    spriteActivity->setTag(TAG_INTERFACE_ACTIVATE);
    spriteBK->addChild(spriteActivity);
    
    // 무기 이미지
    auto spriteWeapon = Sprite::createWithSpriteFrameName(imgPath);
    spriteWeapon->setAnchorPoint(Point(0.5, 0));
    spriteWeapon->setPosition(Point(winSize.width * 0.07, winSize.height * 0.015)); // 67, 98));
    spriteBK->addChild(spriteWeapon);
}

void GameLayer::updateWeaponInterface(float dt)
{
    mVulcanCoolTime += dt;
    if(mVulcanCoolTime > DOKDO_VULCAN_COOLTIME)
        mVulcanCoolTime = DOKDO_VULCAN_COOLTIME;
    
    mCannonCoolTime += dt;
    if(mCannonCoolTime > DOKDO_CANNON_COOLTIME)
        mCannonCoolTime = DOKDO_CANNON_COOLTIME;
    
    mMissileCoolTime += dt;
    if(mMissileCoolTime > DOKDO_MISSILE_COOLTIME)
        mMissileCoolTime = DOKDO_MISSILE_COOLTIME;
    
    auto interface = (SpriteBatchNode*)getChildByTag(TAG_SPRITE_BATCH_NODE_INTERFACE);
    
    interface->getChildByTag(TAG_INTERFACE_VULCAN)
            ->getChildByTag(TAG_INTERFACE_ACTIVATE)
            ->setScale(mVulcanCoolTime / DOKDO_VULCAN_COOLTIME);
    
    interface->getChildByTag(TAG_INTERFACE_CANNON)
            ->getChildByTag(TAG_INTERFACE_ACTIVATE)
            ->setScale(mCannonCoolTime / DOKDO_CANNON_COOLTIME);
    
    interface->getChildByTag(TAG_INTERFACE_MISSILE)
            ->getChildByTag(TAG_INTERFACE_ACTIVATE)
            ->setScale(mMissileCoolTime / DOKDO_MISSILE_COOLTIME);
    
    shootFromDokdo();
}

void GameLayer::checkCollision(float dt)
{
    auto winSize = Director::getInstance()->getWinSize();
    Weapon* weapon = NULL;
    Unit* unit = NULL;
    
    for(std::vector<Weapon*>::iterator iterWeapon = arrWeaponA.begin(); iterWeapon != arrWeaponA.end(); iterWeapon++)
    {
        weapon = (Weapon*)*iterWeapon;
        if(weapon->eWeaponType == BOMB)
            continue;
        
        bool bHit = false;
        for(std::vector<Unit*>::iterator iterUnit = arrUnitE.begin(); iterUnit != arrUnitE.end(); iterUnit++)
        {
            unit = (Unit*)*iterUnit;
            if(weapon->eTargetType == SURFACE && unit->eUnitType == AIRCRAFT)
                continue;
            
            Rect boundingBox = unit->body->getBoundingBox();
            if(boundingBox.containsPoint(weapon->body->getPosition()))
            {
                // 적중
                bHit = true;
                bool surface = unit->eUnitType <= HELICOPTER ? true : false;
                switch (weapon->eWeaponType) {
                    case VULCAN:
                        addExplosion(weapon->body->getPosition(), 0.1, 0.02, surface);
                        break;
                    
                    case CANNON:
                        addExplosion(weapon->body->getPosition(), 0.15, 0.03, surface);
                        break;
                        
                    case MISSILE:
                        addExplosion(weapon->body->getPosition(), 0.2, 0.04, surface);
                        break;
                        
                    default:
                        break;
                }
                
                if(0 >= unit->subEnergy(weapon->damage)) // 적 체력이 0 이하
                {
                    // 적 크기에 비례해서 폭발의 크기를 계산함
                    float wRatio = unit->body->getBoundingBox().size.height * 2;
                    wRatio /= winSize.width;
                    Point pt = unit->body->getPosition();
                    pt.y += unit->body->getBoundingBox().size.height / 2;
                    switch (unit->eUnitType) {
                        case SUBMARINE:
                            break;
                            
                        case SHIP:
                        case HELICOPTER:
                            addExplosion(pt, wRatio, 0.05, false);
                            
                        case AIRCRAFT:
                            addExplosion(pt, wRatio, 0.05, true);
                            
                        default:
                            break;
                    }
                    
                    unit->release();
                    delete unit;
                    iterUnit = arrUnitE.erase(iterUnit);
                    if(iterUnit == arrUnitE.end())
                        break;
                }
                else
                {
                    // 적이 명중했으나 체력이 0이 아님
                }
                break;
            }
        }
        
        if(true == bHit)
        {
            weapon->release();
            delete weapon;
            iterWeapon = arrWeaponA.erase(iterWeapon);
            if(iterWeapon == arrWeaponA.end())
                break;
        }
        
    }
}

void GameLayer::shootFromDokdo()
{
    if(true == mIsShoot)
    {
        if(mVulcanCoolTime >= DOKDO_VULCAN_COOLTIME)
        {
            mVulcanCoolTime = 0;
            fireBullet(mPtDokdo,
                       mPtShoot,
                       DOKDO_VULCAN_DAMAGE,
                       false,
                       VULCAN_MOVE_TIME,
                       VULCAN,
                       true);
        }
        
        if(mCannonCoolTime >= DOKDO_CANNON_COOLTIME)
        {
            mCannonCoolTime = 0;
            fireBullet(mPtDokdo,
                       mPtShoot,
                       DOKDO_CANNON_DAMAGE,
                       false,
                       CANNON_MOVE_TIME,
                       VULCAN,
                       true);

        }
        
        if(mMissileCoolTime >= DOKDO_MISSILE_COOLTIME)
        {
            mMissileCoolTime = 0;
            fireMissile(mPtDokdo, mPtShoot, DOKDO_MISSILE_DAMAGE, false);
        }
    }
}

float GameLayer::calDistance(Point from, Point to)
{
    float x = from.x - to.x;
    float y = from.y - to.y;
    return sqrtf(pow(x,2) + pow(y,2));
}

void GameLayer::fireBullet(Point from,
                           Point to,
                           float damage,
                           bool enemy,
                           int moveTime,
                           WEAPON_TYPE type,
                           bool burface)
{
    
    Size winSize = Director::getInstance()->getWinSize();
    
    float distance = calDistance(from, to);
    
    float lifeTime = (distance * moveTime) / winSize.height;
    
    Weapon* bullet = new Weapon();
    bullet->body = Sprite::createWithSpriteFrameName("bullet.png");
    
    // vulcan 일때와 cannon 일때의 size를 다르게 준다.
    float scaleH = (type == VULCAN ? 0.02 : 0.03);
    bullet->body->setScale(winSize.height * scaleH / bullet->body->getContentSize().height);
    bullet->body->setTag(enemy ? TAG_WEAPON_E : TAG_WEAPON_A);
    bullet->body->setPosition(from);
    bullet->damage = damage;
    bullet->eWeaponType = type;
    bullet->isEnemy = enemy;
    
    // 발사 각도에 따라 이미지 회전
    float angle = (float)atanf((to.x - from.x) / (to.x - from.y)) * (180.f / M_PI);
    
    // bullet.png 파일의 원래 방향에 따라서 180도 회전이 필요할 시 회전한다.
    if(from.y > to.y)
        bullet->body->setRotation(angle);
    else
        bullet->body->setRotation(angle - 180);
    
    auto moveTo = MoveTo::create(lifeTime, to);
    auto actionInterval = EaseOut::create(moveTo, 1.8);
    auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::weaponRemover, this));
    auto sequence = Sequence::create(actionInterval, callfunc, NULL);
    bullet->body->runAction(sequence);
    
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(bullet->body, ZORDER_BULLET);
    addWeapon(bullet);
    
    addShootFire(from,
                 (type == VULCAN ? 0.08 : 0.12),
                 (type == VULCAN ? 0.06 : 0.08),
                 SURFACE,
                 angle);
}

void GameLayer::fireMissile(Point from, Point to, float damage, bool enemy)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    float distance = calDistance(from, to);
    float lifeTime = (distance * MISSILE_MOVE_TIME) / winSize.height;
    
    Weapon* missile = new Weapon();
    missile->body = Sprite::createWithSpriteFrameName("MISSILE.png");
    getChildByTag(TAG_SPRITE_BATCH_NODE_AIR)->addChild(missile->body, ZORDER_MISSILE);
    
    float scale = (winSize.height * 0.03) / missile->body->getContentSize().height;
    missile->body->setScale(scale);
    missile->body->setTag(enemy ? TAG_WEAPON_E : TAG_WEAPON_A);
    missile->body->setPosition(from);
    missile->eWeaponType = MISSILE;
    missile->damage = damage;
    missile->isEnemy = enemy;
    
    // 회전
    float angle = (float)atanf((to.x - from.x) / (to.y - from.y)) * (180.f/M_PI);
    if(from.y > to.y)
        missile->body->setRotation(angle-180);
    else
        missile->body->setRotation(angle);
    
    // 꼬리 불꽃 추가
    auto tail = Sprite::createWithSpriteFrameName("bullet.png");
    tail->setOpacity(180);
    tail->setAnchorPoint(Point(0.5, 0.1));
    tail->setRotation(180);
    tail->setPosition(Point(missile->body->getContentSize().width/2, 0));
    missile->body->addChild(tail);
    
    // 미사일 이동
    auto moveTo = MoveTo::create(lifeTime, to);
    auto actionInterval = EaseIn::create(moveTo, 2.f);
    auto callfunc = CallFuncN::create(CC_CALLBACK_1(GameLayer::weaponRemover, this));
    auto moveSequence = Sequence::create(actionInterval, callfunc, NULL);
    missile->body->runAction(moveSequence);
    
    addWeapon(missile);
}

void GameLayer::addWeapon(Weapon* weapon)
{
    if(true == weapon->isEnemy)
        arrWeaponE.push_back(weapon);
    else
        arrWeaponA.push_back(weapon);
}

void GameLayer::weaponRemover(Node *sender)
{
    Weapon* weapon = NULL;
    int tag = sender->getTag();
    if(TAG_WEAPON_A == tag) // 아군 무기
    {
        // 아군 무기 vector에서 찾아본다.
        for(std::vector<Weapon*>::iterator iter = arrWeaponA.begin(); iter != arrWeaponA.end(); iter++)
        {
            weapon = (Weapon*)*iter;
            if(weapon->body == sender)
            {
                arrWeaponA.erase(iter);
                break;
            }
            weapon = NULL;
        }
    }
    else{
        // 아군 무기 vector에서 찾아본다.
        for(std::vector<Weapon*>::iterator iter = arrWeaponE.begin(); iter != arrWeaponE.end(); iter++)
        {
            weapon = (Weapon*)*iter;
            if(weapon->body == sender)
            {
                arrWeaponE.erase(iter);
                break;
            }
            weapon = NULL;
        }
    }
    
    
    if(NULL != weapon)
    {
        switch (weapon->eWeaponType) {
            case VULCAN:
                addWaterColumn(sender->getPosition(), 0.08, 0.05);
                break;
                
            case CANNON:
                addWaterColumn(sender->getPosition(), 0.14, 0.07);
                break;
                
            case MISSILE:
                addExplosion(sender->getPosition(), 0.2, 0.04, true);
                break;
                
            case TORPEDO:
                break;
                
            case BOMB:
                break;
                
            case NUCLEAR:
                break;
                
            default:
                break;
        }
        
        weapon->release();
        delete weapon;
    }
}

void GameLayer::addUnit(Unit* unit)
{
    if(true == unit->isEnemy)
        arrUnitE.push_back(unit);
    else
        arrUnitA.push_back(unit);
}

void GameLayer::unitRemover(Node *sender)
{
    Unit* unit = NULL;
    int tag = sender->getTag();
    if(TAG_UNIT_A == tag)
    {
        for(std::vector<Unit*>::iterator iter = arrUnitA.begin() ; iter != arrUnitA.end(); iter++)
        {
            unit = (Unit*)*iter;
            if(unit->body == sender)
            {
                arrUnitA.erase(iter);
                break;
            }
            unit = NULL;
        }
    }
    else{
        for(std::vector<Unit*>::iterator iter = arrUnitE.begin() ; iter != arrUnitE.end(); iter++)
        {
            unit = (Unit*)*iter;
            if(unit->body == sender)
            {
                arrUnitE.erase(iter);
                break;
            }
            unit = NULL;
        }
    }
    
    if(NULL != unit)
    {
        unit->release();
        delete unit;
    }
}

void GameLayer::selfRemover(Node* sender)
{
    switch (sender->getTag()) {
    }
    sender->removeFromParentAndCleanup(true);
}

void GameLayer::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchAllAtOnce::create();
    //listener->setSwallowTouches(true); //멀티터치이기 때문에 삼키면 안된다
    
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameLayer::onTouchesCancelled, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
}

void GameLayer::onExit()
{
    _eventDispatcher->removeAllEventListeners();
    Layer::onExit();
}


void GameLayer::onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event)
{
    for (auto &item : touches)
    {
        mIsShoot = true;
        
        auto touch = item;

        //auto touchPoint = touch->getLocation();
        //log("onTouchesBegan id = %d, x = %f, y = %f",
        //    touch->getID(), touchPoint.x, touchPoint.y);
        
        mPtShoot = touch->getLocation();
    }

}

void GameLayer::onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event)
{
    for (auto &item : touches)
    {
        auto touch = item;
        mPtShoot = touch->getLocation();
    }
}

void GameLayer::onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event)
{
    mIsShoot = false;
}

void GameLayer::onTouchesEnded(const std::vector<Touch*>&touches, Event* unused_event)
{
    mIsShoot = false;
    
//    for(auto &item : touches)
//    {
//        auto touch = item;
//        auto location = touch->getLocation();
//        
//        addExplosion(location, 0.2, 0.03, false);
//    }
}
    
