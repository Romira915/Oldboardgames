#include "TCP.h"
#include <cstdio>
#include <DxLib.h>

TCP::TCP()
{
	serverconnect_status = false;
}

TCP::~TCP()
{
}

void TCP::Initialize()
{
}

void TCP::Finalize()
{
}

void TCP::Update()
{
}

void TCP::Draw()
{

}

void TCP::client_connect(const char* ip)
{
	client_th = std::thread(&TCP::client_connect_onthread, this, ip);
}

void TCP::client_close()
{
	closesocket(server_sock);
	serverconnect_status = false;
	WSACleanup();
}

std::string TCP::client_receive()
{
	memset(buf, 0, sizeof(buf));
	int n = recv(server_sock, buf, sizeof(buf), 0);
	if (n < 0) {
		printfDx("recv : %d\n", WSAGetLastError());
		return std::string("error");
	}

	printfDx("%d, %s\n", n, buf);
	return std::string("recv");
}

void TCP::client_connect_onthread(const char* ip)
{
	unsigned int** addrptr;

	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		printfDx("WSAStartup failed\n");
	}
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
			std::lock_guard<std::mutex> lock(mtx_serverconnect_status);
			serverconnect_status = 1;
		}
	}

	return;
}
