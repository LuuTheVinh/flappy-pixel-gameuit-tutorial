#ifndef __PIPE_H__
#define __PIPE_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Pipe : public Node
{
public:
	CREATE_FUNC(Pipe);
	virtual bool init() override;
	virtual void pause() override;

	void moveFinished();

private:
	Sprite* _topPipe;
	Sprite* _bottomPipe;
	
	float _velocity;
	float _endPositionX;
};

#endif //__PIPE_H__