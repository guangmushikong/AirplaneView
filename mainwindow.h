#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QListView>
#include <QStringListModel>
#include <QUdpSocket>
#include <sstream>
#include <QLabel>



#define PainterWidth 600
#define PainterHeight 600

namespace Ui {
  class MainWindow;
}

class PaintArea;
class MapTool;
class UdpSettingDialog;
class AirPlane;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_action_openfile();
  void on_action_closefile();
  void on_action_exit();
  void on_action_normal();
  void on_action_pan();
  void on_action_zoom();
  void on_action_udp();
  void on_action_udp_msg();
  void readPendingDatagrams();

protected:
  void mouseMoveEvent(QMouseEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void wheelEvent(QWheelEvent* event);
  void processTheDatagram(std::string);
  bool getAirPlaneMsg(std::string & data, AirPlane &ap);

private:
  void initializeLegend();

private:
  Ui::MainWindow *ui;
  QListView* pLegend;
  QStringListModel* pSLM;
  QMenuBar* pMenuBar;
  PaintArea* pEagleEyePaint;
  PaintArea* pDetailedPaint;
  QRect DetailedPaintR;
  QRect EagleEyePaintR;
  //MapTool* pMapTool;
  MapTool* pMapZoom;
  MapTool* pMapPan;
  UdpSettingDialog* pUdp;
  QUdpSocket* pSocket;
  //QStatusBar* pStatusBar;
  QLabel* pStatusLabel;
  QRubberBand* pRubberBand;
  QLabel* pPlaneMsgLabel;

private:
  QPoint  rubberBandStart;
  QString defaultPath;
  std::istringstream iss;
};

#endif // MAINWINDOW_H
