#include <vector>

#include <iostream>

#include "TcpServer.h"
#include "Channel.h"

using namespace std;
using namespace TinyMuduo;

void TcpServer::Start()
{
	m_pAcceptor=new Acceptor(m_nEpollFd);
	m_pAcceptor->SetCallBack(this);
	m_pAcceptor->Start();
	for(;;)
	{
		int nfds=epoll_wait(m_nEpollFd,m_aEpollEvents,MAXEPOLLEVENTS,-1);
		vector< Channel *> vChannel;
		for (int i=0;i<nfds;i++)
		{
			Channel * pTemp=static_cast<Channel *> (m_aEpollEvents[i].data.ptr);
			pTemp->SetRevent(m_aEpollEvents[i].events);
			vChannel.push_back(pTemp);
		}
		for (int i=0;i<vChannel.size();i++)
		{
			vChannel[i]->HandleEvent();
		}
	}
}



