#include <arpa/inet.h>
#include <cstring>

#include "arp.h"
#include "../utils/types.h"

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
  ) {
  arpHeader->hardwareType = htons(hardwareType);
  arpHeader->protocolType = htons(protocolType);
  arpHeader->hardwareLength = hardwareLength;
  arpHeader->protocolLength = protocolLength;
  arpHeader->operation = htons(operation);
  memcpy(arpHeader->senderHardwareAddress, senderHardwareAddress, MAC_LENGTH);
  memcpy(arpHeader->senderProtocolAddress, senderProtocolAddress, IPV4_LENGTH);
  memcpy(arpHeader->targetHardwareAddress, targetHardwareAddress, MAC_LENGTH);
  memcpy(arpHeader->targetProtocolAddress, targetProtocolAddress, IPV4_LENGTH);
}