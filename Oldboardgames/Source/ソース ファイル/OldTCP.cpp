#include "OldTCP.h"
#include <cstdio>
#include <DxLib.h>

OldTCP::OldTCP()
{
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		printfDx("WSAStartup failed\n");
	}

	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eClosed;
}

OldTCP::~OldTCP()
{
	WSACleanup();
}

void OldTCP::Initialize()
{
}

void OldTCP::Finalize()
{
	for (std::thread& th : th) {
		th.join();
	}
	th.clear();
}

void OldTCP::Update()
{
}

void OldTCP::Draw()
{

}

void OldTCP::Client_connect(const char* ip, const int port)
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eConnecting;
	th.push_back(std::thread(&OldTCP::Client_connect_onthread, this, ip, port));
}

void OldTCP::Client_close()
{
	closesocket(server_sock);
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eClosed;
}

void OldTCP::Client_receive()
{
	if (tcp_status == eConnected)
	{
		std::lock_guard<std::mutex> lock(mtx_tcp_status);
		tcp_status = eReceiving;
		th.push_back(std::thread(&OldTCP::Client_receive_onthread, this));
	}
}

void OldTCP::Client_send(const char* message)
{
	if (tcp_status == eConnected)
	{
		th.push_back(std::thread(&OldTCP::Client_send_onthread, this, message));
	}
}

void OldTCP::Server_listen(const int port)
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eConnecting;
	th.push_back(std::thread(&OldTCP::Server_listen_onthread, this, port));
}

void OldTCP::Server_close()
{
	closesocket(client_sock);
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eClosed;
}

void OldTCP::Server_receive()
{
	if (tcp_status == eConnected)
	{
		std::lock_guard<std::mutex> lock(mtx_tcp_status);
		tcp_status = eReceiving;
		th.push_back(std::thread(&OldTCP::Server_receive_onthread, this));
	}
}

void OldTCP::Server_send(const char* message)
{
	if (tcp_status == eConnected)
	{
		th.push_back(std::thread(&OldTCP::Server_send_onthread, this, message));
	}
}

std::string OldTCP::Get_message_string()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eConnected;
	std::lock_guard<std::mutex> lock2(mtx_str_receive);
	return str_receive;
}

eTCPstatus OldTCP::Get_TCPstatus()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	return tcp_status;
}

void OldTCP::Clear_TCPstatus()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eFinalize;
}

void OldTCP::Client_connect_onthread(const char* ip, const int port)
{
	printfDx("connectするよ\n");
	unsigned int** addrptr;

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == INVALID_SOCKET) {
		printfDx("socket : %d\n", WSAGetLastError());
		return;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
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

		printfDx("connectするよ２\n");
		// connectが失敗したらエラーを表示して終了
		if (connect(server_sock, (struct sockaddr*) & server, sizeof(server)) != 0) {
			printfDx("connect : %d\n", WSAGetLastError());
			return;
		}
		else
		{
			printfDx("on connect\n");
			mtx_tcp_status.lock();
			tcp_status = eConnected;
			mtx_tcp_status.unlock();

			OldTCP::Client_receive_onthread();
		}
	}

	return;
}

void OldTCP::Client_receive_onthread()
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

void OldTCP::Client_send_onthread(const char* message)
{
	send(server_sock, message, strlen(message), 0);
}

void OldTCP::Server_listen_onthread(const int port)
{
	bind_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (bind_sock == INVALID_SOCKET) {
		printfDx("socket : %d\n", WSAGetLastError());
		return;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	setsockopt(bind_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)& yes, sizeof(yes));

	bind(bind_sock, (struct sockaddr*) & addr, sizeof(addr));

	listen(bind_sock, 5);

	printfDx("listenする準備をするよ\n");
	len = sizeof(client);
	client_sock = accept(bind_sock, (struct sockaddr*) & client, &len);
	mtx_tcp_status.lock();
	tcp_status = eConnected;
	mtx_tcp_status.unlock();
	printfDx("accept\n");

	send(client_sock, "p2p", 3, 0);
	printfDx("send\n");

	mtx_tcp_status.lock();
	tcp_status = eReceiving;
	mtx_tcp_status.unlock();
	OldTCP::Server_receive_onthread();
}

void OldTCP::Server_receive_onthread()
{
	memset(buf, 0, sizeof(buf));
	int n = recv(client_sock, buf, sizeof(buf), 0);
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

void OldTCP::Server_send_onthread(const char* message)
{
	send(server_sock, message, strlen(message), 0);
}
