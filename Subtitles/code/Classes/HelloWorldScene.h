#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"cocos-ext.h"  
#include "Subtitles.h"

struct ChatData
{
	ChatData(const std::string& name,const std::string& say):
		_name(name),
		_say(say)
	{
	}
	std::string _name;
	std::string _say;
};

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();


	//������Ҫ���� m_subtitles
    void updateSay(float interval)
	{
		m_subtitles.update(interval);
	}
	
	///�����ַ����ֵĻص�
	void wordAppear(const char* dialogue,void* userdata)
	{
		m_name->setString(((std::string*)userdata)->c_str());
		m_say->setString(dialogue);
	}

	///��ǰ�Ի���ȫ��ʾ��Ļص�,���Demoû���õ���
	void dialogueEnd(int,const DialogueData&){}

	bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    CREATE_FUNC(HelloWorld);

private:
	Subtitles m_subtitles;
	cocos2d::CCLabelTTF* m_name;
	cocos2d::CCLabelTTF* m_say;

	std::vector<ChatData> m_chatDataList;

	///��json�ļ��м��ضԻ�,�ŵ� m_chatDataList ��
	bool readTextFromJson();
};

#endif // __HELLOWORLD_SCENE_H__
