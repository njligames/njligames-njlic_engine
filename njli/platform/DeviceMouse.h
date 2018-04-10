//
//  DeviceMouse.hpp
//  ios
//
//  Created by James Folk on 5/8/17.
//
//

#ifndef DeviceMouse_hpp
#define DeviceMouse_hpp

#include "DeviceInputTime.h"
#include "btVector2.h"

namespace njli
{
  class DeviceMouse : public DeviceInputTime
  {
  public:
    DeviceMouse();
    DeviceMouse(const DeviceMouse &copy);
    virtual ~DeviceMouse();

    const DeviceMouse &operator=(const DeviceMouse &rhs);

    void set(int button, int eventType, float x, float y, int clicks);

    virtual s32 getType() const { return 1; }

    btVector2 getPosition() const { return btVector2(m_X, m_Y); }

  private:
    int m_Button;
    int m_EventType;
    float m_X;
    float m_Y;
    int m_Clicks;
  };
}

#endif /* DeviceMouse_hpp */
