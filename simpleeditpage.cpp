#include "simpleeditpage.h"
#include "ui_simpleeditpage.h"

simpleEditPage::simpleEditPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simpleEditPage)
{
    ui->setupUi(this);
}

simpleEditPage::~simpleEditPage()
{
    delete ui;
}

void simpleEditPage::on_doneButton_clicked()
{
    amount=ui->amount->text();
    value=ui->value->text();
    emit EditSuccess(row,amount,value);
    this->hide();
}


void simpleEditPage::Init(int row,QString amount,QString value)
{
    this->row=row;
    QString l=QString("%1").arg(amount);
    ui->amount->setText(l);
    l = QString("%1").arg(value);
    ui->value->setText(l);
}
