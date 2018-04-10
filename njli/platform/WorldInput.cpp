//
//  WorldInput.cpp
//  JLIGameEngineTest
//
//  Created by James Folk on 1/30/15.
//  Copyright (c) 2015 James Folk. All rights reserved.
//

#include "WorldInput.h"
#include "DeviceTouch.h"
#include "JLIFactoryTypes.h"
#include "World.h"
//#import <UIKit/UIKit.h>
//#import "GameViewController.h"

#define FORMATSTRING "{\"njli::WorldInput\":[]}"
#include "JsonJLI.h"
#include "btPrint.h"

namespace njli
{
  WorldInput::WorldInput()
      : m_Mouse(new njli::DeviceMouse()),
        m_TouchBuffer(
            new njli::DeviceTouch *[njli::DeviceTouch::MAX_TOUCHES * 3]),
        m_Orientation(0)

  {
  }

  WorldInput::~WorldInput()
  {
    delete m_Mouse;

    delete[] m_TouchBuffer;

    for (std::unordered_map<int, DeviceTouch *>::iterator iter =
             m_FingerDownMap.begin();
         iter != m_FingerDownMap.end(); iter++)
      {
        DeviceTouch *touch = iter->second;
        delete touch;
      }

    for (std::unordered_map<int, DeviceTouch *>::iterator iter =
             m_FingerUpMap.begin();
         iter != m_FingerUpMap.end(); iter++)
      {
        DeviceTouch *touch = iter->second;
        delete touch;
      }

    for (std::unordered_map<int, DeviceTouch *>::iterator iter =
             m_FingerMoveMap.begin();
         iter != m_FingerMoveMap.end(); iter++)
      {
        DeviceTouch *touch = iter->second;
        delete touch;
      }
  }

  const char *WorldInput::getClassName() const { return "WorldInput"; }

  s32 WorldInput::getType() const { return JLI_OBJECT_TYPE_WorldInput; }

  WorldInput::operator std::string() const
  {
    return njli::JsonJLI::parse(string_format("%s", FORMATSTRING));
  }

  void WorldInput::handleFinger(int touchDevId, int pointerFingerId, int action,
                                float x, float y, float dx, float dy,
                                float pressure)
  {
    SDL_assertCheck(
        action >= 0 && action <= 2, "%s",
        "Make sure that the action value is either down=0, up=1, move=2");

    DeviceTouch *touch = NULL;

    switch (action)
      {
      case 0:
        {
          std::unordered_map<int, DeviceTouch *>::iterator iter =
              m_FingerDownMap.find(pointerFingerId);
          if (iter == m_FingerDownMap.end())
            {
              touch = new DeviceTouch();
            }
          else
            {
              touch = m_FingerDownMap[pointerFingerId];
            }

          touch->set(touchDevId, pointerFingerId, SDL_FINGERDOWN, x, y, dx, dy,
                     pressure);

          njli::World::getInstance()->touchDown(*touch);
        }
        break;
      case 1:
        {
          std::unordered_map<int, DeviceTouch *>::iterator iter =
              m_FingerUpMap.find(pointerFingerId);
          if (iter == m_FingerUpMap.end())
            {
              touch = new DeviceTouch();
            }
          else
            {
              touch = m_FingerUpMap[pointerFingerId];
            }

          touch->set(touchDevId, pointerFingerId, SDL_FINGERUP, x, y, dx, dy,
                     pressure);

          njli::World::getInstance()->touchUp(*touch);
        }
        break;
      case 2:
        {
          std::unordered_map<int, DeviceTouch *>::iterator iter =
              m_FingerMoveMap.find(pointerFingerId);
          if (iter == m_FingerMoveMap.end())
            {
              touch = new DeviceTouch();
            }
          else
            {
              touch = m_FingerMoveMap[pointerFingerId];
            }

          touch->set(touchDevId, pointerFingerId, SDL_FINGERMOTION, x, y, dx,
                     dy, pressure);

          njli::World::getInstance()->touchMove(*touch);
        }
        break;
      default:
        return;
      }
  }

  void WorldInput::handleFingers()
  {

    if (!m_FingerDownMap.empty())
      {
        int i = 0;
        for (i = 0; i < njli::DeviceTouch::MAX_TOUCHES * 3; i++)
          {
            m_TouchBuffer[i] = NULL;
          }
        i = 0;
        for (std::unordered_map<int, DeviceTouch *>::iterator iter =
                 m_FingerDownMap.begin();
             iter != m_FingerDownMap.end(); iter++)
          {
            m_TouchBuffer[i++] = iter->second;
          }
        njli::World::getInstance()->touchDown(m_TouchBuffer);
        m_FingerDownMap.clear();
      }

    if (!m_FingerUpMap.empty())
      {
        int i = 0;
        for (i = 0; i < njli::DeviceTouch::MAX_TOUCHES * 3; i++)
          {
            m_TouchBuffer[i] = NULL;
          }
        i = 0;
        for (std::unordered_map<int, DeviceTouch *>::iterator iter =
                 m_FingerUpMap.begin();
             iter != m_FingerUpMap.end(); iter++)
          {
            m_TouchBuffer[i++] = iter->second;
          }
        njli::World::getInstance()->touchDown(m_TouchBuffer);
        m_FingerUpMap.clear();
      }

    if (!m_FingerMoveMap.empty())
      {
        int i = 0;
        for (i = 0; i < njli::DeviceTouch::MAX_TOUCHES * 3; i++)
          {
            m_TouchBuffer[i] = NULL;
          }
        i = 0;
        for (std::unordered_map<int, DeviceTouch *>::iterator iter =
                 m_FingerMoveMap.begin();
             iter != m_FingerMoveMap.end(); iter++)
          {
            m_TouchBuffer[i++] = iter->second;
          }
        njli::World::getInstance()->touchDown(m_TouchBuffer);
        m_FingerMoveMap.clear();
      }
  }

  void WorldInput::handleMouse(int button, int eventType, float x, float y,
                               int clicks)
  {
    m_Mouse->set(button, eventType, x, y, clicks);
    switch (eventType)
      {
      case SDL_MOUSEMOTION:
        njli::World::getInstance()->mouseMove(*m_Mouse);
        break;
      case SDL_MOUSEBUTTONDOWN:
        njli::World::getInstance()->mouseDown(*m_Mouse);
        break;
      case SDL_MOUSEBUTTONUP:
        njli::World::getInstance()->mouseUp(*m_Mouse);
        break;
      default:
        break;
      }
  }

  void WorldInput::handleKeyUp(const char *keycodeName, bool withCapsLock,
                               bool withControl, bool withShift, bool withAlt,
                               bool withGui)
  {
    njli::World::getInstance()->keyUp(keycodeName, withCapsLock, withControl,
                                      withShift, withAlt, withGui);
  }

  void WorldInput::handleKeyDown(const char *keycodeName, bool withCapsLock,
                                 bool withControl, bool withShift, bool withAlt,
                                 bool withGui)
  {
    njli::World::getInstance()->keyDown(keycodeName, withCapsLock, withControl,
                                        withShift, withAlt, withGui);
  }

  void WorldInput::keyboardShow()
  {
    njli::World::getInstance()->keyboardShow();
  }

  void WorldInput::keyboardCancel()
  {
    njli::World::getInstance()->keyboardCancel();
  }

  void WorldInput::keyboardReturn(const char *text)
  {
    njli::World::getInstance()->keyboardReturn(text);
  }

  void WorldInput::setOrientation(const s32 orientation)
  {
    m_Orientation = orientation;
  }

  bool WorldInput::isPortraitOrientation() const
  {
    //        return (((UIInterfaceOrientation)m_Orientation ==
    //        UIInterfaceOrientationPortrait) ||
    //        ((UIInterfaceOrientation)m_Orientation ==
    //        UIInterfaceOrientationPortraitUpsideDown));
    return false;
  }

  bool WorldInput::isLandscapeOrientation() const
  {
    //        return (((UIInterfaceOrientation)m_Orientation ==
    //        UIInterfaceOrientationLandscapeLeft) ||
    //        ((UIInterfaceOrientation)m_Orientation ==
    //        UIInterfaceOrientationLandscapeRight));
    return false;
  }

  s32 WorldInput::getOrientation() const { return m_Orientation; }

  void WorldInput::showKeyboard(const char *currentText)
  {
    //        id<UIApplicationDelegate> appDelegate = [[UIApplication
    //        sharedApplication] delegate];
    //        GameViewController *viewController =
    //        (GameViewController*)appDelegate.window.rootViewController;
    //        [viewController showKeyboard:[NSString
    //        stringWithCString:currentText encoding:NSUTF8StringEncoding]];
  }
}
