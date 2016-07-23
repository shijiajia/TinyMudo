#ifndef CONDITION_H
#define CONDITION_H

#include "Mutex.h"
#include "NoCopyAble.h"

namespace TinyMuduo
{
	class Condition:public NoCopyAble
	{
	public:
		explicit Condition(Mutex& _mutex):m_rMutex(_mutex)
		{
			pthread_cond_init(&m_tCond,NULL);
		}

		~Condition()
		{
			pthread_cond_destroy(&m_tCond);
		}
		void Wait()
		{
			pthread_cond_wait(&m_tCond,m_rMutex.GetPthreadMutex());
		}
		void Notify()
		{
			pthread_cond_signal(&m_tCond);
		}
		void BroadCast()
		{
			pthread_cond_broadcast(&m_tCond);
		}
	private:
		Mutex& m_rMutex;
		pthread_cond_t m_tCond;

	};
}

#endif
