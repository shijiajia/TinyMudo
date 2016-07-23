#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <sys/epoll.h>
#include <errno.h>
#include <string.h>

#include "NoCopyAble.h"
#include "IAcceptorCallBack.h"
#include "TcpConnection.h"
#include "Acceptor.h"

namespace TinyMuduo
{

class TcpServer:public IAcceptorCallBack,public NoCopyAble
{
public:
	static const int MAXSIZE=1024;
	static const int MAXEPOLLEVENTS=1000;
	
	TcpServer():m_nEpollFd(-1){
		m_nEpollFd=epoll_create(MAXEPOLLEVENTS);
	};
	~TcpServer(){
		::close(m_nEpollFd);
	};

	virtual void NewConnection(int connfd)
	{
		TcpConnection *pTcpConnection = new TcpConnection(m_nEpollFd,connfd);
	}

	void Start();

private:
	inline void LOGE(std::string str, int err)
	{
		std::cerr<<str<<" Failed errno:"<<err<<" reason:"<<strerror(errno)<<std::endl;
	}
	int m_nEpollFd;
	struct epoll_event m_aEpollEvents[MAXEPOLLEVENTS];
	Acceptor *m_pAcceptor;
};

}

#endif
