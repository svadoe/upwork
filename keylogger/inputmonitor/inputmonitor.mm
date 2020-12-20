#import "AppKit/AppKit.h"
#import "inputmonitor.h"
#import "server.h"

@interface InputMonitor()
  @property (nonatomic, readonly) Server* internal;
@end


@implementation InputMonitor

- (instancetype) initWithString:(NSString*) string
{
  self = [super init];

  if (self != nil)
  {
    _internal = new Server();




  }

  return self;
}

- (instancetype) init
{
  NSLog(@"Initializing..");
  self = [super init];

 [NSEvent addGlobalMonitorForEventsMatchingMask:NSLeftMouseDownMask handler:^(NSEvent *evt) {
    CGPoint cglocation = [NSEvent mouseLocation];
    NSInteger windowNumber = [NSWindow windowNumberAtPoint:cglocation belowWindowWithWindowNumber:0];

    CGWindowID windowID = (CGWindowID)windowNumber;

    CFArrayRef array = CFArrayCreate(NULL, (const void **)&windowID, 1, NULL);
    NSArray *windowInfos = (NSArray *)CGWindowListCreateDescriptionFromArray(array);
    CFRelease(array);

    if (windowInfos.count > 0) {
        NSDictionary *windowInfo = [windowInfos objectAtIndex:0];
    }
    [windowInfos release];
    NSLog(@"mouse down");
  }];



  return self;
}

#pragma mark -
#pragma mark Self

- (NSString*) string
{
  const char* string = "A String";
  return string ? @(string):nil;
}

#pragma mark -
#pragma mark Cleanup

@end
