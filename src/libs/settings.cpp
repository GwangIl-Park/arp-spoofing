#include "settings.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

Settings settings;

void setSettings(const std::string& filename) {
  std::ifstream file(filename);
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      if (!line.empty() && line[0] != '#') {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
          if (key == "interface_name") {
            settings.interfaceName = value;
          } else if (key == "target1_ip") {
            settings.targetIPAddressA = value;
          } else if (key == "target2_ip") {
            settings.targetIPAddressB = value;
          }
        }
      }
    }
    file.close();
  } else {
    std::cerr << "Error opening file: " << filename << std::endl;
  }
}

Settings getSettings() {
  return settings;
}