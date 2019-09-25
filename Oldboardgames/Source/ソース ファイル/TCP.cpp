#include "TCP.h"
#include <cstdio>
#include <DxLib.h>

TCP::TCP()
{
	serverconnecting = false;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
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
	if (serverconnecting)
	{
		memset(buf, 0, sizeof(buf));
		int n = recv(server_sock, buf, sizeof(buf), 0);
		if (n < 1) {
			if (WSAGetLastError() == WSAEWOULDBLOCK) {
				//�܂����Ȃ��B
				printfDx("MADA KONAI\n");
			}
			else {
				//printfDx("error : 0x%x\n", WSAGetLastError());
			}
		}
		else {
			printfDx("received data\n");
			printfDx("%s\n", buf);
		}

		// �ǂݍ��ݗpfd_set�̏�����
		// select��������e���㏑�����Ă��܂��̂ŁA���񏉊������܂�
		memcpy(&fds, &readfds, sizeof(fd_set));

		// fds�ɐݒ肳�ꂽ�\�P�b�g���ǂݍ��݉\�ɂȂ�܂ő҂��܂�
		select(0, &fds, NULL, NULL, &tv);

		// sock1�ɓǂݍ��݉\�f�[�^������ꍇ
		if (FD_ISSET(server_sock, &fds)) {
			// sock1����f�[�^����M���ĕ\�����܂�
			memset(buf, 0, sizeof(buf));
			//recv(server_sock, buf, sizeof(buf), 0);
			printfDx("%s\n", buf);
			serverconnecting = true;
		}
		else
		{
			printfDx("nodate");
		}
	}


}

void TCP::Draw()
{

}

int TCP::client_init()
{
	if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
		printfDx("WSAStartup failed\n");
	}
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock == INVALID_SOCKET) {
		printfDx("socket : %d\n", WSAGetLastError());
		return -1;
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(59150);

	// fd_set�̏��������܂�
	FD_ZERO(&readfds);
	FD_SET(server_sock, &readfds);

	// �m���u���b�L���O���[�h
	u_long val = 1;
	ioctlsocket(server_sock, FIONBIO, &val);

	return 0;
}

int TCP::client_connect(const char* ip)
{
	unsigned int** addrptr;

	server.sin_addr.S_un.S_addr = inet_addr(ip);
	if (server.sin_addr.S_un.S_addr == 0xffffffff) {
		struct hostent* host;

		host = gethostbyname(ip);
		if (host == NULL) {
			if (WSAGetLastError() == WSAHOST_NOT_FOUND) {
				printfDx("host not found : %s\n", ip);
				return -1;
			}
		}

		addrptr = (unsigned int**)host->h_addr_list;

		while (*addrptr != NULL) {
			server.sin_addr.S_un.S_addr = *(*addrptr);

			// connect()������������loop�𔲂��܂�
			if (connect(server_sock, (struct sockaddr*) & server, sizeof(server)) == 0) {
				break;
			}

			addrptr++;
			// connect�����s�����玟�̃A�h���X�Ŏ����܂�
		}

		// connect���S�Ď��s�����ꍇ
		if (*addrptr == NULL) {
			printfDx("connect : %d\n", WSAGetLastError());
			return -1;
		}
	}
	else {
		// inet_addr()�����������Ƃ�

		// connect�����s������G���[��\�����ďI��
		if (connect(server_sock, (struct sockaddr*) & server, sizeof(server)) != 0) {
			printfDx("connect : %d\n", WSAGetLastError());
			serverconnecting = true;
			return -1;
		}
		else
		{
		}
	}

	return 0;
}

void TCP::client_close()
{
	closesocket(server_sock);
	serverconnecting = false;
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
