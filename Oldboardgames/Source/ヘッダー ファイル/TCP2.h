#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <WinSock2.h>
#include <Task.h>
#include <string>
#include <mutex>
#include <thread>
#include <vector>

class TCP2 : public Task
{
public:
	TCP2();
	~TCP2();
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void Client_connect(const std::string set_ip, const int set_port = 59150);
	void Server_listen(const int set_port = 59150);
	std::string Get_message();
	eTCPstatus Get_TCPstatus();

private:
	void TCP_onthread();

	std::thread tcp_th;

	WSADATA wsaData;
	char buf[32];
	eTCPstatus tcp_status;
	std::mutex mtx_tcp_status;
	std::string message;
	std::mutex mtx_message;
	eTCPmode eTCP_mode;

	std::string ip;
	int port;

	fd_set fds, readfds;
	timeval tv;

	// clientïœêî
	sockaddr_in server;
	SOCKET server_sock;

	// serverïœêî
	SOCKET bind_sock;
	sockaddr_in addr;
	sockaddr_in client;
	int len;
	SOCKET client_sock;
	BOOL yes = 1;
};
