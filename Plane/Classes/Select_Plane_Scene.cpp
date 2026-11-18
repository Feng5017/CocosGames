#include "Select_Plane_Scene.h"
#include "Select_Plane_Layer.h"
#include "Select_Plane_Page.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SelectPlaneScene::createScene()
{
	return SelectPlaneScene::create();
}


bool SelectPlaneScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto size = Director::getInstance()->getWinSize();

	//添加可滑动界面
	SelectPlaneLayer* scrollView = SelectPlaneLayer::create();
	//关卡1-3
	for (int i = 1; i <= 3; i++) {
		auto page = SelectPlanePage::create(i);//添加飞机界面
		page->setTag(i);
		scrollView->addNode(page);//将三个飞机界面添加至可滑动界面中
		//log("Page%d is Finished", page->getTag());
	}
	auto spritebg = Sprite::create("ui/bg_select.png");
	//背景
	spritebg->setPosition(Vec2(size.width / 2, size.height / 2));
	addChild(spritebg);


	this->addChild(scrollView);
	return true;
}


