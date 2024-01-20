#include "socket.h"

#include <iostream>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/if_packet.h>
#include <linux/if_arp.h>
#include <cstring>
#include <netinet/in.h>

Socket::Socket() {}

int Socket::getFileDescriptor()
{
  return this->fileDescriptor;
}

void Socket::openSocket(int domain, int type, int protocol)
{
  this->fileDescriptor = socket(domain, type, htons(protocol));
  if(this->fileDescriptor < 0) {
    std::cerr << "open_socket: Fail to open socket.\n";
    exit(EXIT_FAILURE);
  }
}

// void Socket::bindSocket(const std::string &interface_name)
// {
//   struct ifreq ifr;

//   strcpy(ifr.ifr_name, interface_name.c_str());

//   if (ioctl(this->fileDescriptor, SIOCGIFINDEX, &ifr) == -1) {
//       std::cerr << "bind_socket: Failed to get interface index.\n";
//       exit(EXIT_FAILURE);
//   }

//   struct sockaddr_ll socketAddr;
//   memset(&socketAddr, 0, sizeof(sockaddr_ll));
//   socketAddr.sll_family = AF_PACKET;
//   socketAddr.sll_ifindex = ifr.ifr_ifindex;
//   if(bind(this->fileDescriptor, (struct sockaddr*)&sockaddr, sizeof(sockaddr_ll)))
// }

void Socket::sendTo(sockaddr *to, unsigned char *buffer, unsigned int length)
{
  if(sendto(this->fileDescriptor, buffer, length, 0, to, sizeof(sockaddr)) == -1) {
    std::cerr << "sendTo: Fail to sendTo.\n";
  }
}

void Socket::closeSocket()
{
  close(this->fileDescriptor);
}