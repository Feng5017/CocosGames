#ifndef __STAGE_SCENE_H__
#define __STAGE_SCENE_H__

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include "cocos2d.h"
USING_NS_CC;
class Stage : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	void selectFirst(int x, int y);
	void removeSelectFirst(int x, int y);
	void initMap();	                                //图片生成
	void swap(int x_1, int y_1, int x_2, int y_2);  //坐标交换
	void swapAnimal();                              //坐标交换（游戏进行步骤）：
	
	bool removeAnimal(int x, int y);                //游戏核心：相同图片进行消除
	void removeAnimaLFromPoint(int x, int y);       //消除图片：

	void updateAnimal(float dt);          
	bool ifDelectSwap;

	void fillAnimal();                              //从上面向下掉图片
	void haveRemoveToUp();                          //掉图片具体步骤
	void moveDown(int i, int j, int cnt);           //掉多少个格子

	void initAnimal();
	void initAnimalFromPoint(int x, int y);
	bool haveTag();
	
	void nowScore(int length);                      //计算分数
	void update(float dt);
	CREATE_FUNC(Stage);
	
	static int tag[9][9];                           //图片格子数
	Sprite *animal[9][9];
	int x1, y1, x2, y2;                             //设置坐标
	int up, down, left, right;
	static int score;
	Label *scoreLb;                                 //分数标签
	static int number;
	Label *changeLb;                                //步数标签
	
	Label *	Qlabel;
	long long now_time;
	long long start_time;
	long long GetCurrentTime();
	
};

#endif // __HELLOWORLD_SCENE_H__
