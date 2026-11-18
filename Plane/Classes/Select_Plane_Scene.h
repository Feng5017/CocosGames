#ifndef __SELECT_PLANE_SCENE_H__
#define __SELECT_PLANE_SCENE_H__

#include "cocos2d.h"

class SelectPlaneScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	
	CREATE_FUNC(SelectPlaneScene);
};

#endif
