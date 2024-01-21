#ifndef _ARP_H
#define _ARP_H

const int ETHERNET_TYPE = 1;

const int ARP_REQUEST = 1;

struct ARPHeader {
  unsigned short  hardwareType;
  unsigned short  protocolType;
  unsigned char   hardwareLength;
  unsigned char   protocolLength;
  unsigned short  operation;
  unsigned char   senderHardwareAddress[6];
  unsigned char   senderProtocolAddress[4];
  unsigned char   targetHardwareAddress[6];
  unsigned char   targetProtocolAddress[4];
};

void setARPHeader(
    ARPHeader *arpHeader,
    int hardwareType,
    int protocolType,
    int hardwareLength,
    int protocolLength,
    int operation,
    unsigned char *senderHardwareAddress,
    unsigned char *senderProtocolAddress,
    unsigned char *targetHardwareAddress,
    unsigned char *targetProtocolAddress
);

#endif