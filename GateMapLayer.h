/*!
 * \file GateMapLayer.h
 * \date 2015/05/31 20:09
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 选关功能场景
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __GateMapLayer__H__
#define __GateMapLayer__H__

#include "cocos2d.h"
USING_NS_CC;

class SelectGate;

class GateMapLayer : cocos2d::Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GateMapLayer);

	Sprite *bgPic;
	Sprite *closeBtn;
	Sprite *tips;
	LabelTTF * coin;
	LabelTTF * energy;

	SelectGate* selectGateMenu;

	void gateOneCallBack(Ref* pSender);
	void gateTwoCallBack(Ref* pSender);
	void gateThreeCallBack(Ref* pSender);

	void closeFunc(Ref* pSender);
	void challengeFunc(Ref* pSender);

};

#endif

