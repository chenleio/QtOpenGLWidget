#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myqopenglwidget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_openfile_clicked();

private:
    Ui::MainWindow *ui;
    MyQOpenglWidget* m_pOpenglWidget;

    std::vector<QVector3D> ReadVec3PointCloudASC(QString path);
    void saveVec3PointCloudASC(QString path,const std::vector<QVector3D>& cloud);
    void unitMillimeter2UnitMeter(std::vector<QVector3D> &inOutCloud);
    std::vector<QVector3D> testData(int pointsNum);
    QVector3D randomVec3f();
};

#endif // MAINWINDOW_H
