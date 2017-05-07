//
//  ScoreBoard.hpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 5..
//
//

#ifndef ScoreBoard_hpp
#define ScoreBoard_hpp

#include "cocos2d.h"
#include "Defines.hpp"

#define TAG_SCORE       0
#define TAG_HIGHSCORE   100
#define TAG_MONEY       200
#define TAG_TIME_01     300     // 초 (일의자리)
#define TAG_TIME_02     301     // 초 (십의자리)
#define TAG_TIME_03     302     // 분 (일의자리)
#define TAG_TIME_04     303     // 분 (십의자리)

class ScoreBoard : public cocos2d::Sprite
{
public:
    static ScoreBoard* create();
    ScoreBoard();
    virtual ~ScoreBoard();
    
    void setHighScore(int highscore);
    
    void setScore(int score);
    void addScore(int score);
    int getScore();
    
    void setTime(float time);
    void addTime(float time);
    float getTime();
    
    void setMoney(int money);
    void addMoney(int money);
    int getMoney();
    
    void addNumberSprite(int tag, cocos2d::Point position, float scale);
    
private:
    int mScore;
    int mHighScore;
    float mTime;
    int mMoney;
};

#endif /* ScoreBoard_hpp */
