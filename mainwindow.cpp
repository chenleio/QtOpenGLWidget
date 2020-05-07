#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <QTime>
#include <QtCore/qrandom.h>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pOpenglWidget = new MyQOpenglWidget(ui->openGLWidget);
    m_pOpenglWidget->resize(ui->openGLWidget->width(),ui->openGLWidget->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_openfile_clicked()
{
//    QString qfile = QFileDialog::getOpenFileName(this,
//            tr("Open PointCloud"), ".",
//            tr("ASC files(*.asc)"));

    std::vector<QVector3D> cloud ;
    QString qfile = "E:\\test\\test.asc";
    cloud= ReadVec3PointCloudASC(qfile);
    //unitMillimeter2UnitMeter(cloud);
    //saveVec3PointCloudASC("e:\\cloud.asc",cloud);
    //cloud = testData(180*10000);
    QTime startTime = QTime::currentTime();
    m_pOpenglWidget->showPointCloud(cloud);
    qDebug() << "showPointCloud =" << startTime.msecsTo(QTime::currentTime()) << "ms";
}

std::vector<QVector3D> MainWindow::ReadVec3PointCloudASC(QString path)
{
    std::vector<QVector3D> cloud;
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QIODevice::Text))
    {
        qDebug() << "There is no asc file" ;
        return cloud;
    }
    QTextStream in(&file);
    QString ramData = in.readAll();
    QStringList list = ramData.split("\n");
    QStringList listline;
    cloud.resize(list.count()-1);
    for (int i = 0; i < list.count() - 1; i++)
    {
        listline = list.at(i).split(" ");
        if(listline.size()>=3)
        {
            cloud[i].setX((listline.at(0).toFloat()));
            cloud[i].setY((listline.at(1).toFloat()));
            cloud[i].setZ((listline.at(2).toFloat()));
        }
    }
    return cloud;
}

void MainWindow::saveVec3PointCloudASC(QString path, const std::vector<QVector3D>& cloud)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly | QIODevice::Text))
    {
        qDebug() << "There is no asc file" ;
        return ;
    }
    QTextStream out(&file);
    for(int i = 0 ;i<(int)cloud.size();i++)
    {
        //unit Millimeter 2 Unit Meter
        out<<cloud[i].x()<<" "<<cloud[i].y()<<" "<<cloud[i].z()<<endl;
    }
}

void MainWindow::unitMillimeter2UnitMeter( std::vector<QVector3D> &inOutCloud)
{
    for(int i = 0;i<(int)inOutCloud.size();i++)
    {
        inOutCloud[i] /= 1000;
    }
}

std::vector<QVector3D> MainWindow::testData(int pointsNum)
{
    std::vector<QVector3D> cloud;
    for (int i = 0; i < pointsNum; i++)
    {
        cloud.push_back(randomVec3f());
    }
    return cloud;
}

QVector3D MainWindow::randomVec3f()
{
    return QVector3D((float)(QRandomGenerator::global()->bounded(100)) / 2.0f -
            (float)(QRandomGenerator::global()->bounded(100)) / 2.0f,
            (float)(QRandomGenerator::global()->bounded(100)) / 2.0f -
            (float)(QRandomGenerator::global()->bounded(100)) / 2.0f,
            (float)(QRandomGenerator::global()->bounded(100)) / 10.0f -
            (float)(QRandomGenerator::global()->bounded(100)) / 10.0f);
}
