#include "bitmapdialog.h"
#include "ui_bitmapdialog.h"

BitmapDialog::BitmapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BitmapDialog)
{
    ui->setupUi(this);
    ui->labe_Bitmap->setText("hello");
    //connect(parent, SIGNAL())
}

BitmapDialog::~BitmapDialog()
{
    delete ui;
}
void BitmapDialog::changeBitmap(QImage img)
{
   // ui->labe_Bitmap->setPixmap(QPixmap::fromImage(img));
   // ui->labe_Bitmap->show();
    qDebug("jjj");
    //ui->labe_Bitmap->setText("hello1");
}

