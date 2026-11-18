#include "Select_Plane_Page.h"
#include "MainGame.h"

USING_NS_CC;
#include "cocos2d.h"

SelectPlanePage* SelectPlanePage::create(int page)
{
	SelectPlanePage *pRet = new SelectPlanePage(); //创建界面
	if (pRet && pRet->initLevelPage(page)){		//调用初始化
		pRet->autorelease();
		return pRet;
	}
	else{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool SelectPlanePage::initLevelPage(int page)
{
	if (!Node::init())
		return false;

	page_ = page;
	auto visiable = Director::getInstance()->getWinSize();
//背景
	auto sprite = Sprite::create("ui/bg_select.png");
	sprite->setPosition(Point(visiable.width / 2, visiable.height / 2));
	addChild(sprite);
	sprite->setVisible(false);

//添加帧动画
	auto animation = Animation::create();
	for (int i = 1; i <= 2; i++)
	{
		auto str_name = String::createWithFormat("plane/heros%d_%d.png", page, i);
		animation->addSpriteFrameWithFile(str_name->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(-1);

	auto spr_name = String::createWithFormat("plane/heros%d_1.png", page);
	auto plane_sprite = Sprite::create(spr_name->getCString());
	plane_sprite->setPosition(visiable.width / 2, visiable.height / 2);
	plane_sprite->setScale(2);
	this->addChild(plane_sprite);
	//动作
	auto animate = Animate::create(animation);
	plane_sprite->runAction(animate);

//添加Menu
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/text.xml");
	auto btn_label = Label::create();
	btn_label->setString(((String*)(dictionary->objectForKey("select")))->getCString());
	btn_label->setSystemFontSize(40);
	btn_label->setColor(ccc3(36, 106, 32));
	btn_label->enableOutline(Color4B::BLACK, 3);
	auto start_menu = MenuItemLabel::create(btn_label, CC_CALLBACK_1(SelectPlanePage::menuStartCallBack , this));

	auto menu = Menu::create(start_menu, NULL);
	menu->setPosition(ccp(visiable.width / 2, visiable.height*0.3));
	this->addChild(menu);

	//log("Page%d is been Finished", page);

	return true;
}

void SelectPlanePage::menuStartCallBack(Ref * pSender)
{
	//进入游戏界面
	auto scene = Scene::create();
	auto main_layer = MainGame::create();
	//初始化玩家飞机
	main_layer->init_hero_plane(page_);
	scene->addChild(main_layer);
	UserDefault::getInstance()->setIntegerForKey("plane_type", page_);
	log("You choosed Plane%d", page_);

	Director::getInstance()->replaceScene(TransitionFadeTR::create(0.5, scene));
}