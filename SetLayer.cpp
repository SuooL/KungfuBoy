/*!
 * \class SetLayer
 *
 * \ingroup GroupName
 *
 * \brief 设置功能实现
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
#include "extensions/cocos-ext.h"
#include "SetLayer.h"
#include "GlobalDefine.h"
#include "StartLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::extension;
using namespace CocosDenshion;

Scene* SetLayer::createScene()
{
	Scene* setScene = Scene::create();
	SetLayer* layer = SetLayer::create();
	setScene->addChild(layer);
	return setScene;
}

bool SetLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	float music = getFloatFromXML(MUSICVOL)*100.0f;
	float effect = getFloatFromXML(SOUNDVOL)*100.0f;

	auto BG = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("image-0.png"));
	BG->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	//BG->setColor(cocos2d::ccGRAY);

	auto bgInterface = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BGPicSet.png"));
	bgInterface->setPosition(WINSIZE.width / 2 + 50, WINSIZE.height / 2);

	auto closeBtn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("closeSetNormal.png")), 
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("closeSetSelected.png")), CC_CALLBACK_1(SetLayer::closeBtn, this));
	closeBtn->setPosition(WINSIZE.width - 150, WINSIZE.height - 100);


	auto saveBtn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SaveSettings.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SaveSettings.png")), CC_CALLBACK_1(SetLayer::saveSet, this));
	saveBtn->setPosition(WINSIZE.width/2+40, WINSIZE.height / 2 - 190);

	auto musicOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")));
	auto musicOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")));

	auto effectOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")));
	auto effectOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")));

	auto musicToggle = MenuItemToggle::createWithTarget(this, menu_selector(SetLayer::musicSet), musicOn, musicOff, NULL);
	musicToggle->setPosition(369.5, 457);
	auto effectToggle = MenuItemToggle::createWithTarget(this, menu_selector(SetLayer::effectSet), effectOn, effectOff, NULL);
	effectToggle->setPosition(369.5, 357);

	if (getBoolFromXML(MUSIC_KEY))
	{
		musicToggle->setSelectedIndex(1);
	}
	else
	{
		musicToggle->setSelectedIndex(0);
	}
	if (getBoolFromXML(SOUND_KEY))
	{
		effectToggle->setSelectedIndex(1);
	}
	else
	{
		effectToggle->setSelectedIndex(0);
	}

	auto menu = Menu::create(closeBtn, saveBtn, musicToggle, effectToggle, NULL);
	menu->setPosition(Point::ZERO);

	auto musicSlider = ControlSlider::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgBar.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("progressBar.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ThumbBtn.png")));
	musicSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SetLayer::changeMusicVol), Control::EventType::VALUE_CHANGED);
	auto effectSlider = ControlSlider::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgBar.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("progressBar.png")), Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ThumbBtn.png")));
	effectSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SetLayer::changeEffectVol), Control::EventType::VALUE_CHANGED);
	musicSlider->setPosition(800, 457);
	musicSlider->setMinimumValue(0.0f);
	musicSlider->setMaximumValue(100.0f);
	musicSlider->setMinimumAllowedValue(0.0f);
	musicSlider->setMaximumAllowedValue(100.0f);

	musicSlider->setValue(music);
	effectSlider->setPosition(800, 357);
	effectSlider->setMinimumValue(0.0f);
	effectSlider->setMaximumValue(100.0f);
	effectSlider->setMinimumAllowedValue(0.0f);
	effectSlider->setMaximumAllowedValue(100.0f);
	effectSlider->setValue(effect);


	this->addChild(BG);
	this->addChild(bgInterface);
	this->addChild(musicSlider);
	this->addChild(effectSlider);
	this->addChild(menu);

	return true;

}

void SetLayer::changeMusicVol(Ref* pSender, Control::EventType type)
{
	auto temp = (ControlSlider*)pSender;
	setFloatToXML(MUSICVOL, temp->getValue()/100.0f);
	UserDefault::getInstance()->flush();
	aduioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
}

void SetLayer::changeEffectVol(Ref* pSender, Control::EventType type)
{
	auto temp = (ControlSlider*)pSender;
	setFloatToXML(SOUNDVOL, temp->getValue()/100.0f);
	UserDefault::getInstance()->flush();
	aduioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
}

void SetLayer::closeBtn(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(StartLayer::createScene());
}


void SetLayer::saveSet(Ref* pSender)
{
	PLAYEFFECT;
	Director::getInstance()->replaceScene(StartLayer::createScene());
}

void SetLayer::musicSet(Ref* pSender)
{
	auto musicTemp = (MenuItemToggle*)pSender;
	PLAYEFFECT;
	if (musicTemp->getSelectedIndex() == 0)
	{
		setBoolToXML(MUSIC_KEY, false);
		UserDefault::getInstance()->flush();
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	else
	{
		setBoolToXML(MUSIC_KEY, true);
		UserDefault::getInstance()->flush();
		aduioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}

void SetLayer::effectSet(Ref* pSender)
{
	auto effectTemp = (MenuItemToggle*)pSender;
	if (effectTemp->getSelectedIndex() == 0)
	{
		setBoolToXML(SOUND_KEY, false);
		UserDefault::getInstance()->flush();
	}
	else
	{
		setBoolToXML(SOUND_KEY, true);
		UserDefault::getInstance()->flush();
	}
}