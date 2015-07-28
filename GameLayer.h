/*!
* \file GameLayer.h
* \date 2015/06/13 16:55
*
* \author SuooL
* Contact: hu1020935219@gmail.com
*
* \brief 游戏场景
*
* TODO: long description
*
* \note
*/

#ifndef __GameLayer__H__
#define __GameLayer__H__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "ActionTool.h"
#include "GlobalData.h"
#include "GlobalDefine.h"
#include "extensions/cocos-ext.h"
#include "Monster.h"

USING_NS_CC;
using namespace extension;

class Hero;
class ProgressBar;
class GameMap;

class GameLayer : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();

	// 暂停
	void gamePause(Ref* pSender);

	void gameOver(float delta);
	void gameVictory(float delta);
	// 技能--拳击--脚踢--超级技能--蹦
	void fistAttack(Ref* pSender, Control::EventType type);
	void footAttack(Ref* psender, Control::EventType type);
	void comboAttack(Ref* pSender, Control::EventType type);
	void jump(Ref* pSender, Control::EventType type);

	// 前进，后退
	void forward(Ref* pSender, Control::EventType type);
	void backward(Ref* pSender, Control::EventType type);

	bool isAttackMonster(Hero * hero, Monster* monster);

	virtual void update(float delta);

	CREATE_FUNC(GameLayer);

private:

	// 英雄&怪物
	Hero* m_pHero;
	Monster* m_pMonster1;

	GameMap* myMap;

	// 背景条
	Sprite* m_pBG;
	// 血条，能量前景条
	ProgressTimer* m_pHPBar;
	ProgressTimer* m_pMPBar;

	ControlButton * m_pComboBtn;
	Sprite* m_pComboPic;

	RenderTexture* render;
	RenderTexture* renderResult;

	float velocity = 0.0f;  // 跳起速度
	float getVelocity();    // 获取跳跃的速度

	bool m_bDirection;  // 行走的方向
	bool m_bRun;        // 是否在跑
	bool m_bJump;       // 是否在跳

};

#endif