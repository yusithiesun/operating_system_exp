#include "task.h"
CLOCK CURRENT_TIME;
priority_queue<Task> READY;
Task tasks[10];
int n;

/*��������*/
bool input()
{
	cout << "How many tasks will be processed?" << endl;
	cin >> n;
	cout << "Enter the tasks:" << endl;
	int number;//��ҵ����
	string name;//��ҵ����
	CLOCK submitTime;//�ύʱ��
	int needTime;//Ҫ���������ʱ�䣬�Է��Ӽ�
	for (int i = 0; i < n; i++)
	{
		cin >> number;
		cin >> name;
		cin >> submitTime.hour; 
		getchar();//ð��
		getchar();//�ո�
		cin >> submitTime.min;
		cin >> needTime;
		//cout << needTime;
		getchar();//���з�
		tasks[i]=Task(number,name,submitTime,needTime);
	}
	return true;
}

bool myfunction(Task i, Task j) { return (i.getNeedTime() < j.getNeedTime()); }


/*�����ȷ���*/
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
/*����ҵ����*/
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
/*�����Ӧ��*/
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
	getchar();//ð��
	cin >> CURRENT_TIME.min;
	FCFS();
	SJF();
	HRRN();*/
	return 0;
}