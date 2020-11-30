#pragma once
#include<string.h>
#include<queue>
#include<iomanip>
#include<iostream>
#include<algorithm>
using namespace std;

struct CLOCK
{
	int hour;
	int min;
};

class Task
{
public:
	Task() {};
	Task(int set_number, string set_name, CLOCK set_submitTime, int set_needTime);/*��ҵ��ʼ��*/
	void start(CLOCK set_start_time);/*��ҵ��ʼִ��*/
	void calculateRP();/*������Ӧ��*/

	CLOCK getSubmitTime();/*��ȡ�ύʱ��*/
	int getNeedTime();
	int getNumber();
	CLOCK getStartTime();/*��ȡ��ʼʱ��*/
	CLOCK getFinishTime();/*��ȡ���ʱ��*/
	int getWaitTime();/*��ȡ�ȴ�ʱ��  waitTime=startTime-submitTime*/
	int getRunTime();/*��ȡ��תʱ��  runTime=finishTime-startTime+waitTime*/
	double getRP();/*��ȡ��Ӧ��*/
	bool operator<(const Task& b)const;
private:
	int number;//��ҵ����
	string name;//��ҵ����
	CLOCK submitTime;//�ύʱ��
	int needTime;//Ҫ���������ʱ�䣬�Է��Ӽ�

	CLOCK startTime;//��ʼʱ��
	CLOCK finishTime;//���ʱ��
	int waitTime;//�ȴ�ʱ��  waitTime=startTime-submitTime
	int runTime;//��תʱ��  runTime=finishTime-startTime+waitTime = needTime+waitTime
	double RP;//��Ӧ�� RP=(waitTime + needTime)/needTime
};