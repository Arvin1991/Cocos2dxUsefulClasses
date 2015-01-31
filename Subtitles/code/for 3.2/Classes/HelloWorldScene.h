#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Subtitles.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
   ///������Ҫ���� m_subtitles
    void updateSay(float interval)
	{
		m_subtitles.update(interval);
	}
	
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

    CREATE_FUNC(HelloWorld);

private:
	Subtitles m_subtitles;
	cocos2d::Label* m_name;
	cocos2d::Label* m_say;

	///��json�ļ��м��ضԻ�,�ŵ� m_chatDataList ��
	bool readTextFromJson();
};

#endif // __HELLOWORLD_SCENE_H__
