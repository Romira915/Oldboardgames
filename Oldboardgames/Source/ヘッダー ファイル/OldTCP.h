#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <WinSock2.h>
#include <Task.h>
#include <string>
#include <mutex>
#include <thread>
#include <vector>

class OldTCP : public Task
{
public:
	OldTCP();
	virtual ~OldTCP();
	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void Client_connect(const char* ip, const int port = 59150);
	void Client_close();
	void Client_receive();
	void Client_send(const char* message);

	void Server_listen(const int port = 59150);
	void Server_close();
	void Server_receive();
	void Server_send(const char* message);

	std::string Get_message_string();
	eTCPstatus Get_TCPstatus();
	void Clear_TCPstatus();

private:
	void Client_connect_onthread(const char* ip, const int port);
	void Client_receive_onthread();
	void Client_send_onthread(const char* message);

	void Server_listen_onthread(const int port);
	void Server_receive_onthread();
	void Server_send_onthread(const char* message);

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

