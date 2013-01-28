#ifndef IMAGINGWINDOW_H
#define IMAGINGWINDOW_H

#include <QWidget>

class ImagingWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ImagingWindow(QWidget *parent = 0);
    QPixmap plot;
signals:
    
public slots:
protected:
    void paintEvent(QPaintEvent *event);
    
};

#endif // IMAGINGWINDOW_H
