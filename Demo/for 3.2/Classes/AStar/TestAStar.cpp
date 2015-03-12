#include "TestAStar.h"

USING_NS_CC;
using namespace std;

bool TestAStar::init()
{
    if(!TestBase::init() )
    {
        return false;
    }

	m_aStar.SetMapSize(m_row,m_col);
	m_aStar.ClearObstacles();
	m_aStar.SetDiagonalEnable(false);

	//�յ�
	m_aStar.SetTarget(m_targetCoord);

	m_target = Sprite::create(FILE_TARGET_TEX);
	m_target->setAnchorPoint(Vec2(0.0f,0.0f));
	m_target->setPosition(ascoordToVec2(m_targetCoord));
	this->addChild(m_target);

	//С��
	m_aStar.SetStart(m_startCoord);

	m_people = Sprite::create(FILE_PEOPLE_TEX);
	m_people->setAnchorPoint(Vec2(0.0f,0.0f));
	m_people->setPosition(ascoordToVec2(m_startCoord));
	this->addChild(m_people);

	//�ϰ����
	m_obstacles = Layer::create();
	m_obstacles->setPosition(0,0);
	this->addChild(m_obstacles);

	//����Χǽ
	setWalls();
	
	//�˵�
	MenuItemFont* goItem = MenuItemFont::create("GO!",CC_CALLBACK_1(TestAStar::goCallback,this));
	goItem->setAnchorPoint(Vec2(0.0f,0.0f));
	goItem->setPosition(Vec2(0.0f,m_row*m_blockSize.height));

	MenuItemFont* clearItem = MenuItemFont::create("RESET!",CC_CALLBACK_1(TestAStar::clearCallback,this));
	clearItem->setAnchorPoint(Vec2(0.0f,0.0f));
	clearItem->setPosition(Vec2(200.0f,m_row*m_blockSize.height));

	Menu* menu = Menu::create(goItem,clearItem,NULL);
	menu->setPosition(Vec2(0,0));
	this->addChild(menu);

	//�����¼�
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TestAStar::onTouchBegan,this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);


    return true;
}

void TestAStar::setDesignResolutionSize()
{
	//���޸���Ļ��С
	m_row = 15;
	m_col = 15;
	m_startCoord  = ASCOORD(1,1);
	m_targetCoord = ASCOORD(7,7);
	m_blockSize   = Sprite::create(FILE_BLOCK_TEX)->getContentSize();

	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(
													m_col * m_blockSize.width,
													(m_row + 1) * m_blockSize.height,
													ResolutionPolicy::SHOW_ALL);
}

void TestAStar::setWalls()
{
	float height = (m_row - 1) * m_blockSize.height;
	for(int i = 0 ; i<m_col ; i++)
	{
		//�ϱߵ�ǽ
		Sprite* top = Sprite::create(FILE_BLOCK_TEX);
		top->setAnchorPoint(Vec2(0.0f,0.0f));
		top->setPosition(i*m_blockSize.width, height);
		m_obstacles->addChild(top, 0, (m_row-1)*m_col+i);
		m_aStar.SetObstacle(ASCOORD(i, m_row-1));

		//�±ߵ�ǽ
		Sprite* bottom = Sprite::create(FILE_BLOCK_TEX);
		bottom->setAnchorPoint(Vec2(0.0f,0.0f));
		bottom->setPosition(i*m_blockSize.width, 0.0f);
		m_obstacles->addChild(bottom, 0, i);
		m_aStar.SetObstacle(ASCOORD(i, 0));
	}

	float width = (m_col-1) * m_blockSize.width;
	for(int i = 1 ; i<m_row-1 ; i++)
	{	
		//��ߵ�ǽ
		Sprite* left = Sprite::create(FILE_BLOCK_TEX);
		left->setAnchorPoint(Vec2(0.0f,0.0f));
		left->setPosition(0.0f, i*m_blockSize.height);
		m_obstacles->addChild(left, 0, i*m_col);
		m_aStar.SetObstacle(ASCOORD(0, i));

		//�ұߵ�ǽ
		Sprite* rigth = Sprite::create(FILE_BLOCK_TEX);
		rigth->setAnchorPoint(Vec2(0.0f,0.0f));
		rigth->setPosition(width, i*m_blockSize.height);
		m_obstacles->addChild(rigth, 0, i*m_col+m_col-1);
		m_aStar.SetObstacle(ASCOORD(m_col-1, i));
	}
}

void TestAStar::clearCallback(Ref*)
{
	m_aStar.ClearObstacles();
	m_people->stopAllActions();

	//���
	m_aStar.SetStart(m_startCoord);
	m_people->setPosition(ascoordToVec2(m_startCoord));
	
	//�����ϰ����
	this->removeChild(m_obstacles);
	m_obstacles = Layer::create();
	m_obstacles->setPosition(0,0);
	this->addChild(m_obstacles);

	//����Χǽ
	setWalls();
}

void TestAStar::stepCallback()
{
	//����·��һ��һ�����ӵ���
	if(m_routeStep<m_route.size())
	{
		Vec2 pos(m_route[m_routeStep]._x * m_blockSize.width,
				 m_route[m_routeStep]._y * m_blockSize.height);

		m_people->runAction(Sequence::create(
								CCMoveTo::create(0.2f, pos),
								CallFunc::create(CC_CALLBACK_0(TestAStar::stepCallback,this)),
								NULL)
								);
		m_routeStep++;
	}
}

void TestAStar::goCallback(Ref*)
{
	//����·��
	if(m_aStar.ComputeRoute())
	{
		//��ȡ·���б�
		m_route.clear();
		m_routeStep = 0;
		m_aStar.GetRoute(&m_route);
	
		//�Ժ�Ͱ���·��һ��һ�����ӵ���
		Vec2 pos(m_route[m_routeStep]._x * m_blockSize.width, 
				 m_route[m_routeStep]._y * m_blockSize.height);

		m_people->runAction(Sequence::create(
								CCMoveTo::create(0.2f,pos),
								CallFunc::create(CC_CALLBACK_0(TestAStar::stepCallback,this)),
								NULL));
		m_routeStep++;
	}
	else
		MessageBox("NO ROUTE!","NO ROUTE!");
}

bool TestAStar::onTouchBegan(Touch* touch, Event* e)
{
	ASCOORD coord = Vec2ToAscoord(touch->getLocation());

	//�����һȦΧǽ����ȡ��
	if(!isTouchInWalls(coord))
		return false;

	if(!m_aStar.IsObstacle(coord) && coord!=m_aStar.GetStart() && coord!=m_aStar.GetTarget())
	{
		//�����ϰ���
		Vec2 pos = correctPosition(touch->getLocation());

		Sprite* block = Sprite::create(FILE_BLOCK_TEX);
		block->setAnchorPoint(Vec2(0.0f,0.0f));
		block->setPosition(pos);
		m_obstacles->addChild(block, 0, coord._y * m_col + coord._x);

		m_aStar.SetObstacle(coord);
	}
	else
	{
		//ȡ���ϰ���
		m_aStar.CancleObstacle(coord);
		m_obstacles->removeChildByTag(coord._y * m_col + coord._x);
	}
	
	return false;
}