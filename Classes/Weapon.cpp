//
//  Weapon.cpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 4..
//
//

#include "Weapon.hpp"

Weapon::Weapon() : body(NULL),
                   isEnemy(false),
                   damage(0),
                   eWeaponType(VULCAN),
                   eTargetType(ALL)
{
    
}

Weapon::~Weapon()
{
    
}

void Weapon::release()
{
    if(NULL != body)
    {
        body->removeFromParentAndCleanup(true);
        body = NULL;
    }
}
