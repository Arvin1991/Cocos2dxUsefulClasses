#include "TestScrollingBackground.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

bool TestScrollingBackground::init()
{
    if(!TestBase::init())
    {
        return false;
    }

	createInitMenu();

    return true;
}

//һЩ�˵������ò���Ҳ����,���ͼ��صĲ�����okCallback����
void TestScrollingBackground::createInitMenu()
{
	m_isRunning = false;

	m_setLayer = Layer::create();
	this->addChild(m_setLayer);

	//��������
	Vector<MenuItem*> dirItemFronts;
	dirItemFronts.pushBack(MenuItemFont::create("Right to Left"));
	dirItemFronts.pushBack(MenuItemFont::create("Left to Right"));
	dirItemFronts.pushBack(MenuItemFont::create("Top to Bottom"));
	dirItemFronts.pushBack(MenuItemFont::create("Bottom to Top"));
	m_dirSelItem = MenuItemToggle::createWithCallback(
								CC_CALLBACK_1(TestScrollingBackground::toggleCallback,this),
								dirItemFronts);

	m_dirSelItem->setAnchorPoint(Vec2(0.5f,0.5f));
	m_dirSelItem->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f, m_visibleSize.height / 4.0f * 3.0f));

    MenuItemImage *nextDir = MenuItemImage::create(
                                        "ScrollingBackground/nextNor.png",
                                        "ScrollingBackground/nextCli.png",
                                        CC_CALLBACK_1(TestScrollingBackground::dirChangeCallback,this));

	nextDir->setTag(1);
	nextDir->setAnchorPoint(Vec2(0.5f,0.5f));
	nextDir->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 6.0f * 5, m_visibleSize.height / 4.0f * 3.0f));

	MenuItemImage *lastDir = MenuItemImage::create(
                                        "ScrollingBackground/lastNor.png",
                                        "ScrollingBackground/lastCli.png",
                                        CC_CALLBACK_1(TestScrollingBackground::dirChangeCallback,this));
	lastDir->setTag(-1);
	lastDir->setAnchorPoint(Vec2(0.5f,0.5f));
	lastDir->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 6.0f, m_visibleSize.height / 4.0f * 3.0f));



    //ģʽ����
	Vector<MenuItem*> modeItemFronts;
	modeItemFronts.pushBack(MenuItemFont::create("Loop Mode"));
	modeItemFronts.pushBack(MenuItemFont::create("Drop Mode"));
	m_modeSelItem = MenuItemToggle::createWithCallback(
							   CC_CALLBACK_1(TestScrollingBackground::toggleCallback,this),
							   modeItemFronts);

	m_modeSelItem->setAnchorPoint(Vec2(0.5f,0.5f));
	m_modeSelItem->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f, m_visibleSize.height / 3.0f));

	m_modeSelItem->setAnchorPoint(Vec2(0.5f,0.5f));
	m_modeSelItem->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f , m_visibleSize.height / 2.0f));

	MenuItemImage *nextMode = MenuItemImage::create(
                                        "ScrollingBackground/nextNor.png",
                                        "ScrollingBackground/nextCli.png",
                                        CC_CALLBACK_1(TestScrollingBackground::modeChangeCallback,this));
	nextMode->setTag(1);
	nextMode->setAnchorPoint(Vec2(0.5f,0.5f));
	nextMode->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 6.0f * 5.0f, m_visibleSize.height / 2.0f));

	MenuItemImage *lastMode = MenuItemImage::create(
                                        "ScrollingBackground/lastNor.png",
                                        "ScrollingBackground/lastCli.png",
                                        CC_CALLBACK_1(TestScrollingBackground::modeChangeCallback,this));
	lastMode->setTag(-1);
	lastMode->setAnchorPoint(Vec2(0.5f,0.5f));
	lastMode->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 6.0f, m_visibleSize.height / 2.0f));

	MenuItemFont* pOK = MenuItemFont::create("OK",CC_CALLBACK_1(TestScrollingBackground::okCallback,this));
	pOK->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f,m_visibleSize.height / 4.0f));

	Menu* pMenu = Menu::create(lastDir,m_dirSelItem,nextDir,lastMode,m_modeSelItem,nextMode,pOK,NULL);
	pMenu->setPosition(Vec2::ZERO);

    m_setLayer->addChild(pMenu);

	m_bg = 0;
}

void TestScrollingBackground::pauseCallback(Ref* pObject)
{
	int i = ((MenuItemToggle*)pObject)->getSelectedIndex();
	
	if(i)
		m_bg->pauseScroll();
	else
		m_bg->resumeScroll(m_bg->getVelocity());
}

void TestScrollingBackground::reverseCallback(Ref* pSender)
{
	m_bg->setVelocity(-m_bg->getVelocity());
}

void TestScrollingBackground::addBgSpriteCallback(Ref*)
{
	if(addBgSprite(5))
	{
		m_addTipsLabel->setString("add background - success");
		__String num;
		num.initWithFormat("the number of background sprites : %d",m_bg->getNumBgSprite());
		m_numBgLabel->setString(num.getCString());
	}

	else
		m_addTipsLabel->setString("add background - failure");  
}

void TestScrollingBackground::dirChangeCallback(Ref* pSender)
{
	int index = m_dirSelItem->getSelectedIndex();
	int tag   = ((MenuItemImage*)pSender)->getTag();
	if(tag<0)
	{
		index--;
		if(index<0)
			index = 3;
	}
	else
	{
		index++;
		index%=4;
	}
	m_dirSelItem->setSelectedIndex(index);
}

void TestScrollingBackground::modeChangeCallback(Ref* pSender)
{
	int index = m_modeSelItem->getSelectedIndex();
	int tag   = ((MenuItemImage*)pSender)->getTag();
	if(tag<0)
	{
		index--;
		if(index<0)
			index = 1;
	}
	else
	{
		index++;
		index%=2;
	}
	m_modeSelItem->setSelectedIndex(index);
}

void TestScrollingBackground::toggleCallback(Ref* pSender)
{
	
}

void TestScrollingBackground::nextBgCallback(Ref* pSender)
{
	if(((MenuItemImage*)pSender)->getTag()==0)
	{
		switch(m_direction)
		{
		case ScrollDirection::SD_BOTTOM_TO_TOP:
		case ScrollDirection::SD_LEFT_TO_RIGHT:
			m_bg->scrollToNextBgSprite(m_velocity);
			break;
		case ScrollDirection::SD_TOP_TO_BOTTOM:
		case ScrollDirection::SD_RIGHT_TO_LEFT:
			m_bg->scrollToNextBgSprite(-m_velocity);
			break;
		}
		
	}
	else
	{
		switch(m_direction)
		{
		case ScrollDirection::SD_BOTTOM_TO_TOP:
		case ScrollDirection::SD_LEFT_TO_RIGHT:
			m_bg->scrollToNextBgSprite(-m_velocity);
			break;
		case ScrollDirection::SD_TOP_TO_BOTTOM:
		case ScrollDirection::SD_RIGHT_TO_LEFT:
			m_bg->scrollToNextBgSprite(m_velocity);
			break;
		}
	}
}

void TestScrollingBackground::okCallback(Ref* pSender)
{
	if(!m_bg)
	{
		m_isRunning = true;
		m_runLayer  = Layer::create();
		this->addChild(m_runLayer);

		int dirSel = m_dirSelItem->getSelectedIndex();
		switch (dirSel)
		{
		case 0:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_RIGHT_TO_LEFT);
			m_direction = ScrollDirection::SD_RIGHT_TO_LEFT;
			break;
		case 1:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_LEFT_TO_RIGHT);
			m_direction = ScrollDirection::SD_LEFT_TO_RIGHT;
			break;
		case 2:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_TOP_TO_BOTTOM);
			m_direction = ScrollDirection::SD_TOP_TO_BOTTOM;
			break;
		case 3:
			m_bg = ScrollingBackground::create(ScrollDirection::SD_BOTTOM_TO_TOP);
			m_direction = ScrollDirection::SD_BOTTOM_TO_TOP;
			break;
		default:
			break;
		}

		m_runLayer->addChild(m_bg,1);

		for (int i = 1; i < 5; i++)
		{
			addBgSprite(i);
		}

		/*
		//����һ���������鳹���뿪��Ļ��ʱ�����Ϣ,���ַ�ʽ
		if(m_modeSelItem->getSelectedIndex()==0)
			m_bg->setBgChangeEventListener(this,bgSpriteChangeEvent(HelloWorld::loopBgChangeCallback)); //ѭ��ģʽ
		else
			m_bg->setBgChangeEventListener(this,bgSpriteChangeEvent(HelloWorld::dropBgChangeCallback)); //����ģʽ
		*/
		//����һ���������鳹���뿪��Ļ��ʱ�����Ϣ,���ַ�ʽ
		if(m_modeSelItem->getSelectedIndex()==0)
			m_bg->setBgChangeEventListener(CC_CALLBACK_3(TestScrollingBackground::loopBgChangeCallback,this)); //ѭ��ģʽ
		else
			m_bg->setBgChangeEventListener(CC_CALLBACK_3(TestScrollingBackground::dropBgChangeCallback,this)); //����ģʽ

		/*
		//�����������ƶ�ʱ�����Ϣ,���ַ�ʽ
		m_bg->setBgMoveEventListener(this,bgSpriteMoveEvent(HelloWorld::bgMoveCallback));
		*/
		//�����������ƶ�ʱ�����Ϣ,���ַ�ʽ
		m_bg->setBgMoveEventListener(CC_CALLBACK_2(TestScrollingBackground::bgMoveCallback,this));

		m_velocity = 300.0f;
		m_bgSprite = m_bg->getCurBgSprite();
		m_bg->beginContinuousScroll(m_velocity);

		//һ�����汳���ƶ�������
		m_pItem = Sprite::create("ScrollingBackground/item.png");
		m_pItem->setAnchorPoint(Vec2(0.5f,0.5f));
		m_pItem->setPosition(Vec2(0.0f,0.0f));
		m_runLayer->addChild(m_pItem,2);

		//pItemê��һֱ����(0.5,0.5),����һֱ��(0.0,0.0),ע�⿴�������л���ʱ���������������
		//�������龫���ê�㲻ͬ����Ӱ��pItem��λ��
		m_pItem->setPosition(m_bg->getCurBgSprite()->getPosition());
		




		/*�������һЩ�˵�������,����Ҳ����*/
		//�����෴�ٶȵİ�ť
		MenuItemFont* reverse = MenuItemFont::create("reverse",CC_CALLBACK_1(TestScrollingBackground::reverseCallback,this));

		//��ͣ
		MenuItemToggle* pause = MenuItemToggle::createWithCallback(CC_CALLBACK_1(TestScrollingBackground::pauseCallback,this),
																	MenuItemFont::create("pause"),
																	MenuItemFont::create("resume"),
																	NULL);
		pause->setPosition(Vec2(0.0f,50.0f));

		//��һ������
		MenuItemImage* lastBg = MenuItemImage::create("ScrollingBackground/lastBgNor.png",
													  "ScrollingBackground/lastBgCli.png",
													  "",
													  CC_CALLBACK_1(TestScrollingBackground::nextBgCallback,this));
		lastBg->setTag(0);
		lastBg->setAnchorPoint(Vec2(0.0f,0.5f));
		lastBg->setPosition(m_visibleOrigin + Vec2(-m_visibleSize.width / 2.0f, 0.0f));

		//��һ������
		MenuItemImage* nextBg = MenuItemImage::create("ScrollingBackground/NextBgNor.png",
													  "ScrollingBackground/NextBgCli.png",
													  "",
													  CC_CALLBACK_1(TestScrollingBackground::nextBgCallback,this));
		nextBg->setTag(1);
		nextBg->setAnchorPoint(Vec2(1.0f,0.5f));
		nextBg->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f, 0.0f));

		//���ӱ�������
		MenuItemFont* add = MenuItemFont::create("add background",CC_CALLBACK_1(TestScrollingBackground::addBgSpriteCallback,this));
		add->setPosition(Vec2(0.0f,-50.0f));

		Menu* pMenu = Menu::create(pause,reverse,add,lastBg,nextBg,NULL);
		pMenu->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f, m_visibleSize.height / 2.0f));
		m_runLayer->addChild(pMenu,3);

		//������ʾ��
		Color3B color(255,0,0);
		m_itemTipsLabel = Label::createWithTTF("","ScrollingBackground/fonts/arial.ttf",17.0f);
		m_itemTipsLabel->setColor(color);
		m_itemTipsLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		m_itemTipsLabel->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f, m_visibleSize.height / 6.0f));
		m_runLayer->addChild(m_itemTipsLabel,3);

		m_numBgLabel = Label::createWithTTF("","ScrollingBackground/fonts/arial.ttf",17.0f);
		m_numBgLabel->setColor(color);
		m_numBgLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		m_numBgLabel->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f,m_visibleSize.height / 10.0f));
		m_runLayer->addChild(m_numBgLabel,3);

		
		m_addTipsLabel = Label::createWithTTF("","ScrollingBackground/fonts/arial.ttf",17.0f);
		m_addTipsLabel->setColor(color);
		m_addTipsLabel->setAnchorPoint(Vec2(0.5f,0.5f));
		m_addTipsLabel->setPosition(m_visibleOrigin + Vec2(m_visibleSize.width / 2.0f,m_visibleSize.height / 10.0f * 9.0f));
		m_addTipsLabel->setString("");
		m_runLayer->addChild(m_addTipsLabel,3);

		setTextTips(m_bg->getCurBgSprite());

		this->removeChild(m_setLayer);
		m_setLayer = 0;
	}
}

void TestScrollingBackground::setTextTips(Sprite* bgSprite)
{
	std::string str = "the item is on the ";

	int tag = bgSprite->getTag();
	switch(tag)
	{
	case 1:
		str+="center of the bg (bg : 1)";
		break;
	case 2:
		str+="the lower left corner of the bg (bg : 2)";
		break;
	case 3:
		str+="the upper right corner of the bg (bg : 3)";
		break;
	case 4:
		str+="the lower right corner of the bg (bg : 4)";
		break;
	case 5:
		str+="center of the bg (bg : add)";
		break;
	}

	m_itemTipsLabel->setString(str.c_str());

	__String num;
	num.initWithFormat("the number of background sprites : %d",m_bg->getNumBgSprite());
	m_numBgLabel->setString(num.getCString());
}

bool TestScrollingBackground::addBgSprite(int index)
{
	if(!m_bg)
		return false;

	Sprite *pSprite;
	switch(index)
	{
	case 1:
		pSprite = Sprite::create("ScrollingBackground/1.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(1);
		pSprite->setAnchorPoint(Vec2(0.5f,0.5f));//ê��Ϊ��������
		break;
			  
	case 2:
		pSprite = Sprite::create("ScrollingBackground/2.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(2);
		pSprite->setAnchorPoint(Vec2(0.0f,0.0f));//ê��Ϊ�������½�
		break;


	case 3:
		pSprite = Sprite::create("ScrollingBackground/3.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(3);
		pSprite->setAnchorPoint(Vec2(1.0f,1.0f));//ê��Ϊ�������Ͻ�
		break;

	case 4:
		pSprite = Sprite::create("ScrollingBackground/4.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(4);
		pSprite->setAnchorPoint(Vec2(1.0f,0.0f));//ê��Ϊ�������½�
		break;

	case 5:
		pSprite = Sprite::create("ScrollingBackground/add.png");

		if(pSprite == 0)
			return false;

		pSprite->setTag(5);
		pSprite->setAnchorPoint(Vec2(0.5f,0.5f));//ê��Ϊ��������
		break;

	default:
		return false;
	}


	//���ӱ�������,����Ľڵ���Զ�����������Ļ,���ӵ�����β
	//����һ�߹���һ�����ӱ�������ڵ�,�����ǰ�ڵ�������β,��ʧ�ܲ�����false
	if(m_bg->addBackgroundSprite(pSprite))
		return true;
	else
		return false;
}

void TestScrollingBackground::dropBgChangeCallback(Sprite* current,Sprite* follow,Sprite* leave)
{
	//�������뿪��Ļ�ı��������Ƴ�
	m_bg->removeBgSprite(leave);
	
	if(m_bg->getVelocity()>0.0f)
		m_bgSprite = current; //current�������������뿪��Ļ���Ǹ�����
	else
		m_bgSprite = follow;  //follow�Ǹ����������뿪��Ļ���Ǹ�����

	setTextTips(m_bgSprite);

	switch(m_bgSprite->getTag())
	{
	case 2:
		m_pItem->setAnchorPoint(Vec2(0.0f,0.0f));
		break;
	case 3:
		m_pItem->setAnchorPoint(Vec2(1.0f,1.0f));
		break;
	case 4:
		m_pItem->setAnchorPoint(Vec2(1.0f,0.0f));
		break;
	default:
		m_pItem->setAnchorPoint(Vec2(0.5f,0.5f));
		break;
	}
}

void TestScrollingBackground::loopBgChangeCallback(Sprite* current,Sprite* follow,Sprite* leave)
{
	if(m_bg->getVelocity()>0.0f)
		m_bgSprite = current; //current�������������뿪��Ļ���Ǹ�����
	else
		m_bgSprite = follow;  //follow�Ǹ����������뿪��Ļ���Ǹ�����

	setTextTips(m_bgSprite);

	switch(m_bgSprite->getTag())
	{
	case 2:
		m_pItem->setAnchorPoint(Vec2(0.0f,0.0f));
		break;
	case 3:
		m_pItem->setAnchorPoint(Vec2(1.0f,1.0f));
		break;
	case 4:
		m_pItem->setAnchorPoint(Vec2(1.0f,0.0f));
		break;
	default:
		m_pItem->setAnchorPoint(Vec2(0.5f,0.5f));
		break;
	}
}

void TestScrollingBackground::bgMoveCallback(Sprite* current,Sprite* follow)
{
	m_pItem->setPosition(m_bgSprite->getPosition());
}

void TestScrollingBackground::btBackCallback(Ref* ref)
{
	if(m_isRunning)
	{
		m_runLayer->removeChild(m_bg);
		this->removeChild(m_runLayer);
		m_runLayer = 0;
		m_bg = 0;

		createInitMenu();
	}
	else
	{
		TestBase::btBackCallback(ref);
	}
}