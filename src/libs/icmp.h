#ifndef _ICMP_H
#define _ICMP_H

#include <unistd.h>

struct ICMPHeader {
  unsigned char   type;
  unsigned char   code;
  unsigned short  checksum;
};

struct EchoRequest : public ICMPHeader {
  unsigned short  id;
  unsigned short  seq;
};

void setEchoRequest(EchoRequest *echoRequest);

uint32_t makeEchoRequestChecksum(unsigned char *data);

#endif