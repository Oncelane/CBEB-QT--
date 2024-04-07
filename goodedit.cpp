#include "goodedit.h"
#include "ui_goodedit.h"

GoodEdit::GoodEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoodEdit)
{
    ui->setupUi(this);
}

GoodEdit::~GoodEdit()
{
    delete ui;
}
//初始化修改页面的基础信息
void GoodEdit::InitEdit(QSqlTableModel*model,int row){
    ui->IDEdit->setText(model->record(row).value("货品编码").toString());
    ui->nameEdit->setText(model->record(row).value("货品名称").toString());
    ui->detailEdit->setText(model->record(row).value("简介").toString());
    ui->valueEdit->setText(model->record(row).value("参考价格").toString());
    QString comps = model->record(row).value("供应商公司").toString();
    QSqlQuery sql(QString("select supplierID from supplier where supplierCompany = '%1';").arg(comps));
    sql.exec();sql.next();
    ui->supplierCombox->setCurrentIndex(sql.value(0).toInt());
    QString types = model->record(row).value("类型").toString();
    int typeIndex = types.section(' ',0,0).toInt()-1;
    ui->typeCombox->setCurrentIndex(typeIndex);
}

//初始化修改页面的供应商列表
void GoodEdit::InitUi()
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

void GoodEdit::on_doneButton_clicked()
{
    QString id = ui->IDEdit->text();
    QString goodname = ui->nameEdit->text();
    QString detail = ui->detailEdit->toPlainText();
    QString type = ui->typeCombox->currentText();
    QString unit = ui->unitCombox->currentText();
    QString value = ui->valueEdit->text();
    QString supplier = ui->supplierCombox->currentText();
    QString supplierID = supplier.section('-',0,0);

    //暂未实现部分添加及校验错误
    QSqlQuery sql;
    QString q=QString("update goods set goodName='%1',goodDetail='%2',goodType='%3',goodUnit='%4',goodprice='%5',goodSupplierID='%6' where goodID = '%7';").arg(goodname).arg(detail).arg(type).arg(unit).arg(value).arg(supplierID).arg(id);
    qDebug()<<q;
    if(sql.exec(q)){
        emit success();
        this->hide();
    }
    else {
        return;
    }
}
