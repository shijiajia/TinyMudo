#include "Acceptor.h"

using namespace TinyMuduo;

void Acceptor::Start()
{
	SocketAndBind();
	m_pChannel=new Channel(m_nEpollfd,m_nListenFd);
	m_pChannel->SetCallBack(this);
	m_pChannel->EableReading();
	if (listen(m_nListenFd,BACKLOG)<0) std::cout<<"listen failed: errno"<<errno<<std::endl;
}

void Acceptor::SocketAndBind()
{
	int on=1;
	if ((m_nListenFd=socket(AF_INET, SOCK_STREAM, 0))<0) 
		std::cout<<"Socket Failed errno:"<<errno<<std::endl;
	setsockopt(m_nListenFd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	fcntl(m_nListenFd,F_SETFL,O_NONBLOCK);
	m_sServerAddr.sin_family = AF_INET;
	m_sServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_sServerAddr.sin_port = htons(PORT);
	if (bind(m_nListenFd,(struct sockaddr *)&m_sServerAddr,sizeof(m_sServerAddr))<0) 
		std::cout<<"Socket Failed errno:"<<errno<<std::endl;
}

