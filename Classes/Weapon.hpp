//
//  Weapon.hpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 4..
//
//

#ifndef Weapon_hpp
#define Weapon_hpp

#include "cocos2d.h"
#include "Defines.hpp"

enum WEAPON_TYPE{
    VULCAN = 0,
    CANNON,
    MISSILE,
    TORPEDO,
    BOMB,
    NUCLEAR
};

enum TARGET_TYPE{
    SURFACE = 0,
    AIR,
    ALL
};

class Weapon
{
    
public:
    Weapon();
    virtual ~Weapon();
    
    void release();             // body 정리하고 삭제
    
    cocos2d::Sprite* body;      // 무기 이미지
    
    bool isEnemy;               // 피아
    WEAPON_TYPE eWeaponType;    // 무기의 종류
    TARGET_TYPE eTargetType;    // 타켓의 종류
    float damage;               // 위력
};

#endif /* Weapon_hpp */
