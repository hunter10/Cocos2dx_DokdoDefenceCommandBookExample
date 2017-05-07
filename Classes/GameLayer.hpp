//
//  GameLayer.hpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 3..
//
//

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "cocos2d.h"
#include "Defines.hpp"
#include "Weapon.hpp"
#include "Unit.hpp"
#include "ScoreBoard.hpp"

USING_NS_CC;

class GameLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
    void addPatrol(float dt);
    void addDestroyer(float dt);
    void addCruiser(float dt);
    void addCarrier(float dt);
    
    void addHelicopter(float dt);
    void addFighter(float dt);
    void addBomber(float dt);
    void addStrategyBomber(float dt);
    
    void setFirstPosition(Sprite* sprite);
    void bezierToDokdo(Sprite* sprite, float moveTime);
    
    void shootFromDokdo();
    void dropNuclearBomb(float dt);
    
    void selfRemover(Node* sender);
    
    void addCloud(float dt);
    void addWaterColumn(Point pt, float hRatio, float delayPerUnit);
    void addExplosion(Point pt, float wRatio, float delayPerUnit, bool surface);
    void addWeaponInterface(const char* imgPath, const char* txtPath, Point pt, int tag);
    void updateWeaponInterface(float dt);
    void checkCollision(float dt);
    float calDistance(Point from, Point to);
    
    void fireBullet(Point from, Point to, float damage, bool enemy, int moveTime, WEAPON_TYPE type, bool burface);
    void fireMissile(Point from, Point to, float damage, bool enemy);
    
    void addWeapon(Weapon* weapon);
    void weaponRemover(Node* sender);
    void addShootFire(Point pt, float hRatio, float delayPerUnit, bool surface, float angle);
    
    std::vector<Weapon*> arrWeaponA; // 아군이 발사한 무기
    std::vector<Weapon*> arrWeaponE; // 적군이 발사한 무기
    
    void addUnit(Unit* unit);
    void unitRemover(Node* sender);

    std::vector<Unit*> arrUnitA;    // 아군 유닛
    std::vector<Unit*> arrUnitE;    // 적군 유닛
    

    virtual void onEnter();
    virtual void onExit();
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
    virtual void onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event);
    
private:
    cocos2d::Point mPtDokdo;                                    // 자주 사용되는 독도의 위치
    float mVulcanCoolTime, mCannonCoolTime, mMissileCoolTime;
    bool mIsShoot;
    Point mPtShoot;
};

#endif /* GameLayer_hpp */
