#ifndef ICHANNELCALLBACK_H
#define ICHANNELCALLBACK_H

namespace TinyMuduo
{

class IChannelCallBack
{
public:
	virtual void HandleEvent()=0;
};

}

#endif
