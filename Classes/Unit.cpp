//
//  Unit.cpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 4..
//
//

#include "Unit.hpp"

Unit::Unit() : body(NULL),
            maxEnergy(100),
            curEnergy(0),
            eUnitType(SHIP),
            isEnemy(true)
{
    
}

Unit::~Unit()
{
    release();
}

void Unit::release()
{
    if(NULL != body)
    {
        body->removeFromParentAndCleanup(true);
        body = NULL;
    }
}

void Unit::setEnergy(float max)
{
    maxEnergy = curEnergy = max;
}

float Unit::subEnergy(float damage)
{
    curEnergy -= damage;
    if(curEnergy < 0)
    {
        curEnergy = 0;
    }
    
    return curEnergy;
}
