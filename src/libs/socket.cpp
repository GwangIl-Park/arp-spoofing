#include "socket.h"
#include "../utils/types.h"
#include "../utils/mac.h"

#include <iostream>
#include <sys/ioctl.h>
#include <linux/if_arp.h>
#include <cstring>
#include <netinet/in.h>

Socket::Socket(int domain, int type, int protocol) {
  this->fileDescriptor = socket(domain, type, protocol);
  if(this->fileDescriptor == -1) {
    std::cerr << "open_socket: Fail to open socket.\n";
    exit(EXIT_FAILURE);
  }
}

Socket::~Socket() {
  close(this->fileDescriptor);
}

int Socket::getFileDescriptor() {
  return this->fileDescriptor;
}

void Socket::sendTo(sockaddr *to, unsigned int toLength, unsigned char *buffer, unsigned int length) {
  if(sendto(this->fileDescriptor, buffer, length, 0, to, toLength) == -1) {
    std::cerr << "sendTo: Fail to sendTo.\n";
  }
}

void setLowLevelSocketAddress(
    sockaddr_ll *socketAddress,
    unsigned short protocol,
    int fileDescriptor,
    const char *interfaceName,
    unsigned short hardwareType,
    unsigned char packetType,
    const char *address
) {
  memset(socketAddress, 0, sizeof(sockaddr_ll));
  socketAddress->sll_family = AF_PACKET;
  socketAddress->sll_protocol = protocol;
  socketAddress->sll_ifindex = getInterfaceIndex(fileDescriptor, interfaceName);
  socketAddress->sll_hatype = hardwareType;
  socketAddress->sll_pkttype = packetType;
  socketAddress->sll_halen = MAC_LENGTH;
  macAddressToByte(socketAddress->sll_addr, address);
}

void setInternetSocketAddress(sockaddr_in *socketAddress, const char *address, unsigned short port) {
  memset(socketAddress, 0, sizeof(sockaddr_in));
  socketAddress->sin_family = AF_INET;
  socketAddress->sin_addr.s_addr = inet_addr(address);
  socketAddress->sin_port = port;
}