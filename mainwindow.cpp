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

  setFixedSize(815, 630);
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
  pMenu = pMenuBar->addMenu(tr("&View"));
  pAction = pMenu->addAction(tr("Normal"));
  pAction->setShortcut(QKeySequence(tr("Ctrl+N")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_normal()) );
  pAction = pMenu->addAction(tr("Pan"));
  pAction->setShortcut(QKeySequence(tr("Ctrl+P")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_pan()) );
  pAction = pMenu->addAction(tr("Zoom"));
  pAction->setShortcut(QKeySequence(tr("Ctrl+Z")));
  connect(pAction, SIGNAL(triggered()), this, SLOT(on_action_zoom()) );
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

  // View
  EagleEyePaintR.setRect(5, 24, 200, 200);
  pEagleEyePaint = new EagleEyeMap(this);
  pEagleEyePaint->setGeometry(EagleEyePaintR);
  DetailedPaintR.setRect(210, 24, 600, 600);
  pDetailedPaint = new DetailedMap(this);
  pDetailedPaint->setGeometry(DetailedPaintR);

  // Legend
  pLegend = new QListView(this);
  pLegend->setGeometry(5, 229, 200, 395);
  initializeLegend();

  pUdp = new UdpSettingDialog(this);

  // Socket
  pSocket = new QUdpSocket(this);
  	pSocket->bind(7001, QUdpSocket::ShareAddress);
  	connect(pSocket, SIGNAL(readyRead()),
  		this, SLOT(readPendingDatagrams()));

  pMapTool = 0;
  defaultPath = ".";
}

MainWindow::~MainWindow()
{
  delete pSLM;
  delete pLegend;
  delete pMenuBar;
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
  if (pMapTool)
  {
    delete pMapTool; pMapTool = 0;
  }

  pDetailedPaint->setCursor(Qt::ArrowCursor);
}

void MainWindow::on_action_pan()
{
  if (pMapTool)
  {
      delete pMapTool;
      pMapTool = 0;
  }

  pMapTool = new MapToolPan(pDetailedPaint);
  pDetailedPaint->setCursor(Qt::PointingHandCursor);
}

void MainWindow::on_action_zoom()
{
  if (pMapTool)
  {
      delete pMapTool;
      pMapTool = 0;
  }

  pMapTool = new MapToolZoom(pDetailedPaint);
  pDetailedPaint->setCursor(Qt::OpenHandCursor);
}

void MainWindow::on_action_udp_msg()
{
  udpmsgformat dlg;
  dlg.exec();
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
      if (pMapTool)
      {
          if (Qt::LeftButton == event->button())
          {
            pMapTool->OnLButtonDown(event->localPos());
          }
      }
  }
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
      if (pMapTool)
      {
          if (Qt::LeftButton == event->button())
          {
            pMapTool->OnLButtonUp(event->localPos());
          }
      }
  }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
  if (DetailedPaintR.contains(event->pos()) )
  {
    if (pMapTool && (0<event->delta()) )
    {
        int step = event->delta()/8/15;
        pMapTool->OnWheelZoom(step*1.25);
    }
    else if (pMapTool && (0>event->delta()))
    {
      double _scale = 1.0;
      int step = -(event->delta()/8/15);
      for (int i=0; i<step; ++i)
        _scale *= 0.85;
      pMapTool->OnWheelZoom(_scale);
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
  QStringList sl;
  sl.push_back("Guidance Point   -- Green");
  sl.push_back("Guidance Line    -- Blue");
  sl.push_back("Airplane Trail   -- White");
  sl.push_back("Current Airplane -- Red");
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

      pSocket->readDatagram(datagram.data(), datagram.size(),
                            &sender, &senderPort);
      processTheDatagram(std::string(datagram.data()));
    }
}

void MainWindow::processTheDatagram(std::string data)
{
  AirPlane ap;
  if (getAirPlaneMsg(data, ap))
    {
      if (ap.status)
        {
          PaintArea::setAirPlane(ap.pos);
          pDetailedPaint->update();
          pEagleEyePaint->update();
        }
    }
}

bool MainWindow::getAirPlaneMsg(std::string & data, AirPlane &ap)
{
  if (data.size() <= 0)
    return false;

  double dlon, dlat;
  int nstatus;
  std::string time, lon, lat, hgt, vel, az, status;

  while (std::string::npos != data.find(","))
    {
      data.replace(data.find(","), 1, " ");
    }

  try
  {
    iss.clear();
    iss.str(data);
    iss >> time >> lon >> lat >> hgt >> vel >> az >> status;

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

    status.replace(status.find(":"), 1, " ");
    iss.clear();
    iss.str(status);
    iss >> status >> nstatus;
    ap.status = nstatus;
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
