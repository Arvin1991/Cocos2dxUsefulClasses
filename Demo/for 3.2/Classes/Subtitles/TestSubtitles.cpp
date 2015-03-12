#include "TestSubtitles.h"

USING_NS_CC;
using namespace  rapidjson;

bool TestSubtitles::init()
{
    if ( !TestBase::init() )
    {
        return false;
    }

	//����Label
	m_name = Label::create();
	m_name->setAnchorPoint(Vec2::ZERO);
	m_name->setPosition(Vec2(30.0f,200.0f));
	this->addChild(m_name);

	m_say = Label::create();
	m_say->setAnchorPoint(Vec2(0.0f,1.0f));
	m_say->setPosition(Vec2(30.0f,200.0f));
	this->addChild(m_say);
    
	//��json�ж�ȡ�Ի�,Ȼ���� m_subtitles 
    if(readTextFromJson())
	{
		//��ʼ����
		m_subtitles.setRunning(true);

		//ÿ0.1�����һ�����ַ�
		m_subtitles.setWordInterval(0.1f);

		//�������ַ����ֵĻص�,����������label����ʾ�ַ���
		m_subtitles.setWordAppearEvent(CC_CALLBACK_3(TestSubtitles::wordAppear,this));

		//��ǰ�Ի���ȫ��ʾ��Ļص�,���Demoû���õ���
		m_subtitles.setDialogueEndEvent(CC_CALLBACK_2(TestSubtitles::dialogueEnd,this));
	}

	//���ô��������¼�
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan     = CC_CALLBACK_2(TestSubtitles::onTouchBegan,this);
	listener->onTouchEnded     = CC_CALLBACK_2(TestSubtitles::onTouchEnded,this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

    return true;
}


bool TestSubtitles::readTextFromJson()
{
	Data data = FileUtils::getInstance()->getDataFromFile("Subtitles/text.json");
	if(data.isNull())
		return false;

	char*p = (char*)data.getBytes();
	
	std::string json;

	for(int i = 0 ;i<data.getSize() ; i++)
		json+=*(p+i);

	rapidjson::Document doc;
	doc.Parse<0>(json.c_str());

	std::vector<DialogueData> list;

	if (doc.IsObject()) 
	{
		std::string name = doc["name"].GetString();
		int numDialogue = doc["say"].Size();

		for(int i = 0 ; i<numDialogue ; i++)
			list.push_back(DialogueData(name, doc["say"][(rapidjson::SizeType)i].GetString(),0));
	}
	else
		return false;
	
	//���˶Ի�
	m_subtitles.setDialogueList(list);

	return true;
}

bool TestSubtitles::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
	return true;
}

void TestSubtitles::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
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