#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
 
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCMenuItemFont* pIncrease = CCMenuItemFont::create("increase 20",this,menu_selector(HelloWorld::increaseCallback));
	pIncrease->setAnchorPoint(ccp(0.0f,1.0f));
	pIncrease->setPosition(0.0f,visibleSize.height - 0.0f);


	CCMenuItemFont* pReduce   = CCMenuItemFont::create("reduce 20",this,menu_selector(HelloWorld::reduceCallback));
	pReduce->setAnchorPoint(ccp(0.0f,1.0f));
	pReduce->setPosition(0.0f,visibleSize.height - 40.0f);

	CCMenuItemFont* pGoto     = CCMenuItemFont::create("goto 100",this,menu_selector(HelloWorld::gotoCallback));
	pGoto->setAnchorPoint(ccp(0.0f,1.0f));
	pGoto->setPosition(0.0f,visibleSize.height - 80.0f);

	CCMenu* pMenu = CCMenu::create(pIncrease,pReduce,pGoto, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);



	//////////////////////////////////////////////////////////////


	CCLabelAtlas* pNumber = CCLabelAtlas::create("","number.png",55,84,'0');
	pNumber->setAnchorPoint(ccp(0.5f,0.0f));
	pNumber->setPosition(ccp(visibleSize.width/2.0f,
                             visibleSize.height/2.0f));

	this->addChild(pNumber);

	m_finishTip = CCLabelTTF::create();
	m_finishTip->setAnchorPoint(ccp(0.5f,1.0f));
	m_finishTip->setPosition(ccp(visibleSize.width*0.5f,
                                  visibleSize.height*0.5f));
	this->addChild(m_finishTip);

	//����Ǵ�cocostudio�����Ļ������NumberCount::setTextAtlas
	m_numberCount.setLabelAtlas(pNumber); 

	//������ÿһ����������ʼ��Ϊ3
	m_numberCount.setNumberDelta(3);

	//�����ֱ仯ʱ��������Ϊ0.1��
	m_numberCount.setTimeDelta(0.1f);

	//�����ֳ�ʼ��Ϊ100
	m_numberCount.setNumber(100,false);

	//��������ֹͣ�仯ʱ��Ļص�
	m_numberCount.setChangeFinishCallback(changeFinish_selector(HelloWorld::finishCallback),this);

	////����������������10�뵹��ʱ
	//m_numberCount.setNumberDelta(1);
	//m_numberCount.setTimeDelta(1.0f);
	//m_numberCount.setNumber(9,false);
	//m_numberCount.setNumber(0,true);
	//m_numberCount.setChangeFinishCallback(changeFinish_selector(HelloWorld::finishCallback),this);

    return true;
}


void HelloWorld::increaseCallback(CCObject* pSender)
{
	m_numberCount.add(20);
	m_finishTip->setString("");
}

void HelloWorld::reduceCallback(CCObject* pSender)
{
	if(m_numberCount.getNumberTarget()-20>0)
	{
		m_numberCount.add(-20);
		m_finishTip->setString("");
	}
}

void HelloWorld::gotoCallback(CCObject* pSender)
{
	m_numberCount.setNumber(100,true);
	m_finishTip->setString("");
}

void HelloWorld::finishCallback(int targetNumber)
{
	m_finishTip->setString("finish !");
}