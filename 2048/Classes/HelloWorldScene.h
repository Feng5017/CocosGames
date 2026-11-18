#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"
#include "GameStart.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
 //void menuCloseCallback(cocos2d::Ref* pSender);
    CREATE_FUNC(HelloWorld);

//加入手势
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
	//上下左右的方法
	bool doUp();
	bool doDown();
	bool doLeft();
	bool doRight();
	//自动卡片的生成
	void autocreateCardNumber();
	//游戏是否还能继续运行下去
	void doCheckGameOver();

	virtual void menuCallback(cocos2d::Ref* pSender);

	CCActionInterval *action1, *action2;


private:
	int firstX, firstY, endX, endY;//点击的元素
	void createCardSprite(cocos2d::Size size);//创建卡片
	//定义二维数组
	CardSprite *cardArr[4][4];

//整体游戏的分数
	int score;
	Label* bestscore;	
	//定义显示数据的控件
	cocos2d::LabelTTF *labTTFCardNumber;

	/*int susScore;
	cocos2d::LabelTTF *susScoreTTF;*/
};

#endif // __HELLOWORLD_SCENE_H__
