/*!
 * \file GlobalData.h
 * \date 2015/05/14 12:51
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 全局参数
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __GlobalData__H__
#define __GlobalData__H__

#include <iostream>
#include "cocos2d.h"

class Monster;

USING_NS_CC;

extern Vector<Monster*> monsterOneList;
extern Vector<Monster*> monsterTwoList;
extern Vector<Monster*> monsterThreeList;
extern Vector<Monster*> monsterFourList;
extern Vector<Monster*> monsterFiveList;
extern Vector<Monster*> monsterShowList;

extern bool m_bFlag1;
extern bool m_bFlag2;
extern bool m_bFlag3;
extern bool m_bFlag4;
extern bool m_bFlag5;
// 最大地图关数
#define MAPMAX 9
// 当前选择的关卡
extern int m_iSelectGate;
// 敌人种类
const static int gl_iEnemyType = 1;
// 怪物名字
const static std::string gl_sEnemyName[gl_iEnemyType] = { "muzhuang" };
// 怪物受伤动作名字
const static std::string gl_sEnemyByHurt[gl_iEnemyType] = { "mzaHurt" };
// 怪物战力动作帧图片名字
const static std::string gl_sEnemyFrameName[gl_iEnemyType] = { "mzStand" };
// 怪物死亡动作名字
const static std::string gl_sEnemyDie[gl_iEnemyType] = { "mzDead" };

// 怪物移动动作名字
const static std::string gl_sEnemyMoveSpriteAnimation[gl_iEnemyType] = { "mzWalk" };
// 怪物动作帧图片延时
const static float gl_fEnemyMoveSpriteAnimationDelay[gl_iEnemyType] = { 0.0625 };
// 怪物移动动作帧图片数量
const static int gl_iEnemyMoveFrameCount[gl_iEnemyType] = { 16 };

// 怪物攻击帧图片数量
const static int gl_iEnemyAttackFrameCount[gl_iEnemyType] = { 11 };
// 怪物攻击帧图片帧图片延时
const static float gl_fEnemyAttackFrameDelay[gl_iEnemyType] = { 0.1 };
// 怪物是否有武器
const static std::string gl_sEnemyBullet[gl_iEnemyType] = { "0" }; //0代表没有，1代表有
// 怪物的攻击能量
const static std::string gl_sEnemyPower[gl_iEnemyType] = { "50" };
// 怪物的血量
const static std::string gl_sEnemyBlood[gl_iEnemyType] = { "550" };
// 怪物死亡后的提供的经验
const static std::string gl_sEnemyExp[gl_iEnemyType] = { "200" };

#endif