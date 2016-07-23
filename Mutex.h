#ifndef MUTEX_H
#define MUTEX_H

#include "NoCopyAble.h"
#include <pthread.h>

namespace TinyMuduo
{
	class Mutex:public NoCopyAble
	{
	public:
		Mutex(){
			pthread_mutex_init(&m_tMutex,NULL);
		}
		void Lock()
		{
			pthread_mutex_lock(&m_tMutex);
		}
		void UnLock()
		{
			pthread_mutex_unlock(&m_tMutex);
		}
		pthread_mutex_t* GetPthreadMutex()
		{
			return &m_tMutex;
		}
		~Mutex()
		{
			pthread_mutex_destroy(&m_tMutex);
		}
	private:
		pthread_mutex_t m_tMutex;
	};

	class ScopeMutex:public NoCopyAble
	{
	public:
		ScopeMutex(Mutex& _mutex):m_rMutext(_mutex)
		{
			m_rMutext.Lock();
		}
		~ScopeMutex()
		{
			m_rMutext.UnLock();
		}
	private:
		Mutex& m_rMutext;
	};
}

#endif
