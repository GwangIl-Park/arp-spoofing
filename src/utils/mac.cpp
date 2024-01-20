#include <net/if.h>
#include <string>
#include <cstring>
#include <sys/ioctl.h>

#include "mac.h"
#include "types.h"

unsigned char* getMyMacAddress(char *interfaceName) {
  int socketFd = socket(AF_INET, SOCK_DGRAM, 0);
  if(socketFd == -1) {
    exit(EXIT_FAILURE);
  }

  struct ifreq ifr;
  std::strcpy(ifr.ifr_name, interfaceName);

  if(ioctl(socketFd, SIOCGIFHWADDR, &ifr) == -1) {
    exit(EXIT_FAILURE);
  }

  unsigned char buffer[MAC_LENGTH];
  memcpy(buffer, ifr.ifr_hwaddr.sa_data, MAC_LENGTH);
  return buffer;
}