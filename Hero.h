/*!
 * \file Hero.h
 * \date 2015/05/08 22:13
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 英雄实体类
 *
 * TODO: long description
 *
 * \note
*/
#ifndef __Hero__H__
#define __Hero__H__

#include "cocos2d.h"
USING_NS_CC;

class Hero : public Node
{
public:
	// 根据图片名创建英雄
	void InitHeroSprite(char *hero_name, int iLevel);
	// 返回当前英雄
	Sprite* GetSprite();

	// 设置动画，run_directon为精灵脸朝向，false朝右,frameName为图片帧名字
	void SetAnimation(const char *frameName, float delay, bool run_directon);
	// 停止动画
	void StopAnimation();
	// 跳起动画
	void JumpUpAnimation(const char *name_each, float delay, bool run_directon);
	// 跳落动画
	void JumpDownAnimation(const char *name_each, float delay, bool run_directon);
	// 跳落动画结束
	void JumpEnd();
	// 攻击动画
	void AttackAnimation(const char *name_each, float delay, bool run_directon);
	// 攻击动画结束
	void AttackEnd();
	// 死亡动画
	void DeadAnimation(const char *name_each, float delay, bool run_directon);
	// 死亡动画结束
	void DeadEnd();
	// 受伤动画
	void HurtByMonsterAnimation(const char *name_each, float delay, bool run_directon);
	// 受伤动画结束
	void HurtByMonsterEnd();
	// 判断英雄是否运动到了窗口的中间位置,visibleSize为当前窗口的大小  
	bool JudgePosition(Size visibleSize);

	bool IsDead;

	// HP & MP 值
	float m_iCurrentHp;
	float m_iTotleHp;
	float m_iCurrentMp;
	float m_iTotleMp;

	float percentage;
	float m_iSpeed;

	bool m_bIsAction;          // 查看当前是否已经在打怪了
	bool m_bIsJumping;         // 查看是否在跳
	bool IsRunning;  // 判断是否在跑动画
	bool IsAttack;  // 判断是否在攻击动画
	
	bool IsHurt; // 判断是否受伤
	
	bool HeroDirecton; // 英雄运动的方向
	bool m_bCanCrazy; // 判断是否处于狂暴状态

	CREATE_FUNC(Hero);
private:
	Sprite* m_HeroSprite; // 精灵
	char *Hero_name; // 用来保存初始状态的精灵图片名称
};
#endif