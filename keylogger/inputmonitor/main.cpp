// #include <QCoreApplication>
#include <QApplication>

#include "wrapper.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  Wrapper wrapper;

  return a.exec();
}

