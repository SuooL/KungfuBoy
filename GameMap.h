﻿/*!
 * \file GameMap.h
 * \date 2015/06/08 11:19
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __GameMap__H__
#define __GameMap__H__

#include "cocos2d.h"
USING_NS_CC;

class Hero;

class GameMap : public Node
{
public:
	GameMap();
	~GameMap();
	// 初始化地图
	void InitMap(const char *map_name1,const char *map_name2, const char *map_name3);
	//根据精灵的位置移动地图，visibleSize为当前窗口的大小
	void MoveMap(Hero *hero);
	//判断地图是否到达边缘
	bool JudgeMap(Hero *hero);

	CREATE_FUNC(GameMap);
private:
	Sprite* m_map1;
	Sprite* m_map2;
	Sprite* m_map3;
	ParallaxNode* parallax;
};

#endif 