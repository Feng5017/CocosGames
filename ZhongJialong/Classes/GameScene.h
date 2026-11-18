#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include "GameOver.h"
#include "Coin.h" 
#include "HelloWorld.h"
USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;
#define MAX_MONSTER_NUM 5//怪物最大数量

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	EventListenerPhysicsContact* lis;	//物理世界事件监听器
	std::map<cocos2d::EventKeyboard::KeyCode, bool>keyMap;//存放按键状态
	Sprite *player;		//人物
	Label* label_score_num_; //当前分
	Label* label_blood_num;
	int hp;
	int score;
	//Vector<ValueMap> coinsList;//定义一个vector存储路径	
	void onEnter();	
	void update(float delta);	//定时器刷新
	void onExit();

	TMXTiledMap *tileMap1;
	TMXTiledMap *tileMap2;
	TMXLayer *collidable;
	bool onTouchBegan(cocos2d::Touch *touch, Event *event);
	void onTouchMoved(cocos2d::Touch *touch, Event *event);
	void onTouchEnded(cocos2d::Touch *touch, Event *event);

	Monster* monster;//怪物类
	Monster* monster_arr[10];//存放怪物的数组
	Coin* coin;
	Coin* coin_arr[10];

	bool is_collision(Sprite* sprite1, Sprite* sprite2);

    CREATE_FUNC(GameScene);
};

#endif // __HELLOWORLD_SCENE_H__
