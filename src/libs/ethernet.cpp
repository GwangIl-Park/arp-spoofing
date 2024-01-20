#include <cstring>
#include <arpa/inet.h>

#include "ethernet.h"

void setEthernetHeader(
    EthernetHeader *ethernetHeader,
    unsigned char *destinationAddress,
    unsigned char *sourceAddress,
    unsigned short type
    )
{
  memcpy(ethernetHeader->destinationAddress, destinationAddress, sizeof(char)*6);
  memcpy(ethernetHeader->sourceAddress, sourceAddress, sizeof(char)*6);
  ethernetHeader->type = htons(type);
}