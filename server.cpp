#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <thread>
#include <string>
using namespace std;


const char CODE_AUTH = '1';


void writeSocket(int socket, const string& message) {
    send(socket, message.data(), message.size(), 0);
}

string createMessage(char code, const string & message) {
    string strCode(&code, 1);
    return strCode + ":" + message;
}

void workWithClient(int socket) {
    string message = createMessage(CODE_AUTH, "Enter your login:");
    writeSocket(socket, message);
}


int main() {
    int serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int socket;

    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(2222);

    bind(serverSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(serverSocket, 1);

    while (true) {
        socket = accept(serverSocket, nullptr, nullptr);
        thread (workWithClient, socket).detach();
    }
}
