/*!
 * \file Monster.h
 * \date 2015/05/10 11:14
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 怪物实体类
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __Monster__H__
#define __Monster__H__
#include "cocos2d.h"
class Hero;
class GameMap;

USING_NS_CC;

class Monster :public cocos2d::Node
{
public:
	Monster(void);
	~Monster(void);
	// 公有属性
	// 怪物种类
	int m_iType;
	//判断是否在跑动画
	bool IsRunning;
	//判断是否在攻击动画
	bool IsAttack;
	//判断是否在受伤动画
	bool IsHurt;
	//判断是否死亡
	bool Isdead;
	//怪物运动的方向
	bool MonsterDirecton;

	// 方法
	// 根据图片名创建怪物，不带血条的怪物
	void InitMonsterSprite(char *name, char *a, char *die, char *walk, char *dieLast, int m_iLevel);
	//返回英雄
	Sprite* GetSprite();

	//设置走动动画,num为图片数目，run_directon为精灵脸朝向，false朝右,name_each为name_png中每一小张图片的公共名称部分
	void SetAnimation(const char *name_each, bool run_directon, float delay, int iLoops);
	//停止走动动画
	void StopAnimation();

	//攻击动画
	void AttackAnimation(const char *name_each, bool run_directon, float delay, int iLoops);
	//攻击动画结束
	void AttackEnd();

	//受伤动画
	void HurtAnimation(const char *name_each, bool run_directon, float delay, int iLoops);
	//受伤动画结束
	void HurtEnd();

	//死亡动画
	void DeadAnimation(const char *name_each,  bool run_directon, float delay, int iLoops);
	//死亡动画结束
	void DeadEnd();

	//怪物死亡闪烁结束
	void BlinkEnd();

	//在可视范围内，怪物跟随英雄运动
	void FollowRun(Hero* m_hero, GameMap* m_map);
	//判断是否攻击
	void JudegeAttack(float dt);


	//怪物启动监听英雄
	void StartListen(Hero* m_hero, GameMap* m_map);
	//监听函数,每隔3秒检测下，计算英雄与怪物的距离
	void updateMonster(float delta);
	//更新函数，如果英雄在可视范围内，不断触发
	void update(float delta);

	CREATE_FUNC(Monster);

private:
	Sprite* m_MonsterSprite;     // 怪物精灵
	char *Monster_name;            // 用来保存初始状态的精灵图片名称
	char *Monster_a;                    // 怪物攻击帧
	char *Monster_die;                // 死亡帧
	char *Monster_walk;             // 行走帧
	char *Die_name;

	Hero* my_hero;                     // 当前英雄
	GameMap* my_map;           // 当前地图
	float dis;                                   // 当前怪物和英雄的距离
	int   m_iHP;
};
#endif 
