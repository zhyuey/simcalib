#ifndef BITMAPDIALOG_H
#define BITMAPDIALOG_H

#include <QDialog>
#include <QImage>

namespace Ui {
class BitmapDialog;
}

class BitmapDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BitmapDialog(QWidget *parent = 0);
    ~BitmapDialog();

private:
    Ui::BitmapDialog *ui;

public slots:
    void changeBitmap(QImage img);
};

#endif // BITMAPDIALOG_H
