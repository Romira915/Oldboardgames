#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <cstring>

int main()
{
    int sock0;
    struct sockaddr_in addr;
    struct sockaddr_in client1, client2;
    socklen_t len1, len2;
    int sock1, sock2;
    int yes = 1;

    if ((sock0 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(59150);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock0, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return -1;
    }

    if (listen(sock0, SOMAXCONN) < 0)
    {
        perror("listen");
        return -1;
    }

    setsockopt(sock0, SOL_SOCKET, SO_REUSEADDR, (const char *)&yes, sizeof(yes));

    std::string client1_ip;

    while (1)
    {
        // len1 = sizeof(client1);
        // sock1 = accept(sock0, (struct sockaddr *)&client1, &len1);

        // len2 = sizeof(client2);
        // sock2 = accept(sock0, (struct sockaddr *)&client2, &len2);

        while (true)
        {
            if (write(sock1, "server", 6) < 0)
            {
                len1 = sizeof(client1);
                sock1 = accept(sock0, (struct sockaddr *)&client1, &len1);
                client1_ip = std::string("ip") + std::string(inet_ntoa(client1.sin_addr));
            }
            else
            {
                break;
            }
        }

        while (true)
        {
            if (write(sock2, client1_ip.c_str(), client1_ip.length()) < 0)
            {
                len2 = sizeof(client2);
                sock2 = accept(sock0, (struct sockaddr *)&client2, &len2);
            }
            else
            {
                break;
            }
        }

        close(sock1);
        close(sock2);
    }

    close(sock0);

    return 0;
}