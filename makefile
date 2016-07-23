OBJS = Channel.o TcpConnection.o Acceptor.o TcpServer.o
HDRS = IChannelCallBack.h IAcceptorCallBack.h

server : $(OBJS) $(HDRS)
	g++ -g $(OBJS) Main.cpp  -o server

.PHONY : clean  

clean :
	rm server $(OBJS) 


