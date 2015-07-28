/*!
 * \file GlobalDefine.h
 * \date 2015/05/14 12:47
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 全局宏定义
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __GlobalDefine__H__
#define __GlobalDefine__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define WINSIZE Director::getInstance()->getWinSize()

#define setIntToXML     UserDefault::getInstance()->setIntegerForKey
#define setFloatToXML   UserDefault::getInstance()->setFloatForKey
#define setBoolToXML    UserDefault::getInstance()->setBoolForKey
#define getIntFromXML   UserDefault::getInstance()->getIntegerForKey
#define getFloatFromXML UserDefault::getInstance()->getFloatForKey
#define getBoolFromXML  UserDefault::getInstance()->getBoolForKey

#define SOUND_KEY       "soundClose"            // 背景音效
#define MUSIC_KEY       "musicClose"              // 背景音乐
#define SOUNDVOL        "soundVolume"        // 音效音量
#define MUSICVOL        "musicVolume"          // 音乐音量
#define EXP_KEY         "heroCurrentExp"        // 英雄当前经验
#define GAMELEVEL_KEY   "gameLevel"        // 当前关卡
#define HEROLEVEL_KEY   "heroLevel"          // 当前等级
#define HEROCOIN_KEY    "heroCoin"            // 英雄金币
#define HEROENERGY_KEY  "heroEnergy"   // 英雄体力
#define HEROHP_KEY      "heroHP"                // 英雄血量
#define HEROMP_KEY      "heroMP"               // 英雄能量
#define HEROAPOWER_KEY  "heroAPower"  // 英雄普攻伤害
#define HEROABILITY_KEY "heroAbility"        // 英雄能力等级
#define SELECTGATE      "selectGate"               // 选择的关卡
#define GATEONE         "gateOne"                     // 第一关
#define GATETWO         "gateTwo"                    // 第二关
#define GATETHREE       "gateThree"               // 第三关
#define GAMEOVER        "gameOver"              // 游戏结束结果

#define aduioEngine   SimpleAudioEngine::getInstance()


#define PLAYEFFECT if (getBoolFromXML(SOUND_KEY)) \
{\
	aduioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));\
	aduioEngine->playEffect("Sound/button.wav");\
}

#endif