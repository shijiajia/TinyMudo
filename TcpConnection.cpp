#include "TcpConnection.h"

#include <iostream>
#include <string>
#include <unistd.h>

using namespace TinyMuduo;

TcpConnection::TcpConnection(int _epollfd,int _sockfd):m_nEpollFd(_epollfd),m_nConnFd(_sockfd)
{
	m_pChannel=new Channel(m_nEpollFd,m_nConnFd);
	m_pChannel->SetCallBack(this);
	m_pChannel->EableReading();
}

