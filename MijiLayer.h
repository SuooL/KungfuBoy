/*!
 * \file MijiLayer.h
 * \date 2015/05/16 11:08
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 秘籍界面实现
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __MijiLayer__H__
#define __MijiLayer__H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

class MijiLayer :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MijiLayer);

	Sprite* spriteBG;
	Sprite* interface_1;
	Sprite* interface_2;

	bool flag;
};

#endif