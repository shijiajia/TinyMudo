#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include "NoCopyAble.h"
#include "IChannelCallBack.h"
#include "Channel.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <errno.h>

namespace TinyMuduo
{
class TcpConnection:public NoCopyAble,public IChannelCallBack
{
public:
	TcpConnection(int epollfd,int sockfd);
	~TcpConnection(){
		delete m_pChannel;
	};
	virtual void HandleEvent()
	{
		char buf[1024];
		memset(buf,0,sizeof(buf));
		int n=read(m_nConnFd,buf,1024);
		if (n<0)
		{
			std::cout<<"read error errno"<<errno<<std::endl;
			close(m_nConnFd);
		}else if (n==0)
		{
			std::cout<<"client close"<<std::endl;
			close(m_nConnFd);
		}else{
			if (write(m_nConnFd,buf,n)!=n)
				std::cout<<"write error errno:"<<errno<<std::endl;;
		}
	}

private:
	int m_nEpollFd;
	int m_nConnFd;
	Channel *m_pChannel;
};

}

#endif
