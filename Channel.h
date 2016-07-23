#ifndef CHANNEL_H
#define CHANNEL_H


namespace TinyMuduo
{

class IChannelCallBack; 

class Channel
{
public:
	Channel(int epfd,int fd):m_nEpollFd(epfd),m_nFd(fd){};
	~Channel();
	void SetCallBack(IChannelCallBack* cb);
	void EableReading();
	void HandleEvent();
	void SetRevent(int revent);

private:
	void Update();
	int m_nEpollFd;
	int m_nFd;
	int m_nEvents;
	int m_nRevents;
	IChannelCallBack* m_pIChannelCallBack;
};

}

#endif
