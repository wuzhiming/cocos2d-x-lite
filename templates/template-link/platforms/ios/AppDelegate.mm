/****************************************************************************
 Copyright (c) 2010-2013 cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "AppDelegate.h"
#import "ViewController.h"
#include "platform/ios/View.h"
#include "cocos/bindings/event/EventDispatcher.h"

#include "Game.h"

cc::Device::Rotation _lastLocation;

@implementation AppDelegate

Game* game = nullptr;
@synthesize window;

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Add the view controller's view to the window and display.
    CGRect bounds = [[UIScreen mainScreen] bounds];
    self.window = [[UIWindow alloc] initWithFrame: bounds];

    // Should create view controller first, cc::Application will use it.
    _viewController = [[ViewController alloc]init];
    _viewController.view = [[View alloc] initWithFrame:bounds];
    _viewController.view.contentScaleFactor = UIScreen.mainScreen.scale;
    [self.window setRootViewController:_viewController];

    // cocos2d application instance
    game = new Game(bounds.size.width, bounds.size.height);
    game->init();

    [[NSNotificationCenter defaultCenter] addObserver:self
        selector:@selector(orientationChanged:)name:UIDeviceOrientationDidChangeNotification object:nil];

    [self.window makeKeyAndVisible];

    return YES;
}


- (void) orientationChanged:(NSNotification *)note {
    cc::Device::Rotation rotation = cc::Device::Rotation::_0;
    UIDevice * device = note.object;

    switch (device.orientation)
    {
        case UIDeviceOrientationPortrait:
            rotation = cc::Device::Rotation::_0;
            break;
        case UIDeviceOrientationLandscapeRight:
            rotation = cc::Device::Rotation::_90;
            break;
        case UIDeviceOrientationPortraitUpsideDown:
            rotation = cc::Device::Rotation::_180;
            break;
        case UIDeviceOrientationLandscapeLeft:
            rotation = cc::Device::Rotation::_270;
            break;
        default:
            break;
    };
    if (_lastLocation != rotation) {
        cc::EventDispatcher::dispatchOrientationChangeEvent((int) rotation);
        _lastLocation = rotation;
    }
}

- (void)applicationWillResignActive:(UIApplication *)application {
    game->onPause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    game->onResume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
}

- (void)applicationWillTerminate:(UIApplication *)application {
    delete game;
    game = nullptr;
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    cc::EventDispatcher::dispatchMemoryWarningEvent();
}

@end
