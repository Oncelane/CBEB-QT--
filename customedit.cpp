#include "customedit.h"
#include "ui_customedit.h"

CustomEdit::CustomEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomEdit)
{
    ui->setupUi(this);


}

CustomEdit::~CustomEdit()
{
    delete ui;
}

void CustomEdit::Init(QSqlTableModel *model, int row)
{
    ui->idedit->setText(model->record(row).value("ID").toString());
    ui->nameEdit->setText(model->record(row).value("名字").toString());
    ui->phoneEdit->setText(model->record(row).value("手机号").toString());
    ui->areaEdit->setText(model->record(row).value("区域").toString());
    ui->addressEdit->setText(model->record(row).value("地址").toString());
    if(model->record(row).value("国外").toBool()){
        ui->yes->setChecked(1);
    }
    else ui->no->setChecked(1);
}

void CustomEdit::on_doneButton_clicked()
{
    QString id = ui->idedit->text();
    QString name = ui->nameEdit->text();
    QString phone = ui->phoneEdit->text();
    QString area = ui->areaEdit->text();
    QString address = ui->addressEdit->toPlainText();
    bool abord = ui->yes->isChecked();
    QSqlQuery sql;
    QString q = QString("update customView set 名字='%1',手机号='%2',区域='%3',地址='%4',国外='%5' where ID='%6';").arg(name).arg(phone).arg(area).arg(address).arg(abord).arg(id);
    if(!sql.exec(q)){
        return;
    }
    emit success();
    this->hide();
}
