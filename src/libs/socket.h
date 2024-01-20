#ifndef _SOCKET_H
#define _SOCKET_H

#include <string>

class Socket
{
  private:
    int fileDescriptor;
  public:
    int getFileDescriptor();
    void openSocket(int domain, int type, int protocol);
    //void bindSocket(const std::string &interface_name);
    void sendTo(sockaddr* to, unsigned char *buffer, unsigned int length);
    void closeSocket();
};

#endif