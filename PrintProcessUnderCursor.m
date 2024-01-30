// compile with `clang -fobjc-arc -framework Cocoa PrintProcessUnderCursor.m` (install commandline developer tools with `xcode-select --install` first)
// and execute with `./a.out`
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <ApplicationServices/ApplicationServices.h>

AXUIElementRef SystemWideElement() {
    static AXUIElementRef systemWideElement = NULL;
    if (!systemWideElement) {
        systemWideElement = AXUIElementCreateSystemWide();
    }
    return systemWideElement;
}

int main() {
    @autoreleasepool {
        [NSTimer scheduledTimerWithTimeInterval:0.5 repeats:YES block:^(NSTimer * _Nonnull timer) {
            NSPoint mouseLocation = [NSEvent mouseLocation];
            mouseLocation.y = NSHeight(NSScreen.mainScreen.frame) - mouseLocation.y;

            NSLog(@"Mouse Location: %@", NSStringFromPoint(mouseLocation));

            AXUIElementRef systemWideElement = SystemWideElement();
            AXUIElementRef elementUnderMouse = NULL;
            AXError error = AXUIElementCopyElementAtPosition(systemWideElement, mouseLocation.x, mouseLocation.y, &elementUnderMouse);

            if (error == kAXErrorSuccess && elementUnderMouse) {
                CFTypeRef appRef = NULL;
                AXError appError = AXUIElementCopyAttributeValue(elementUnderMouse, kAXParentAttribute, &appRef);

                if (appError == kAXErrorSuccess && appRef) {
                    pid_t pid;
                    AXUIElementGetPid((AXUIElementRef)appRef, &pid);
                    NSRunningApplication *app = [NSRunningApplication runningApplicationWithProcessIdentifier:pid];
                    if (app) {
                        NSLog(@"App under cursor: %@ (PID: %d)", app.localizedName, pid);
                    }
                    CFRelease(appRef);
                }
                CFRelease(elementUnderMouse);
            }
        }];

        [[NSRunLoop currentRunLoop] run];
    }
    return 0;
}
