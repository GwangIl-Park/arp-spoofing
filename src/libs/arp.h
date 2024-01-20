#ifndef _ARP_H
#define _ARP_H

struct ARPHeader {
  unsigned short  hardwareType;
  unsigned short  protocolType;
  unsigned char   hardwareLength;
  unsigned char   protocolLength;
  unsigned short  operation;
  unsigned char   senderHardwareAddress[4];
  unsigned char   senderProtocolAddress[4];
  unsigned char   targetHardwareAddress[4];
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