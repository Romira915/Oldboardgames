#include "TCP.h"
#include <cstdio>
#include <DxLib.h>

TCP::TCP()
{
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		printfDx("WSAStartup failed\n");
	}

	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eClosed;
}

TCP::~TCP()
{
	WSACleanup();
}

void TCP::Initialize()
{
}

void TCP::Finalize()
{
	for (std::thread& th : th) {
		th.join();
	}
	th.clear();
}

void TCP::Update()
{
}

void TCP::Draw()
{

}

void TCP::Client_connect(const char* ip)
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eConnecting;
	th.push_back(std::thread(&TCP::Client_connect_onthread, this, ip));
}

void TCP::Client_close()
{
	closesocket(server_sock);
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eClosed;
}

void TCP::Client_receive()
{
	if (tcp_status == eConnected)
	{
		std::lock_guard<std::mutex> lock(mtx_tcp_status);
		tcp_status = eReceiving;
		th.push_back(std::thread(&TCP::Client_receive_onthread, this));
	}
}

void TCP::Server_listen()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eConnecting;
	th.push_back(std::thread(&TCP::Server_listen_onthread, this));
}

void TCP::Server_close()
{
	closesocket(client_sock);
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eClosed;
}

void TCP::Server_receive()
{
}

std::string TCP::Get_message_string()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eConnected;
	std::lock_guard<std::mutex> lock2(mtx_str_receive);
	return str_receive;
}

eTCPstatus TCP::Get_TCPstatus()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	return tcp_status;
}

void TCP::Clear_TCPstatus()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eNone;
}

void TCP::Client_connect_onthread(const char* ip)
{
	unsigned int** addrptr;
	
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == INVALID_SOCKET) {
		printfDx("socket : %d\n", WSAGetLastError());
		return;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(59150);
	server.sin_addr.S_un.S_addr = inet_addr(ip);

	if (server.sin_addr.S_un.S_addr == 0xffffffff) {
		struct hostent* host;

		host = gethostbyname(ip);
		if (host == NULL) {
			if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
				printfDx("host not found : %s\n", ip);
				return;
			}
		}

		addrptr = (unsigned int**)host->h_addr_list;

		while (*addrptr != NULL) {
			server.sin_addr.S_un.S_addr = *(*addrptr);

			// connect()が成功したらloopを抜けます
			if (connect(server_sock, (struct sockaddr*) & server, sizeof(server)) == 0) {
				break;
			}

			addrptr++;
			// connectが失敗したら次のアドレスで試します
		}

		// connectが全て失敗した場合
		if (*addrptr == NULL) {
			printfDx("connect : %d\n", WSAGetLastError());
			return;
		}
	}
	else {
		// inet_addr()が成功したとき

		// connectが失敗したらエラーを表示して終了
		if (connect(server_sock, (struct sockaddr*) & server, sizeof(server)) != 0) {
			printfDx("connect : %d\n", WSAGetLastError());
			return;
		}
		else
		{
			printfDx("on connect");
			mtx_tcp_status.lock();
			tcp_status = eConnected;
			mtx_tcp_status.unlock();

			TCP::Client_receive_onthread();
		}
	}

	return;
}

void TCP::Client_receive_onthread()
{
	memset(buf, 0, sizeof(buf));
	int n = recv(server_sock, buf, sizeof(buf), 0);
	if (n < 0) {
		printfDx("recv : %d\n", WSAGetLastError());
		return;
	}

	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eReceived;
	std::lock_guard<std::mutex> lock2(mtx_str_receive);
	str_receive = std::string(buf);

	printfDx("%d, %s\n", n, buf);
}

void TCP::Server_listen_onthread()
{
	bind_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (bind_sock == INVALID_SOCKET) {
		printfDx("socket : %d\n", WSAGetLastError());
		return;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(59150);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	setsockopt(bind_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)& yes, sizeof(yes));

	bind(bind_sock, (struct sockaddr*) & addr, sizeof(addr));

	listen(bind_sock, 5);

	len = sizeof(client);
	client_sock = accept(bind_sock, (struct sockaddr*)& client, &len);
	mtx_tcp_status.lock();
	tcp_status = eConnected;
	mtx_tcp_status.unlock();
	printfDx("accept");

	send(client_sock, "p2p", 3, 0);
}

void TCP::Server_receive_onthread()
{
}
