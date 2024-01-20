#ifndef _SOCKET_H
#define _SOCKET_H

#include <string>
#include <sys/socket.h>

class Socket {
private:
  int fileDescriptor;
public:
  Socket(int domain, int type, int protocol);
  virtual ~Socket();
  int getFileDescriptor();
  void sendTo(sockaddr* to, unsigned char *buffer, unsigned int length);
};

#endif