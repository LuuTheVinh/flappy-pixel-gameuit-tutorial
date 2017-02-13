#include "PlayScene.h"
#include "Pipe.h"
#include "MenuScene.h"
#include "OverLayer.h"

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	// scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	// background
	Sprite *menuBackground = Sprite::create("PlayBackground.png");
	menuBackground->setPosition(_origin.x + _visibleSize.width / 2, _origin.y + _visibleSize.height / 2);
	this->addChild(menuBackground);

	// player
	_pixel = Pixel::create();
	this->addChild(_pixel);

    // event mouse Listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(PlayScene::onMouseDown, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	// contact listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	// update
	this->scheduleUpdate();

	// schedule create pipe
	this->schedule(schedule_selector(PlayScene::createPipe, this), 2.0f);

	// create first pipe
	auto pipe = Pipe::create();
	this->addChild(pipe);

	// score
	_score = 0;
	_scoreLabel = LabelTTF::create("0", "fonts/Minecrafter.ttf", 100);
	_scoreLabel->setPosition(_origin.x + _visibleSize.width / 2, _origin.y + (_visibleSize.height / 6) * 5);

	this->addChild(_scoreLabel, 50);

    return true;
}

void PlayScene::update(float dt)
{
	if (_pixel->isDead())
	{
		this->removeChild(_scoreLabel);
		this->pause();

		auto children = this->getChildren();
		for (auto child : children)
		{
			child->pause();
		}

		auto overlayer = OverLayer::create();
		overlayer->setScore(_score);

		overlayer->setPosition(_origin.x, _origin.y);
		this->addChild(overlayer, 110);
	}
}

void PlayScene::onMouseDown(Event* _event)
{
	EventMouse* mouse = (EventMouse*)_event;
	if (mouse->getMouseButton() == MOUSE_BUTTON_LEFT)
	{
		_pixel->flap();
		this->scheduleOnce(schedule_selector(PlayScene::pixelFall), 0.1f);
	}
}

void PlayScene::pixelFall(float dt)
{
	_pixel->fall();
}

void PlayScene::createPipe(float dt)
{
	auto pipe = Pipe::create();
	this->addChild(pipe);
}

bool PlayScene::onContactBegin(PhysicsContact &contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	if ((shapeA->getCategoryBitmask() == eObjectBitmask::PIPE && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL) ||
		(shapeB->getCategoryBitmask() == eObjectBitmask::PIPE && shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL))
	{
		_pixel->setDead(true);
	}
	else
	{
		if ((shapeA->getCategoryBitmask() == eObjectBitmask::LINE && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL) ||
			(shapeB->getCategoryBitmask() == eObjectBitmask::LINE && shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL))
		{
			_score++;
			_scoreLabel->setString(String::createWithFormat("%d", _score)->getCString());
		}
	}


	return true;
}