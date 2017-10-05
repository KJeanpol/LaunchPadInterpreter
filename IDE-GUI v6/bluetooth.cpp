#include "bluetooth.h"
#include "ui_bluetooth.h"

bluetooth::bluetooth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteSelector)
{
    ui->setupUi(this);
}

bluetooth::~bluetooth()
{
    delete ui;
}
