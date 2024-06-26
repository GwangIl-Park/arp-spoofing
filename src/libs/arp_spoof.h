#ifndef _ARP_SPOOF_H
#define _ARP_SPOOF_H

#include <sys/socket.h>

#include "socket.h"
#include "ethernet.h"
#include "arp.h"
#include "../utils/types.h"

const int BUFFER_SIZE = sizeof(EthernetHeader) + sizeof(ARPHeader);

class ARPSpoof {
private:
  Socket *socket;

  unsigned char buffer[BUFFER_SIZE];

  unsigned char targetMacAddress[MAC_LENGTH];
  unsigned char targetIPAddress[IPV4_LENGTH];

  unsigned char destinationIPAddress[IPV4_LENGTH];
public:
  ARPSpoof(Socket *socket, unsigned char *targetMacAddress, unsigned char *targetIPAddress, unsigned char *destinationIPAddress);
  virtual ~ARPSpoof();
  void makeSpoofData();
  void spoof(sockaddr_ll *to, int duration);
};

#endif