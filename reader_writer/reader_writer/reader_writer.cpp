#pragma warning(disable:4996);
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024
using namespace std;
/*
ʵ��Ҫ��
�����鲢�����̣����ߺ�д�ߣ�����һ���ļ�F��Ҫ��
(1)���������߿�ͬʱ���ļ�ִ�ж�������
(2)ֻ����һ��д�����ļ���д��Ϣ��
(3)��һд�������д����֮ǰ�������������߻�д�߹�����
(4)д��ִ��д����ǰ��Ӧ�����е�д�ߺͶ���ȫ���˳���
*/

int mutex = 1;//�����ź�������Ӧ����д�߹�ͬ���ʵ����ݶ�������ʵ�֣���&д��д&д�Ļ���
int rmutex = 1;//�����ź�������Ӧ��������߹�ͬ���ʵ�readcount������ʵ�֣����߶�readcount�����Ļ������
int readcount = 0;//���ڽ��ж��Ķ�����Ŀ

bool reader(const char* file);//������
bool writer(const char* file);//д����
bool wait_mutex();//�ȴ�д���̲�������ź�
bool wait_rmutex();//�ȴ�readcount����ռ�õ��ź�
void signal_mutex();//���Կ�ʼд����
void signal_rmutex();//�����޸�readcount
bool read(const char* file);//��ȡ�ļ�����
bool write(const char* file);//���ļ�д������


bool reader(const char* file)//������
{
	puts("reader thread begins...");
	if (!wait_rmutex())
	{   
		puts("readcount��ȡ����");
			return false;
	}
	if (readcount == 0) {
		if (!wait_mutex())
		{
			puts("��д���̼以��");
			return false;
		}
	}
	readcount++;
	signal_rmutex();
	if (!read(file))
	{
		puts("����ʧ��");
		return false;
	}
	if (!wait_rmutex())
	{
		puts("readcountд�ػ���");
		return false;
	}
	readcount--;
	if (readcount == 0)signal_mutex();
	signal_rmutex();
	puts("reader thread ends");
	return true;
}

bool writer(const char* file)//д����
{
	puts("writer thread begins...");
	if (!wait_mutex())return false;
	write(file);
	signal_mutex();
	puts("writer thread ends");
	return true;
}




bool wait_mutex()//�ȴ�д���̲�������ź�
{
	if (mutex)return true;
	else return false;
}

bool wait_rmutex()//�ȴ�readcount����ռ�õ��ź�
{
	if (mutex)return true;
	else return false;
}

void signal_mutex()//���Կ�ʼд����
{
	mutex = 1;
}

void signal_rmutex()//�����޸�readcount
{
	rmutex = 1;
}

bool read(const char* file)//��ȡ�ļ�����
{
	puts("��ȡ�ļ����ݣ�");
	char buf[MAX_LINE];
	FILE* fp;
	int len;             /*���ַ�����*/
	if ((fp = fopen(file, "r")) == NULL)
	{
		puts("���ļ�ʧ��");
		return false;
	}
	rmutex--;
	while (fgets(buf, MAX_LINE, fp) != NULL)
	{
		//len = strlen(buf);
		//buf[len - 1] = '\0';  /*ȥ�����з�*/
		printf("%s\n",buf);
	}
	fclose(fp);
	return true;
}
bool write(const char* file)//���ļ�д������
{
	FILE* fp = fopen(file, "w");
	if (fp == NULL){ 
		puts("���ļ�ʧ��");
		return false; 
	}
	mutex--;
	char txt[10] = "hello";
	//puts("Write something to the file:");
	//gets(txt);
    fprintf(fp, "%s",txt);
	fclose(fp);
	return true;
}


int main()
{
	writer("test.txt");
	reader("test.txt");
	return 0;
}