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
        [NSTimer scheduledTimerWithTimeInterval:0.3 repeats:YES block:^(NSTimer * _Nonnull timer) {
            NSPoint mouseLocation = [NSEvent mouseLocation];
            mouseLocation.y = NSHeight(NSScreen.mainScreen.frame) - mouseLocation.y;

            NSLog(@"Mouse Location: %@", NSStringFromPoint(mouseLocation));

            AXUIElementRef systemWideElement = SystemWideElement();
            AXUIElementRef elementUnderMouse = NULL;
            AXError error = AXUIElementCopyElementAtPosition(systemWideElement, mouseLocation.x, mouseLocation.y, &elementUnderMouse);

            if (error == kAXErrorSuccess && elementUnderMouse) {
                CFTypeRef role;
                AXError roleError = AXUIElementCopyAttributeValue(elementUnderMouse, kAXRoleAttribute, &role);

                if (roleError == kAXErrorSuccess && role) {
                    NSLog(@"Element under cursor: %@", role);

                    // Check if the element is a text area
                    if (CFStringCompare(role, kAXTextAreaRole, 0) == kCFCompareEqualTo) {
                        CFTypeRef value;
                        AXError valueError = AXUIElementCopyAttributeValue(elementUnderMouse, kAXValueAttribute, &value);

                        if (valueError == kAXErrorSuccess && value) {
                            NSString *content = (__bridge NSString *)value;
                            NSLog(@"Content of AXTextArea (%lu bytes):\n\e[7m'%@'\e[0m\n", (unsigned long)[content lengthOfBytesUsingEncoding:NSUTF8StringEncoding], content);
                            CFRelease(value);
                        } else {
                            NSLog(@"Unable to get content of AXTextArea");
                        }
                    }

                    CFRelease(role);
                } else {
                    NSLog(@"Unable to determine element under cursor");
                }
                CFRelease(elementUnderMouse);
            }
        }];

        [[NSRunLoop currentRunLoop] run];
    }
    return 0;
}
