#include <linux/if_arp.h>
#include <netinet/ip_icmp.h>
#include <thread>
#include <cstring>
#include <arpa/inet.h>

#include "libs/socket.h"
#include "libs/arp_spoof.h"
#include "libs/ping.h"

int main(int argc, char *argv[]) {
  Socket *socketForPing = new Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  sockaddr_in dest_addr;
  memset(&dest_addr, 0, sizeof(dest_addr));
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_addr.s_addr = inet_addr("192.168.56.1");
  ping(socketForPing, (sockaddr*)&dest_addr);


  // Socket *socketA = new Socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
  // ARPSpoof *arpSpoofA = new ARPSpoof(socketA);

  // Socket *socketB = new Socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
  // ARPSpoof *arpSpoofB = new ARPSpoof(socketB);

  // std::thread threadA(arpSpoofA->spoof, );
  // std::thread threadB(arpSpoofB->spoof, );

  // threadA.join();
  // threadB.join();

  // delete socketA;
  // delete arpSpoofA;

  // delete socketB;
  // delete arpSpoofB;

  return 0;
}