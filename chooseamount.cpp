#include "chooseamount.h"
#include "ui_chooseamount.h"

ChooseAmount::ChooseAmount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseAmount)
{
    ui->setupUi(this);
}

ChooseAmount::~ChooseAmount()
{
    delete ui;
}
