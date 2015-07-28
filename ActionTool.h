/*!
 * \file ActionTool.h
 * \date 2015/05/07 22:10
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief 工具类：创建动画
 *
 * TODO: long description
 *
 * \note
*/

#ifndef ActionTool_H__
#define ActionTool_H__

#include "cocos2d.h"
USING_NS_CC;

class ActionTool {
public:
	static Animate* animationWithFrameName(const char *frameName, int iloops, float delay);
	static Animate* animationWithFrameAndNum(const char *frameName, int num, float delay);
};

#endif // ActionTool_H__s