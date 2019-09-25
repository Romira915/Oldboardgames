#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <WinSock2.h>
#include <Task.h>
#include <string>
#include <mutex>
#include <thread>

class TCP : public Task
{
public:
	TCP();
	virtual ~TCP();
	void Initialize(); 
	void Finalize();  
	void Update();   
	void Draw();   

	void client_connect(const char* ip);
	void client_close();
	std::string client_receive();

private:
	void client_connect_onthread(const char* ip);

	WSADATA wsaData;

	// client•Ï”
	std::thread client_th;
	sockaddr_in server;
	SOCKET server_sock;
	char buf[32];
	// 0 –¢Ú‘±
	// 1 Ú‘±’†
	int serverconnect_status;
	std::mutex mtx_serverconnect_status;

	std::string str_receive;
};

