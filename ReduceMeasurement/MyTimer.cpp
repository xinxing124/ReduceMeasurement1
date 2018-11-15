#include "stdafx.h"  
#include "MyTimer.h"  
  
#include <iostream>  
#include <time.h>  
  
using namespace std;  
  
MyTimer::MyTimer()  
{  
    m_hThread = CreateThread(NULL, 0, ThreadFunc, LPVOID(this), 0, NULL);  
}  
  
MyTimer::~MyTimer()  
{  
    CloseHandle(m_hThread);  
    m_hThread = NULL;  
}  
  
void MyTimer::startTimer(int timeID, unsigned int nElapse, TimerCallBack func)  
{  
    Timer_Info info = {nElapse, time(NULL), func};  
    m_timerList.insert(std::make_pair(timeID, info));       //�˴�û���ж�timeID�Ƿ���ھ�ֱ��insert������Ϊmap::insert��key����ʱ��insert��ʧ�ܡ�  
}  
  
void MyTimer::endTimer(int timeID)  
{  
    m_timerList.erase(timeID);      //ֱ��eraseԭ��ͬinsert��������ʱ�� eraseʧ��  
}  
  
DWORD WINAPI MyTimer::ThreadFunc(LPVOID lpParam)  
{  
    MyTimer *pThis = (MyTimer*)(lpParam);  
  
    if (pThis == NULL)  return -1;  
  
    while (true)  
    {  
        if (pThis->m_timerList.size() != 0)      //ֻ�ڶ�ʱ���б�����IDʱ��������  
        {  
            time_t endTime = time(NULL);  
            int diff;  
  
            //�ڶ�ʱ���б��У�������ѯ�ĸ���ʱ��ʱ�䵽�  
            for (TIMER_LIST::iterator iter =pThis->m_timerList.begin(); iter != pThis->m_timerList.end(); iter++)  
            {  
                diff = (int)difftime(endTime, iter->second.beginTime);  
                if (diff >= iter->second.nElapse )  
                {  
                    iter->second.onTimer(iter->first);  
                    iter->second.beginTime = endTime;  
                }  
            }  
        }  
          
    }  
}  