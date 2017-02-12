#include "Pipe.h"

bool Pipe::init()
{
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();

	_velocity = 120;

	// bottom pipe
	_bottomPipe = Sprite::create("Pipe.png");
	
	int minY = -(int)(_bottomPipe->getContentSize().height / 4);
	int maxY = (int)(_bottomPipe->getContentSize().height / 3);
	float randomY = RandomHelper::random_int(minY, maxY);

	_bottomPipe->setPosition(origin.x + visibleSize.width + _bottomPipe->getContentSize().width / 2, origin.y + randomY);

	auto bottomBody = PhysicsBody::createBox(_bottomPipe->getContentSize(), PhysicsMaterial(0, 0, 0));
	bottomBody->setDynamic(false);
	bottomBody->setCategoryBitmask(eObjectBitmask::PIPE);
	bottomBody->setCollisionBitmask(0);
	bottomBody->setContactTestBitmask(eObjectBitmask::PIXEL);

	_bottomPipe->setPhysicsBody(bottomBody);

	this->addChild(_bottomPipe);

	// top pipe
	_topPipe = Sprite::create("Pipe.png");
	_topPipe->setPosition(_bottomPipe->getPositionX(), _bottomPipe->getPositionY() + _topPipe->getContentSize().height + 220);

	auto topBody = PhysicsBody::createBox(_topPipe->getContentSize(), PhysicsMaterial(0, 0, 0));
	topBody->setDynamic(false);
	topBody->setCategoryBitmask(eObjectBitmask::PIPE);
	topBody->setCollisionBitmask(0);
	topBody->setContactTestBitmask(eObjectBitmask::PIXEL);

	_topPipe->setPhysicsBody(topBody);

	this->addChild(_topPipe);

	// score line
	auto scoreline = Node::create();
	scoreline->setPosition(Point(_bottomPipe->getContentSize().width, _bottomPipe->getContentSize().height + 110));
	auto linebody = PhysicsBody::createBox(Size(1, 300), PhysicsMaterial(0, 0, 0));
	linebody->setDynamic(false);

	linebody->setCategoryBitmask(eObjectBitmask::LINE);
	linebody->setCollisionBitmask(0);
	linebody->setContactTestBitmask(eObjectBitmask::PIXEL);

	scoreline->setPhysicsBody(linebody);

	_bottomPipe->addChild(scoreline);

	// move
	_endPositionX = origin.x - _bottomPipe->getContentSize().width / 2;

	float time = visibleSize.width / _velocity;
	auto topEndPosition = Vec2(_endPositionX, _topPipe->getPositionY());
	auto botEndPosition = Vec2(_endPositionX, _bottomPipe->getPositionY());

	_bottomPipe->runAction(Sequence::createWithTwoActions(MoveTo::create(time, botEndPosition) , CallFunc::create(CC_CALLBACK_0(Pipe::moveFinished, this))));
	_topPipe->runAction(Sequence::createWithTwoActions(MoveTo::create(time, topEndPosition), CallFunc::create(CC_CALLBACK_0(Pipe::moveFinished, this))));

	return true;
}

void Pipe::pause()
{
	Node::pause();

	// pause children
	auto childen = this->getChildren();
	for (auto child : childen)
	{
		child->pause();
	}
}

void Pipe::moveFinished()
{
	this->removeFromParent();
}