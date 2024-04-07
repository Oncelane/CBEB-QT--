#include "goodadd.h"
#include "ui_goodadd.h"

GoodAdd::GoodAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoodAdd)
{
    ui->setupUi(this);
}

GoodAdd::~GoodAdd()
{
    delete ui;
}

void GoodAdd::on_editButton_clicked()
{
    exit(0);
}

void GoodAdd::on_doneButton_clicked()
{
    QString goodname = ui->nameEdit->text();
    QString detail = ui->detailEdit->toPlainText();
    QString type = ui->typeCombox->currentText();
    QString unit = ui->unitCombox->currentText();
    QString value = ui->valueEdit->text();
    QString supplier = ui->supplierCombox->currentText();
    QString supplierID = supplier.section('-',0,0);

    //暂未实现添加初始数量
    //暂未实现部分添加及校验错误
    QSqlQuery sql;
    QString q=QString("insert into goods (goodName, goodprice,goodUnit, goodType, goodDetail, goodSupplierID) values ('%1','%2','%3','%4','%5','%6');").arg(goodname).arg(value).arg(unit).arg(type).arg(detail).arg(supplierID);
    qDebug()<<q;
    if(sql.exec(q)){
        emit success();
        this->hide();
    }
    else {
        return;
    }
}
    //初始化添加页面的供应商列表
void GoodAdd::InitUi()
{
    QSqlQuery sql;
    QString q = QString("select supplierID,supplierCompany from supplier;");
    if(!sql.exec(q)){
        return;
    }
    int row=0;
    while(sql.next()){
        QString temp=sql.value(0).toString()+"-"+sql.value(1).toString();
        ui->supplierCombox->addItem(temp);
        row++;
    }
}


