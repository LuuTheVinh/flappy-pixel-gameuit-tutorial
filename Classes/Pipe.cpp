#include "Pipe.h"

Pipe::Pipe(Layer* layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	velocity = 120;

	bottomTexture = Sprite::create("Pipe.png");
	float randomY = RandomHelper::random_int(-(int)(bottomTexture->getContentSize().height / 4), (int)(bottomTexture->getContentSize().height / 3));

	bottomTexture->setPosition(origin.x + visibleSize.width + bottomTexture->getContentSize().width / 2, origin.y + randomY);

	auto bottomBody = PhysicsBody::createBox(bottomTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	bottomBody->setDynamic(false);
	bottomBody->setCategoryBitmask(eObjectBitmask::PIPE);
	bottomBody->setCollisionBitmask(0);
	bottomBody->setContactTestBitmask(eObjectBitmask::PIXEL);

	bottomTexture->setPhysicsBody(bottomBody);

	layer->addChild(bottomTexture);

	topTexture = Sprite::create("Pipe.png");
	topTexture->setPosition(bottomTexture->getPositionX(), bottomTexture->getPositionY() + topTexture->getContentSize().height + 220);

	auto topBody = PhysicsBody::createBox(topTexture->getContentSize(), PhysicsMaterial(0, 0, 0));
	topBody->setDynamic(false);
	topBody->setCategoryBitmask(eObjectBitmask::PIPE);
	topBody->setCollisionBitmask(0);
	topBody->setContactTestBitmask(eObjectBitmask::PIXEL);

	topTexture->setPhysicsBody(topBody);

	//Score Line
	auto scoreline = Node::create();
	scoreline->setPosition(Point(bottomTexture->getContentSize().width, bottomTexture->getContentSize().height + 110));
	auto linebody = PhysicsBody::createBox(Size(1, 300), PhysicsMaterial(0, 0, 0));
	linebody->setDynamic(false);

	linebody->setCategoryBitmask(eObjectBitmask::LINE);
	linebody->setCollisionBitmask(0);
	linebody->setContactTestBitmask(eObjectBitmask::PIXEL);

	scoreline->setPhysicsBody(linebody);
	bottomTexture->addChild(scoreline);

	//Move
	endPositionX = origin.x - bottomTexture->getContentSize().width / 2;
	isMoveFinished = false;

	bottomTexture->runAction(Sequence::createWithTwoActions(MoveTo::create(visibleSize.width / velocity, Point(endPositionX, bottomTexture->getPositionY())), CallFunc::create(CC_CALLBACK_0(Pipe::moveFinished, this))));
	topTexture->runAction(Sequence::createWithTwoActions(MoveTo::create(visibleSize.width / velocity, Point(endPositionX, topTexture->getPositionY())), CallFunc::create(CC_CALLBACK_0(Pipe::moveFinished, this))));

	layer->addChild(topTexture);
}

void Pipe::moveFinished()
{
	topTexture->removeFromParent();
	bottomTexture->removeFromParent();

	isMoveFinished = true;
}