#include "arp_table.h"
#include "types.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

strToStrUMap setARPTableFromARPFile() {
  strToStrUMap arpTable;
  std::ifstream arpFile("/proc/net/arp");
  if (arpFile.is_open()) {
    std::string line;
    while (getline(arpFile, line)) {
      std::istringstream iss(line);
      std::string ipAddress, hwType, flags, hwAddress, mask, device;

      iss >> ipAddress >> hwType >> flags >> hwAddress >> mask >> device;

      arpTable.insert(std::pair<std::string, std::string>(ipAddress, hwAddress));
    }

    arpFile.close();

    return arpTable;
  } else {
    std::cerr << "Failed to open /proc/net/arp" << std::endl;
  }
}

std::string getMacAddressByIPFromARPTable(std::string macAddress) {
  strToStrUMap arpTable = setARPTableFromARPFile();
  auto it = arpTable.find(macAddress);
  if(it==arpTable.end()) return "";
  else return it->second;
}