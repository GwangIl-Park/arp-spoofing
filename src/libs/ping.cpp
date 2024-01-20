#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>

#include "ping.h"
#include "icmp.h"
#include "socket.h"

void ping(Socket *socket, sockaddr *to) {
  EchoRequest echoRequest;
  setEchoRequest(&echoRequest);

  socket->sendTo(to, (unsigned char*)&echoRequest, sizeof(EchoRequest));
}