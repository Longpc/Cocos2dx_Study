#include "TestBox2D.h"
#define SCALE_RATIO 32.0

Scene* TestBox2D::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TestBox2D::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestBox2D::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto closeBt = Button::create("close.png", "close.png");
	closeBt->setTouchEnabled(true);
	closeBt->addTouchEventListener(CC_CALLBACK_2(TestBox2D::clickBack, this));
	addChild(closeBt);
	closeBt->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));

	//SET MOUSE LISTENER
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(TestBox2D::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TestBox2D::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TestBox2D::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	
	//Create BOX2D World
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);

	//CREATE A BALL
	dragOffsetStartX = 0;
	dragOffsetEndX = 0;
	dragOffsetStartY = 0;
	dragOffsetEndY = 0;
	existBall = false;
	ballX = 500;
	ballY = 200;
	powerMultiplier = 10;
	ball = Sprite::create("ball.png");
	ball->setPosition(Vec2(ballX, ballY));
	this->addChild(ball);
	/*ball2 = Sprite::create("ball.png");
	ball2->setPosition(ball->getPosition());
	addChild(ball2); */
	//HelloWorl2d::defineBall();
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);


	addWall(visibleSize.width, 10, (visibleSize.width / 2), 0); //CEIL
	addWall(10, visibleSize.height, 0, (visibleSize.height / 2)); //LEFT
	addWall(10, visibleSize.height, visibleSize.width, (visibleSize.height / 2)); //RIGHT

	for (int i = 1; i <= 99; i++){
		points[i] = Sprite::create("node.png");
		this->addChild(points[i]);
	}
	

	auto box = Sprite::create("box.png");
	box->setPosition(Vec2(200, box->getContentSize().height));
	addChild(box);

	b2BodyDef boxBdDef;
	boxBdDef.type = b2_dynamicBody;
	boxBdDef.position.Set(200 / SCALE_RATIO, box->getPositionY() / SCALE_RATIO);
	boxBdDef.angle = 0;
	boxBdDef.userData = box;

	b2PolygonShape boxShape;
	boxShape.SetAsBox(2 , 2);
	b2FixtureDef boxFixture;
	boxFixture.density = 10;
	boxFixture.friction = 0.8;
	boxFixture.restitution = 0.6;
	boxFixture.shape = &boxShape;

	b2Body* boxBd = world->CreateBody(&boxBdDef);
	boxBd->CreateFixture(&boxFixture);
	boxBd->SetGravityScale(10);
	scheduleUpdate();
	return true;
}

//Simulate Physics
void TestBox2D::update(float dt){
	int positionIterations = 10;
	int velocityIterations = 10;

	deltaTime = dt;
	world->Step(dt, velocityIterations, positionIterations);
	cocos2d::log("ball pos: %f   %f", ball->getPosition().x, ball->getPosition().y);
	for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())
		if (body->GetUserData())
		{
			Sprite *sprite = (Sprite *)body->GetUserData();
			sprite->setPosition(Vec2(body->GetPosition().x * SCALE_RATIO, body->GetPosition().y * SCALE_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));



		}
	world->ClearForces();
	world->DrawDebugData(); 

}

void TestBox2D::addWall(float w, float h, float px, float py) {

	b2PolygonShape floorShape;

	floorShape.SetAsBox(w / SCALE_RATIO, h / SCALE_RATIO);
	b2FixtureDef floorFixture;
	floorFixture.density = 5;
	floorFixture.friction = 5;
	floorFixture.restitution = 0.5;
	floorFixture.shape = &floorShape;
	b2BodyDef floorBodyDef;

	floorBodyDef.position.Set(px / SCALE_RATIO, py / SCALE_RATIO);
	b2Body *floorBody = world->CreateBody(&floorBodyDef);

	floorBody->CreateFixture(&floorFixture);

}

void TestBox2D::defineBall(){
	ballShape.m_radius = 45 / SCALE_RATIO;
	b2FixtureDef ballFixture;
	ballFixture.density = 10;
	ballFixture.friction = 0.8;
	ballFixture.restitution = 0.6;
	ballFixture.shape = &ballShape;

	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.userData = ball;
	ballBodyDef.bullet = true;
	ballBodyDef.position.Set(ball->getPosition().x / SCALE_RATIO, ball->getPosition().y / SCALE_RATIO);

	ballBody = world->CreateBody(&ballBodyDef);
	ballBody->CreateFixture(&ballFixture);
	ballBody->SetGravityScale(10);
	
}
void TestBox2D::defineNode(Point location) {
	auto sprite = Sprite::create("ball.png");
	sprite->setPosition(location);
	addChild(sprite);
	
	b2Body *nodeBody;
	b2BodyDef nodeBodyDef;
	b2CircleShape nodeShape;

	nodeShape.m_radius = 45/SCALE_RATIO;
	b2FixtureDef nodeFixture;
	nodeFixture.density = 10;
	nodeFixture.friction = 0.5;
	nodeFixture.restitution = 0.5;
	nodeFixture.shape = &nodeShape;
	nodeFixture.userData = sprite;

	nodeBodyDef.type = b2_dynamicBody;
	nodeBodyDef.bullet = false;
	nodeBodyDef.position.Set(location.x / SCALE_RATIO, location.y/ SCALE_RATIO);

	nodeBody = world->CreateBody(&nodeBodyDef);
	nodeBody->CreateFixture(&nodeFixture);
	nodeBody->SetGravityScale(10);
}

bool TestBox2D::onTouchBegan(Touch* touch, Event* event)
{
	dragOffsetStartX = touch->getLocation().x;
	dragOffsetStartY = touch->getLocation().y;


	Vec2 touchLocation = touch->getLocation();
	Vec2 convPoint = Director::getInstance()->convertToGL(touchLocation);
	b2Vec2 v = b2Vec2(convPoint.x / SCALE_RATIO,convPoint.y/SCALE_RATIO);
	cocos2d::log("////////////////////////////////\nTOuch location: %f-%f\nconvLocation: %f-%f\n b2Vec: %f-%f", touchLocation.x, touchLocation.y, convPoint.x, convPoint.y, v.x, v.y);
	auto arr = world->GetBodyList();
	auto f = arr->GetFixtureList();
	while (arr)
	{
		cocos2d::log("%f,%f",arr->GetPosition().x,arr->GetPosition().y);
		arr = arr->GetNext();
	}
	
	while (f)
	{
		if (f->TestPoint(v))
		{
			cocos2d::log("You touched a body");
		}
		f = f->GetNext();
	}
	ballX = touchLocation.x;
	ballY = touchLocation.y;
	if (existBall){
		world->DestroyBody(ballBody);
		//world->DestroyBody(ball2Body);
	}

	ball->setPosition(Vec2(ballX, ballY));
	//ball2->setPosition(Vec2(200, 200));
	return true;
}

void TestBox2D::onTouchMoved(Touch* touch, Event* event)
{
	Vec2 touchLocation = touch->getLocation();

	dragOffsetEndX = touchLocation.x;
	dragOffsetEndY = touchLocation.y;

	float dragDistanceX = dragOffsetStartX - dragOffsetEndX;
	float dragDistanceY = dragOffsetStartY - dragOffsetEndY;

	//TestBox2D::simulateTrajectory(b2Vec2((dragDistanceX )/SCALE_RATIO,(dragDistanceY )/SCALE_RATIO));
	//TestBox2D::simulateTrajectory(b2Vec2((dragDistanceX * powerMultiplier) / SCALE_RATIO, (dragDistanceY * powerMultiplier) / SCALE_RATIO));

}

void TestBox2D::onTouchEnded(Touch* touch, Event* event)
{
	existBall = true;

	TestBox2D::defineBall();
	
	Vec2 touchLocation = touch->getLocation();
	TestBox2D::defineNode(touchLocation - Vec2(0, 100));
	dragOffsetEndX = touchLocation.x;
	dragOffsetEndY = touchLocation.y;

	float dragDistanceX = dragOffsetStartX - dragOffsetEndX;
	float dragDistanceY = dragOffsetStartY - dragOffsetEndY;

	//ballBody->SetLinearVelocity(b2Vec2((dragDistanceX)/SCALE_RATIO,(dragDistanceY)/SCALE_RATIO));
	//ballBody->SetLinearVelocity(b2Vec2((dragDistanceX * powerMultiplier) / SCALE_RATIO, (dragDistanceY * powerMultiplier) / SCALE_RATIO));
}

void TestBox2D::simulateTrajectory(b2Vec2 coord){

	//define ball physicis
	TestBox2D::defineBall();

	ballBody->SetLinearVelocity(b2Vec2(coord.x, coord.y));
	for (int i = 1; i <= 99; i++){
		world->Step(deltaTime, 10, 10);
		points[i]->setPosition(Vec2(ballBody->GetPosition().x*SCALE_RATIO, ballBody->GetPosition().y*SCALE_RATIO));
		world->ClearForces();

	}

	world->DestroyBody(ballBody);
}

void TestBox2D::clickBack(Ref *pSender, Widget::TouchEventType type)
{
	auto scene = GameOverScene::createScene(-1);
	Director::getInstance()->replaceScene(TransitionMoveInR::create(1, scene));
}

void TestBox2D::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	cocos2d::log("Draw");
	Layer::draw(renderer, transform, flags);

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	Director* director = Director::getInstance();

	CCASSERT(nullptr != director, "abcdef");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	_modelViewMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

	_customCommand.init(1);
	_customCommand.func = CC_CALLBACK_0(TestBox2D::onDraw, this);
	renderer->addCommand(&_customCommand);

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}

void TestBox2D::onDraw()
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");

	Mat4 oldMV;
	oldMV = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, _modelViewMV);
	world->DrawDebugData();
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, oldMV);

}
