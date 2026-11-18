#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#include "ContactListener.h"
using namespace std;

cocos2d::Scene * ContactListener::createScene()
{
	auto scene = Scene::create();//创建一个具有物理引擎的场景
	auto layer = ContactListener::create();
	scene->addChild(layer);
	return scene;
}

bool ContactListener::init()
{
	if (!Scene::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto goItem = MenuItemImage::create("go-down.png", "go-up.png",
		CC_CALLBACK_1(ContactListener::menuGoCallback, this));
	goItem->setPosition(Vec2(visibleSize.width - 200, 100));

	auto backItem = MenuItemImage::create("back-down.png", "go-up.png",
		CC_CALLBACK_1(ContactListener::menuCloseCallback, this));
	backItem->setPosition(Vec2(200, 100));
	
	auto mn = Menu::create(goItem, backItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn, 100);	//为了让按钮在球上面

	//使用create创建对象是会自动释放的
	this->list1 = Array::createWithCapacity(MAX_COUNT);
	this->list1->retain();
	
	this->list2 = Vector<Sprite*>(MAX_COUNT);
	
	this->dict1 = Dictionary::create();
	this->dict1->retain();
	this->dict2 = Dictionary::create();
	this->dict2->retain();

	this->map1 = Map<std::string, Sprite*>();
	this->map2 = Map<std::string, Sprite*>();

	return true;
}

void ContactListener::menuGoCallback(Ref * pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	log("list->count():%d", this->list1->count());
	
	Ref* obj = nullptr;	
	
	DictElement* elem;
//返回"键"值
	std::vector<std::string>mapKeyVec1;
	mapKeyVec1 = this->map1.keys();
	std::vector<std::string>mapKeyVec2;
	mapKeyVec2 = this->map2.keys();
	
	int tagIndex = 0;
	switch (this->getTag()){
	case ARRAY_TAG:		
		CCARRAY_FOREACH(this->list1, obj) {
			auto sp = (Sprite*)obj;
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp->setPosition(Vec2(x, y));
			this->removeChild(sp);
			this->addChild(sp);
		}
		break;
	case VECTOR_TAG:
		for (const auto& sp:this->list2)
		{
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp->setPosition(Vec2(x, y));
			this->removeChild(sp);
			this->addChild(sp);
		}
		break;
	case DICT_TAG:{
		CCDICT_FOREACH(dict1, elem) {
			int key = elem->getIntKey();//整数类型
			log("Add Sprite %d", key);
			Sprite* sp = (Sprite*)elem->getObject();
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp->setPosition(Vec2(x, y));
			this->removeChild(sp);
			this->addChild(sp);
		}
		CCDICT_FOREACH(dict2, elem) {
			const char* key = elem->getStrKey();//字符串类型
			log("Add Sprite %s", key);
			Sprite* sp = (Sprite*)elem->getObject();
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp->setPosition(Vec2(x, y));
			this->removeChild(sp);
			this->addChild(sp);
		}
		}break;
	case MAP_TAG:
		for (auto key:mapKeyVec1){
			Sprite* sp1 = this->map1.at(key);
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp1->setPosition(Vec2(x, y));
			this->removeChild(sp1);
			this->addChild(sp1);
		}
		for (auto key:mapKeyVec2) {
			Sprite* sp2 = this->map2.at(key);
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp2->setPosition(Vec2(x, y));
			this->removeChild(sp2);
			this->addChild(sp2);
		}
		break;
	case VALUE_TAG:
		for (auto&v :list3){
			auto sp = Sprite::create(v.asString());
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp->setPosition(Vec2(x, y));
			this->removeChildByTag(tagIndex);
			this->addChild(sp,1,tagIndex++);
		}
		break;
	case VALUEMAP_TAG:
		for (auto&pair :vmap1) {
			log("VMap1 key-value=%s-%s", pair.first.c_str(), pair.second.asString().c_str());
			auto sp1 = Sprite::create(pair.second.asString());
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp1->setPosition(Vec2(x, y));
			this->removeChildByTag(tagIndex);
			this->addChild(sp1,1,tagIndex++);
		}
		for (auto&pair : vmap2) {
			log("VMap2 key-value=%s-%s", pair.first.c_str(), pair.second.asString().c_str());
			auto sp2 = Sprite::create(pair.second.asString());
			int x = CCRANDOM_0_1()*visibleSize.width;
			int y = CCRANDOM_0_1()*visibleSize.height;
			sp2->setPosition(Vec2(x, y));
			this->removeChildByTag(tagIndex);
			this->addChild(sp2, 1, tagIndex++);
		}
		break;
	}
	
}

void ContactListener::menuCloseCallback(Ref * pSender)
{
	auto sc = HelloWorld::createScene();
	Director::getInstance()->replaceScene(sc);
}

void ContactListener::onEnter()
{
	Scene::onEnter();
	log("onEnter layer->tag =%d", this->getTag());
	switch (this->getTag()) {
	case ARRAY_TAG:
		//使用create创建对象是会自动释放的
		for (int i = 0; i < MAX_COUNT; i++){
			auto sp = Sprite::create("1.png");
			this->list1->addObject(sp);
		}
		break;
	case VECTOR_TAG:
		for (int i = 0; i < MAX_COUNT; i++) {//不需要管内存
			auto sp = Sprite::create("9.png");
			this->list2.pushBack(sp);//移除最后一个元素
		}
		break;
	case DICT_TAG:
		for (int i = 0; i < MAX_COUNT; i++) {
			auto sp1 = Sprite::create("3.png");
			this->dict1->setObject(sp1, i);
			auto sp2 = Sprite::create("2.png");
			String* key = String::createWithFormat("key%d", i);
			this->dict2->setObject(sp2, key->getCString());//字符转换
		}
		break;
	case MAP_TAG:
		for (int i = 0; i < MAX_COUNT; i++) {
			String* key1 = String::createWithFormat("key_5 %d", i);
			auto sp1 = Sprite::create("5.png");
			map1.insert(key1->getCString(), sp1);
			String* key2 = String::createWithFormat("key_7 %d", i);
			auto sp2 = Sprite::create("7.png");
			map2.insert(key2->getCString(), sp2);
		}
		break;
	case VALUE_TAG:
		for (int i = 0; i < MAX_COUNT; i++) {
			Value spname("4.png");
			list3.push_back(spname);
		}
		break;
	case VALUEMAP_TAG:
		for (int i = 0; i < MAX_COUNT; i++) {
			String* key1 = String::createWithFormat("key_6 %d", i);
			std::pair<std::string, Value>pair1(key1->getCString(), Value("6.png"));
			vmap1.insert(pair1);
			String* key2 = String::createWithFormat("key_8 %d", i);
			std::pair<std::string, Value>pair2(key2->getCString(), Value("8.png"));
			vmap2.insert(pair2);
		}
		break;
	}
}

ContactListener::~ContactListener()
{
	this->list1->removeAllObjects();		//释放容器中的其他可能元素，以免占用内存
	CC_SAFE_RELEASE_NULL(this->list1);
	dict1->removeAllObjects();
	dict2->removeAllObjects();
}
