#ifndef __SELECT_SCENE_H__
#define __SELECT_SCENE_H__
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "cocos2d.h"

USING_NS_CC;
class SelectScene : public cocos2d::Scene
{
public:
	bool  isopen;
	static cocos2d::Scene* createScene();
	virtual bool init();

	void toFirst();
	void toSecond();
	void toThird();
	void toExit();	
	void menuMusicToggleCallback(Ref* pSender);  //“Ù¿÷ø™πÿ

	static int flag;
	const char *p;
	CREATE_FUNC(SelectScene);
	
};

#endif // __HELLOWORLD_SCENE_H__
