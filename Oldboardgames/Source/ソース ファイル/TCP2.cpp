#define _CRT_SECURE_NO_WARNINGS
#include "TCP2.h"
#include "errno.h"
#include "DxLib.h"

TCP2::TCP2()
{
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		//printfDx("WSAStartup failed\n");
	}

	memset(buf, 0, sizeof(buf));
	port = 0;
	server_sock = 0;
	bind_sock = 0;
	len = 0;
	client_sock = 0;

	tv.tv_sec = 0;
	tv.tv_usec = 10000;
	{
		std::lock_guard<std::mutex> lock2(mtx_eTCP_mode);
		eTCP_mode = eNone;
		std::lock_guard<std::mutex> lock(mtx_tcp_status);
		tcp_status = eClosed;
	}
	tcp_th = std::thread(&TCP2::TCP_onthread, this);
}

TCP2::~TCP2()
{
	WSACleanup();
}

void TCP2::Initialize()
{

}

void TCP2::Finalize()
{
	if (Get_TCPstatus() != eFinalize)
	{
		{
			std::lock_guard<std::mutex> lock(mtx_tcp_status);
			tcp_status = eRequestClosing;
		}

		while (true)
		{
			if (Get_TCPstatus() == eClosed)
			{
				std::lock_guard<std::mutex> lock(mtx_tcp_status);
				tcp_status = eFinalize;
				break;
			}
		}
	}

	tcp_th.join();
}

void TCP2::Update()
{
}

void TCP2::Draw()
{
}

void TCP2::Client_connect(const std::string set_ip, const int set_port)
{
	ip = set_ip;
	port = set_port;
	std::lock_guard<std::mutex> lock2(mtx_eTCP_mode);
	eTCP_mode = eClient;
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eRequestConnecting;
}

void TCP2::Server_listen(const int set_port)
{
	port = set_port;
	std::lock_guard<std::mutex> lock2(mtx_eTCP_mode);
	eTCP_mode = eServer;
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	tcp_status = eRequestConnecting;
}

std::string TCP2::Get_message()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	if (tcp_status == eReceived)
	{
		tcp_status = eConnected;
		return message;
	}
	return std::string("no message");
}

eTCPstatus TCP2::Get_TCPstatus()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	return tcp_status;
}

eTCPmode TCP2::Get_TCPmode()
{
	std::lock_guard<std::mutex> lock(mtx_tcp_status);
	return eTCP_mode;
}

void TCP2::Send_message(const std::string send_str)
{
	SOCKET sock = 0;

	{
		std::lock_guard<std::mutex> lock(mtx_eTCP_mode);
		if (eTCP_mode == eClient)
		{
			sock = server_sock;
		}
		else if (eTCP_mode == eServer)
		{
			sock = client_sock;
		}
	}

	{
		std::lock_guard<std::mutex> lock(mtx_tcp_status);
		if (tcp_status == eConnected)
		{
			send(sock, send_str.c_str(), send_str.length(), 0);
		}
	}
}

void TCP2::TCP_onthread()
{
	while (true)
	{
		mtx_tcp_status.lock();
		switch (tcp_status)
		{
		case eRequestConnecting:
		{
			mtx_tcp_status.unlock();
			if (eTCP_mode == eClient)
			{
				{
					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eConnecting;
				}

				unsigned int** addrptr;

				server_sock = socket(AF_INET, SOCK_STREAM, 0);
				if (server_sock == INVALID_SOCKET) {
					//printfDx("socket : %d\n", WSAGetLastError());
					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eError;
					break;
				}

				server.sin_family = AF_INET;
				server.sin_port = htons(port);
				server.sin_addr.S_un.S_addr = inet_addr(ip.c_str());

				FD_ZERO(&readfds);
				FD_SET(server_sock, &readfds);

				if (server.sin_addr.S_un.S_addr == 0xffffffff) {
					struct hostent* host;

					host = gethostbyname(ip.c_str());
					if (host == NULL) {
						if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
							//printfDx("host not found : %s\n", ip);
							std::lock_guard<std::mutex> lock(mtx_tcp_status);
							tcp_status = eError;
							break;
						}
					}

					addrptr = (unsigned int**)host->h_addr_list;

					while (*addrptr != NULL) {
						server.sin_addr.S_un.S_addr = *(*addrptr);

						// connect()が成功したらloopを抜けます
						if (connect(server_sock, (struct sockaddr*) & server, sizeof(server)) == 0) {
							std::lock_guard<std::mutex> lock(mtx_tcp_status);
							tcp_status = eConnected;
						}

						addrptr++;
						// connectが失敗したら次のアドレスで試します
					}

					// connectが全て失敗した場合
					if (*addrptr == NULL) {
						//printfDx("connect : %d\n", WSAGetLastError());
						std::lock_guard<std::mutex> lock(mtx_tcp_status);
						tcp_status = eError;
						break;
					}
				}
				else {
					// inet_addr()が成功したとき

					// connectが失敗したらエラーを表示して終了
					if (connect(server_sock, (struct sockaddr*) & server, sizeof(server)) != 0) {
						//printfDx("connect : %d\n", WSAGetLastError());
						std::lock_guard<std::mutex> lock(mtx_tcp_status);
						tcp_status = eError;
						break;
					}
					else
					{
						//printfDx("on connect\n");
						std::lock_guard<std::mutex> lock(mtx_tcp_status);
						tcp_status = eConnected;
					}
				}
			}
			else if (eTCP_mode == eServer)
			{
				{
					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eConnecting;
				}

				bind_sock = socket(AF_INET, SOCK_STREAM, 0);
				if (bind_sock == INVALID_SOCKET) {
					//printfDx("socket : %d\n", WSAGetLastError());
					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eError;
					break;
				}

				addr.sin_family = AF_INET;
				addr.sin_port = htons(port);
				addr.sin_addr.S_un.S_addr = INADDR_ANY;

				FD_ZERO(&readfds);
				FD_SET(bind_sock, &readfds);

				setsockopt(bind_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));

				if (bind(bind_sock, (struct sockaddr*) & addr, sizeof(addr)) != 0) {
					//printfDx("bind : %d\n", WSAGetLastError());
					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eError;
					break;
				}

				if (listen(bind_sock, 5) != 0)
				{
					//printfDx("listen : %d\n", WSAGetLastError());
					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eError;
					break;
				}

				//printfDx("listenする準備をするよ\n");
				len = sizeof(client);
				while (tcp_status != eRequestClosing)
				{
					//printfDx("accept待ち\n");
					memcpy(&fds, &readfds, sizeof(fd_set));

					select(0, &fds, NULL, NULL, &tv);
					if (FD_ISSET(bind_sock, &fds))
					{
						client_sock = accept(bind_sock, (struct sockaddr*) & client, &len);
						FD_SET(client_sock, &readfds);

						break;
					}
				}
				if (tcp_status == eRequestClosing)
				{
					break;
				}

				{
					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eConnected;
				}
				//printfDx("accept\n");
			}
		}
		break;
		case eConnecting:
			mtx_tcp_status.unlock();
			break;
		case eConnected:
		{
			mtx_tcp_status.unlock();

			memcpy(&fds, &readfds, sizeof(fd_set));

			if (select(0, &fds, NULL, NULL, &tv) > 0)
			{
				//printfDx("select\n");
				SOCKET sock = 0;

				if (eTCP_mode == eClient)
				{
					sock = server_sock;
				}
				else if (eTCP_mode == eServer)
				{
					sock = client_sock;
				}
				memset(buf, 0, sizeof(buf));
				if (FD_ISSET(sock, &fds)) {
					int n = recv(sock, buf, sizeof(buf), 0);

					if (n < 0) {
						//printfDx("recv : %d\n", WSAGetLastError());
						std::lock_guard<std::mutex> lock(mtx_tcp_status);
						tcp_status = eError;
						break;
					}
					else if (n == 0)
					{
						std::lock_guard<std::mutex> lock(mtx_tcp_status);
						tcp_status = eClosed;
						break;
					}

					std::lock_guard<std::mutex> lock(mtx_tcp_status);
					tcp_status = eReceived;
					std::lock_guard<std::mutex> lock2(mtx_message);
					message = std::string(buf);

					//printfDx("%d, %s, eConnected内\n", n, buf);
				}
			}
		}
		break;
		case eRequestClosing:
		{
			mtx_tcp_status.unlock();

			if (server_sock != 0)
			{
				closesocket(server_sock);
			}
			if (client_sock != 0)
			{
				closesocket(client_sock);
			}

			std::lock_guard<std::mutex> lock2(mtx_eTCP_mode);
			eTCP_mode = eNone;
			std::lock_guard<std::mutex> lock(mtx_tcp_status);
			tcp_status = eClosed;
		}
		break;
		case eClosing:
			mtx_tcp_status.unlock();
			break;
		case eClosed:
			mtx_tcp_status.unlock();
			break;
		case eReceiving:
			mtx_tcp_status.unlock();
			break;
		case eReceived:
			mtx_tcp_status.unlock();
			break;
		case eRequestSend:
			mtx_tcp_status.unlock();
			break;
		case eError:
			mtx_tcp_status.unlock();

			if (server_sock != 0)
			{
				closesocket(server_sock);
			}
			if (client_sock != 0)
			{
				closesocket(client_sock);
			}
			{
				std::lock_guard<std::mutex> lock(mtx_tcp_status);
				tcp_status = eFinalize;
			}
			break;
		case eFinalize:
			mtx_tcp_status.unlock();
			return;
			break;
		default:
			mtx_tcp_status.unlock();
			break;
		}
	}
}
