//
//  Defines.hpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 4. 26..
//
//

#ifndef Defines_hpp
#define Defines_hpp

#define ZORDER_SEA                              0 // 바다 배경
#define ZORDER_SPRITE_BATCH_NODE_SURFACE        1 // 지상유닛
#define ZORDER_SPRITE_BATCH_NODE_CLOUD          2 // 구름그림자
#define ZORDER_SPRITE_BATCH_NODE_EXPLOSION_S    3 // 지상폭발
#define ZORDER_SPRITE_BATCH_NODE_AIR            4 // 공중유닛
#define ZORDER_SPRITE_BATCH_NODE_EXPLOSION_A    5 // 공중폭발
#define ZORDER_SPRITE_BATCH_NODE_INTERFACE      6 // 인터페이스

// Surface Z-ORDER
#define ZORDER_RADAR            1       // 레이더
#define ZORDER_SUBMARINE        2       // 잠수함
#define ZORDER_SHIPTAIL         3       // 배의 물결
#define ZORDER_SHIP             4       // 배
#define ZORDER_DOKDO            5       // 독도
#define ZORDER_SHADOW           6       // 항공기 그림자
#define ZORDER_WATERCOLUMN      7       // 물기둥

// Air Z-ORDER
#define ZORDER_BULLET           1       // 총탄
#define ZORDER_LYNX             2      // 링스헬기
#define ZORDER_HELICOPTER       3      // 공격헬기
#define ZORDER_CLOUD            4      // 구름 그림자
#define ZORDER_BOMB             5      // 폭탄
#define ZORDER_BOMBER           6      // 폭격기
#define ZORDER_FIGHTER          7      // 전투기
#define ZORDER_STRATEGYBOMBER   8      // 전략폭격기
#define ZORDER_MISSILE          9      // 미사일
#define ZORDER_PEACEEYE         10      // 피스아이 조기 경보기
#define ZORDER_NUCLEAR          11      // 핵폭탄

#define TAG_SPRITE_BATCH_NODE_SURFACE       1000
#define TAG_SPRITE_BATCH_NODE_CLOUD         1001
#define TAG_SPRITE_BATCH_NODE_EXPLOSION_S   1002
#define TAG_SPRITE_BATCH_NODE_AIR           1003
#define TAG_SPRITE_BATCH_NODE_EXPLOSION_A   1004
#define TAG_SPRITE_BATCH_NODE_INTERFACE     1005

#define TAG_BULLET 2000
#define TAG_NUCLEAR 2001

#define TAG_INTERFACE_CANNON                3000
#define TAG_INTERFACE_VULCAN                3001
#define TAG_INTERFACE_MISSILE               3002
#define TAG_INTERFACE_ACTIVATE              3003

#define TAG_WEAPON_E                        3100
#define TAG_WEAPON_A                        3101
#define TAG_UNIT_E                          3102
#define TAG_UNIT_A                          3103

#define TAG_INTERFACE_SCOREBOARD            3200

// 유닛의 체력
#define HP_PATROL           10
#define HP_DESTROYER        20
#define HP_CRUISER          40
#define HP_CARRIER          80
#define HP_HELICOPTER       5
#define HP_FIGHTER          15
#define HP_BOMBER           30
#define HP_STRATEGYBOMBER   60

// 적 유닛 생성 시간
#define ADD_PATROL_TERM             4
#define ADD_DESTROYER_TERM          7
#define ADD_CRUISER_TERM            13
#define ADD_CARRIER_TERM            17

#define ADD_HELICOPTER_TERM         5
#define ADD_FIGHTER_TERM            9
#define ADD_BOMBER_TERM             14
#define ADD_STRATEGY_BOMBER_TERM    21

// 적 유닛 이동 시간
#define PATROL_MOVE_TIME            14
#define DESTROYER_MOVE_TIME         18
#define CRUISER_MOVE_TIME           24
#define CARRIER_MOVE_TIME           33

#define HELICOPTER_MOVE_TIME        12
#define FIGHTER_MOVE_TIME           9
#define BOMBER_MOVE_TIME            14
#define STRATEGY_BOMBER_MOVE_TIME   20

// 독도 무기 쿨 타임
#define DOKDO_VULCAN_COOLTIME       0.2f
#define DOKDO_CANNON_COOLTIME       0.8f
#define DOKDO_MISSILE_COOLTIME      1.8f

// 독도 무기 위력
#define DOKDO_VULCAN_DAMAGE         1
#define DOKDO_CANNON_DAMAGE         8
#define DOKDO_MISSILE_DAMAGE        20

// 무기 이동시간
#define VULCAN_MOVE_TIME        1.5
#define CANNON_MOVE_TIME        2.5
#define MISSILE_MOVE_TIME       4

#define BATCHMODE true


#endif /* Defines_hpp */
