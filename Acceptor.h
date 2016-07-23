#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include "NoCopyAble.h"
#include "IChannelCallBack.h"
#include "Channel.h"
#include "IAcceptorCallBack.h"

#include <fcntl.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>



namespace TinyMuduo
{

class Acceptor:public NoCopyAble,public IChannelCallBack
{
public:
	const static int PORT=8787;
	const static int MAXEPOLLEVENTS=1024;
	const static int BACKLOG=5;
	Acceptor(int epollfd):m_nEpollfd(epollfd){
	};
	~Acceptor(){
		delete m_pChannel;
	};
	void Start();
	void SetCallBack(IAcceptorCallBack *cb)
	{
		m_pIAcceptorCallBack=cb;
	}
	virtual void HandleEvent()
	{
		std::cout<<"Acceptor::HandleEvent()"<<std::endl;
		struct sockaddr_in cliaddr;
		socklen_t clilen=sizeof(cliaddr);
		memset(&cliaddr,0,sizeof(cliaddr));
		int connFd=accept(m_nListenFd,(struct sockaddr *)&cliaddr,&clilen);
		if(connFd<0) std::cout<<"Accept failed errno:"<<errno<<std::endl;
		else
		{
			std::cout << "new connection from " 
	                     << "[" << inet_ntoa(cliaddr.sin_addr) 
	                     << ":" << ntohs(cliaddr.sin_port) << "]" 
	                     << " accept socket fd:" << connFd 
	                     << std::endl;
	        fcntl(connFd,F_SETFL,O_NONBLOCK);
	        m_pIAcceptorCallBack->NewConnection(connFd);
		}
	}
private:
	void SocketAndBind();
	struct sockaddr_in m_sServerAddr;
	int m_nEpollfd;
	IAcceptorCallBack *m_pIAcceptorCallBack;
	int m_nListenFd;
	Channel *m_pChannel;
};

}

#endif
