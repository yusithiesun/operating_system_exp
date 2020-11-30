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
	Task(int set_number, string set_name, CLOCK set_submitTime, int set_needTime);/*作业初始化*/
	void start(CLOCK set_start_time);/*作业开始执行*/
	void calculateRP();/*计算响应比*/

	CLOCK getSubmitTime();/*获取提交时间*/
	int getNeedTime();
	int getNumber();
	CLOCK getStartTime();/*获取开始时间*/
	CLOCK getFinishTime();/*获取完成时间*/
	int getWaitTime();/*获取等待时间  waitTime=startTime-submitTime*/
	int getRunTime();/*获取周转时间  runTime=finishTime-startTime+waitTime*/
	double getRP();/*获取响应比*/
	bool operator<(const Task& b)const;
private:
	int number;//作业编码
	string name;//作业名称
	CLOCK submitTime;//提交时间
	int needTime;//要求服务运行时间，以分钟计

	CLOCK startTime;//开始时间
	CLOCK finishTime;//完成时间
	int waitTime;//等待时间  waitTime=startTime-submitTime
	int runTime;//周转时间  runTime=finishTime-startTime+waitTime = needTime+waitTime
	double RP;//响应比 RP=(waitTime + needTime)/needTime
};