#ifndef _ARP_SPOOF_H
#define _ARP_SPOOF_H

#include <sys/socket.h>

#include "socket.h"
#include "../utils/types.h"

const int BUFFER_SIZE = sizeof(EthernetHeader) + sizeof(ARPHeader);

class ARPSpoof
{
private:
  Socket *socket;

  unsigned char buffer[BUFFER_SIZE];

  unsigned char targetMacAddress[MAC_LENGTH];
  unsigned char targetIPAddress[IPV4_LENGTH];

  unsigned char destinationIPAddress[IPV4_LENGTH];
public:
  ARPSpoof(Socket *socket);
  virtual ~ARPSpoof();
  void makeSpoofData();
  void spoof(sockaddr *to);
};

#endif