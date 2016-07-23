#ifndef NOCOPYABLE_H
#define NOCOPYABLE_H

namespace TinyMuduo
{

class NoCopyAble{
public:
	NoCopyAble(){};
	~NoCopyAble(){};
private:
	NoCopyAble& operator=(const NoCopyAble& obj){};
	NoCopyAble(const NoCopyAble& obj){};
};

}

#endif
