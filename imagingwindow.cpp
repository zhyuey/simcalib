#include "imagingwindow.h"
#include <QPainter>
ImagingWindow::ImagingWindow(QWidget *parent) :
    QWidget(parent)
{
    //setFixedSize(600, 600);
      setWindowTitle("Image View");
}
void ImagingWindow::paintEvent(QPaintEvent *)
{
   QPainter painter(this);
   painter.drawPixmap(0, 0, plot);
}
