#include "custommanage.h"
#include "ui_custommanage.h"

CustomManage::CustomManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomManage)
{
    ui->setupUi(this);
    customadd = new CustomAdd;
    customedit = new CustomEdit;

    connect(customadd,&CustomAdd::success,this,&CustomManage::flashContent);
    connect(customedit,&CustomEdit::success,this,&CustomManage::flashContent);

    model = new QSqlTableModel;
    model->setTable("customView");
    ui->tableView->setModel(model);
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

CustomManage::~CustomManage()
{
    delete ui;
}

void CustomManage::flashContent()
{
    model->select();
}

void CustomManage::on_addbutton_clicked()
{
    customadd->show();
}

void CustomManage::on_editbutton_clicked()
{
    int row=ui->tableView->currentIndex().row();
    if(row<0||row>=ui->tableView->model()->rowCount()){
        return;
    }
    customedit->Init(model,row);
    customedit->show();
}

void CustomManage::on_deletebutton_clicked()
{
    int row=ui->tableView->currentIndex().row();
    if(row<0||row>=ui->tableView->model()->rowCount()){
        return;
    }
    QSqlQuery sql;
    QString id=model->record(row).value("ID").toString();
    QString q=QString("delete from custom where customID='%1';").arg(id);
    if(sql.exec(q)){
        qDebug()<<"删除成功";
        emit deletesuppliersuccess();
    }
    else qDebug()<<"删除失败";
    flashContent();
}

void CustomManage::on_query_clicked()
{
    bool allempty = true;
    QString id = ui->idedit->text();
    allempty &=ui->idedit->text().isEmpty();

    QString agent = ui->customEdit->text();
    allempty &=ui->customEdit->text().isEmpty();

    QString phone = ui->phoneedit->text();
    allempty &=ui->phoneedit->text().isEmpty();

    QString company = ui->addressEdit->text();
    allempty &=ui->addressEdit->text().isEmpty();


    QString q;
    model->setFilter("");
    if(allempty){
        model->select();
        qDebug()<<"搜索条件全空";
    }
    else{
        qDebug()<<"含有搜索条件";
        bool isfirst = true;
        if(!ui->idedit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("ID = %1 ").arg(id);
        }
        if(!ui->customEdit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("名字 = '%1' ").arg(agent);
        }
        if(!ui->phoneedit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("手机号 = '%1' ").arg(phone);
        }
        if(!ui->addressEdit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("地址 = '%1' ").arg(company);
        }

        //按商品搜索暂未实现
        model->setFilter(q);
        model->select();
    }
}
