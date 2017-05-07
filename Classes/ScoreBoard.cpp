//
//  ScoreBoard.cpp
//  DokdoDefenceCommand
//
//  Created by hunter Mac on 2017. 5. 5..
//
//

#include "ScoreBoard.hpp"

USING_NS_CC;


ScoreBoard::ScoreBoard() : mScore(0), mHighScore(0), mMoney(0), mTime(0)
{
    
}

ScoreBoard* ScoreBoard::create()
{
    ScoreBoard* scoreBoard = new ScoreBoard();
    if(scoreBoard && scoreBoard->initWithSpriteFrameName("score_board.png"))
    {
        scoreBoard->autorelease();
        
        float xPos = 10;//168;
        for(int i=0 ; i<9 ;i++)
        {
            scoreBoard->addNumberSprite(TAG_SCORE + i,
                                        Point(xPos, 10), //58),
                                        1.f);
            xPos -= 3;//15;
        }
        
        return scoreBoard;
    }
    
    CC_SAFE_DELETE(scoreBoard);
    return NULL;
}

void ScoreBoard::addNumberSprite(int tag, Point position, float scale)
{
    auto sprite = Sprite::createWithSpriteFrameName("score_0.png");
    sprite->setPosition(position);
    sprite->setScale(scale);
    sprite->setTag(tag);
    addChild(sprite);
}


ScoreBoard::~ScoreBoard()
{
    
}

void ScoreBoard::setHighScore(int highscore)
{
    mHighScore = highscore;
}

void ScoreBoard::setScore(int score)
{
    mScore = score;
}

void ScoreBoard::addScore(int score)
{
    mScore += score;
}

int ScoreBoard::getScore()
{
    return mScore;
}

void ScoreBoard::setTime(float time)
{
    mTime = time;
}

void ScoreBoard::addTime(float time)
{
    mTime += time;
}

float ScoreBoard::getTime()
{
    return mTime;
}

void ScoreBoard::setMoney(int money)
{
    mMoney = money;
}

void ScoreBoard::addMoney(int money)
{
    mMoney += money;
}

int ScoreBoard::getMoney()
{
    return mMoney;
}


