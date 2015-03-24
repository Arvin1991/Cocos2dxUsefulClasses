/****************************************************************************
 author : LuoYu
 
 e-mail : 466474482@qq.com

 github : https://github.com/bluesky466/cocos2dxUsefulClasses
 ****************************************************************************/

#ifndef _A_STAR_H_
#define _A_STAR_H_

#include <math.h>
#include <list>
#include <vector>
#include "Mark.h"

struct ASCOORD
{
	int _x;
	int _y;

	ASCOORD()
	{
	}
	
	ASCOORD(int x,int y):
		_x(x),
		_y(y)
	{
	}

	inline bool operator == (const ASCOORD& coord)const
	{
		return this->_x == coord._x && this->_y == coord._y;
	}

	inline bool operator != (const ASCOORD& coord)const
	{
		return this->_x != coord._x || this->_y != coord._y;
	}

	inline void operator += (const ASCOORD& coord)
	{
		this->_x += coord._x ;
		this->_y += coord._y;
	}

	inline void operator -= (const ASCOORD& coord)
	{
		this->_x -= coord._x ;
		this->_y -= coord._y;
	}

	inline ASCOORD operator - (const ASCOORD& coord)
	{
		return ASCOORD(this->_x-coord._x,this->_y-coord._y);
	}

	inline ASCOORD operator + (const ASCOORD& coord)
	{
		return ASCOORD(this->_x+coord._x,this->_y+coord._y);
	}
};

struct StepData
{
	int _h;
	int _g;

	ASCOORD _coord;
	ASCOORD _parentCoord;

	StepData()
	{
	}

	StepData(const ASCOORD& coord):
		_coord(coord)
	{
	}
};

/**
 * A* Ѱ·�㷨
 * �����ȵ���SetMapSize���õ�ͼ��С
 */
class AStar
{
public:
	AStar();

	///���õ�ͼ�Ĵ�С,������һ��ʼ����
	void SetMapSize(unsigned int row,unsigned int col) {m_mark.setSize(row,col);}

	/**
	 * ����·��
	 * @return true - �д���㵽�յ��·��,����GetRoute�������·��; false - �Ҳ�������㵽�յ��·�� 
	 */
	bool ComputeRoute();

	///��ô���㵽�յ��·��
	bool GetRoute(std::vector<ASCOORD>* list);

	///��������ϰ���
	void ClearObstacles();

	///�����ϰ���
	void SetObstacle(const ASCOORD& coord)    {m_mark.setMark(coord._y,coord._x);}
	
	///�����ϰ���,ֱ�Ӵ���ȫ��
	void SetMark(const Mark& mark)			  {m_mark=mark;}

	///ȡ���ϰ���
	void CancleObstacle(const ASCOORD& coord) {m_mark.cancelMark(coord._y,coord._x);}

	///�ж�������������û���ϰ���
	bool IsObstacle(const ASCOORD& coord)     {return m_mark.isMask(coord._y,coord._x);}
	
	int  GetRow()	{return m_mark.getRow();}
	int  GetCol()   {return m_mark.getCol();}
	void SetStart(const ASCOORD& coord)   {m_start  = coord;}
	void SetTarget(const ASCOORD& coord)  {m_target = coord;}
	const ASCOORD& GetStart()             {return m_start;}
	const ASCOORD& GetTarget()            {return m_target;}

	///���ÿɲ������߶Խ���
	void SetDiagonalEnable(bool bEnable) {m_numSurround = bEnable?8:4;}
	
private:
	Mark m_mark;

	ASCOORD m_target;
	ASCOORD m_start;

	//�ڼ������ܷ����ʱ��ʹ��
	int     m_numSurround;
	int     m_gAdd[8];
	ASCOORD m_surround[8];
	
	std::list<StepData> m_openList;
	std::list<StepData> m_closeList;
	
	bool popBestStep(StepData* pSD); 
	bool isInList(std::list<StepData>& list, const ASCOORD& coord);
	bool judgeSurround(const ASCOORD& coord,const ASCOORD& parentCoord, int G);

	StepData* findFromList(std::list<StepData>& list, const ASCOORD& coord);

	int computeH(const ASCOORD& coord) {return fabs((float)(m_target._x-coord._x))*10 + fabs((float)m_target._y-coord._y)*10;}
};

inline void AStar::ClearObstacles()
{
	m_mark.clearMarks();
	m_closeList.clear();
	m_openList.clear();
}

#endif