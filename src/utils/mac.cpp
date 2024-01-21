#include <net/if.h>
#include <string>
#include <cstring>
#include <sys/ioctl.h>
#include <iostream>

#include "mac.h"
#include "types.h"

void getMyMacAddress(unsigned char *buffer, const char *interfaceName) {
  int socketFd = socket(AF_INET, SOCK_DGRAM, 0);
  if(socketFd == -1) {
    exit(EXIT_FAILURE);
  }

  struct ifreq ifr;
  std::strcpy(ifr.ifr_name, interfaceName);

  if(ioctl(socketFd, SIOCGIFHWADDR, &ifr) == -1) {
    exit(EXIT_FAILURE);
  }

  memcpy(buffer, ifr.ifr_hwaddr.sa_data, MAC_LENGTH);
}

void macAddressToByte(unsigned char *buffer, const char *macAddress) {
  uint32_t int_buffer[MAC_LENGTH];
  sscanf(macAddress, "%02X:%02X:%02X:%02X:%02X:%02X",
    &int_buffer[0], &int_buffer[1], &int_buffer[2],
    &int_buffer[3], &int_buffer[4], &int_buffer[5]);
  
  for (int i = 0; i < MAC_LENGTH; i++) {
    buffer[i] = int_buffer[i];
  }
}

int getInterfaceIndex(int fileDescriptor, const char *interfaceName) {
  struct ifreq ifr;
  strcpy(ifr.ifr_name, interfaceName);
  if (ioctl(fileDescriptor, SIOCGIFINDEX, &ifr) == -1) {
    std::cerr << "get_interface_index: Failed to get interface index.\n";
    exit(EXIT_FAILURE);
  }
  return ifr.ifr_ifindex;
}