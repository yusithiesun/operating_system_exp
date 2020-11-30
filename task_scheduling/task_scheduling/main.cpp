#include "task.h"
CLOCK CURRENT_TIME;
priority_queue<Task> READY;
Task tasks[10];
int n;

/*数据输入*/
bool input()
{
	cout << "How many tasks will be processed?" << endl;
	cin >> n;
	cout << "Enter the tasks:" << endl;
	int number;//作业编码
	string name;//作业名称
	CLOCK submitTime;//提交时间
	int needTime;//要求服务运行时间，以分钟计
	for (int i = 0; i < n; i++)
	{
		cin >> number;
		cin >> name;
		cin >> submitTime.hour; 
		getchar();//冒号
		getchar();//空格
		cin >> submitTime.min;
		cin >> needTime;
		//cout << needTime;
		getchar();//换行符
		tasks[i]=Task(number,name,submitTime,needTime);
	}
	return true;
}

bool myfunction(Task i, Task j) { return (i.getNeedTime() < j.getNeedTime()); }


/*先来先服务*/
bool FCFS()
{
	cout << "FCFS"<<endl;
	for (int i = 0; i < n; i++)
	{
		if (CURRENT_TIME.hour < tasks[i].getSubmitTime().hour | (CURRENT_TIME.hour == tasks[i].getSubmitTime().hour && CURRENT_TIME.min < tasks[i].getSubmitTime().min))
		{
			CURRENT_TIME = tasks[i].getSubmitTime();
		}
		tasks[i].start(CURRENT_TIME);
		CURRENT_TIME = tasks[i].getFinishTime();
		//CURRENT_TIME.hour+=(CURRENT_TIME.min + tasks[i].getNeedTime())/60;
		//CURRENT_TIME.min = (CURRENT_TIME.min + tasks[i].getNeedTime()) % 60;
		cout << "Runing task " << tasks[i].getNumber() << endl;
	}

	cout << "The tasks are finished at " << CURRENT_TIME.hour << ":" << CURRENT_TIME.min;
	return true;
}
/*短作业优先*/
bool SJF()
{
	cout << "SJF"<<endl;
	/*
	do {
		for (int i = 0; i < n; i++)
		{
			if (CURRENT_TIME.hour < tasks[i].getSubmitTime().hour | (CURRENT_TIME.hour == tasks[i].getSubmitTime().hour && CURRENT_TIME.min < tasks[i].getSubmitTime().min))
			{
				CURRENT_TIME = tasks[i].getSubmitTime();
			}
			else READY.push(tasks[i]);
		}
		const_cast<Task&>(READY.top()).start(CURRENT_TIME);
		CURRENT_TIME = const_cast<Task&>(READY.top()).getFinishTime();
		cout << "The tasks are finished at " << CURRENT_TIME.hour << ":" << CURRENT_TIME.min;
		READY.pop();
	} while (!READY.empty());
	*/
	return true;
}
/*最高响应比*/
bool HRRN()
{
	cout << "HRRN";
	return true;
}

int main()
{
	input();
	cout << "Enter current time:" << endl;
	cin >> CURRENT_TIME.hour;
	getchar();
	cin >> CURRENT_TIME.min;
	int signal;
	cout << "Enter 1 for FCFS, 2 for SJF, 3 for HRRN" << endl;
	getchar();
	cin >> signal;
	switch (signal)
	{
		case 1:
			FCFS(); break;
		case 2:
			SJF(); break;
		case 3:
			HRRN(); break;
	}
	/*
	input();
	cout << "Enter current time:" << endl;
	cin >> CURRENT_TIME.hour;
	getchar();//冒号
	cin >> CURRENT_TIME.min;
	FCFS();
	SJF();
	HRRN();*/
	return 0;
}