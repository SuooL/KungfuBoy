/*!
 * \file HelpLayer.h
 * \date 2015/05/30 15:43
 *
 * \author SuooL
 * Contact: hu1020935219@gmail.com
 *
 * \brief  帮助关于界面 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef __HelpLayer__H__
#define __HelpLayer__H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelpLayer : public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpLayer);

private:
	LabelTTF* text;
	void scrollback();
};

#endif
