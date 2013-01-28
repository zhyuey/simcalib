#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//#include "opencv.hpp"
#include <QMainWindow>
#include <QCloseEvent>
#include "calibratethread.h"
#include "bitmapdialog.h"
#include "imagingwindow.h"

using namespace cv;
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
    void on_pushButton_Browse_clicked();

    void on_pushButton_Calibrate_clicked();

protected:
    void closeEvent ( QCloseEvent * event );

private:
    Ui::MainWindow *ui;
    QStringList getImages();
    CalibrateThread* mythread;

    ImagingWindow *imageWindow;


   // BitmapDialog *bDialog;
    void myCalibrateCamera(QStringList imgList);
public slots:
    void appendInformation(QString str);
    void showErrorMessage(QString str);

    void on_pushButton_Stop_clicked();
    void displayImage(const QImage &);
    void closeImageWindow();

};

#endif // MAINWINDOW_H
