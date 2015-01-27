#include "HelloWorldScene.h"

USING_NS_CC;
USING_NS_CC_EXT;  
using namespace rapidjson;  

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

	//����Label
	m_name = CCLabelTTF::create();
	m_name->setAnchorPoint(ccp(0.0f,0.0f));
	m_name->setPosition(ccp(30.0f,200.0f));
	this->addChild(m_name);

	m_say = CCLabelTTF::create();
	m_say->setAnchorPoint(ccp(0.0f,1.0f));
	m_say->setPosition(ccp(30.0f,200.0f));
	this->addChild(m_say);
    
	//��json�ж�ȡ�Ի�,Ȼ���� m_subtitles 
    if(readTextFromJson())
	{
		std::vector<DialogueData> list;
		std::vector<ChatData>::iterator i = m_chatDataList.begin();
		while(i!=m_chatDataList.end())
		{
			list.push_back(DialogueData(i->_say,&i->_name));
			i++;
		}

		//���˶Ի�
		m_subtitles.setDialogueList(list);

		//��ʼ����
		m_subtitles.setRunning(true);

		//ÿ0.1�����һ�����ַ�
		m_subtitles.setWordInterval(0.1f);

		//�������ַ����ֵĻص�,����������label����ʾ�ַ���
		m_subtitles.setWordAppearEvent(this,WordAppearEvent_selector(HelloWorld::wordAppear));

		//��ǰ�Ի���ȫ��ʾ��Ļص�,���Demoû���õ���
		m_subtitles.setDialogueEndEvent(this,DialogueEnd_selector(HelloWorld::dialogueEnd));
	}

	this->schedule(schedule_selector(HelloWorld::updateSay));
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);

    return true;
}


bool HelloWorld::readTextFromJson()
{
	unsigned long size;
	char* data = (char*)CCFileUtils::sharedFileUtils()->getFileData("text.json","rt",&size);
	*(data+size)='\0';

	if(!data)
		return false;
	
	std::string json = data;

	rapidjson::Document doc;
	doc.Parse<0>(json.c_str());

	m_chatDataList.clear();
	if (doc.IsObject()) 
	{
		std::string name = doc["name"].GetString();
		int numDialogue = doc["say"].Size();

		for(int i = 0 ; i<numDialogue ; i++)
			m_chatDataList.push_back(ChatData(name, doc["say"][(rapidjson::SizeType)i].GetString()));
	}
	else
		return false;

	return true;
}

void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//����öζԻ��Ѿ���ʾ��ȫ
	if(m_subtitles.isShowWholeDialogue())
	{
		//�������һ�ζԻ�,���ص�һ�ζԻ�
		if(m_subtitles.isEndofDialogueList())
			m_subtitles.jumpToDialogue(0);

		//������һ�ζԻ�
		else
			m_subtitles.nextDialogue();
	}
	else
	{
		//����öζԻ�û����ʾ��ȫ,������ȫ��ʾ
		m_subtitles.showWholeDialogue();
	}
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	return true;
}