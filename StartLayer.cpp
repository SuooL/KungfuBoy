/*!
 * \class StartLayer
 *
 * \ingroup GroupName
 *
 * \brief 开始主界面，包含设置，开始游戏等控制按钮
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

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "StartLayer.h"
#include "MijiLayer.h"
#include "SetLayer.h"
#include "TujiLayer.h"
#include "HelpLayer.h"
#include "GateMapLayer.h"
#include "HelloWorldScene.h"


using namespace cocos2d;
using namespace CocosDenshion;

Scene* StartLayer::createScene()
{
	Scene* startScene = Scene::create();
	StartLayer* layer = StartLayer::create();
	startScene->addChild(layer);

	return startScene;
}

bool StartLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 加载游戏图片资源缓存
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/galleryLayer.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/monster.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/resultLayer.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapBg.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapMid.plist");

	// 根据音乐的开关来播放背景音乐
	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		aduioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			aduioEngine->pauseBackgroundMusic();
			aduioEngine->playBackgroundMusic("Sound/startBGM.mp3", true);
		}
		else
			aduioEngine->playBackgroundMusic("Sound/startBGM.mp3", true);
	}
	else
		aduioEngine->pauseBackgroundMusic();

	// 精灵初始化及位置设定
	title = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Title.png"));
	title->setPosition(WINSIZE.width / 2 - 222, WINSIZE.height / 2 + 186);
	bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MainMenuBackground.png"));
	bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);

	this->addChild(bgPic);
	this->addChild(title);

	// 按钮初始化以及时间绑定
	auto helpItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpSelected.png")),
		CC_CALLBACK_1(StartLayer::touchHelp, this)); // 帮助

	auto tujiItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PhotoGalleryNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PhotoGallerySelected.png")),
		CC_CALLBACK_1(StartLayer::touchLib, this)); // 图籍

	auto setItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetSelected.png")),
		CC_CALLBACK_1(StartLayer::touchSet, this)); // 设置


	auto mijiItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsSelected.png")),
		CC_CALLBACK_1(StartLayer::touchMiJi, this)); // 秘籍

	auto chuangguanItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("EmigratedNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("EmigratedSelected.png")),
		CC_CALLBACK_1(StartLayer::touchCG, this)); // 闯关

	auto tiaozhanItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ChallengeNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ChallengeSelected.png")),
		CC_CALLBACK_1(StartLayer::touchTZ, this)); // 挑战
	
	tujiItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 73);
	mijiItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 209);
	setItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 346);
	helpItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 473);
	chuangguanItem->setPosition(WINSIZE.width / 2 - 240, WINSIZE.height / 2 - 86);
	tiaozhanItem->setPosition(WINSIZE.width / 2 - 240, WINSIZE.height / 2 - 250);


	auto menu = Menu::create(tujiItem,mijiItem, setItem, helpItem, chuangguanItem, tiaozhanItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);


	return true;
}

// 按钮事件实现
void StartLayer::touchSet(Ref* pSender)
{
	PLAYEFFECT;
   Director::getInstance()->replaceScene(SetLayer::createScene());
}

void StartLayer::touchLib(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(TujiLayer::createScene());
}

void StartLayer::touchMiJi(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(MijiLayer::createScene());
}

void StartLayer::touchCG(Ref* pSender)
{
	if (getBoolFromXML(SOUND_KEY))
	{
		aduioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
		aduioEngine->playEffect("Sound/button.mp3");
	}
	Director::getInstance()->replaceScene(GateMapLayer::createScene());
}

void StartLayer::touchTZ(Ref* pSender)
{
	PLAYEFFECT;
//	Director::getInstance()->replaceScene(GateMapLayer::createScene());
}

void StartLayer::touchHelp(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(HelpLayer::createScene());
}
