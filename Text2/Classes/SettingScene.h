#ifndef __Setting_SCENE_H__//活动预处理
#define __Setting_SCENE_H__

#include "HelloWorldScene.h"

#include "cocos2d.h"

class Setting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();	
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	// a selector callback
	//bool isEffect;
	//void menuSoundToggleCallback(cocos2d::Ref* pSender);
	//void menuMusicToggleCallback(cocos2d::Ref* pSender);
	void menuOkCallback(cocos2d::Ref* pSender);

	void menuCloseCallback(cocos2d::Ref* pSender);
	// implement the "static create()" method manually
	CREATE_FUNC(Setting);
};
#endif // __Setting_SCENE_H__