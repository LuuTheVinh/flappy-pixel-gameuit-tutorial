#include "Pixel.h"

bool Pixel::init()
{
	if (!this->initWithFile("Pixel.png"))
	{
		return false;
	}

	auto origin = Director::getInstance()->getVisibleOrigin();
	_visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(origin.x + _visibleSize.width / 2, origin.y + _visibleSize.height / 2);

	auto body = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0, 0, 0));

	// I am a pixel
	body->setCategoryBitmask(eObjectBitmask::PIXEL);
	// I collide with ...
	body->setCollisionBitmask(0);
	body->setContactTestBitmask(eObjectBitmask::PIPE | eObjectBitmask::LINE);

	this->setPhysicsBody(body);

	_isDead = false;
	_isFalling = true;

	_velocity = Vec2(0, 0);
	_rotation = 0.0f;

	// update
	this->scheduleUpdate();

	return true;
}

void Pixel::update(float dt)
{
	if (_isFalling)
	{
		if (this->getPositionY() > this->getContentSize().height / 2)
		{
			_velocity.y += -1;
			_rotation += 3;
		}
		else
		{
			_velocity.y = 0;
			_rotation = 0;
			_isDead = true;

			this->setPositionY(this->getContentSize().height / 2);
		}
	}
	else
	{
		if (this->getPositionY() < _visibleSize.height - this->getContentSize().height / 2)
		{
			_velocity.y = 10;
			_rotation += -10;
		}
		else
		{
			_velocity.y = 0;
			_rotation = 0;
		}
	}

	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() + _velocity.y));
	this->setRotation(_rotation);
}

void Pixel::flap()
{
	_isFalling = false;
}

void Pixel::fall()
{
	_isFalling = true;
}

void Pixel::setDead(bool dead)
{
	_isDead = dead;
}

bool Pixel::isDead()
{
	return _isDead;
}
