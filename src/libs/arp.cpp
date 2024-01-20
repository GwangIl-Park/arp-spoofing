#include <arpa/inet.h>
#include <cstring>

#include "arp.h"

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
  )
{
  arpHeader->hardwareType = htons(hardwareType);
  arpHeader->protocolType = htons(protocolType);
  arpHeader->hardwareLength = hardwareLength;
  arpHeader->protocolLength = protocolLength;
  arpHeader->operation = operation;
  memcpy(arpHeader->senderHardwareAddress, senderHardwareAddress, sizeof(uint32_t));
  memcpy(arpHeader->senderProtocolAddress, senderProtocolAddress, sizeof(uint32_t));
  memcpy(arpHeader->targetHardwareAddress, targetHardwareAddress, sizeof(uint32_t));
  memcpy(arpHeader->targetProtocolAddress, targetProtocolAddress, sizeof(uint32_t));
}