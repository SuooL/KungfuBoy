/*!
 * \file MijiLayer.cpp
 * \date 2015/05/17 21:58
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 秘籍场景
 *
 * TODO: long description
 *
 * \note
*/

#include "MijiLayer.h"
#include "GlobalDefine.h"
#include "StartLayer.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

Scene* MijiLayer::createScene()
{
	Scene* scene = Scene::create();
	MijiLayer* layer = MijiLayer::create();
	scene->addChild(layer);
	return scene;
}

bool MijiLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	flag = true;
	// 背景
	spriteBG = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsBackground.png"));
	spriteBG->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(spriteBG);
	
	// 秘籍技能界面
	interface_1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsInterface1.png"));
	interface_2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsInterface2.png"));
	interface_1->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 10);
	interface_1->setVisible(true);
	interface_2->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 10);
	interface_2->setVisible(false);
	spriteBG->addChild(interface_1);
	spriteBG->addChild(interface_2);

	// 关闭按钮
	auto closeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("OffNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("offSelected.png")),
		[](Ref * ref){
		// 切换主界面场景
		PLAYEFFECT;
		Director::getInstance()->replaceScene(StartLayer::createScene()); });
	closeItem->setPosition(WINSIZE.width-164, WINSIZE.height-132);

	// 点击切换按钮
	auto nextRightItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnSelected.png")),
		[&](Ref * ref){
		PLAYEFFECT;
		// 切换秘籍
		if (flag)
		{
			interface_2->setVisible(true);
			flag = false;
		}
		else
		{
			interface_2->setVisible(false);
			flag = true;
		}
		 });
	nextRightItem->setPosition(WINSIZE.width - 55, WINSIZE.height / 2 - 14);

	// 点击切换按钮
	auto nor = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnNormal.png"));
	nor->setFlippedX(true);
	auto sel = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnSelected.png"));
	sel->setFlippedX(true);
	auto nextLeftItem = MenuItemSprite::create(nor, sel,
		[&](Ref * ref){
		PLAYEFFECT;
		// 切换秘籍
		if (flag)
		{
			interface_2->setVisible(true);
			flag = false;
		}
		else
		{
			interface_2->setVisible(false);
			flag = true;
		}
	});
	nextLeftItem->setPosition(55, WINSIZE.height / 2 - 14);

	auto menu = Menu::create(closeItem, nextRightItem, nextLeftItem, NULL);
	menu->setPosition(Point::ZERO);

	spriteBG->addChild(menu);

	return true;
}