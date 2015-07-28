/*!
 * \class Monster
 *
 * \ingroup GroupName
 *
 * \brief 怪物实体类
 *
 * TODO: long description
 *
 * \note 
 *
 * \author SuooL
 *
 * \version 1.0
 *
 * \date 五月 2015
 *
 * Contact: hu1020935219@gmail.com
 *
 */

#include "Monster.h"
#include "ActionTool.h"
#include "Hero.h"
#include "GameMap.h"

USING_NS_CC;

Monster::Monster()
{
	IsRunning = false;              // 不在跑动
	MonsterDirecton = true;   // 向右运动
	Monster_name = NULL;
	IsAttack = false;
	my_hero = NULL;               // 当前英雄
	my_map = NULL;               // 当前地图
	dis = 10000;
	IsHurt = false;
	Isdead = false;
}

Monster::~Monster()
{
}

Sprite* Monster::GetSprite()
{
	return m_MonsterSprite;
}

void Monster::InitMonsterSprite(char *name, char *a, char *die, char *walk, char *dieLast,int m_iLevel)
{
	Monster_name = name;
	Monster_a = a;
	Monster_walk = walk;
	Monster_die = die;
	Die_name = dieLast;

	m_iHP = 100 * (1+ 0.3*m_iLevel);
	this->m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	this->addChild(m_MonsterSprite);
}

void Monster::SetAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	// 设置怪物方向
	if (MonsterDirecton!= run_directon)
	{
		MonsterDirecton = run_directon;
		m_MonsterSprite->setFlippedX(run_directon);
	}
	// 怪物在走动或，受伤，攻击，死亡，返回
	if (IsRunning || IsAttack || IsHurt || Isdead)
		return;
	// 创建动作 
	Animate* action = ActionTool::animationWithFrameName(name_each, iLoops, delay);
	m_MonsterSprite->runAction(RepeatForever::create(action));
	CCLog("walk~!!!");
	IsRunning = true;
}

// 停止走动后
void  Monster::StopAnimation()
{
	if (!IsRunning)
		return;

	m_MonsterSprite->stopAllActions();// 当前精灵停止所有动画
	// 恢复精灵原来的初始化贴图 
	this->removeChild(m_MonsterSprite, true);// 把原来的精灵删除掉
	m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name));//恢复精灵原来的贴图样子
	m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
	IsRunning = false;
}

// 攻击
void  Monster::AttackAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	// 正在走动、攻击、受伤或已死亡，就返回
	if (IsRunning || IsAttack || IsHurt || Isdead)
		return;
	// 创建动作
	Animate* action =ActionTool::animationWithFrameName(name_each, 1, delay);
	//创建回调动作，攻击结束后调用AttackEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::AttackEnd));
	//创建连续动作

	m_MonsterSprite->runAction(Sequence::create(action, callFunc, NULL));
	IsAttack = true;

}
void Monster::AttackEnd()
{
	// 恢复精灵原来的初始化贴图 
	this->removeChild(m_MonsterSprite, true); // 把原来的精灵删除掉
	m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name)); // 恢复精灵原来的贴图样子
	m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
	IsAttack = false;
}

// 受伤
void Monster::HurtAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	if (IsHurt || Isdead)
		return;
	//受伤优先
	if (IsRunning || IsAttack)
	{
		m_MonsterSprite->stopAllActions();// 当前精灵停止所有动画
		// 恢复精灵原来的初始化贴图 
		this->removeChild(m_MonsterSprite, true);// 把原来的精灵删除掉
		m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Monster_name));//恢复精灵原来的贴图样子
		m_MonsterSprite->setFlipX(MonsterDirecton);
		this->addChild(m_MonsterSprite);
		IsRunning = false;
		IsAttack = false;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	// 创建回调动作，受伤动画结束调用HurtEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Monster::HurtEnd));
	// 创建连续动作
	ActionInterval* hurtackact = Sequence::create(action, callFunc, NULL);

	m_MonsterSprite->runAction(hurtackact);
	IsHurt = true;
}
// 受伤结束
void Monster::HurtEnd()
{
	IsHurt = false;


	if (my_hero->m_bCanCrazy)
	{
		m_iHP -= 100;
	}
	else
		m_iHP -= 30;

	if (m_iHP <= 0)
	{
		//播放怪物死亡
		DeadAnimation(Monster_die,  MonsterDirecton, 0.1f, 1.0f);
	}
	log("Monster Hurt");
}
// 死亡
void Monster::DeadAnimation(const char *name_each, bool run_directon, float delay, int iLoops)
{
	Isdead = true;
	// 创建动作
	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	// 创建回调动作，死亡结束后调用deadact()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::DeadEnd));
	// 创建连续动作
	CCActionInterval* deadact = Sequence::create(action, callFunc, NULL);
	m_MonsterSprite->runAction(deadact);
	if (my_hero->m_iCurrentMp < 100)
	{
		my_hero->m_iCurrentMp = (my_hero->m_iCurrentMp + 50);
		if (my_hero->m_iCurrentMp > 100)
		{
			my_hero->m_iCurrentMp = 100;
		}
	}
}
// 死亡结束
void Monster::DeadEnd()
{
	// 恢复死亡的样子
	this->removeChild(m_MonsterSprite, true);  // 把原来的精灵删除掉
	m_MonsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Die_name)); // 恢复死亡的样子
	m_MonsterSprite->setFlipX(MonsterDirecton);
	this->addChild(m_MonsterSprite);
	
	// 怪物闪下再死亡
	Blink* blinkact = Blink::create(3, 3);//3是持续时间，6是闪的次数

	// 创建回调动作，闪烁结束后调用BlinkEnd()
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(Monster::BlinkEnd));
	// 创建连续动作
	CCActionInterval* deadact = Sequence::create(blinkact, callFunc, NULL);
	m_MonsterSprite->runAction(deadact);

}
// 闪烁结束
void Monster::BlinkEnd()
{
	this->removeAllChildren();//把怪物和血条都删除掉;
}

void Monster::FollowRun(Hero* m_hero, GameMap* m_map)
{

	// 得到两点x的距离,记得怪物的坐标要加上地图的
	float x = m_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());

	// 先计算怪物和英雄的距离
	dis = fabs(x);

	if (x >= 1280)// 当怪物与英雄距离超过1280
		return;
	if (dis <= 120)// 在怪物攻击范围内，怪物停止移动
	{
		this->StopAnimation();// 停止跑动
		scheduleOnce(schedule_selector(Monster::JudegeAttack),2.5f); //以一定的概率判断是是否出动攻击
		return;
	}

	if (x < -100)// 判断怪物横坐标和英雄的距离
	{
		MonsterDirecton = false;
		m_MonsterSprite->setFlippedX(MonsterDirecton);// 设置方向
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirecton, 0.1f, -1);// 播放动画
		this->setPosition(this->getPositionX() - 1.5, this->getPositionY());// 怪物向英雄移动
	}
	else if (x > 100)
	{

		MonsterDirecton = true;
		m_MonsterSprite->setFlippedX(MonsterDirecton);// 设置方向
		if (IsAttack)
			return;
		this->SetAnimation(Monster_walk, MonsterDirecton, 0.1f, -1);// 播放动画
		this->setPosition(this->getPositionX() + 1.5, this->getPositionY());
	}

}
void Monster::JudegeAttack(float dt)
{

	this->AttackAnimation(Monster_a, MonsterDirecton, 0.08f, 0);
}

// 启动监听
void Monster::StartListen(Hero* m_hero, GameMap* m_map)
{
	my_hero = m_hero;
	my_map = m_map;
	this->schedule(schedule_selector(Monster::updateMonster), 1.0f);// 每隔1秒计算距离
	this->scheduleUpdate();// 英雄一旦进入可视范围，怪物追着英雄打
}

// 监听函数,每隔1秒检测下
void Monster::updateMonster(float delta)
{
	// 已死亡，就返回
	if (Isdead || my_hero->IsDead)
		return;
	// 得到两点x的距离,记得怪物的坐标要加上地图的
	float x = my_hero->getPositionX() - (this->getPositionX() + my_map->getPositionX());
	
	// 先计算怪物和英雄的距离
	dis = fabs(x);

}
void Monster::update(float delta)
{
	// 已死亡，就返回
	if (Isdead || my_hero->IsDead)
		return;
	if (dis < 1280 && my_hero->IsDead == false)// 当英雄在它的可视范围内，不断追着英雄
		FollowRun(my_hero, my_map);
}