#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
//#include <QListView>
//#include <QStringListModel>
#include <QTableView>
#include <QStandardItemModel>
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
class IndicatingMsgWidget;
class IndicateHeadingWidget;

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
  void on_action_view_set();
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
  QTableView* pLegend;
  QStandardItemModel* pSIM;
  QMenuBar* pMenuBar;
  QActionGroup* pViewDirGroup;
  PaintArea* pEagleEyePaint;
  PaintArea* pDetailedPaint;
  QRect DetailedPaintR;
  QRect EagleEyePaintR;
  MapTool* pMapZoom;
  MapTool* pMapPan;
  UdpSettingDialog* pUdp;
  QUdpSocket* pSocket;
  QLabel* pStatusLabel;
  //QRubberBand* pRubberBand;
  QLabel* pPlaneMsgLabel;
  IndicatingMsgWidget* pIndicatingMsgWidget;      // indicate height
  IndicateHeadingWidget* pIndicatingHeadWidget;   // indicate heading


private:
  QPoint  rubberBandStart;
  QString defaultPath;
  std::istringstream iss;
};

#endif // MAINWINDOW_H
