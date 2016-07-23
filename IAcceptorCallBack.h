#ifndef IACCEPTORCALLBACK_H
#define IACCEPTORCALLBACK_H

namespace TinyMuduo
{
	
class IAcceptorCallBack
{
public:
	virtual void NewConnection(int connfd)=0;
};

}

#endif
