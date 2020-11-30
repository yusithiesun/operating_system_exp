#pragma warning(disable:4996);
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 1024
using namespace std;
/*
实验要求：
有两组并发进程：读者和写者，共享一个文件F，要求：
(1)允许多个读者可同时对文件执行读操作；
(2)只允许一个写者往文件中写信息；
(3)任一写者在完成写操作之前不允许其他读者或写者工作；
(4)写者执行写操作前，应需已有的写者和读者全部退出。
*/

int mutex = 1;//互斥信号量。对应被读写者共同访问的数据对象，用来实现：读&写，写&写的互斥
int rmutex = 1;//互斥信号量。对应被多个读者共同访问的readcount，用来实现：读者对readcount变量的互斥访问
int readcount = 0;//正在进行读的读者数目

bool reader(const char* file);//读进程
bool writer(const char* file);//写进程
bool wait_mutex();//等待写进程不互斥的信号
bool wait_rmutex();//等待readcount不被占用的信号
void signal_mutex();//可以开始写进程
void signal_rmutex();//可以修改readcount
bool read(const char* file);//读取文件内容
bool write(const char* file);//向文件写入内容


bool reader(const char* file)//读进程
{
	puts("reader thread begins...");
	if (!wait_rmutex())
	{   
		puts("readcount读取互斥");
			return false;
	}
	if (readcount == 0) {
		if (!wait_mutex())
		{
			puts("读写进程间互斥");
			return false;
		}
	}
	readcount++;
	signal_rmutex();
	if (!read(file))
	{
		puts("操作失败");
		return false;
	}
	if (!wait_rmutex())
	{
		puts("readcount写回互斥");
		return false;
	}
	readcount--;
	if (readcount == 0)signal_mutex();
	signal_rmutex();
	puts("reader thread ends");
	return true;
}

bool writer(const char* file)//写进程
{
	puts("writer thread begins...");
	if (!wait_mutex())return false;
	write(file);
	signal_mutex();
	puts("writer thread ends");
	return true;
}




bool wait_mutex()//等待写进程不互斥的信号
{
	if (mutex)return true;
	else return false;
}

bool wait_rmutex()//等待readcount不被占用的信号
{
	if (mutex)return true;
	else return false;
}

void signal_mutex()//可以开始写进程
{
	mutex = 1;
}

void signal_rmutex()//可以修改readcount
{
	rmutex = 1;
}

bool read(const char* file)//读取文件内容
{
	puts("读取文件内容：");
	char buf[MAX_LINE];
	FILE* fp;
	int len;             /*行字符个数*/
	if ((fp = fopen(file, "r")) == NULL)
	{
		puts("打开文件失败");
		return false;
	}
	rmutex--;
	while (fgets(buf, MAX_LINE, fp) != NULL)
	{
		//len = strlen(buf);
		//buf[len - 1] = '\0';  /*去掉换行符*/
		printf("%s\n",buf);
	}
	fclose(fp);
	return true;
}
bool write(const char* file)//向文件写入内容
{
	FILE* fp = fopen(file, "w");
	if (fp == NULL){ 
		puts("打开文件失败");
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