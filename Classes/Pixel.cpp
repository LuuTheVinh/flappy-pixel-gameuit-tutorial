#include "Pixel.h"

Pixel::Pixel(Layer* layer)
{
	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();

	pixelTexture = Sprite::create("Pixel.png");
	pixelTexture->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	pixelBody = PhysicsBody::createBox(pixelTexture->getContentSize(), PhysicsMaterial(0,0,0));
	//I am a pixel
	pixelBody->setCategoryBitmask(eObjectBitmask::PIXEL);
	//I collide with ...
	//pixelBody->setCollisionBitmask(eObjectBitmask::PIPE);
	pixelBody->setContactTestBitmask(eObjectBitmask::PIPE | eObjectBitmask::LINE);

	//////////////////////

	pixelTexture->setPhysicsBody(pixelBody);

	layer->addChild(pixelTexture, 100);

	isFalling = true;

	velocity = Vec2(0, 0);
	rotation = 0.0f;

	isDead = false;
}

void Pixel::Update()
{
	if (isFalling)
	{
		if (pixelTexture->getPositionY() > pixelTexture->getContentSize().height / 2)
		{
			velocity.y += -1;
			rotation += 3;
		}
		else
		{
			velocity.y = 0;
			rotation = 0;

			pixelTexture->setPositionY(pixelTexture->getContentSize().height / 2);

			isDead = true;
		}
	}
	else
	{
		if (pixelTexture->getPositionY() < visibleSize.height - pixelTexture->getContentSize().height / 2)
		{
			velocity.y = 10;
			rotation += -10;
		}
		else
		{
			velocity.y = 0;
			rotation = 0;
		}
	}

	pixelTexture->setPosition(Point(pixelTexture->getPositionX(), pixelTexture->getPositionY() + velocity.y));
	pixelTexture->setRotation(rotation);
}

void Pixel::Flap()
{
	isFalling = false;
}

void Pixel::Fall()
{
	isFalling = true;
}