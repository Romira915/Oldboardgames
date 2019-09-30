#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <WinSock2.h>
#include <Task.h>
#include <string>
#include <mutex>
#include <thread>
#include <vector>

class TCP : public Task
{
public:
	TCP();
	virtual ~TCP();
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void Client_connect(const char* ip);
	void Client_close();
	void Client_receive();

	void Server_listen();
	void Server_close();
	void Server_receive();

	std::string Get_message_string();
	eTCPstatus Get_TCPstatus();
	void Clear_TCPstatus();

private:
	void Client_connect_onthread(const char* ip);
	void Client_receive_onthread();

	void Server_listen_onthread();
	void Server_receive_onthread();

	WSADATA wsaData;
	std::vector<std::thread> th;
	char buf[32];
	std::mutex mtx_tcp_status;
	std::string str_receive;
	std::mutex mtx_str_receive;

	// clientïœêî
	sockaddr_in server;
	SOCKET server_sock;
	eTCPstatus tcp_status;

	// serverïœêî
	SOCKET bind_sock;
	sockaddr_in addr;
	sockaddr_in client;
	int len;
	SOCKET client_sock;
	BOOL yes = 1;
};

