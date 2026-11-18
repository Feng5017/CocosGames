#include "MyAction.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* MyAction::createScene()
{
	return MyAction::create();
}

bool MyAction::init()
{
	if (!Scene::init()){
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

//创建精灵帧缓存处理背景，采用纹理贴图的方式
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("bgImage/bg.plist");
	//返回按钮
	auto pItmb = Label::createWithBMFont("fonts/fnt8.fnt", "<Back");
	auto backMItem = MenuItemLabel::create(pItmb, CC_CALLBACK_1(MyAction::menuCallback, this));
	backMItem->setPosition(Point(visibleSize.width - 100, 100));
	Menu* mn = Menu::create(backMItem, NULL);
	mn->setPosition(Point::ZERO);
	this->addChild(mn, 3);

	pb = Label::createWithBMFont("fonts/fnt8.fnt", "");
	pb->setPosition(Point(visibleSize.width / 2, visibleSize.height - 50));
	this->addChild(pb, 3);

	/*background = Sprite::createWithSpriteFrameName("");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));*/
	return true;
}

void MyAction::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	ParticleSystem* system;

	Size vsize = Director::getInstance()->getVisibleSize();
	switch (this->getTag()){
	case kExplosion:
		system = ParticleExplosion::create();//爆炸特效
		system->setPosition(vsize.width / 2, vsize.height / 2);
		system->setDuration(-1);//设置持续时间为无限循环
		/*background->setSpriteFrame("Fire.png");
		this->addChild(background, 0);*/
		pb->setString("Explosion");
		break;
	case kFire:
		system = ParticleFire::create();//火焰粒子特效
		system->setPosition(vsize.width / 2 - 70, vsize.height / 2);
		background = Sprite::createWithSpriteFrameName("Fire.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Fire");
		break;
	case kFireworks:
		system = ParticleFireworks::create();//烟花粒子特效
		system->setTexture(CCTextureCache::sharedTextureCache()->addImage("bgImage/star.png"));
		system->setPosition(vsize.width / 2 - 17, vsize.height / 2);
		system->setStartColor(Color4F(1, 1, 1, 0.5));
		system->setStartSize(5);
		system->setAngleVar(30);
		background = Sprite::createWithSpriteFrameName("Flowers.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Fireworks");
		break;
	case kFlower:
		system = ParticleFlower::create();//花束粒子特效
		system->setTexture(CCTextureCache::sharedTextureCache()->addImage("bgImage/flower.png"));
		system->setRadialAccel(-20);//设置径向加速度
		system->setPosition(vsize.width / 2, vsize.height / 2);
		pb->setString("Flower");
		break;
	case kGalaxy:
		system = ParticleGalaxy::create();//星系粒子特效
		system->setPosition(vsize.width / 2, vsize.height / 2);
		system->setStartSize(30);
		system->setSpeed(100);
		system->setSpeedVar(50);
		background = Sprite::createWithSpriteFrameName("Galaxy.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Galaxy");
		break;
	case kMeteor:
		system = ParticleMeteor::create();//流星粒子特效
		system->setPosition(vsize.width / 2, vsize.height / 2);
		system->setStartSize(90);
		background = Sprite::createWithSpriteFrameName("Galaxy.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Meteor");
		break;
	case kRain:
		system = ParticleRain::create();//下雨粒子特效
		system->setTexture(CCTextureCache::sharedTextureCache()->addImage("bgImage/lizi.png"));
		system->setStartSize(20);
		system->setScale(5.0f);
		system->setSpeed(4);
		background = Sprite::createWithSpriteFrameName("Rain.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Rain");
		break;
	case kSmoke:
		system = ParticleSmoke::create();//烟雾粒子特效
		system->setPosition(Vec2(460, 370));
		system->setSpeed(50);
		system->setSpeedVar(30);
		system->setAngleVar(30);
		background = Sprite::createWithSpriteFrameName("Smoke.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Smoke");
		break;
	case kSnow:
		system = ParticleSystemQuad::create("snow.plist");//下雪粒子特效
		system->setPosition(vsize.width / 2, vsize.height);
		background = Sprite::createWithSpriteFrameName("Snow.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Snow");
		break;
	case kSpiral:
		system = ParticleSpiral::create();//旋涡粒子特效
		system->setTexture(CCTextureCache::sharedTextureCache()->addImage("bgImage/star.png"));
		system->setSpeed(300);
		system->setPosition(vsize.width / 2, vsize.height / 2);
		background = Sprite::createWithSpriteFrameName("Spiral.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Spiral");
		break;
	case kSun:
		system = ParticleSun::create();//太阳粒子特效
		system->setPosition(vsize.width / 2, vsize.height / 2);
		system->setStartSize(100);
		system->setStartSizeVar(100);
		background = Sprite::createWithSpriteFrameName("Sun.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Sun");
		break;
	case kPlist:
		system = ParticleSystemQuad::create("bgImage/fireworks.plist");
		system->setPosition(Vec2(420, 200));
		background = Sprite::createWithSpriteFrameName("Plist.png");
		background->setPosition(Vec2(vsize.width / 2, vsize.height / 2));
		this->addChild(background, 0);
		pb->setString("Plist");
		break;
	}
	this->addChild(system, 2);
}

void MyAction::menuCallback(cocos2d::Ref * pSender)
{
	auto sc = HelloWorld::createScene();
	auto tsc = TransitionFadeTR::create(1.0f, sc);
	Director::getInstance()->replaceScene(tsc);
}
