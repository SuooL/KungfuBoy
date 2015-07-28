/*!
 * \class Hero
 *
 * \ingroup GroupName
 *
 * \brief 英雄实体类
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

#include "Hero.h"
#include "ActionTool.h"

USING_NS_CC;

// 构造性方法
void Hero::InitHeroSprite(char *hero_name, int m_iLevel)
{
	// 属性初始化
	m_HeroSprite = NULL;
	m_bCanCrazy = false;   
	m_bIsAction = false;
	m_bIsJumping = false;
	HeroDirecton = false;    	// 向右运动
	Hero_name = NULL;
	IsRunning = false;
	IsAttack = false;
	IsHurt = false;
	IsDead = false;
	m_iCurrentMp = 0.0f;
	m_iTotleMp = 100.0f;
	m_iSpeed = 5;
	Hero_name = hero_name;
	m_iCurrentHp = m_iTotleHp = 300.0f*m_iLevel;
	percentage = 100.0f;

	this->m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(hero_name));
	this->addChild(m_HeroSprite);
}

Sprite* Hero::GetSprite()
{
	return m_HeroSprite;
}

// 动作方法
// 设置动作
void Hero::SetAnimation(const char *frameName, float delay, bool run_directon)
{
	// 调整方向
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlippedX(run_directon);
	}
	if (IsRunning || IsHurt || IsAttack)
		return;

	/* 创建动画动作 */
	Animate* action = ActionTool::animationWithFrameName(frameName, -1, delay);
	m_HeroSprite->runAction(action);
	IsRunning = true;
}

// 停止动作
void Hero::StopAnimation()
{
	if (!IsRunning)
		return;
	m_HeroSprite->stopAllActions();//当前精灵停止所有动画

	//恢复精灵原来的初始化贴图 
	this->removeChild(m_HeroSprite, true);//把原来的精灵删除掉
	this->m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hero_name));//恢复精灵原来的贴图样子
	m_HeroSprite->setFlippedX(HeroDirecton);
	this->addChild(m_HeroSprite);
	IsRunning = false;
}

// 跳起
void Hero::JumpUpAnimation(const char *name_each, float delay, bool run_directon)
{
	// 调整方向
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlippedX(run_directon);
	}
	if (IsHurt || IsAttack || IsDead)
		return;

	// 创建动画动作 
	Animate* action = ActionTool::animationWithFrameName(name_each, -1, delay);
	m_HeroSprite->runAction(action);
	m_bIsJumping = true;
}

// 跳落
void Hero::JumpDownAnimation(const char *name_each, float delay, bool run_directon)
{
	// 调整方向
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlippedX(run_directon);
	}
	if (IsHurt || IsAttack)
		return;

	/* 创建动画动作 */
	Animate* action = ActionTool::animationWithFrameName(name_each, -1, delay);
	m_HeroSprite->runAction(action);
	m_bIsJumping = true;
}

// 跳完
void Hero::JumpEnd()
{
	m_HeroSprite->stopAllActions();//当前精灵停止所有动画

	// 恢复精灵原来的初始化贴图 
	this->removeChild(m_HeroSprite, true);//把原来的精灵删除掉
	this->m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hero_name));//恢复精灵原来的贴图样子
	m_HeroSprite->setFlippedX(HeroDirecton);
	this->addChild(m_HeroSprite);
	m_bIsJumping = false;
}

// 攻击
void Hero::AttackAnimation(const char *name_each, float delay, bool run_directon)
{
	// 调整方向
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlippedX(run_directon);
	}
	if (IsAttack || m_bIsJumping)
		return;
	// 创建动作
	Animate* act = ActionTool::animationWithFrameName(name_each, 1, delay);
	// 创建回调动作，攻击结束后调用AttackEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::AttackEnd));
	// 创建连续动作
	ActionInterval* attackact = Sequence::create(act, callFunc, NULL);
	IsAttack = true;
	m_HeroSprite->runAction(attackact);
}

// 攻击结束
void Hero::AttackEnd()
{
	m_HeroSprite->setFlippedX(HeroDirecton);
	IsAttack = false;
	if (m_bCanCrazy == true)
	{
		m_bCanCrazy = false;
		m_iCurrentMp = 0;
	}
}

// 受伤
void Hero::HurtByMonsterAnimation(const char *name_each, float delay, bool run_directon)
{
	if (IsHurt || IsDead)
		return;
	//受伤优先
	if (IsRunning || IsAttack)
	{
		m_HeroSprite->stopAllActions();//当前精灵停止所有动画
		//恢复精灵原来的初始化贴图 
		this->removeChild(m_HeroSprite, true);//把原来的精灵删除掉
		m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(Hero_name));//恢复精灵原来的贴图样子
		m_HeroSprite->setFlippedX(HeroDirecton);
		this->addChild(m_HeroSprite);
		IsRunning = false;
		IsAttack = false;
	}

	Animate* action = ActionTool::animationWithFrameName(name_each, 1, delay);
	//创建回调动作，受伤动画结束调用HurtEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::HurtByMonsterEnd));
	//创建连续动作
	ActionInterval* hurtackact = Sequence::create(action, callFunc, NULL);

	m_HeroSprite->runAction(hurtackact);
	IsHurt = true;


}

// 受伤结束
void Hero::HurtByMonsterEnd()
{
	m_iCurrentHp -= 20.0f;
	IsHurt = false;
	percentage = m_iCurrentHp / m_iTotleHp * 100.0f;
	if (m_iCurrentHp < 0.0f)
	{
		DeadAnimation("dead", 0, HeroDirecton);
	}
}

// 死亡
void Hero::DeadAnimation(const char *name_each, float delay, bool run_directon)
{
	m_HeroSprite->stopAllActions();
	// 调整方向
	if (HeroDirecton != run_directon)
	{
		HeroDirecton = run_directon;
		m_HeroSprite->setFlippedX(run_directon);
	}
	// 创建动作
	Animate* act = ActionTool::animationWithFrameName(name_each, 1, delay);
	//创建回调动作，攻击结束后调用AttackEnd()
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(Hero::DeadEnd));
	//创建连续动作
	ActionInterval* attackact = Sequence::create(act, callFunc, NULL);
	m_HeroSprite->runAction(attackact);
	Director::getInstance()->getScheduler()->setTimeScale(0.5);
}

// 死亡结束
void Hero::DeadEnd()
{
	IsDead = true;
	//恢复死亡的样子
	this->removeChild(m_HeroSprite, true);  //把原来的精灵删除掉
	m_HeroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("monsterDie6.png")); //恢复死亡的样子
	m_HeroSprite->setFlippedX(HeroDirecton);
	this->addChild(m_HeroSprite);

}

// 判断位置
bool Hero::JudgePosition(Size visibleSize)
{
	if (this->getPositionX() > (visibleSize.width / 2.0 + 2.0) || (this->getPositionX() < visibleSize.width / 2.0 - 2.0)) // 精灵到达mid?
		return false;
	else
		return true;//到达中间位置
}
