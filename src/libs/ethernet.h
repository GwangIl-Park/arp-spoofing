#ifndef _ETHERNET_H
#define _ETHERNET_H

struct EthernetHeader
{
  unsigned char   destinationAddress[6];
  unsigned char   sourceAddress[6];
  unsigned short  type;
};

void setEthernetHeader(
    EthernetHeader *ethernetHeader,
    unsigned char *destinationAddress,
    unsigned char *sourceAddress,
    unsigned short type
);

#endif