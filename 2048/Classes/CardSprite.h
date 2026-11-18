#ifndef __CARD_SPRITE_H__
#define __CARD_SPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

class CardSprite : public cocos2d::Sprite
{
public:
	//初始化游戏(卡片初始化数值，卡片宽度，卡片高度，卡片的X轴，Y轴)
	static CardSprite* createCardSprite(int number,int width,int height,float CardSpriteX,float CardSpriteY);
	virtual bool init();
	CREATE_FUNC(CardSprite);
	//获取数字
	void setNumber(int num);
	//设置数字
	int getNumber();
private:
	//显示在界面的数字
	int number;
	void enemyInit(int numbers, int width, int height, float CardSpriteX, float CardSpriteY);
	//定义显示数字的控件
	cocos2d::LabelTTF* labTTFCardNumber;
	//定义背景
	cocos2d::LayerColor *layerColorBG;
};

#endif // __HELLOWORLD_SCENE_H__

