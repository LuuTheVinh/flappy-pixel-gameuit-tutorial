#ifndef __PIXEL_H__
#define __PIXEL_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Pixel : public Sprite
{
public:
	CREATE_FUNC(Pixel);

	virtual bool init() override;
	virtual void update(float dt) override;

	void flap();
	void fall();

	void setDead(bool dead);
	bool isDead();

private:
	Size _visibleSize;

	bool _isDead;
	bool _isFalling;

	Vec2 _velocity;
	float _rotation;
};

#endif //__PIXEL_H__