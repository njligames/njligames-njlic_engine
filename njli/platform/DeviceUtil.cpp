//
//  DeviceUtil.cpp
//  macOS
//
//  Created by James Folk on 4/29/17.
//
//

#include "DeviceUtil.h"

#include <sys/types.h>

#if defined(__ANDROID__) || defined(__EMSCRIPTEN__) || defined(__linux__)
#include <sys/utsname.h>
#else
#include <sys/sysctl.h>
#endif

std::string DeviceUtil::hardwareString()
{
#if defined(__ANDROID__) || defined(__EMSCRIPTEN__) || defined(__linux__)

  std::string hardware;

  struct utsname buffer;

  // int errno = 0;
  if (uname(&buffer) != 0)
    {
      perror("uname");
    }

  printf("system name = %s\n", buffer.sysname);
  printf("node name   = %s\n", buffer.nodename);
  printf("release     = %s\n", buffer.release);
  printf("version     = %s\n", buffer.version);
  printf("machine     = %s\n", buffer.machine);

  hardware = std::string(buffer.sysname);
  hardware += "_";
  hardware += buffer.machine;

  return hardware;

#else
  int name[] = {CTL_HW, HW_MACHINE};
  size_t size = 100;
  sysctl(name, 2, NULL, &size, NULL, 0); // getting size of answer
  //    char *hw_machine = (char *)malloc(size);
  char *hw_machine = new char[size];

  sysctl(name, 2, hw_machine, &size, NULL, 0);
  std::string hardware(hw_machine);
  //    free(hw_machine);
  delete[] hw_machine;

  return hardware;
#endif
}

std::string DeviceUtil::hardwareDescription()
{
  std::string hardware = DeviceUtil::hardwareString();

  if (hardware == std::string("iPhone1,1"))
    return "iPhone 2G";
  if (hardware == std::string("iPhone1,2"))
    return "iPhone 3G";
  if (hardware == std::string("iPhone2,1"))
    return "iPhone 3GS";
  if (hardware == std::string("iPhone3,1"))
    return "iPhone 4 (GSM)";
  if (hardware == std::string("iPhone3,2"))
    return "iPhone 4 (GSM Rev. A)";
  if (hardware == std::string("iPhone3,3"))
    return "iPhone 4 (CDMA)";
  if (hardware == std::string("iPhone4,1"))
    return "iPhone 4S";
  if (hardware == std::string("iPhone5,1"))
    return "iPhone 5 (GSM)";
  if (hardware == std::string("iPhone5,2"))
    return "iPhone 5 (Global)";
  if (hardware == std::string("iPhone5,3"))
    return "iPhone 5C (GSM)";
  if (hardware == std::string("iPhone5,4"))
    return "iPhone 5C (Global)";
  if (hardware == std::string("iPhone6,1"))
    return "iPhone 5s (GSM)";
  if (hardware == std::string("iPhone6,2"))
    return "iPhone 5s (Global)";

  if (hardware == std::string("iPhone7,1"))
    return "iPhone 6 Plus";
  if (hardware == std::string("iPhone7,2"))
    return "iPhone 6";

  if (hardware == std::string("iPod1,1"))
    return "iPod Touch (1 Gen)";
  if (hardware == std::string("iPod2,1"))
    return "iPod Touch (2 Gen)";
  if (hardware == std::string("iPod3,1"))
    return "iPod Touch (3 Gen)";
  if (hardware == std::string("iPod4,1"))
    return "iPod Touch (4 Gen)";
  if (hardware == std::string("iPod5,1"))
    return "iPod Touch (5 Gen)";

  if (hardware == std::string("iPad1,1"))
    return "iPad (WiFi)";
  if (hardware == std::string("iPad1,2"))
    return "iPad 3G";
  if (hardware == std::string("iPad2,1"))
    return "iPad 2 (WiFi)";
  if (hardware == std::string("iPad2,2"))
    return "iPad 2 (GSM)";
  if (hardware == std::string("iPad2,3"))
    return "iPad 2 (CDMA)";
  if (hardware == std::string("iPad2,4"))
    return "iPad 2 (WiFi Rev. A)";
  if (hardware == std::string("iPad2,5"))
    return "iPad Mini (WiFi)";
  if (hardware == std::string("iPad2,6"))
    return "iPad Mini (GSM)";
  if (hardware == std::string("iPad2,7"))
    return "iPad Mini (CDMA)";
  if (hardware == std::string("iPad3,1"))
    return "iPad 3 (WiFi)";
  if (hardware == std::string("iPad3,2"))
    return "iPad 3 (CDMA)";
  if (hardware == std::string("iPad3,3"))
    return "iPad 3 (Global)";
  if (hardware == std::string("iPad3,4"))
    return "iPad 4 (WiFi)";
  if (hardware == std::string("iPad3,5"))
    return "iPad 4 (CDMA)";
  if (hardware == std::string("iPad3,6"))
    return "iPad 4 (Global)";
  if (hardware == std::string("iPad4,1"))
    return "iPad Air (WiFi)";
  if (hardware == std::string("iPad4,2"))
    return "iPad Air (WiFi+GSM)";
  if (hardware == std::string("iPad4,3"))
    return "iPad Air (WiFi+CDMA)";
  if (hardware == std::string("iPad4,4"))
    return "iPad Mini Retina (WiFi)";
  if (hardware == std::string("iPad4,5"))
    return "iPad Mini Retina (WiFi+CDMA)";
  if (hardware == std::string("iPad4,6"))
    return "iPad Mini Retina (Wi-Fi + Cellular CN)";
  if (hardware == std::string("iPad4,7"))
    return "iPad Mini 3 (Wi-Fi)";
  if (hardware == std::string("iPad4,8"))
    return "iPad Mini 3 (Wi-Fi + Cellular)";
  if (hardware == std::string("iPad5,3"))
    return "iPad Air 2 (Wi-Fi)";
  if (hardware == std::string("iPad5,4"))
    return "iPad Air 2 (Wi-Fi + Cellular)";

  if (hardware == std::string("i386"))
    return "i386";
  if (hardware == std::string("x86_64"))
    return "x86_64";

  std::string foo("iPhone");
  std::string foobar(hardware);
  auto res = std::mismatch(foo.begin(), foo.end(), foobar.begin());
  if (res.first == foo.end())
    {
      // foo is a prefix of foobar.
      return "iPhone";
    }

  foo = std::string("iPod");
  foobar = std::string(hardware);
  res = std::mismatch(foo.begin(), foo.end(), foobar.begin());
  if (res.first == foo.end())
    {
      // foo is a prefix of foobar.
      return "iPod";
    }

  foo = std::string("iPad");
  foobar = std::string(hardware);
  res = std::mismatch(foo.begin(), foo.end(), foobar.begin());
  if (res.first == foo.end())
    {
      // foo is a prefix of foobar.
      return "iPad";
    }

  return "";
}

DeviceUtil::HardwareId DeviceUtil::hardwareId() { return NOT_AVAILABLE; }
