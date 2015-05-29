#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStyle>
#include <QDir>
#include "paintarea.h"
#include "eagleeyemap.h"
#include "detailedmap.h"
#include "maptool.h"
#include "udpsettingdialog.h"
#include "udpmsgformat.h"
#include "datadefine.h"

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
  pPlaneMsgLabel->setGeometry(710, 24, 100, 100);
  pPlaneMsgLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  // Legend
  pLegend = new QListView(this);
  pLegend->setGeometry(5, 229, 200, 395);
  initializeLegend();

  // RubberBand
  pRubberBand = new QRubberBand(QRubberBand::Line, pEagleEyePaint);

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
  delete pRubberBand;
  delete pSLM;
  delete pLegend;
  delete pMenuBar;
  delete pStatusLabel;
  delete pPlaneMsgLabel;
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
  else if (pEagleEyePaint->geometry().contains(event->pos()))
  {
      pRubberBand->setGeometry(QRect(rubberBandStart, event->pos()).normalized());
      pRubberBand->show();
  }
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
      connect(pSocket, SIGNAL(readyRead()),
              this, SLOT(readPendingDatagrams()));
  }
}

void MainWindow::initializeLegend()
{
  //pLegend->setPalette(QPalette(QColor(128, 128, 128)));
  //pLegend->setAutoFillBackground(true);
  QStringList sl;
  sl.push_back("Guidance Point   -- Green");
  sl.push_back("Guidance Line    -- Blue");
  sl.push_back("Exposure Point   -- White");
  sl.push_back("Current Airplane -- Red");
  sl.push_back("Airplane Trail -- Light Green");
  pSLM = new QStringListModel(sl);
  pLegend->setModel(pSLM);
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

      //QString qSocket(datagram.data());
      //std::string planeMsg(datagram.data());
      //while (planeMsg.find(''))
      //pPlaneMsgLabel->setText(qSocket);
  }
}

void MainWindow::processTheDatagram(std::string data)
{
  AirPlane ap;
  if (getAirPlaneMsg(data, ap))
  {
      PaintArea::setAirPlane(ap.pos);
      if (ap.status){ PaintArea::setExposurePoint(ap.pos); }
      pDetailedPaint->update();
      pEagleEyePaint->update();

      double x = ap.pos.x();
      double y = ap.pos.y();
      double z = ap.hgt;
      double speed = ap.speed;
      double angle = ap.angle;
      QString labelMsg("");
      labelMsg += QString("Line: ") + QString::number(ap.lineIdx) + QString("\r\n");
      labelMsg += QString("Point: ") + QString::number(ap.pointIdx) + QString("\r\n");
      labelMsg += QString("x: ") + QString::number(x, 'g', 9) + QString("\r\n");
      labelMsg += QString("y: ") + QString::number(y, 'g', 9) + QString("\r\n");
      labelMsg += QString("z: ") + QString::number(z, 'g', 9) + QString("\r\n");
      labelMsg += QString("vel: ") + QString::number(speed, 'g', 9) + QString("\r\n");
      labelMsg += QString("az: ") + QString::number(angle, 'g', 9);
      pPlaneMsgLabel->setText(labelMsg);
  }
}

bool MainWindow::getAirPlaneMsg(std::string & data, AirPlane &ap)
{
  if (data.size() <= 0)
    return false;

  double dlon, dlat, dhgt, dvel, daz;
  int nstatus, nLineIdx, nPointIdx;
  std::string time, lon, lat, hgt, vel, az, status, lineIdx, pointIdx;

  while (std::string::npos != data.find(","))
  {
      data.replace(data.find(","), 1, " ");
  }

  try
  {
    iss.clear();
    iss.str(data);
    iss >> time >> lon >> lat >> hgt >> vel >> az >> status >> lineIdx >> pointIdx;

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

    lineIdx.replace(lineIdx.find(":"), 1, " ");
    iss.clear();
    iss.str(lineIdx);
    iss >> lineIdx >> nLineIdx;
    ap.lineIdx = nLineIdx;

    pointIdx.replace(pointIdx.find(":"), 1, " ");
    iss.clear();
    iss.str(pointIdx);
    iss >> pointIdx >> nPointIdx;
    ap.pointIdx = nPointIdx;
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
