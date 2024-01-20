#include <linux/if_arp.h>
#include <thread>

#include "libs/socket.h"
#include "libs/arp_spoof.h"

int main(int argc, char *argv[]) {
  Socket *socketA = new Socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
  ARPSpoof *arpSpoofA = new ARPSpoof(socketA);

  Socket *socketB = new Socket(AF_PACKET, SOCK_RAW, ETH_P_ARP);
  ARPSpoof *arpSpoofB = new ARPSpoof(socketB);

  std::thread threadA(arpSpoofA->spoof, );
  std::thread threadB(arpSpoofB->spoof, );

  threadA.join();
  threadB.join();

  delete socketA;
  delete arpSpoofA;

  delete socketB;
  delete arpSpoofB;

  return 0;
}