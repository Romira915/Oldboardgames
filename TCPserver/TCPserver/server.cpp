#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <winsock2.h>
#include <cstring>
#include <iostream>

int main()
{
	WSADATA wsaData;
	SOCKET sock0;
	struct sockaddr_in addr;
	struct sockaddr_in client1, client2;
	int len1, len2;
	SOCKET sock1, sock2;
	BOOL yes = 1;
	char buf[32];

	WSAStartup(MAKEWORD(2, 0), &wsaData);

	sock0 = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(59150);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;

	setsockopt(sock0, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));

	bind(sock0, (struct sockaddr*) & addr, sizeof(addr));

	listen(sock0, 5);

	while (1) {
		len1 = sizeof(client1);
		sock1 = accept(sock0, (struct sockaddr*) & client1, &len1);

		len2 = sizeof(client2);
		sock2 = accept(sock0, (struct sockaddr*) & client2, &len2);
		std::string client1_ip = std::string("ip") + std::string(inet_ntoa(client1.sin_addr));

		send(sock1, "server", 6, 0);
		memset(buf, 0, sizeof(buf));
		recv(sock1, buf, sizeof(buf), 0);
		if (std::string(buf) == "on server")
		{
			send(sock2, client1_ip.c_str(), client1_ip.length(), 0);
		}
		else
		{
			send(sock2, "disconnect", 10, 0);
		}

		closesocket(sock1);
		closesocket(sock2);
	}

	closesocket(sock0);

	WSACleanup();

	return 0;
}