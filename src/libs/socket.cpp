#include "socket.h"

#include <iostream>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if_packet.h>
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

void Socket::sendTo(sockaddr *to, unsigned char *buffer, unsigned int length) {
  if(sendto(this->fileDescriptor, buffer, length, 0, to, sizeof(sockaddr)) == -1) {
    std::cerr << "sendTo: Fail to sendTo.\n";
  }
}