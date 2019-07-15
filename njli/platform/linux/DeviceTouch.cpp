//
//  DeviceTouch.mm
//  JLIGameEngineTest
//
//  Created by James Folk on 12/8/14.
//  Copyright (c) 2014 James Folk. All rights reserved.
//

#include "DeviceTouch.h"
// #include <UIKit/UIKit.h>
#include "JLIFactoryTypes.h"
#include "World.h"

namespace njli {
const u8 DeviceTouch::MAX_TOUCHES = 5;

int DeviceTouch::eventFilter(void *userdata, SDL_Event *event)
{
    return 0;
}


void DeviceTouch::convert(DeviceTouch& t, const void* _touch)
{
    if (_touch) {
        // UITouch *touch = (__bridge UITouch*)_touch;
        // CGFloat scaleFactor = touch.view.contentScaleFactor;
        // t.setTimeStampFrame(touch.timestamp);
        // CGPoint p = [touch locationInView:touch.view];
        // m_xpos = (p.x * scaleFactor);
        // m_ypos = njli::World::getInstance()->getViewportDimensions().y() - (p.y * scaleFactor);
        // p = [touch previousLocationInView:touch.view];
        // m_prev_xpos = (p.x * scaleFactor);
        // m_prev_ypos = njli::World::getInstance()->getViewportDimensions().y() - (p.y * scaleFactor);
        // t.m_address = [touch hash];
        // t.m_tapCount = [touch tapCount];
    }
}

int DeviceTouch::screenPPI()
{
//   static const int CONVERSION(
//       ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) ? 132 : 163));
//   CGFloat ns = [[UIScreen mainScreen] nativeScale];
//   return ns * CONVERSION;
    return 1;
}

int DeviceTouch::pointToPixel(const int point)
{
//   static const int CONVERSION(
//       ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) ? 132 : 163));
//   static const int DPI(DeviceTouch::screenPPI());
//   return static_cast<int>((point * DPI) / CONVERSION);
    return point;
}

int DeviceTouch::pixelToPoint(const int pixel)
{
//   static const int CONVERSION(
//       ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) ? 132 : 163));
//   static const int DPI(DeviceTouch::screenPPI());
//   return ((CONVERSION * pixel) / DPI);
    return pixel;
}

}

