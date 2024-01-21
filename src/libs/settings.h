#ifndef _SETTINGS_H
#define _SETTINGS_H

#include <string>

struct Settings {
  std::string interfaceName;
  std::string targetIPAddressA;
  std::string targetIPAddressB;
};

void setSettings(const std::string& filename);
Settings getSettings();

#endif