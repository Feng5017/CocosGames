#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Box2D\Box2D.h"
#include "ContactListener.h"
USING_NS_CC;
#define TAG 1//定义一个标签，用于判别碰撞物体时候是box而不是边界
using namespace cocos2d;

#define PTM_RATIO 32

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();//创建一个具有物理引擎的场景
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
        return false;
	
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto pb1 = Label::createWithBMFont("fonts/fnt8.fnt", "Array");
	auto pm1 = MenuItemLabel::create(pb1, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	pm1->setTag(ARRAY_TAG);
	auto pb2 = Label::createWithBMFont("fonts/fnt8.fnt", "Vector");
	auto pm2 = MenuItemLabel::create(pb2, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	pm2->setTag(VECTOR_TAG);
	auto pb3 = Label::createWithBMFont("fonts/fnt8.fnt", "Dictionary");
	auto pm3 = MenuItemLabel::create(pb3, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	pm3->setTag(DICT_TAG);
	auto pb4 = Label::createWithBMFont("fonts/fnt8.fnt", "Map");
	auto pm4 = MenuItemLabel::create(pb4, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	pm4->setTag(MAP_TAG);
	auto pb5 = Label::createWithBMFont("fonts/fnt8.fnt", "ValueVector");
	auto pm5 = MenuItemLabel::create(pb5, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	pm5->setTag(VALUE_TAG);
	auto pb6 = Label::createWithBMFont("fonts/fnt8.fnt", "ValueMap");
	auto pm6 = MenuItemLabel::create(pb6, CC_CALLBACK_1(HelloWorld::menuCallback, this));
	pm6->setTag(VALUEMAP_TAG);

	auto mn = Menu::create(pm1, pm2, pm3, pm4, pm5, pm6, NULL);
	mn->alignItemsVertically();
	this->addChild(mn);
	
	return true;
}

void HelloWorld::menuCallback(cocos2d::Ref * pSender)
{
	MenuItem* mitem = (MenuItem*)pSender;

	auto sc = Scene::create();
	auto layer = ContactListener::create();
	sc->addChild(layer);
	layer->setTag(mitem->getTag());//设置层标签
	log("layer flag=%d", layer->getTag());

	Director::getInstance()->replaceScene(sc);
}



