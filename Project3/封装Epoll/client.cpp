#include <iostream>
#include "tcpsocket.hpp"

int main()
{
    TcpSocket sock;
    sock.createSocket();
    sock.connectSocket("127.0.0.1",1244);

    while(1) {
        string buf;
        cout<<"client say:";
        getline(cin,buf);
        sock.sendInfo(buf);

        buf.clear();
        sock.receiveInfo(buf);
        cout<<"server say:"<<buf<<endl;
    }
    sock.closeSocket();
    return 0;
}
