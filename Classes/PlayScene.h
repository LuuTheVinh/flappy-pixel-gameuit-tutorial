#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Pixel.h"
#include "Pipe.h"
#include "MenuScene.h"
#include "OverLayer.h"

USING_NS_CC;

class PlayScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(PlayScene);

	void onMouseDown(Event* _event);
	void update(float dt);
	void onExit();
	bool onContactBegin(PhysicsContact &contact);

private:
	Size visibleSize;
	Vec2 origin;

	Pixel* pixel;
	void pixelFall(float dt);

	void createPipe(float dt);
	void pipeMoveFinished();
	std::list<Pipe*> listPipes;

	bool isDead;

	LabelTTF* scoreLabel;
	int score;
};

#endif // __PLAY_SCENE_H__
