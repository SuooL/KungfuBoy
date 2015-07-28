/*!
 * \class ActionTool
 *
 * \ingroup GroupName
 *
 * \brief 动画创建器
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

#include "ActionTool.h"

Animate* ActionTool::animationWithFrameName(const char *frameName, int iloops, float delay)
{
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	int index = 1;
	// 创建帧对象 
	do
	{
		String * name = String::createWithFormat("%s%d.png", frameName, index++);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
		if (frame == NULL)
		{
			break;
		}
		animation->addSpriteFrame(frame);
	} while (true);
	animation->setDelayPerUnit(delay);  // 每帧播放间隔
	animation->setRestoreOriginalFrame(true);
	animation->setLoops(iloops);
	// 创建动画动作
	Animate* action = Animate::create(animation);
	return action;
}

Animate* ActionTool::animationWithFrameAndNum(const char *frameName, int framecount, float delay)
{
	SpriteFrame* frame = NULL;
	Animation* animation = Animation::create();
	// 遍历图片帧
	for (int index = 1; index <= framecount; index++)
	{
		String * name = String::createWithFormat("%s%d.png", frameName, index++);
		frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(delay);
	animation->setRestoreOriginalFrame(true);
	Animate* animate = Animate::create(animation);

/*
	// 第二中实现方式，用一个帧图片的向量数组，创建Animation
	Vector<SpriteFrame*> animFrames;
	char str[20];
	for (int k = 1; k <= framecount; k++)
	{
		sprintf(str, "%s%d.png", frameName, k);
		SpriteFrame *frame = SpriteFrameCache::getInstance()->spriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	return Animate::create(Animation::createWithSpriteFrames(animFrames, delay));*/

	return animate;
}