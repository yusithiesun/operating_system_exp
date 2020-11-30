#include "task.h"

Task::Task(int set_number, string set_name, CLOCK set_submitTime, int set_needTime)
{
	this->number = set_number;
	this->name = set_name;
	this->submitTime = set_submitTime;
	this->needTime = set_needTime;
}


void Task::start(CLOCK set_start_time)
{
	this->startTime = set_start_time;
	this->finishTime.min = (startTime.min+ needTime)%60;
	this->finishTime.hour = startTime.hour + (startTime.min + needTime) / 60;
	this->waitTime = (startTime.hour - submitTime.hour)*60+startTime.min-submitTime.min;
	this->runTime = needTime + waitTime;
}

void Task::calculateRP()
{
	this->RP = (waitTime + needTime) / needTime;
}

CLOCK Task::getStartTime()
{
	return this->startTime;
}
CLOCK Task::getFinishTime()
{
	return this->finishTime;
}
int Task::getWaitTime()
{
	return this->waitTime;
}
int Task::getRunTime()
{
	return this->runTime;
}
double Task::getRP()
{
	return this->RP;
}
CLOCK Task::getSubmitTime()
{
	return this->submitTime;
}

int Task::getNeedTime()
{
	return this->needTime;
}

int Task::getNumber()
{
	return this->number;
}

bool Task::operator<(const Task& b)const
{
	return runTime < const_cast<Task&>(b).getRunTime();
}