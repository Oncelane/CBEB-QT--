#include "supplieredit.h"
#include "ui_supplieredit.h"

SupplierEdit::SupplierEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierEdit)
{
    ui->setupUi(this);
}

SupplierEdit::~SupplierEdit()
{
    delete ui;
}
void SupplierEdit::InitEdit(QSqlTableModel *model,int row)
{
    ui->idedit->setText(model->record(row).value("ID").toString());
    ui->agentedit->setText(model->record(row).value("代理人").toString());
    ui->phoneedit->setText(model->record(row).value("电话").toString());
    ui->companyedit->setText(model->record(row).value("公司名称").toString());    ui->idedit->setText(model->record(row).value("ID").toString());
    ui->companylocationedit->setText(model->record(row).value("公司地址").toString());    ui->idedit->setText(model->record(row).value("ID").toString());
    ui->areaedit->setText(model->record(row).value("产地").toString());
}

void SupplierEdit::on_doneButton_clicked()
{
    QString id = ui->idedit->text();
    QString agentname = ui->agentedit->text();
    QString phone = ui->phoneedit->text();
    QString company = ui->companyedit->text();
    QString companyaddress = ui->companylocationedit->toPlainText();
    QString area = ui->areaedit->text();

    QSqlQuery sql;
    QString q= QString("update supplierView set supplierView.代理人='%1',电话='%2',公司名称='%3',产地='%4',公司地址='%5' where ID = '%6';").arg(agentname).arg(phone).arg(company).arg(area).arg(companyaddress).arg(id);
    if(sql.exec((q))){
        emit editsuppliersuccess();
        this->hide();
        qDebug()<<"修改成功";
    }
    else qDebug() << "SQL query error:" << sql.lastError().text();;
}
