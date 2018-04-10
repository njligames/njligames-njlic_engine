//
//  DeviceKey.h
//  macOS
//
//  Created by James Folk on 1/6/18.
//

#ifndef DeviceKey_h
#define DeviceKey_h

#include "DeviceInputTime.h"
//#include "JLIFactoryTypes.h"
#include "Game.h"
#include "btVector2.h"
#include <string>

namespace njli
{
  class DeviceKey : public DeviceInputTime
  {
  public:
    DeviceKey() : m_ScanCode(0), m_ScanCodeName("NOT SET") {}

    DeviceKey(const DeviceKey &rhs)
        : m_ScanCode(rhs.m_ScanCode), m_ScanCodeName(rhs.m_ScanCodeName)
    {
    }

    DeviceKey &operator=(const DeviceKey &rhs)
    {
      if (this != &rhs)
        {
          m_ScanCode = rhs.m_ScanCode;
          m_ScanCodeName = rhs.m_ScanCodeName;
        }
      return *this;
    }

    DeviceKey(int scanCode, const std::string &scanCodeName)
    {
      set(scanCode, scanCodeName);
    }

    virtual ~DeviceKey() {}

    virtual const char *getClassName() const { return "DeviceKey"; }
    virtual s32 getType() const { return 0; }
    operator std::string() const
    {
      char buffer[1024];

      sprintf(buffer, "\n\
                    Scan Code [%d]\n\
                    Scan Code Name [%s]\n",
              m_ScanCode, m_ScanCodeName.c_str());

      return std::string(buffer);
    }

    void set(int scanCode, const std::string &scanCodeName)
    {
      m_ScanCode = scanCode;
      m_ScanCodeName = scanCodeName;
    }

    int getScanCode() const { return m_ScanCode; }
    std::string getScanCodeName() const { return m_ScanCodeName; }

  private:
    int m_ScanCode;
    std::string m_ScanCodeName;
  };
}

#endif /* DeviceKey_h */
