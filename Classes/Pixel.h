#ifndef __PIXEL_H__
#define __PIXEL_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Pixel
{
public:
	Pixel(Layer* layer);
	void Flap();
	void Update();
	void Fall();
	bool isDead;

private:
	Sprite* pixelTexture;
	PhysicsBody* pixelBody;

	Size visibleSize;
	Vec2 origin;

	bool isFalling;
	Vec2 velocity;
	float rotation;
};

#endif //__PIXEL_H__