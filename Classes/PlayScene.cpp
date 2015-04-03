#include "PlayScene.h"

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////

	isDead = false;

	Sprite *menuBackground = Sprite::create("PlayBackground.png");
	menuBackground->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(menuBackground);

	//EdgeBox
	/*auto edgeBox = Node::create();
	auto edgeBoxBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

	edgeBox->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	edgeBox->setPhysicsBody(edgeBoxBody);
	this->addChild(edgeBox);*/


	//Player
	pixel = new Pixel(this);

    //Event Listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(PlayScene::onMouseDown, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//Contact listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayScene::onContactBegin, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//Update
	this->scheduleUpdate();

	this->schedule(schedule_selector(PlayScene::createPipe, this), 2.0f);

	listPipes.push_back(new Pipe(this));

	//Score
	score = 0;
	scoreLabel = LabelTTF::create("0", "fonts/Minecrafter.ttf", 100);
	scoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 6) * 5);

	this->addChild(scoreLabel, 50);

    return true;
}

void PlayScene::update(float dt)
{
	
	for (std::list<Pipe*>::iterator pipe = listPipes.begin(); pipe != listPipes.end(); pipe++)
	{
		if ((*pipe)->isMoveFinished)
		{
			CC_SAFE_DELETE((*pipe));
			listPipes.remove(*pipe);
			break;
		}
	}

	pixel->Update();

	if (isDead || pixel->isDead)
	{
		this->removeChild(scoreLabel);
		this->pause();

		auto childs = this->getChildren();
		for each (auto child in childs)
		{
			child->pause();
		}

		auto overlayer = OverLayer::create();
		overlayer->setScore(score);

		overlayer->setPosition(origin.x, origin.y);
		this->addChild(overlayer, 110);
	}
	
}

void PlayScene::onMouseDown(Event* _event)
{
	EventMouse* mouse = (EventMouse*)_event;
	if (mouse->getMouseButton() == MOUSE_BUTTON_LEFT)
	{
		pixel->Flap();
		this->scheduleOnce(schedule_selector(PlayScene::pixelFall), 0.1);
	}
}

void PlayScene::pixelFall(float dt)
{
	pixel->Fall();
}

void PlayScene::onExit()
{
	Layer::onExit();

	CC_SAFE_DELETE(pixel);
	
	while (!listPipes.empty())
	{
		CC_SAFE_DELETE(listPipes.front());
		listPipes.pop_front();
	}
}

void PlayScene::createPipe(float dt)
{
	listPipes.push_back(new Pipe(this));
}

bool PlayScene::onContactBegin(PhysicsContact &contact)
{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	if ((shapeA->getCategoryBitmask() == eObjectBitmask::PIPE && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL) ||
		(shapeB->getCategoryBitmask() == eObjectBitmask::PIPE && shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL))
	{
		isDead = true;
	}
	else
	{
		if ((shapeA->getCategoryBitmask() == eObjectBitmask::LINE && shapeB->getCategoryBitmask() == eObjectBitmask::PIXEL) ||
			(shapeB->getCategoryBitmask() == eObjectBitmask::LINE && shapeA->getCategoryBitmask() == eObjectBitmask::PIXEL))
		{
			score++;
			scoreLabel->setString(String::createWithFormat("%d", score)->getCString());
		}
	}


	return true;
}