#ifndef _TCP_SOCKET_H
#define _TCP_SOCKET_H

#include "socket.h"

class TCPSocket : public Socket {
public:
  TCPSocket() : Socket(AF_INET, SOCK_STREAM, 0){}
  virtual ~TCPSocket();
  bool bind();
  bool send();
};

#endif