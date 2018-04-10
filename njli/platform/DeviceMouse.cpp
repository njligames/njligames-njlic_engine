//
//  DeviceMouse.cpp
//  ios
//
//  Created by James Folk on 5/8/17.
//
//

#include "DeviceMouse.h"

namespace njli
{
  DeviceMouse::DeviceMouse()
      : m_Button(0), m_EventType(0), m_X(0), m_Y(0), m_Clicks(0)
  {
  }

  DeviceMouse::DeviceMouse(const DeviceMouse &copy)
      : m_Button(copy.m_Button), m_EventType(copy.m_EventType), m_X(copy.m_X),
        m_Y(copy.m_Y), m_Clicks(copy.m_Clicks)
  {
  }

  DeviceMouse::~DeviceMouse() {}

  const DeviceMouse &DeviceMouse::operator=(const DeviceMouse &rhs)
  {
    if (this != &rhs)
      {
        m_Button = rhs.m_Button;
        m_EventType = rhs.m_EventType;
        m_X = rhs.m_X;
        m_Y = rhs.m_Y;
        m_Clicks = rhs.m_Clicks;
      }
    return *this;
  }

  void DeviceMouse::set(int button, int eventType, float x, float y, int clicks)
  {
    m_Button = button;
    m_EventType = eventType;
    m_X = x;
    m_Y = y;
    m_Clicks = clicks;
  }
}
