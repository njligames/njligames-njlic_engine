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

	int DeviceTouch::eventFilter(void *userdata, SDL_Event *event)
    {
        //    dispatch_block_t block = ^{
        //      //            njli::NJLIGameEngine::handleEvent(&event);
        //      //    SDLTest_PrintEvent(event);
        //
        //      Uint32 eventType = event->type;
        //
        //      switch (eventType)
        //        {
        //        case SDL_JOYDEVICEMOTION:
        //          {
        //
        //            NJLI_HandleVRCameraRotationYPR(
        //                static_cast<float>(event->jmotion.yaw),
        //                static_cast<float>(event->jmotion.pitch),
        //                static_cast<float>(event->jmotion.roll));
        //          }
        //          break;
        //        case SDL_FINGERMOTION:
        //        case SDL_FINGERDOWN:
        //        case SDL_FINGERUP:
        //          NJLI_HandleTouch(
        //              (int)event->tfinger.touchId,
        //              (int)event->tfinger.fingerId, event->type,
        //              event->tfinger.x, event->tfinger.y, event->tfinger.dx,
        //              event->tfinger.dy, event->tfinger.pressure);
        //          break;
        //        default:
        //          break;
        //        }
        //      NJLI_HandleFinishTouches();
        //    };
        //
        //    if ([NSThread isMainThread])
        //      {
        //        block();
        //      }
        //    else
        //      {
        //        dispatch_async(dispatch_get_main_queue(), block);
        //      }
        return 0;
    }

    int DeviceTouch::screenPPI()
    {
        //    static const int CONVERSION(
        //        ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) ? 132
        //        : 163));
        //    CGFloat ns = [[UIScreen mainScreen] nativeScale];
        //    return ns * CONVERSION;
        return 1;
    }

    int DeviceTouch::pointToPixel(const int point)
    {
        //    static const int CONVERSION(
        //        ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) ? 132
        //        : 163));
        //    static const int DPI(DeviceTouch::screenPPI());
        //    return static_cast<int>((point * DPI) / CONVERSION);
        return 1;
    }

    int DeviceTouch::pixelToPoint(const int pixel)
    {
        //    static const int CONVERSION(
        //        ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) ? 132
        //        : 163));
        //    static const int DPI(DeviceTouch::screenPPI());
        //    return ((CONVERSION * pixel) / DPI);
        return 1;
    }
    const u8 DeviceTouch::MAX_TOUCHES = 5;

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
}
