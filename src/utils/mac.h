#ifndef _MAC_H
#define _MAC_H

void getMyMacAddress(unsigned char *buffer, const char *interfaceName);
void macAddressToByte(unsigned char *buffer, const char *macAddress);
int getInterfaceIndex(int fileDescriptor, const char *interfaceName);

#endif