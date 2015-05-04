#include "mainwindow.h"
#include <QApplication>
//#include <QMotifStyle>
#include <QFile>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  // QApplication::setStyle("windowsvista");
  QString qss;
  QFile qssFile("E:/GitHub/PlaneTest/qss/css.qss");
  qssFile.open(QFile::ReadOnly);
  if (qssFile.isOpen())
  {
      qss = QLatin1String(qssFile.readAll());
      a.setStyleSheet(qss);
      qssFile.close();
  }
  MainWindow w;
  w.show();

  return a.exec();
}
