#include "Select_Plane_Layer.h"
#include "MainGame.h"
#define SHORTEST_SLIDE_LENGTH 50
USING_NS_CC;
#include "cocos2d.h"

SelectPlaneLayer::SelectPlaneLayer() {}
SelectPlaneLayer::~SelectPlaneLayer() {}

Scene* SelectPlaneLayer::createScene()
{
	auto sc = Scene::create();
	auto layer = SelectPlaneLayer::create();
	sc->addChild(layer);
	return sc;
}

bool SelectPlaneLayer::init()
{
	if (!Layer::init())
		return false;
//添加触摸绑定时间
	page_node = 0;//一定要赋初始值
	cur_page_node = 0;
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SelectPlaneLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SelectPlaneLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SelectPlaneLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	size_x = Director::getInstance()->getWinSize().width;
	size_y = Director::getInstance()->getWinSize().height;
	return true;
}

void SelectPlaneLayer::goToCurrNode() {
	
	this->runAction(MoveTo::create(0.4f, Point(-cur_page_node * size_x, 0)));
}

void SelectPlaneLayer::addNode(Node *level) {
	if (level) {
		level->setContentSize(Size(size_x, size_y));
		level->setPosition(Point(size_x * page_node, 0));
		this->addChild(level);
		//记录添加几个飞机界面
		page_node++;
		//log("now is page%d", page_node);
	}
}

bool SelectPlaneLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
	touch_down_point = touch->getLocation();
	touch_cur_point = touch_down_point;
	return true;
}

void SelectPlaneLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
	Point touchPoint = touch->getLocation();
	auto currX = this->getPositionX() + touchPoint.x - touch_cur_point.x;
	Point pos_point = Point(currX, getPositionY());
	touch_cur_point = touchPoint;
}

void SelectPlaneLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
	//坐标差
	touch_up_point = touch_cur_point;
	auto dis = touch_up_point.getDistance(touch_down_point);
	if (dis >= SHORTEST_SLIDE_LENGTH)
	{
		if (touch_down_point.x > touch_up_point.x) {
			++cur_page_node; //记录当前页
			if (page_node - 1 < cur_page_node)
				cur_page_node = page_node - 1;
		}
		else if (touch_down_point.x < touch_up_point.x) {
			--cur_page_node; //记录当前页
			if (cur_page_node < 0) {
				cur_page_node = 0;
			}
		}
		//播放滚动界面
		goToCurrNode();
		//log("You choosed page%d", cur_page_node);
	}
}
