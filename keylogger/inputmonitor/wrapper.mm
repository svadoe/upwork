#include "wrapper.h"

#import "inputmonitor.h"

Wrapper::Wrapper(QObject *parent)
  : QObject(parent)
{
  InputMonitor* monitor_ = [[InputMonitor alloc] init];
  // NSLog(@"", [monitor_ string]);

  // delete monitor_;

}

Wrapper::~Wrapper()
{
  // delete monitor;
}
