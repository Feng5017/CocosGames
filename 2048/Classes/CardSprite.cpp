#include "CardSprite.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

//创建卡片的方法
CardSprite * CardSprite::createCardSprite(int number, int width, int height, float CardSpriteX, float CardSpriteY)
{
	CardSprite *enemy = new CardSprite();
	if (enemy&&enemy->init()){
		enemy->autorelease();//释放原来的卡片
		enemy->enemyInit(number, width, height, CardSpriteX, CardSpriteY);

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool CardSprite::init()
{
	if (!Sprite::init())
		return false;
	else
		return true;
}

//设置数字
void CardSprite::setNumber(int num)
{
	number = num;
	//判断数字的大小来调整字体的大小
	if (number >= 0)
		labTTFCardNumber->setFontSize(100);
	if (number >= 16)
		labTTFCardNumber->setFontSize(90);
	if (number >= 128)
		labTTFCardNumber->setFontSize(60);
	if (number >= 1024)
		labTTFCardNumber->setFontSize(40);
	//判断数字颜色的大小来调整颜色
	if (number == 0)
		layerColorBG->setColor(cocos2d::Color3B(255, 200, 0));
	if (number == 2)
		layerColorBG->setColor(cocos2d::Color3B(240, 230, 220));
	if (number == 4)
		layerColorBG->setColor(cocos2d::Color3B(240, 220, 200));
	if (number == 8)
		layerColorBG->setColor(cocos2d::Color3B(240, 180, 120));
	if (number == 16)
		layerColorBG->setColor(cocos2d::Color3B(240, 140, 90));
	if (number == 32)
		layerColorBG->setColor(cocos2d::Color3B(240, 120, 90));
	if (number == 64)
		layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
	if (number == 128)
		layerColorBG->setColor(cocos2d::Color3B(240, 90, 60));
	if (number == 256)
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	if (number == 512)
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	if (number == 1024)
		layerColorBG->setColor(cocos2d::Color3B(0, 190, 0));
	if (number == 2048)
		layerColorBG->setColor(cocos2d::Color3B(0, 130, 0));
	//更新显示的数字
	if (number > 0){
		labTTFCardNumber->setString(__String::createWithFormat("%i", number)->getCString());
	}else{
		labTTFCardNumber->setString("");
	}
}
//获取数字
int CardSprite::getNumber()
{
	return number;
}

void CardSprite::enemyInit(int numbers, int width, int height, float CardSpriteX, float CardSpriteY)
{
//初始化数字
	number = numbers;
//加入游戏卡片背景颜色
	layerColorBG = LayerColor::create(Color4B(255, 200, 0, 255), width - 15, height - 15);//宽高减去边界
	layerColorBG->setPosition(Point(CardSpriteX, CardSpriteY));
//判断如果不等于0就显示，否则为空
	if (number>0){
		//加入中间字体
		labTTFCardNumber = LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "Arial", 100);
		//设置到颜色背景的中间
		labTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labTTFCardNumber);
	}
	else{
		labTTFCardNumber = LabelTTF::create("", "Arial", 100);
		labTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labTTFCardNumber);
	}
	this->addChild(layerColorBG);
}
