//读者写者问题：读者优先. g++/windows
#include <windows.h>
#include <stdio.h>
#include <time.h>

DWORD dwID;

#define C(S) CreateSemaphore(NULL, 1, 3, (S)) 
#define P(S) WaitForSingleObject((S), INFINITE)
#define V(S) ReleaseSemaphore((S), 1, NULL)
#define CT(func, args) CreateThread(NULL, 0, (func), (args), 0, &dwID)
#define PM(num, S) WaitForMultipleObjects((num), (S), true, INFINITE)

struct TInfo
{
    int id;
    char type;
    double s;
    double d;
};
TInfo threads[100];
HANDLE hThread[100];
HANDLE s1, s2, s3;
int c = 0;
int Reader_Count = 0;

void Read_TInfo();
//void RP();
DWORD WINAPI Reader(LPVOID lpParam);
DWORD WINAPI Writer(LPVOID lpParam);


void Read_TInfo()
{
    FILE* fp;
    fp = fopen("in.txt", "r");
    while (fscanf(fp, "%d %c %lf %lf", &threads[c].id,
        &threads[c].type, &threads[c].s, &threads[c].d) != EOF) {
        c++;
    }
    fclose(fp);
}

void RP()
{
    s1 = C(L"sig1");
    s2 = C(L"sig2");
    for (int i = 0; i < c; ++i) {
        if (threads[i].type == 'W') {
            hThread[i] = CT(Writer, &threads[i]);
        }
        else {
            hThread[i] = CT(Reader, &threads[i]);
        }
    }
    PM(c, hThread); //等待所有线程结束
}

DWORD WINAPI Reader(LPVOID lpParam)
{
    TInfo* arg = (TInfo*)lpParam;
    Sleep(arg->s * 1000);
    P(s1);
    if (Reader_Count == 0) {
        P(s2);
    }
    Reader_Count++;
    V(s1);
    printf("线程 %d 正在读!\n", arg->id);
    Sleep(arg->d * 1000);
    printf("线程 %d 读完了!\n", arg->id);
    P(s1);
    Reader_Count--;
    if (Reader_Count == 0) {
        V(s2);
    }
    V(s1);
}

DWORD WINAPI Writer(LPVOID lpParam)
{
    TInfo* arg = (TInfo*)lpParam;
    Sleep(arg->s * 1000);
    P(s2);
    printf("线程 %d 正在写!\n", arg->id);
    Sleep(arg->d * 1000);
    printf("线程 %d 写完了!\n", arg->id);
    V(s2);
}

int main()
{
    Read_TInfo();
    RP();
    //Sleep(3000);
    return 0;
}


//读者写者问题：读者优先. g++/windows
#include <windows.h>
#include <stdio.h>
#include <time.h>

DWORD dwID;

#define C(S) CreateSemaphore(NULL, 1, 3, (S)) 
#define P(S) WaitForSingleObject((S), INFINITE)
#define V(S) ReleaseSemaphore((S), 1, NULL)
#define CT(func, args) CreateThread(NULL, 0, (func), (args), 0, &dwID)
#define PM(num, S) WaitForMultipleObjects((num), (S), true, INFINITE)

struct TInfo
{
    int id;
    char type;
    double s;
    double d;
};

TInfo threads[100];
HANDLE hThread[100];
HANDLE s1, s2, s3;
int c = 0;
int Reader_Count = 0;

void Read_TInfo();
void RP();
DWORD WINAPI Reader(LPVOID lpParam);
DWORD WINAPI Writer(LPVOID lpParam);


void Read_TInfo()
{
    FILE* fp;
    fp = fopen("in.txt", "r");
    while (fscanf_s(fp, "%d %c %lf %lf", &threads[c].id,
        &threads[c].type, &threads[c].s, &threads[c].d) != EOF) {
        c++;
    }
    fclose(fp);
}

void RP()
{
    s1 = C(L"sig1");
    s2 = C(L"sig2");
    s3 = C(L"sig3");
    for (int i = 0; i < c; ++i) {
        if (threads[i].type == 'W') {
            hThread[i] = CT(Writer, &threads[i]);
        }
        else {
            hThread[i] = CT(Reader, &threads[i]);
        }
    }
    PM(c, hThread); //等待所有线程结束
}

DWORD WINAPI Reader(LPVOID lpParam)
{
    TInfo* arg = (TInfo*)lpParam;
    Sleep(arg->s * 1000);
    P(s3);
    P(s1);
    if (Reader_Count == 0) {
        P(s2);
    }
    Reader_Count++;
    V(s1);
    V(s3);
    printf("线程 %d 正在读!\n", arg->id);
    Sleep(arg->d * 1000);
    printf("线程 %d 读完了!\n", arg->id);
    P(s1);
    Reader_Count--;
    if (Reader_Count == 0) {
        V(s2);
    }
    V(s1);
}

DWORD WINAPI Writer(LPVOID lpParam)
{
    TInfo* arg = (TInfo*)lpParam;
    Sleep(arg->s * 1000);
    P(s3);
    P(s2);
    printf("线程 %d 正在写!\n", arg->id);
    Sleep(arg->d * 1000);
    printf("线程 %d 写完了!\n", arg->id);
    V(s2);
    V(s3);
}

int main()
{
    Read_TInfo();
    RP();
    //Sleep(3000);
    return 0;
}