#include "TestJoint.h"


Scene* TestJoint::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0.0f, -50.0f));
	auto layer = TestJoint::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	auto infoLayer = InforLayer::create();
	scene->addChild(infoLayer);
	return scene;
}

bool TestJoint::init()
{
	if (!Layer::init())
	{
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createEdgeBox(visibleSize, MASTERIAL, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	body->getShape(0)->setRestitution(1.0f);
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	auto ball = Sprite3D::create("3d/model.obj");
	ball->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	ball->setTexture("3d/ball.png");
	ball->setScale(100);
	addChild(ball);

	this->setAccelerometerEnabled(true);
	auto aListener = EventListenerAcceleration::create(CC_CALLBACK_2(TestJoint::onAccleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(aListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(TestJoint::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(TestJoint::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(TestJoint::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(TestJoint::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	auto closeBt = Button::create("close.png", "close.png");
	closeBt->setTouchEnabled(true);
	closeBt->addTouchEventListener(CC_CALLBACK_2(TestJoint::clickBack, this));
	addChild(closeBt);
	closeBt->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
	/*auto node = Node::create();
	node->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto body2 = PhysicsBody::createBox(Size(visibleSize.width, 150), PHYSICSBODY_MATERIAL_DEFAULT);
	body2->setDynamic(false);
	body2->setGravityEnable(false);
	body2->setContactTestBitmask(0xFFFFFFFF);
	node->setPhysicsBody(body2);
	addChild(node);
	*/
	srand(time(NULL));
	this->scheduleUpdate();

	return true;
}
void TestJoint::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();

}
void TestJoint::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	
}

bool TestJoint::onTouchBegan(Touch* touch, Event* evnet) {
	
	auto location = touch->getLocation();
	auto arr = _myWorld->getShapes(location);
	cocos2d::log("Touch %d",arr.size());
	PhysicsBody* body = nullptr;
	for (auto& obj : arr)
	{
			body = obj->getBody();
			cocos2d::log("TAG %d", obj->getTag());
			break;
	}
	if (body != nullptr)
	{
		mouse = Node::create();
		mouse->setPhysicsBody(PhysicsBody::createBox(Size(10,10), PhysicsMaterial(1000000,1,1)));
		mouse->getPhysicsBody()->setDynamic(false);
		mouse->getPhysicsBody()->setContactTestBitmask(0x00000000);
		mouse->setPosition(location);
		this->addChild(mouse);
		/*PhysicsJointLimit* joint = PhysicsJointLimit::construct(mouse->getPhysicsBody(), body, Vec2::ZERO, Vec2::ZERO);
		//joint->setDistance(cocos2d::ccpDistance(joint->getBodyB()->getPosition(),joint->getBodyA()->getPosition()));
		//joint->setMaxForce(5000.0f * body->getMass());
		//joint->setMax(ccpDistance(joint->getBodyA()->getPosition(), joint->getBodyB()->getPosition()));
		joint->setCollisionEnable(false);*/
		PhysicsJointPin* joint = PhysicsJointPin::construct(mouse->getPhysicsBody(), body, location);
		joint->setMaxForce(5000.0f * body->getMass());
		joint->setCollisionEnable(false);
		_myWorld->addJoint(joint);
		return true;
	}
	return false;
}
void TestJoint::onTouchEnded(Touch* touch, Event* event) {
	removeChild(mouse);
}
void TestJoint::onTouchMoved(Touch* touch, Event* event){
	Vec2 touchLocation = touch->getLocation();
	mouse->setPosition(touchLocation);
}
void TestJoint::update(float dt) {
	if (this->getChildrenCount() < 17) {
		addSprite(rand() % 3 + 2);
	}
}
void TestJoint::onAccleration(Acceleration *pAccelerationValue, Event *event) {
	cocos2d::log("accleration");

}
bool TestJoint::onContactBegin(const PhysicsContact &contact) {
	cocos2d::log("contact");
	return contact.getContactData()->normal.y >= 0;
	//return true;
}


TestJoint::TestJoint() {
	cocos2d::log("On contruct");

}
TestJoint::~TestJoint() {
	cocos2d::log("On TestJoint Destruct");

}

void TestJoint::clickBack(Ref *pSender, Widget::TouchEventType type)
{
	auto scene = GameOverScene::createScene(-1);
	Director::getInstance()->replaceScene(TransitionMoveInR::create(1, scene));
}

void TestJoint::addSprite(int offset)
{
	
	char imagePath[20] = { 0 };
	sprintf(imagePath, "Join/%d%d.png", offset,offset);

	auto temp = /*SimpleSpriteCreator::createWithImage*/Sprite::create(imagePath);
	PhysicsBody *body = PhysicsBody::createBox(temp->getContentSize(), MASTERIAL);

	body->setContactTestBitmask(CONTACT_TEST_BITMASK);
	//body->setCategoryBitmask(offset);
	//body->setCollisionBitmask(offset%2+1);
	body->setLinearDamping(0.9);
	body->setAngularDamping(1);
	//body->setRotationEnable(false);
	body->setContactTestBitmask(0xFFFFFFFF);
	body->setMass(1.0f);
	temp->setTag(offset);
	temp->setPhysicsBody(body);
	temp->getPhysicsBody()->setGravityEnable(true);
	temp->setPosition(Vec2(offset * 100, 300*offset));
	addChild(temp);
}

