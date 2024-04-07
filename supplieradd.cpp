#include "supplieradd.h"
#include "ui_supplieradd.h"

SupplierAdd::SupplierAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierAdd)
{
    ui->setupUi(this);
}

SupplierAdd::~SupplierAdd()
{
    delete ui;
}



void SupplierAdd::on_doneButton_clicked()
{
    QString agentname = ui->agentedit->text();
    QString phone = ui->phoneedit->text();
    QString company = ui->companyedit->text();
    QString companyaddress = ui->companylocationedit->toPlainText();
    QString area = ui->areaedit->text();

    QSqlQuery sql;
    QString q=QString("insert into supplier (supplierContactMan,supplierPhone,supplierCompany,supplierArea,supplierCompanyAddress) values ('%1','%2','%3','%4','%5');").arg(agentname).arg(phone).arg(company).arg(area).arg(companyaddress);
    if(sql.exec(q)){
        qDebug()<<"成功添加";
        emit addsuppliersuccess();
        this->hide();
    }
    else qDebug()<<"发生错误";
}
