#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Pixel.h"

USING_NS_CC;

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
	virtual void update(float dt) override;

	CREATE_FUNC(PlayScene);

	void onMouseDown(Event* _event);
	bool onContactBegin(PhysicsContact &contact);

private:
	Size _visibleSize;
	Vec2 _origin;

	Pixel* _pixel;
	
	void pixelFall(float dt);
	void createPipe(float dt);

	LabelTTF* _scoreLabel;
	int _score;
};

#endif // __PLAY_SCENE_H__
