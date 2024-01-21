#ifndef _PING_H
#define _PING_H

#include <sys/socket.h>
#include "socket.h"

void ping(Socket *socket, sockaddr_in *to);

#endif