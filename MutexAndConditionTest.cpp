#include <iostream>
#include <pthread.h>
#include "Mutex.h"
#include "Condition.h"
using namespace std;
using namespace TinyMuduo;
void ThreadFunc(void * arg)
{
	for (int i=1;i<=20;i++)
		cout<<"PID :"<<pthread_self()<<"i="<<i<<endl;
}

void ThreadFunc1(void * arg)
{
	for (int i=1;i<=20;i++)
		cout<<"PID :"<<pthread_self()<<"j="<<i<<endl;
}

int main()
{
	Mutex mutex;
	pthread_t tid,tid1;

	pthread_create(&tid,NULL, (void *) ThreadFunc,NULL);
	pthread_create(&tid1,NULL, (void *) ThreadFunc1,NULL);
	pthread_join(tid,NULL);
	pthread_join(tid1,NULL);
	return 0
}
