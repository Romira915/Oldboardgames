#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <WinSock2.h>
#include <Task.h>
#include <string>

class TCP : public Task
{
public:
	TCP();
	virtual ~TCP();
	void Initialize(); 
	void Finalize();  
	void Update();   
	void Draw();   

	int client_init();
	int client_connect(const char* ip);
	void client_close();
	std::string client_receive();

private:
	WSADATA wsaData;

	// clientïœêî
	sockaddr_in server;
	SOCKET server_sock;
	char buf[32];
	bool serverconnecting;
	timeval tv;
	fd_set fds, readfds;

	std::string str_receive;
};

