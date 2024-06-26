#include <arpa/inet.h>
#include <netinet/ip_icmp.h>

#include "icmp.h"

void setEchoRequest(
    EchoRequest     *echoRequest
) {
  echoRequest->type = ICMP_ECHO;
  echoRequest->code = 0;
  echoRequest->checksum = 0;
  echoRequest->id = htons(getpid());
  echoRequest->seq = htons(1);
  echoRequest->checksum = makeEchoRequestChecksum((unsigned char *)echoRequest);
}

uint32_t makeEchoRequestChecksum(unsigned char *data) {
  uint16_t *data16 = (uint16_t *)data;
  uint32_t sum = 0;
  int length = sizeof(EchoRequest);

  for (sum = 0; length > 1; length -= 2)
      sum += *data16++;
  if (length == 1)
      sum += *(unsigned char *)data16;

  sum = (sum >> 16) + (sum & 0xffff);
  sum += (sum >> 16);
  return ~sum;
}