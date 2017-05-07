//
//  Unit.hpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 4..
//
//

#ifndef Unit_hpp
#define Unit_hpp

#include "cocos2d.h"
#include "Defines.hpp"

USING_NS_CC;

enum UNIT_TYPE{
    SUBMARINE = 0,
    SHIP,
    HELICOPTER,
    AIRCRAFT
};

class Unit
{
  
public:
    Unit();
    virtual ~Unit();
    
    void setEnergy(float max);
    float subEnergy(float damage);
    void release();
    
    Sprite* body;
    
    UNIT_TYPE eUnitType;
    float maxEnergy;
    float curEnergy;
    bool isEnemy;
};

#endif /* Unit_hpp */
