#ifndef _TEST_SUBTITLES_H_
#define _TEST_SUBTITLES_H_

#include "cocos2d.h"
#include "TestBase.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Subtitles.h"

class TestSubtitles : public TestBase
{
public:

    bool init();  
	
	///�����ַ����ֵĻص�
	void wordAppear(const std::string& who, const std::string& say, void* userData)
	{
		m_name->setString(who.c_str());
		m_say->setString(say.c_str());
	}

	///��ǰ�Ի���ȫ��ʾ��Ļص�,���Demoû���õ���
	void dialogueEnd(int,const DialogueData&){}

	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);

    CREATE_FUNC(TestSubtitles);
    CREATE_SCENE(TestSubtitles);

private:
	Subtitles m_subtitles;
	cocos2d::Label* m_name;
	cocos2d::Label* m_say;

	///��json�ļ��м��ضԻ�,�ŵ� m_chatDataList ��
	bool readTextFromJson();
};

#endif
