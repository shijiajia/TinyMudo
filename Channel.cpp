#include "Channel.h"
#include <iostream>

#include <sys/epoll.h>
#include "IChannelCallBack.h"

using namespace std;
using namespace TinyMuduo;

void Channel::SetCallBack(IChannelCallBack *cb)
{
	m_pIChannelCallBack=cb;
}

void Channel::EableReading()
{
	m_nEvents |= EPOLLIN;
	Update();
}

void Channel::HandleEvent()
{
	if (m_nRevents & EPOLLIN)
	{
		m_pIChannelCallBack->HandleEvent();
	}
}

void Channel::SetRevent(int revent)
{
	m_nRevents=revent;
}

void Channel::Update()
{
	struct epoll_event ev;
	ev.events=m_nEvents;
	ev.data.ptr=this;
	epoll_ctl(m_nEpollFd,EPOLL_CTL_ADD,m_nFd,&ev);
}

