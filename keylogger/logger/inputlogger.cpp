#include <QtNetwork>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include <QStandardPaths>
#include <QTextStream>
#include <QDateTime>
#include <QLocalSocket>

#include "inputlogger.h"
// #include "usagedata6model.h"
 
InputLogger::InputLogger(QString server_name, QObject *parent)
  // :QObject(parent)
  // ,server_name_(server_name)
  :Client(server_name,parent) 
{
  socket_ = new QLocalSocket(this);
  logfilelocation = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

  in_.setDevice(socket_);
  in_.setVersion(QDataStream::Qt_5_10);

  connect_to_server();
  connect(socket_, &QLocalSocket::readyRead, this, &InputLogger::read_input);
  connect(this, &InputLogger::input_read, this, &InputLogger::format_data);
  // connect(socket_, &QLocalSocket::disconnected, this, &InputLogger::connect_to_server);
  connect(socket_, &QLocalSocket::errorOccurred, this, &InputLogger::display_error);

  QTimer* timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &InputLogger::connect_to_server);
  // connect(timer, &QTimer::timeout, this, &InputLogger::connect_to_server);
  // connect(this, &InputLogger::input_read, this, &InputLogger::format_data);
  timer->start(1000);
/*  */
  QTimer* file_save_timer = new QTimer(this);
  connect(file_save_timer, &QTimer::timeout, this, &InputLogger::save_to_database);
  file_save_timer->start(5000);
}


void InputLogger::save_to_database()
{
  QDateTime datetime{QDateTime::currentDateTimeUtc()};
  
  QString data; 
  data_to_json(data);
  usagedata6_.insert_data(datetime, data);

  buttonclicks_.clear();
  keystrokes_.clear();
  mousemovement_.clear();
}

void InputLogger::data_to_json(QString& data)
{
  data.append("{\"activityPerSecond\":{");

  int size;

  buttonclicks_.prepend("\"buttonClicks\":[");
  size = buttonclicks_.size();
  buttonclicks_.remove(size-1, 1); //removes the last ,
  buttonclicks_.append("]");

  keystrokes_.prepend("\"keystrokes\":[");
  size = keystrokes_.size();
  keystrokes_.remove(size-1, 1); //removes the last ,
  keystrokes_.append("]");

  mousemovement_.prepend("\"mouseMovement\":[");
  size = mousemovement_.size();
  mousemovement_.remove(size-1, 1); //removes the last ,
  mousemovement_.append("]");

  data.append(buttonclicks_);
  data.append(",");
  data.append(keystrokes_);
  data.append(",");
  data.append(mousemovement_);

  data.append("}");
}


void InputLogger::format_data()
{
  
  // qDebug() << "input: " << input_;
  int mouseclick_count_next = input_.split(" ")[0].toInt();
  int icurrentMouseClicks = currentMouseClicks.toInt();

  if (mouseclick_count_next == icurrentMouseClicks) {
    mouseclick_count_next = 0;
  } else {
    mouseclick_count_next = mouseclick_count_next - icurrentMouseClicks;
  }

  int key_count_next = input_.split(" ")[1].toInt();
  int icurrentKeyCount = currentKeyCount.toInt();

  if (key_count_next == icurrentKeyCount) {
      key_count_next = 0;
  } else {
      key_count_next = key_count_next - icurrentKeyCount;
  }

  
  int mouse_movement_count_next = input_.split(" ")[2].toInt();
  int icurrentMouseMovement = currentMouseMovementCount.toInt();

  if (mouse_movement_count_next == icurrentMouseMovement) {
      mouse_movement_count_next = 0;
  } else {
      mouse_movement_count_next = mouse_movement_count_next - icurrentMouseMovement;
  }

  currentMouseClicks = input_.split(" ")[0];
  currentKeyCount = input_.split(" ")[1];
  currentMouseMovementCount = input_.split(" ")[2];

  buttonclicks_ += "\"" + QString::number(mouseclick_count_next) + "\",";
  keystrokes_ += "\"" + QString::number(key_count_next) + "\",";
  mousemovement_ += "\"" + QString::number(mouse_movement_count_next) + "\",";

  std::cout << buttonclicks_.toUtf8().constBegin() << "\n";
  // std::cout << keystrokes_.toUtf8().constBegin() << "\n";
  // std::cout << mousemovement_.toUtf8().constBegin() << "\n";
/*  */
}




