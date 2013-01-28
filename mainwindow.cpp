#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "opencv.hpp"
#include <QFileDialog>
#include <QDirIterator>
#include <QMessageBox>
#include <QDir>
#include <time.h>

using namespace cv;
using namespace std;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int height = geometry().height();
    int width = geometry().width();

    setGeometry(50, 200, width, height);
    setFixedSize(width, height);
    //qRegisterMetaType<QImage>("QImage");
    this->setWindowTitle("Calibration Tools Writen V1.0 By Yueyi Zhang");
    mythread = NULL;
    imageWindow = NULL;


}

MainWindow::~MainWindow()
{

    delete ui;
}



void MainWindow::on_pushButton_Browse_clicked()
{
    QFileDialog* openFolderPath = new QFileDialog(this, "Please choose work folder");
    openFolderPath->setFileMode(QFileDialog::DirectoryOnly);

    if(openFolderPath->exec() == QFileDialog::Accepted)
    {
        ui->lineEdit_WorkFolder->setText(openFolderPath->selectedFiles()[0]);
    }
    delete openFolderPath;
    //getImages();
}

QStringList MainWindow::getImages()
{
    QStringList imageList;
    QString workFolder = ui->lineEdit_WorkFolder->text();
    QDirIterator it(workFolder, QDir::Files | QDir::NoSymLinks, QDirIterator::NoIteratorFlags);
    QString strInfo = "";
    while(it.hasNext())
    {
        QString imageFile = it.next().toLower();
        QStringList list = imageFile.split('.');

        QString last = list.takeLast(); // extension name
        if ("png"  == last || "bmp" == last || "ppm" == last || "jpg" == last || "pgm" == last)
        {
            imageList << imageFile;
            strInfo += ("\n" + imageFile);
        }
    }
    QString head = "In total, there are " + QString::number(imageList.size()) + " images in this folder.";
    ui->textEdit_Information->setText(head + strInfo);
    //ui->label_Information->setText(strInfo);

    return imageList;
}

void MainWindow::on_pushButton_Calibrate_clicked()
{
    ui->textEdit_Information->setText("");

    if(mythread && mythread->isRunning())
    {
        showErrorMessage("Please wait for the completeness of current thread!\n Or you can terminate the current thread!");
        return;
    }

    if(!QDir(ui->lineEdit_WorkFolder->text()).exists())
    {
        showErrorMessage("The folder doesn't exist!\n");

        return;
    }



    QStringList imgList= getImages();

    myCalibrateCamera(imgList);
}

void MainWindow::myCalibrateCamera(QStringList imgList)
{

   // bDialog = new BitmapDialog();


    imageWindow = new ImagingWindow();
    mythread = new CalibrateThread();
    mythread->imgList = imgList;
    mythread->strFileName = ui->lineEdit_WorkFolder->text() + "/" + ui->lineEdit_OutputName->text();
    mythread->m_width = ui->spinBox_HorCornerNum->text().toInt();
    mythread->m_height = ui->spinBox_VerCornerNum->text().toInt();
    mythread->m_squaresize = ui->doubleSpinBox_SquareSize->text().toFloat();

    connect(mythread, SIGNAL(closeImageWindow()), this, SLOT(closeImageWindow()));
    connect(mythread, SIGNAL(showBitmap(const QImage &)), this, SLOT(displayImage(const QImage &)));
    connect(mythread, SIGNAL(appendText(QString)), this, SLOT(appendInformation(QString)), Qt::QueuedConnection);
    connect(mythread, SIGNAL(popupErrorInformation(QString)), this, SLOT(showErrorMessage(QString)), Qt::QueuedConnection);
   // bDialog->show();
    mythread->start();
}

void MainWindow::appendInformation(QString str)
{
    ui->textEdit_Information->append(str);
    QTextCursor cursor = ui->textEdit_Information->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_Information->setTextCursor(cursor);
}

void MainWindow::showErrorMessage(QString str)
{
    QMessageBox::critical(this, "error", str);
}


void MainWindow::on_pushButton_Stop_clicked()
{
    if(mythread)
    {
        mythread->terminate();
        mythread = NULL;
        ui->textEdit_Information->setText("The calibrating thread has been terminated!");
        closeImageWindow();
    }
}

void MainWindow::displayImage(const QImage &image)
{
    int windowLeft = this->geometry().left();
    int windowTop = this->geometry().top();
    int windowWidth = this->geometry().width();
    //int windowHeight = this->geometry().height();


   imageWindow->setGeometry(windowLeft + windowWidth + 15, windowTop, image.width(), image.height());
   imageWindow->plot = QPixmap::fromImage(image);
   imageWindow->show();
   imageWindow->update();
   imageWindow->raise();
   imageWindow->activateWindow();
}

void MainWindow::closeEvent ( QCloseEvent * event )
{
    closeImageWindow();
}

void MainWindow::closeImageWindow()
{
    if(imageWindow)
    {
        delete imageWindow;
        imageWindow = NULL;
    }
}
