#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
using namespace std;


int readSocket(int socket, char *buffer) {
    return recv(socket, buffer, 255, 0);
}

int main()
{
    int clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    char buffer[256];
    struct sockaddr_in addr;
    int response_len;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(2222);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    connect(clientSocket, (struct sockaddr *)&addr, sizeof(addr));

    response_len = readSocket(clientSocket, buffer);
    string response(buffer, response_len);

    cout << response << endl;

    close(clientSocket);
}