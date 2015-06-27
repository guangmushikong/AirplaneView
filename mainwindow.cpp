#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStyle>
#include <QDir>
#include <QHeaderView>
#include "paintarea.h"
#include "eagleeyemap.h"
#include "detailedmap.h"
#include "indicatingmsgwidget.h"
#include "indicateheadingwidget.h"
#include "maptool.h"
#include "udpsettingdialog.h"
#include "udpmsgformat.h"
#include "datadefine.h"
#include "uiparamconfig.h"


#include <fstream>


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  setFixedSize(815, 650);
  setPalette(QPalette(QColor(203, 213, 228)));
  setAutoFillBackground(true);

  // MenuBar
  pMenuBar = new QMenuBar(this);
  pMenuBar->setGeometry(QRect(0, 0, this->geometry().width(), 24));
  // Menu - File
  QMenu* pMenu = pMenuBar->addMenu(tr("&File"));
  QAction* pAction = pMenu->addAction(tr("Open"));
  pAction->setShortcut(QKeySequence(tr("Ctrl+O")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_openfile()));
  pAction = pMenu->addAction(tr("Close"));
  pAction->setShortcut(QKeySequence(tr("Ctrl+C")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_closefile()));
  pAction = pMenu->addAction(tr("Exit"));
  pAction->setShortcut(QKeySequence(tr("Alt+F4")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_exit()) );
  // Menu - View
  pViewDirGroup = new QActionGroup(this);
  pViewDirGroup->setExclusive(true);
  pMenu = pMenuBar->addMenu(tr("&View"));
  pAction = pMenu->addAction(tr("PolarHead"));
  pViewDirGroup->addAction(pAction);
  pAction->setCheckable(true);
  pAction->setChecked(true);
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_view_set()) );
  pAction = pMenu->addAction(tr("PlaneHead"));
  pAction->setCheckable(true);
  pViewDirGroup->addAction(pAction);
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_view_set()) );
//  // Menu - View
//  pMenu = pMenuBar->addMenu(tr("&View"));
//  pAction = pMenu->addAction(tr("Normal"));
//  pAction->setShortcut(QKeySequence(tr("Ctrl+N")));
//  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_normal()) );
//  pAction = pMenu->addAction(tr("Pan"));
//  pAction->setShortcut(QKeySequence(tr("Ctrl+P")));
//  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_pan()) );
//  pAction = pMenu->addAction(tr("Zoom"));
//  pAction->setShortcut(QKeySequence(tr("Ctrl+Z")));
//  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_zoom()) );
  // Menu - Tool
  pMenu = pMenuBar->addMenu(tr("&Tool"));
  pAction = pMenu->addAction(tr("UdpSocket"));
  pAction->setShortcut(QKeySequence(tr("Ctrl+U")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_udp()) );
  // Menu - About Us
  pMenu = pMenuBar->addMenu(tr("&Help"));
  pAction = pMenu->addAction(tr("UdpMsg"));
  pAction->setShortcut(QKeySequence(tr("Ctrl+M")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_udp_msg()) );

  // Status Bar
  pStatusLabel = new QLabel();
  pStatusLabel->setMinimumSize(pStatusLabel->sizeHint());
  pStatusLabel->setAlignment(Qt::AlignHCenter);
  statusBar()->addWidget(pStatusLabel);

  // View
  EagleEyePaintR.setRect(5, 24, 200, 200);
  pEagleEyePaint = new EagleEyeMap(this);
  pEagleEyePaint->setGeometry(EagleEyePaintR);
  DetailedPaintR.setRect(210, 24, 600, 600);
  pDetailedPaint = new DetailedMap(this);
  pDetailedPaint->setGeometry(DetailedPaintR);
  pDetailedPaint->setCursor(Qt::OpenHandCursor);

  // Plane Msg Label
  pPlaneMsgLabel = new QLabel(this);
  pPlaneMsgLabel->setGeometry(590, 24, 220, 200);
  //pPlaneMsgLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  QFont font;
  font.setPointSize(17);
  pPlaneMsgLabel->setFont(font);
  QPalette palette;
  palette.setColor(QPalette::WindowText, Qt::white);
  pPlaneMsgLabel->setPalette(palette);

  // Indicating heading widget
  pIndicatingHeadWidget = new IndicateHeadingWidget(this);
  pIndicatingHeadWidget->setGeometry(5, 229, 200, 200);

  // Plane Indicating Msg Widget
  //pIndicatingMsgWidget = new IndicatingMsgWidget(this);
  //pIndicatingMsgWidget->setGeometry(5, 229, 200, 200);
  pIndicatingMsgWidget = new IndicatingMsgWidget(pDetailedPaint);
  pIndicatingMsgWidget->setGeometry(0, 0, 50, 200);

  // Legend
  //pLegend = new QListView(this);
  //pLegend->setGeometry(5, 229, 200, 395);
  pLegend = new QTableView(this);
  pLegend->setGeometry(5, 434, 200, 190);
  initializeLegend();

  // RubberBand
  //pRubberBand = new QRubberBand(QRubberBand::Line, pEagleEyePaint);

  pUdp = new UdpSettingDialog(this);

  // Socket
  pSocket = new QUdpSocket(this);
  pSocket->bind(7001, QUdpSocket::ShareAddress);
  connect(pSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

  //pMapTool = 0;
  pMapZoom = new MapToolZoom(pDetailedPaint);
  pMapPan  = new MapToolPan(pDetailedPaint);
  defaultPath = ".";
}

MainWindow::~MainWindow()
{
  delete pMapZoom;
  delete pMapPan;
  //delete pRubberBand;
  //delete pSLM;
  delete pSIM;
  delete pLegend;
  delete pViewDirGroup;
  delete pMenuBar;
  delete pStatusLabel;
  delete pPlaneMsgLabel;
  delete pIndicatingMsgWidget;
  delete pEagleEyePaint;
  delete pDetailedPaint;
  delete pUdp;
  delete pSocket;
  delete ui;
}

void MainWindow::on_action_openfile()
{
  defaultPath = QFileDialog::getOpenFileName(
                               this,
                               tr("Open ght File"),
                               defaultPath,
                               tr("Ght Files(*.ght)"));
  if (0 < defaultPath.length())
  {
    pEagleEyePaint->registerGhtFile(defaultPath.toStdString());
    pDetailedPaint->registerGhtFile(defaultPath.toStdString());
    pEagleEyePaint->update();
    pDetailedPaint->update();
  }
}

void MainWindow::on_action_closefile()
{
  pEagleEyePaint->releaseShapes();
  pDetailedPaint->releaseShapes();
  pEagleEyePaint->update();
  pDetailedPaint->update();
}

void MainWindow::on_action_exit()
{
  this->close();
}

void MainWindow::on_action_normal()
{
//  if (pMapTool)
//  {
//      delete pMapTool;
//      pMapTool = 0;
//  }

//  pDetailedPaint->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_action_pan()
{
//  if (pMapTool)
//  {
//      delete pMapTool;
//      pMapTool = 0;
//  }

//  pMapTool = new MapToolPan(pDetailedPaint);
//  pDetailedPaint->setCursor(Qt::PointingHandCursor);
}

void MainWindow::on_action_zoom()
{
//  if (pMapTool)
//  {
//      delete pMapTool;
//      pMapTool = 0;
//  }

//  pMapTool = new MapToolZoom(pDetailedPaint);
//  pDetailedPaint->setCursor(Qt::OpenHandCursor);
}

void MainWindow::on_action_udp_msg()
{
  udpmsgformat dlg;
  dlg.exec();
}

void MainWindow::on_action_view_set()
{
  if (pMenuBar)
  {
    QAction* pAction = pViewDirGroup->checkedAction();
    QString text = pAction->text();
    ViewDirection dir;
    if (text == "PolarHead")
    {
        dir = PolarHeading;
    }
    else if (text == "PlaneHead")
    {
        dir = PlaneHeading;
    }

    if (UIParamConfig::getViewDirection() != dir)
    {
      UIParamConfig::setViewDirection(dir);
      update();
    }
  }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
  if (pDetailedPaint->geometry().contains(event->pos()))
  {
      QPoint  relativePos;
      QPointF worldPos;
      QString statusMsg("Current Position: ");
      if (pDetailedPaint->geometry().contains(event->pos()))
      {
          relativePos = event->pos() - pDetailedPaint->geometry().topLeft();
          worldPos = pDetailedPaint->getWorldCoord(relativePos);
      }
      else if (pEagleEyePaint->geometry().contains(event->pos()))
      {
          relativePos = event->pos() - pEagleEyePaint->geometry().topLeft();
          worldPos = pEagleEyePaint->getWorldCoord(relativePos);
      }
      statusMsg += (QString::number(worldPos.x()) +
                    QString(", ") +
                    QString::number(worldPos.y()));
      pStatusLabel->setText(statusMsg);
  }
  //else if (pEagleEyePaint->geometry().contains(event->pos()))
  //{
  //    pRubberBand->setGeometry(QRect(rubberBandStart, event->pos()).normalized());
  //    pRubberBand->show();
  //}
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

  double Xmouse = event->localPos().x();
  double Ymouse = event->localPos().y();
  int Xmin, Ymin, Xmax, Ymax;
  DetailedPaintR.getCoords(&Xmin, &Ymin, &Xmax, &Ymax);
  if ( Xmouse > Xmin && Xmouse < Xmax &&
       Ymouse > Ymin && Ymouse < Ymax)
  {
      if (pMapPan)
      {
          if (Qt::LeftButton == event->button())
          {
            pMapPan->OnLButtonDown(event->localPos());
          }
      }
  }
//  else if (pEagleEyePaint->geometry().contains(event->pos()))
//  {
//      if (pMapTool)
//      {
//          if (Qt::LeftButton == event->button())
//          {
//              rubberBandStart = event->pos();
//              pMapTool->OnLButtonDown(event->localPos());
//              pRubberBand->setGeometry(QRect(rubberBandStart, QSize()));
//              pRubberBand->show();
//          }
//      }
//  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
  double Xmouse = event->localPos().x();
  double Ymouse = event->localPos().y();
  int Xmin, Ymin, Xmax, Ymax;
  DetailedPaintR.getCoords(&Xmin, &Ymin, &Xmax, &Ymax);
  if ( Xmouse > Xmin && Xmouse < Xmax &&
       Ymouse > Ymin && Ymouse < Ymax)
  {
      if (pMapPan)
      {
          if (Qt::LeftButton == event->button())
          {
            pMapPan->OnLButtonUp(event->localPos());
          }
      }
  }
//  else if (pEagleEyePaint->geometry().contains(event->pos()))
//  {
//      if (pMapTool)
//      {
//          if (Qt::LeftButton == event->button())
//          {
//              pMapTool->OnLButtonUp(event->localPos());
//          }
//      }

//      pRubberBand->hide();
//  }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
  if (DetailedPaintR.contains(event->pos()) )
  {
    if (pMapZoom && (0<event->delta()) )
    {
        int step = event->delta()/8/15;
        pMapZoom->OnWheelZoom(step*1.25, event->pos());
    }
    else if (pMapZoom && (0>event->delta()))
    {
      double _scale = 1.0;
      int step = -(event->delta()/8/15);
      for (int i=0; i<step; ++i)
        _scale *= 0.85;
      pMapZoom->OnWheelZoom(_scale, event->pos());
    }
  }
}

void MainWindow::on_action_udp()
{
  if ( QDialog::Accepted == pUdp->exec() )
  {
      pSocket->abort();
      pSocket->bind(pUdp->getPort(), QUdpSocket::ShareAddress);
      connect(pSocket,
              SIGNAL(readyRead()),
              this,
              SLOT(readPendingDatagrams()));
  }
}

void MainWindow::initializeLegend()
{
  pLegend->setPalette(QPalette(QColor(0, 0, 0)));
  pLegend->verticalHeader()->setVisible(false);
  pLegend->horizontalHeader()->setVisible(false);

  QStandardItem* pItem;
  pSIM = new QStandardItemModel();
  pSIM->setColumnCount(2);
  pSIM->setRowCount(3);
  pSIM->setItem(0, 0, new QStandardItem(tr("设计信息")));
  pItem = new QStandardItem();
  pItem->setBackground(QBrush(QColor(0, 255, 0)));
  pSIM->setItem(0, 1, pItem);
  pSIM->setItem(1, 0, new QStandardItem(tr("曝光信息")));
  pItem = new QStandardItem();
  pItem->setBackground(QBrush(QColor(255, 255, 255)));
  pSIM->setItem(1, 1, pItem);
  pSIM->setItem(2, 0, new QStandardItem(tr("航迹信息")));
  pItem = new QStandardItem();
  pItem->setBackground(QBrush(QColor(255, 255, 255, 125)));
  pSIM->setItem(2, 1, pItem);
  //pSIM->setItem(3, 0, new QStandardItem(tr("航线角度")));
  //pItem = new QStandardItem();
  //pItem->setBackground(QBrush(QColor(0, 0, 255)));
  //pSIM->setItem(3, 1, pItem);
  //pSIM->setItem(4, 0, new QStandardItem(tr("实际角度")));
  //pItem = new QStandardItem();
  //pItem->setBackground(QBrush(QColor(QColor(255, 0, 255))));
  //pSIM->setItem(4, 1, pItem);


  pLegend->setModel(pSIM);
}

void MainWindow::readPendingDatagrams()
{
  while (pSocket->hasPendingDatagrams())
  {
      QByteArray datagram;
      datagram.resize(pSocket->pendingDatagramSize());
      QHostAddress sender;
      quint16 senderPort;
      std::string socketdata;

      pSocket->readDatagram(datagram.data(), datagram.size(),
                            &sender, &senderPort);
      socketdata = std::string(datagram.data());
      processTheDatagram(socketdata);
  }
}

void MainWindow::processTheDatagram(std::string data)
{
  AirPlane ap;
  if (getAirPlaneMsg(data, ap))
  {
      pDetailedPaint->move2point(ap.pos);
      pEagleEyePaint->move2point(ap.pos);

      PaintArea::setAirPlane(ap.pos);
      PaintArea::setHeadingAngle(ap.angle);
      PaintArea::setGuidanceLine(ap.pos, ap.nextPos);
      if (ap.status){ PaintArea::setExposurePoint(ap.pos); }
      pDetailedPaint->update();
      pEagleEyePaint->update();

      //double x = ap.pos.x();
      //double y = ap.pos.y();
      //double z = ap.hgt;
      double speed = ap.speed;
      double angle = ap.angle;
      QString labelMsg("");
      labelMsg += QString("Strip    : ") + QString::fromStdString(ap.cLineIdx) + QString("\r\n");
      labelMsg += QString("Point No.: ") + QString::fromStdString(ap.cPointIdx) + QString("\r\n");
      //labelMsg += QString("x: ") + QString::number(x, 'g', 9) + QString("\r\n");
      //labelMsg += QString("y: ") + QString::number(y, 'g', 9) + QString("\r\n");
      //labelMsg += QString("z: ") + QString::number(z, 'g', 9) + QString("\r\n");
      labelMsg += QString("HV       : ") + QString::number(speed, 'g', 9) + QString("\r\n");
      labelMsg += QString("Azimuth  : ") + QString::number(angle, 'g', 9) + QString("\r\n");
      labelMsg += QString("Altitude : ") + QString::number(ap.hgt, 'g', 9) + QString("\r\n");
      labelMsg += QString("Distance : ") + QString::number(ap.distance, 'g', 9) + QString("\r\n");
      labelMsg += QString("Dev.Angle: ") + QString::number(ap.aoy, 'g', 9);
      //labelMsg += QString("Dev. Dist : ") + QString::number(ap.distance, 'g', 9) + QString("\r\n");
      pPlaneMsgLabel->setText(labelMsg);

      pIndicatingMsgWidget->setHeight(int(ap.hgt));

      pIndicatingHeadWidget->setAngle(ap.designAngle, ap.angle);
  }
}

bool MainWindow::getAirPlaneMsg(std::string & data, AirPlane &ap)
{
  if (data.size() <= 0)
    return false;

  double dlon, dlat, dhgt, dvel, daz;
  double dFlon, dFlat, dFhgt, daoy, dDistan, dDesignAZ;
  int nstatus;
  std::string _cLineIdx, _cPointIdx, cLineIdx, cPointIdx;
  std::string _fLineIdx, _fPointIdx, fLineIdx, fPointIdx;
  std::string time, lon, lat, hgt, vel, az, status;
  std::string flon, flat, fhgt, aoy, distan, designAZ;

  while (std::string::npos != data.find(","))
  {
      data.replace(data.find(","), 1, " ");
  }

  try
  {
    iss.clear();
    iss.str(data);
    iss >> time >> lon >> lat >> hgt >> vel >> az >> status >> _cLineIdx >> _cPointIdx
        >> _fLineIdx >> _fPointIdx >> flon >> flat >> fhgt >> aoy >> distan >> designAZ;

    lon.replace(lon.find(":"), 1, " ");
    iss.clear();
    iss.str(lon);
    iss >> lon >> dlon;
    ap.pos.setX(dlon);

    lat.replace(lat.find(":"), 1, " ");
    iss.clear();
    iss.str(lat);
    iss >> lat >> dlat;
    ap.pos.setY(dlat);

    hgt.replace(hgt.find(":"), 1, " ");
    iss.clear();;
    iss.str(hgt);
    iss >> hgt >> dhgt;
    ap.hgt = dhgt;

    vel.replace(vel.find(":"), 1, " ");
    iss.clear();
    iss.str(vel);
    iss >> vel >> dvel;
    ap.speed = dvel;

    az.replace(az.find(":"), 1, " ");
    iss.clear();
    iss.str(az);
    iss >> az >> daz;
    ap.angle = daz;

    status.replace(status.find(":"), 1, " ");
    iss.clear();
    iss.str(status);
    iss >> status >> nstatus;
    ap.status = nstatus;

    _cLineIdx.replace(_cLineIdx.find(":"), 1, " ");
    iss.clear();
    iss.str(_cLineIdx);
    iss >> _cLineIdx >> cLineIdx;
    ap.cLineIdx = cLineIdx;

    _cPointIdx.replace(_cPointIdx.find(":"), 1, " ");
    iss.clear();
    iss.str(_cPointIdx);
    iss >> _cPointIdx >> cPointIdx;
    ap.cPointIdx = cPointIdx;

    _fLineIdx.replace(_fLineIdx.find(":"), 1, " ");
    iss.clear();
    iss.str(_fLineIdx);
    iss >> _fLineIdx >> fLineIdx;
    ap.FlineIdx = fLineIdx;

    _fPointIdx.replace(_fPointIdx.find(":"), 1, " ");
    iss.clear();
    iss.str(_fPointIdx);
    iss >> _fPointIdx >> fPointIdx;
    ap.FpointIdx = fPointIdx;

    flon.replace(flon.find(":"), 1, " ");
    iss.clear();
    iss.str(flon);
    iss >> flon >> dFlon;
    ap.nextPos.setX(dFlon);

    flat.replace(flat.find(":"), 1, " ");
    iss.clear();
    iss.str(flat);
    iss >> flat >> dFlat;
    ap.nextPos.setY(dFlat);

    fhgt.replace(fhgt.find(":"), 1, " ");
    iss.clear();;
    iss.str(fhgt);
    iss >> fhgt >> dFhgt;
    ap.Fhgt = dFhgt;

    aoy.replace(aoy.find(":"), 1, " ");
    iss.clear();
    iss.str(aoy);
    iss >> aoy >> daoy;
    ap.aoy = daoy;

    distan.replace(distan.find(":"), 1, " ");
    iss.clear();
    iss.str(distan);
    iss >> distan >> dDistan;
    ap.distance = dDistan;

    designAZ.replace(designAZ.find(":"), 1, " ");
    iss.clear();
    iss.str(designAZ);
    iss >> designAZ >> dDesignAZ;
    ap.designAngle = dDesignAZ;
  }
  catch(...)
  {
    QDir dir;
    std::string runtimelog = dir.currentPath().toStdString();
    runtimelog += std::string("/runtime.log");
    std::ofstream outfile(runtimelog, std::ios::app);
    if (outfile.is_open())
    {
        outfile << "Message format("
                << data << ") received by UDPSocket isn't right..."
                << std::endl;
    }

    return false;
  }

  return true;
}
