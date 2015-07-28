/*!
 * \class HelpLayer
 *
 * \ingroup GroupName
 *
 * \brief  帮助关于界面 
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

#include "HelpLayer.h"
#include "StartLayer.h"
#include "GlobalDefine.h"
#include "cocos2d.h"
#include "XMLParser.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelpLayer::createScene()
{
	Scene* scene = Scene::create();
	HelpLayer* helpLayer = HelpLayer::create();

	scene->addChild(helpLayer);

	return scene;
}

bool HelpLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto bgSprite = Sprite::create("Help.png");
	bgSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(bgSprite);

	auto closeItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffSelected.png")),
		[&](Ref * ref){
		PLAYEFFECT;
		//弹出场景
		Director::getInstance()->replaceScene(StartLayer::createScene()); });
	// 关闭按钮
	closeItem->setPosition(WINSIZE.width / 2 + 580, WINSIZE.height / 2 + 320);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto titleSp = Sprite::create("TitleLogo.png");
	titleSp->setPosition(WINSIZE.width / 2 + 200, WINSIZE.height / 2);
	this->addChild(titleSp);

	// 创建文字Label
	XMLParser *pXmlParser = XMLParser::parseWithFile("tujiLayer.xml");
	String *label = pXmlParser->getString("label_help");
	text = LabelTTF::create(label->getCString(), "", 23);
	text->setColor(ccc3(0, 255, 255));
	text->setTag(15);
	text->setPosition(250, 100);

	// 绘制裁剪区域
	DrawNode* area = DrawNode::create();
	Point point[4] = { Point(50, 100), Point(500, 100), Point(500, 450), Point(50, 450) };
	area->drawPolygon(point, 4, ccc4f(255, 255, 255, 255), 0, ccc4f(255, 255, 255, 255));

	// 创建遮罩层
	ClippingNode* m_pClipArea = ClippingNode::create();
	m_pClipArea->setInverted(false);
	m_pClipArea->setStencil(area);
	m_pClipArea->addChild(text);
	this->addChild(m_pClipArea);

	MoveBy* moveact = CCMoveBy::create(5.0f, Point(0, 400)); //10秒向上移动400 
	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(HelpLayer::scrollback));
	// 创建连续动作
	ActionInterval* attackact = Sequence::create(moveact, callFunc, NULL);

	text->runAction(RepeatForever::create(attackact));


	return true;
}

void HelpLayer::scrollback()
{
	text->setPosition(250, 100);
}