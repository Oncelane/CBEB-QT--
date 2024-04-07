#include "customadd.h"
#include "ui_customadd.h"

CustomAdd::CustomAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomAdd)
{
    ui->setupUi(this);
}

CustomAdd::~CustomAdd()
{
    delete ui;
}

void CustomAdd::on_doneButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString phone = ui->phoneEdit->text();
    QString area = ui->areaEdit->text();
    QString address = ui->addressEdit->toPlainText();
    bool abord = ui->yes->isChecked();
    QSqlQuery sql;
    QString q = QString("insert into customView(名字,手机号,区域,地址,国外) values ('%1','%2','%3','%4',%5)").arg(name).arg(phone).arg(area).arg(address).arg(abord);
    if(!sql.exec(q)){
        return;
    }
    emit success();
    this->hide();
}
