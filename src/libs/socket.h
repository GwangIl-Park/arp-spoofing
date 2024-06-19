#ifndef _SOCKET_H
#define _SOCKET_H

#include <string>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket {
protected:
  int fileDescriptor;
public:
  Socket(int domain, int type, int protocol);
  virtual ~Socket();
  int getFileDescriptor();
  void sendTo(sockaddr* to, unsigned int toLenth, unsigned char *buffer, unsigned int length);
};

void setLowLevelSocketAddress(
    sockaddr_ll *socketAddress,
    unsigned short protocol,
    int fileDescriptor,
    const char *interfaceName,
    unsigned short hardwareType,
    unsigned char packetType,
    const char *address
);
void setInternetSocketAddress(sockaddr_in *socketAddress, const char *address, unsigned short port);

#endif