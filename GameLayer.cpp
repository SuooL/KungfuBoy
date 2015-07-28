/*!
* \class GameLayer
*
* \ingroup GroupName
*
* \brief
*
* TODO: long description
*
* \note
*
* \author SuooL
*
* \version 1.0
*
* \date 六月 2015
*
* Contact: hu1020935219@gmail.com
*
*/
#include "GameLayer.h"
#include "GameMap.h"
#include "Hero.h"
#include "Monster.h"
#include "PauseLayer.h"
#include "GateMapLayer.h"
#include "MonsterOne.h"
#include "extensions/cocos-ext.h"   
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::extension; //引用cocos2d::extension命名空间

Scene* GameLayer::createScene()
{
	Scene* scene = Scene::create();
	GameLayer* layer = GameLayer::create();
	scene->addChild(layer);

	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		aduioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			aduioEngine->pauseBackgroundMusic();
			aduioEngine->playBackgroundMusic("Sound/gameBGM.wav", true);
		}
		else
			aduioEngine->playBackgroundMusic("Sound/gameBGM.wav", true);
	}
	else
		aduioEngine->pauseBackgroundMusic();

	velocity = 10.0f;
	m_bDirection = false;
	m_bRun = false;
	m_bJump = false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapBefore.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/mapRoad.plist");

	String *bgName = String::createWithFormat("bgmap%d.png", m_iSelectGate);
	String *midName = String::createWithFormat("MapMiddle%d.png", m_iSelectGate);
	String *groundName = String::createWithFormat("MapGround%d.png", m_iSelectGate);
	String *beforeName = String::createWithFormat("MapBefore%d.png", m_iSelectGate);
	String *comoboName = String::createWithFormat("comboBtn%d.png", m_iSelectGate);

	auto bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgName->getCString()));
	bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(bgPic, 0);
	myMap = GameMap::create();
	myMap->InitMap(midName->getCString(), groundName->getCString(), beforeName->getCString());
	this->addChild(myMap, 1);

	// 界面控制键初始化
	// 技能键
	auto m_pFistBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fist.png"));
	auto m_pFistBtn = ControlButton::create(m_pFistBG);
	m_pFistBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("fist.png"))->getContentSize());

	auto m_pFootBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("foot.png"));
	auto m_pFootBtn = ControlButton::create(m_pFootBG);
	m_pFootBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("foot.png"))->getContentSize());

	auto m_pJumpBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump.png"));
	auto m_pJumpBtn = ControlButton::create(m_pJumpBG);
	m_pJumpBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jump.png"))->getContentSize());

	auto m_pComboBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(comoboName->getCString()));
	m_pComboBtn = ControlButton::create(m_pComboBG);
	m_pComboBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(comoboName->getCString()))->getContentSize());

	// 按键背景
	auto m_pFistPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("quan.png"));
	auto m_pFootPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jiao.png"));
	auto m_pJumpPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiao.png"));
	m_pComboPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiao.png"));

	auto m_pFistPicSize = m_pFistPic->getContentSize();
	m_pFistBtn->setPosition(ccp(m_pFistPicSize.width / 2, m_pFistPicSize.height / 2));
	m_pFistBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::fistAttack), Control::EventType::TOUCH_UP_INSIDE);

	auto m_pFootPicSize = m_pFootPic->getContentSize();
	m_pFootBtn->setPosition(ccp(m_pFootPicSize.width / 2, m_pFootPicSize.height / 2));
	m_pFootBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::footAttack), Control::EventType::TOUCH_UP_INSIDE);

	auto m_pJumpPicSize = m_pJumpPic->getContentSize();
	m_pJumpBtn->setPosition(ccp(m_pJumpPicSize.width / 2.0 - 1.5, m_pJumpPicSize.height / 2));
	m_pJumpBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::jump), Control::EventType::TOUCH_UP_INSIDE);

	auto m_pComboPicSize = m_pComboPic->getContentSize();
	m_pComboBtn->setPosition(ccp(m_pComboPicSize.width / 2 - 1.5, m_pComboPicSize.height / 2));
	m_pComboBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::comboAttack), Control::EventType::TOUCH_UP_INSIDE);

	m_pFistPic->addChild(m_pFistBtn, 1);
	m_pFootPic->addChild(m_pFootBtn, 1);
	m_pJumpPic->addChild(m_pJumpBtn, 1);
	m_pComboPic->addChild(m_pComboBtn, 1);

	m_pFistPic->setPosition(WINSIZE.width - 230, 76);
	m_pFootPic->setPosition(WINSIZE.width - 73, 76);
	m_pJumpPic->setPosition(WINSIZE.width - 60, 220);
	m_pComboPic->setPosition(WINSIZE.width - 387, 76);

	m_pComboPic->setVisible(false);


	this->addChild(m_pFistPic, 1);
	this->addChild(m_pFootPic, 1);
	this->addChild(m_pJumpPic, 1);
	this->addChild(m_pComboPic, 1);

	// 行走控制键，暂停键
	auto puaseGameItem = MenuItemSprite::create(
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseNormal.png")),
		Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseSelected.png")),
		CC_CALLBACK_1(GameLayer::gamePause, this)); // Pause

	auto backwardBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionNormal.png"));
	auto backwardSelBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionSelected.png"));
	auto backwardBtn = ControlButton::create(backwardBG);
	backwardBtn->setBackgroundSpriteForState(backwardSelBG, Control::State::HIGH_LIGHTED);
	backwardBtn->setZoomOnTouchDown(false);
	backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::TOUCH_DOWN);
	backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::TOUCH_UP_INSIDE);
	backwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::backward), Control::EventType::DRAG_OUTSIDE);
	backwardBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionNormal.png"))->getContentSize());

	auto forwardBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForNor.png"));
	auto forwardSelBG = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForSel.png"));
	auto forwardBtn = ControlButton::create(forwardBG);
	forwardBtn->setBackgroundSpriteForState(forwardSelBG, Control::State::HIGH_LIGHTED);
	forwardBtn->setZoomOnTouchDown(false);
	forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::TOUCH_DOWN);
	forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::TOUCH_UP_INSIDE);
	forwardBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameLayer::forward), Control::EventType::DRAG_OUTSIDE);
	forwardBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForNor.png"))->getContentSize());

	puaseGameItem->setPosition(WINSIZE.width - 50, WINSIZE.height - 48);
	backwardBtn->setPosition(117, 70);
	forwardBtn->setPosition(304, 70);

	auto menuWalk = Menu::create(puaseGameItem, NULL);
	menuWalk->setPosition(Point::ZERO);
	this->addChild(backwardBtn, 1);
	this->addChild(forwardBtn, 1);
	this->addChild(menuWalk, 1);

	// 状态条
	m_pBG = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("barGround.png"));

	m_pHPBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HPBar.png")));
	m_pHPBar->setType(ProgressTimer::Type::BAR);
	m_pHPBar->setMidpoint(ccp(0, 0.5));
	m_pHPBar->setBarChangeRate(ccp(1, 0));
	m_pHPBar->setPercentage(100);

	m_pMPBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MPBar.png")));
	m_pMPBar->setType(ProgressTimer::Type::BAR);
	m_pMPBar->setMidpoint(ccp(0, 0.5));
	m_pMPBar->setBarChangeRate(ccp(1, 0));
	m_pMPBar->setPercentage(0);

	m_pHPBar->setPosition(240, 45);
	m_pMPBar->setPosition(226, 30);

	m_pBG->addChild(m_pHPBar);
	m_pBG->addChild(m_pMPBar);

	m_pBG->setPosition(260, WINSIZE.height - 60);

	this->addChild(m_pBG, 1);

	// 英雄
	m_pHero = Hero::create();
	m_pHero->InitHeroSprite("idle.png", 1);
	m_pHero->setPosition(100, 360);
	this->addChild(m_pHero, 3);


	MonsterOne *monster = MonsterOne::createWithMapAndHero(myMap, m_pHero);

	this->scheduleUpdate();
	return true;
}

// 拳击
void GameLayer::fistAttack(Ref* pSender, Control::EventType type)
{
	if (m_pHero->IsRunning || m_pHero->IsAttack || m_pHero->IsHurt || m_pHero->m_bIsJumping)
	{
		return;
	}
	PLAYEFFECT;
	m_pHero->AttackAnimation("fist", 0.1f, m_bDirection);
}

// 腿击
void GameLayer::footAttack(Ref* psender, Control::EventType type)
{
	if (m_pHero->IsRunning || m_pHero->IsAttack || m_pHero->IsHurt || m_pHero->m_bIsJumping)
	{
		return;
	}
	PLAYEFFECT;
	m_pHero->AttackAnimation("leg", 0.1f, m_bDirection);
}

// 
void GameLayer::jump(Ref* pSender, Control::EventType type)
{

	if (m_pHero->IsRunning || m_pHero->IsAttack || m_pHero->IsHurt || m_bJump)
	{
		return;
	}

	if (getBoolFromXML(SOUND_KEY))
	{
		aduioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
		aduioEngine->playEffect("Sound/Jump.wav");
	}

	m_bJump = true;
}

void GameLayer::comboAttack(Ref* pSender, Control::EventType type)
{
	if (m_pHero->IsAttack || m_pHero->m_bIsJumping == true || m_pHero->m_bCanCrazy)
	{
		return;
	}
	if (getBoolFromXML(SOUND_KEY))
	{
		aduioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
		aduioEngine->playEffect("Sound/combo.wav");
	}
	m_pHero->m_bCanCrazy = true;
	switch (m_iSelectGate)
	{
	case 1:
		m_pHero->AttackAnimation("combo", 0.1, m_bDirection);
		break;
	case 2:
		m_pHero->AttackAnimation("bakandao", 0.1, m_bDirection);
		break;
	case 3:
		m_pHero->AttackAnimation("gun", 0.1, m_bDirection);
		break;
	default:
		break;
	}
}



void GameLayer::gamePause(Ref* pSender)
{
	//可以直接使用pause方法暂停当前的场景，但是这样做有一个bug，就是不能够屏蔽触摸事件，所以采用截图的方法
	//Director::getInstance()->pause();

	/*截取当前场景的图片并且保存*/

	auto size = Director::getInstance()->getWinSize();
	//RenderTexture是一个纹理渲染类，我们需要把要渲染的当前场景放进去，这是初始化它的大小
	render = RenderTexture::create(size.width, size.height);
	//开始获取内容
	render->begin();
	//是用节点的visit方法加入到渲染中
	Director::getInstance()->getRunningScene()->visit();
	//结束
	render->end();
	render->retain();

	//3.0 截屏需要在截完屏的下一帧才能处理RenderTexture，这点要注意
	auto _schedule = this->getScheduler();
	auto replaceScene = [&](float tm)
	{
		//最后切换场景
		Director::getInstance()->pushScene(PauseLayer::createScene(render));
	};
	_schedule->schedule(replaceScene, this, 0.0f, 0, 0.0f, false, "screenshot");
}


void GameLayer::backward(Ref* pSender, Control::EventType type)
{
	if (m_pHero->IsAttack && m_pHero->m_bIsJumping == true)
	{
		return;
	}
	switch (type)
	{
	case cocos2d::extension::Control::EventType::TOUCH_DOWN:
		m_bRun = true;
		m_bDirection = true;
		break;
	case cocos2d::extension::Control::EventType::DRAG_INSIDE:
		break;
	case cocos2d::extension::Control::EventType::DRAG_OUTSIDE:
		m_bRun = false;
		m_pHero->StopAnimation();
		break;
	case cocos2d::extension::Control::EventType::DRAG_ENTER:
		break;
	case cocos2d::extension::Control::EventType::DRAG_EXIT:
		break;
	case cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE:
		m_bRun = false;
		m_pHero->StopAnimation();
		break;
	case cocos2d::extension::Control::EventType::TOUCH_UP_OUTSIDE:
		break;
	case cocos2d::extension::Control::EventType::TOUCH_CANCEL:
		break;
	case cocos2d::extension::Control::EventType::VALUE_CHANGED:
		break;
	default:
		break;
	}
}

void GameLayer::forward(Ref* pSender, Control::EventType type)
{
	if (m_pHero->IsAttack && m_pHero->m_bIsJumping == true)
	{
		return;
	}
	switch (type)
	{
	case cocos2d::extension::Control::EventType::TOUCH_DOWN:
		m_bRun = true;
		m_bDirection = false;
		break;
	case cocos2d::extension::Control::EventType::DRAG_INSIDE:
		break;
	case cocos2d::extension::Control::EventType::DRAG_OUTSIDE:
		m_bRun = false;
		m_pHero->StopAnimation();
		break;
	case cocos2d::extension::Control::EventType::DRAG_ENTER:
		break;
	case cocos2d::extension::Control::EventType::DRAG_EXIT:
		break;
	case cocos2d::extension::Control::EventType::TOUCH_UP_INSIDE:
		m_bRun = false;
		m_pHero->StopAnimation();
		break;
	case cocos2d::extension::Control::EventType::TOUCH_UP_OUTSIDE:
		break;
	case cocos2d::extension::Control::EventType::TOUCH_CANCEL:
		break;
	case cocos2d::extension::Control::EventType::VALUE_CHANGED:
		break;
	default:
		break;
	}
}

void GameLayer::gameOver(float delta)
{
	// 对声音的处理
	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		aduioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			aduioEngine->pauseBackgroundMusic();
			aduioEngine->playBackgroundMusic("Sound/failure.wav", true);
		}
		else
			aduioEngine->playBackgroundMusic("Sound/failure.wav", true);
	}
	else
		aduioEngine->pauseBackgroundMusic();
	// 弹出游戏失败的界面
	auto bgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heiping.png"));
	bgSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(bgSprite, 5);
	auto bgTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgTitle.png"));
	bgTitle->setPosition(WINSIZE.width / 2 + 23, WINSIZE.height / 2 + 17);
	auto faliureTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("faliure.png"));
	faliureTitle->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 + 227);
	auto energyTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tili.png"));
	energyTitle->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 23);
	auto tips = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tipsNext.png"));
	tips->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 227);

	auto m_pEnergyLabel = LabelTTF::create("-  1", "", 45);
	m_pEnergyLabel->setColor(ccc3(0, 255, 255));
	m_pEnergyLabel->setPosition(300, 60);

	bgSprite->addChild(bgTitle);
	bgSprite->addChild(faliureTitle);
	bgSprite->addChild(energyTitle);
	bgSprite->addChild(tips);

	// 获取事件分发器
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	// 触摸监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){return true; };
	listener->onTouchMoved = [](Touch* touch, Event* event){};
	listener->onTouchEnded = [](Touch* touch, Event* event){
		Director::getInstance()->replaceScene(GateMapLayer::createScene());
	};
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);
}

void GameLayer::gameVictory(float delta)
{
	// 对声音的处理
	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		aduioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			aduioEngine->pauseBackgroundMusic();
			aduioEngine->playBackgroundMusic("Sound/victory.wav", true);
		}
		else
			aduioEngine->playBackgroundMusic("Sound/victory.wav", true);
	}
	else
		aduioEngine->pauseBackgroundMusic();

	if (m_iSelectGate == 1)
	{
		setBoolToXML(GATEONE, true);
	}
	else if (m_iSelectGate == 2)
	{
		setBoolToXML(GATETWO, true);
	}
	else
		setBoolToXML(GATETHREE, true);

	// 弹出游戏胜利的界面
	auto bgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heiping.png"));
	bgSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(bgSprite, 5);
	auto bgTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgTitle.png"));
	bgTitle->setPosition(WINSIZE.width / 2 + 23, WINSIZE.height / 2 + 17);
	auto victoryTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("victory.png"));
	victoryTitle->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 + 227);
	auto energyTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tili.png"));
	energyTitle->setPosition(WINSIZE.width / 2 + 116, WINSIZE.height / 2 - 23);
	auto moneyTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jinbi.png"));
	moneyTitle->setPosition(WINSIZE.width / 2 - 275, WINSIZE.height / 2 - 27);
	auto tips = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tipsNext.png"));
	tips->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 227);
	bgSprite->addChild(bgTitle);
	bgSprite->addChild(victoryTitle);
	bgSprite->addChild(energyTitle);
	bgSprite->addChild(moneyTitle);
	bgSprite->addChild(tips);

	// 获取事件分发器
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	// 触摸监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event* event){return true; };
	listener->onTouchMoved = [](Touch* touch, Event* event){};
	listener->onTouchEnded = [](Touch* touch, Event* event){
		Director::getInstance()->replaceScene(GateMapLayer::createScene());
	};
	listener->setSwallowTouches(true);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, bgSprite);
}

bool GameLayer::isAttackMonster(Hero * hero, Monster* monster)
{
	bool hero_dire = hero->HeroDirecton;
	bool monster_dire = monster->MonsterDirecton;
	float hero_x = hero->getPositionX();
	float monster_x = monster->getPositionX() + myMap->getPositionX();
	if (hero_dire)
	{
		if (monster_x <= hero_x)
		{
			return true;
		}
	}
	else
	{
		if (monster_x >= hero_x)
		{
			return true;
		}
	}

	return false;
}

float GameLayer::getVelocity()
{
	velocity = velocity - 0.3f;
	return velocity;
}

void GameLayer::update(float delta)
{
	// 人物跳起
	if (m_bJump)
	{
		getVelocity();

		if (velocity >= 0.1)  // 速度不为0
		{
			m_pHero->JumpUpAnimation("jumpup", 0.1f, m_bDirection);
			if (m_bDirection == false)
			{
				if (m_pHero->getPositionX() <= WINSIZE.width - 8)//不让精灵超出右边,8可以改成你喜欢的
				{
					if (!m_pHero->JudgePosition(WINSIZE) || myMap->JudgeMap(m_pHero)) //精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
						m_pHero->setPosition(ccp(m_pHero->getPosition().x + m_pHero->m_iSpeed, m_pHero->getPosition().y + velocity)); //向右走
					else
					{
						m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
					}
					//下面是移动地图
					myMap->MoveMap(m_pHero);
				}
				else
					m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
			}
			else
			{
				if (m_pHero->getPositionX() >= 8)//不让精灵超出左边,8可以改成你喜欢的
				{
					if (!m_pHero->JudgePosition(WINSIZE) || myMap->JudgeMap(m_pHero))//精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
						m_pHero->setPosition(ccp(m_pHero->getPosition().x - m_pHero->m_iSpeed, m_pHero->getPosition().y + velocity)); //向左走
					else
					{
						m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
					}
					//下面是移动地图
					myMap->MoveMap(m_pHero);
				}
				else
					m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
			}

		}
		else
		{
			m_pHero->JumpDownAnimation("jumpdown", 0.1f, m_bDirection);
			if (m_bDirection == false)
			{
				if (m_pHero->getPositionX() <= WINSIZE.width - 8)//不让精灵超出右边,8可以改成你喜欢的
				{
					if (!m_pHero->JudgePosition(WINSIZE) || myMap->JudgeMap(m_pHero))//精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
						m_pHero->setPosition(ccp(m_pHero->getPosition().x + m_pHero->m_iSpeed, m_pHero->getPosition().y + velocity)); //向右走
					else
					{
						m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
					}
					//下面是移动地图
					myMap->MoveMap(m_pHero);
				}
				else
					m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
			}
			else
			{
				if (m_pHero->getPositionX() >= 8)//不让精灵超出左边,8可以改成你喜欢的
				{
					if (!m_pHero->JudgePosition(WINSIZE) || myMap->JudgeMap(m_pHero))//精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
						m_pHero->setPosition(ccp(m_pHero->getPosition().x - m_pHero->m_iSpeed, m_pHero->getPosition().y + velocity)); //向左走
					else
					{
						m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
					}
					//下面是移动地图
					myMap->MoveMap(m_pHero);
				}
				else
					m_pHero->setPosition(ccp(m_pHero->getPosition().x, m_pHero->getPosition().y + velocity)); //向左走
			}
		}

		if (m_pHero->getPositionY() <= 359)
		{
			m_pHero->JumpEnd();
			m_pHero->setPosition(ccp(m_pHero->getPosition().x + 3, 360));
			velocity = 10.0f;
			m_bJump = false;
		}
	}

	// 人物移动
	if (m_bRun && m_bDirection == false && m_pHero->IsHurt == false && m_pHero->IsAttack == false && m_pHero->m_bIsJumping == false)
	{
		m_pHero->SetAnimation("run", 0.07f, m_bDirection);
		if (m_pHero->getPositionX() <= WINSIZE.width - 8)//不让精灵超出右边,8可以改成你喜欢的
		{
			if (!m_pHero->JudgePosition(WINSIZE) || myMap->JudgeMap(m_pHero))//精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
				m_pHero->setPosition(ccp(m_pHero->getPosition().x + m_pHero->m_iSpeed, m_pHero->getPosition().y)); //向右走
			//下面是移动地图
			myMap->MoveMap(m_pHero);
		}
	}
	else if (m_bRun && m_bDirection == true && m_pHero->IsHurt == false && m_pHero->m_bIsJumping == false)
	{
		m_pHero->SetAnimation("run", 0.07f, m_bDirection);
		if (m_pHero->getPositionX() >= 8)//不让精灵超出左边,8可以改成你喜欢的
		{
			if (!m_pHero->JudgePosition(WINSIZE) || myMap->JudgeMap(m_pHero))//精灵没到达窗口中间位置或者地图已经移动到边缘了，精灵才可以移动，否则只播放动画
				m_pHero->setPosition(ccp(m_pHero->getPosition().x - m_pHero->m_iSpeed, m_pHero->getPosition().y)); //向右走
			//下面是移动地图
			myMap->MoveMap(m_pHero);
		}
	}

	// 主角和怪物攻击碰撞检测
	if (m_pHero->IsAttack)
	{
		for (auto monster : monsterShowList)
		{
			// 怪物没死
			if (monster->Isdead == false && isAttackMonster(m_pHero, monster) && m_pHero->m_bIsJumping == false)
			{
				// 得到两点x的距离, 记得怪物的坐标要加上地图的
				float x = m_pHero->getPositionX() - (monster->getPositionX() + myMap->getPositionX());

				//先计算怪物和英雄的距离
				auto dis = fabs(x);
				if (dis <= 150)
				{
					if (monster->m_iType == 1)
					{
						monster->HurtAnimation("monsterHurt", monster->MonsterDirecton, 0.2f, 1);
					}
					else if (monster->m_iType == 2)
					{
						monster->HurtAnimation("lionHurt", monster->MonsterDirecton, 0.2f, 1);
					}
					else
					{
						monster->HurtAnimation("stoneHurt", monster->MonsterDirecton, 0.2f, 1);
					}
				}
				// 				if (this->isRectCollision(CCRectMake(m_pHero->getPositionX(), m_pHero->getPositionY(), m_pHero->GetSprite()->getContentSize().width-30, m_pHero->GetSprite()->getContentSize().height-20), 
				// 					CCRectMake(monster->getPositionX(), monster->getPositionY(), monster->GetSprite()->getContentSize().width - 30, monster->GetSprite()->getContentSize().height - 20)))
				// 				{
				// 					monster->HurtAnimation("monsterHurt", monster->MonsterDirecton, 0.2f, 1);
				// 				}
			}
		}
	}

	for (auto monster : monsterShowList)
	{
		if (!monster->Isdead)
		{
			if (monster->IsAttack && m_pHero->IsDead == false && m_pHero->m_bIsJumping == false)
			{
				// 得到两点x的距离, 记得怪物的坐标要加上地图的
				float x = m_pHero->getPositionX() - (monster->getPositionX() + myMap->getPositionX());

				//先计算怪物和英雄的距离
				auto dis = fabs(x);
				if (dis <= 130)
				{
					m_pHero->HurtByMonsterAnimation("hurt", 0.2f, m_bDirection);
					m_pHPBar->setPercentage(m_pHero->percentage);
				}
			}
		}
	}

	m_pMPBar->setPercentage(m_pHero->m_iCurrentMp);
	if (m_pMPBar->getPercentage() >= 100)
	{
		m_pComboPic->setVisible(true);
	}
	else
	{
		m_pComboPic->setVisible(false);
	}

	// 主角和怪物攻击碰撞检测
	if (m_pHero->IsAttack && m_pHero->m_bCanCrazy)
	{
		for (auto monster : monsterShowList)
		{
			// 怪物没死
			if (monster->Isdead == false && isAttackMonster(m_pHero, monster) && m_pHero->m_bIsJumping == false)
			{
				// 得到两点x的距离, 记得怪物的坐标要加上地图的
				float x = m_pHero->getPositionX() - (monster->getPositionX() + myMap->getPositionX());

				//先计算怪物和英雄的距离
				auto dis = fabs(x);
				if (dis <= 350)
				{
					monster->HurtAnimation("monsterHurt", monster->MonsterDirecton, 0.2f, 1);
				}
				// 				if (this->isRectCollision(CCRectMake(m_pHero->getPositionX(), m_pHero->getPositionY(), m_pHero->GetSprite()->getContentSize().width-30, m_pHero->GetSprite()->getContentSize().height-20), 
				// 					CCRectMake(monster->getPositionX(), monster->getPositionY(), monster->GetSprite()->getContentSize().width - 30, monster->GetSprite()->getContentSize().height - 20)))
				// 				{
				// 					monster->HurtAnimation("monsterHurt", monster->MonsterDirecton, 0.2f, 1);
				// 				}
			}
		}
	}

	// 游戏结束判定
	if (m_pHero->IsDead)
	{
		// 游戏结束
		this->scheduleOnce(schedule_selector(GameLayer::gameOver), 1.0f);
		this->unscheduleUpdate();
	}
	// 怪物全死
	if (m_bFlag3 == false)
	{
		bool noMonster = true;
		for (auto monster : monsterShowList)
		{
			if (!monster->Isdead)
			{
				noMonster = false;
			}
		}
		if (noMonster)
		{
			this->scheduleOnce(schedule_selector(GameLayer::gameVictory), 2.0f);
			this->unscheduleUpdate();
		}
	}
}
