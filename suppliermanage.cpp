#include "suppliermanage.h"
#include "ui_suppliermanage.h"



SupplierManage::SupplierManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SupplierManage)
{
    ui->setupUi(this);
    model = new QSqlTableModel;
    model->setTable("supplierView");
    model->select();
    ui->tableView->setModel(model);
    model->select();

    supplieradd = new SupplierAdd;
    supplieredit = new SupplierEdit;
    auto f=[&](){
        flashContent();
    };
    connect(supplieradd,&SupplierAdd::addsuppliersuccess,this,f);
    connect(this,&SupplierManage::deletesuppliersuccess,this,f);
    connect(supplieredit,&SupplierEdit::editsuppliersuccess,this,f);

//    connect(this,&SupplierManage::searchChange,this,&SupplierManage::on_query_clicked);
//    connect(this,&SupplierManage::searchChange,this,&SupplierManage::on_query_clicked);
//    connect(this,&SupplierManage::searchChange,this,&SupplierManage::on_query_clicked);
//    connect(this,&SupplierManage::searchChange,this,&SupplierManage::on_query_clicked);
//    connect(this,&SupplierManage::searchChange,this,&SupplierManage::on_query_clicked);

    flashContent();



}
void SupplierManage::flashContent()
{
    model->select();
}

SupplierManage::~SupplierManage()
{
    delete ui;
}

void SupplierManage::on_addbutton_clicked()
{
    supplieradd->show();
}

void SupplierManage::on_editbutton_clicked()
{
    int currentRow=ui->tableView->currentIndex().row();
    if(!checkRowAvalid(currentRow)) return;
    supplieredit->InitEdit(model,currentRow);
    supplieredit->show();
}

void SupplierManage::on_query_clicked()
{
    bool allempty = true;
    QString id = ui->idedit->text();
    allempty &=ui->idedit->text().isEmpty();

    QString agent = ui->agenedit->text();
    allempty &=ui->agenedit->text().isEmpty();

    QString phone = ui->phoneedit->text();
    allempty &=ui->phoneedit->text().isEmpty();

    QString company = ui->companyedit->text();
    allempty &=ui->companyedit->text().isEmpty();

    QString area = ui->areaedit->text();
    allempty &=ui->areaedit->text().isEmpty();

    QString good = ui->goodscombox->currentText();
    allempty &=ui->goodscombox->currentText().isEmpty();

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
        if(!ui->agenedit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("代理人 = '%1' ").arg(agent);
        }
        if(!ui->phoneedit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("电话 = '%1' ").arg(phone);
        }
        if(!ui->companyedit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("公司名称 = '%1' ").arg(company);
        }
        if(!ui->areaedit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("产地 = '%1' ").arg(area);
        }
        //按商品搜索暂未实现
        model->setFilter(q);
        model->select();
    }

}

void SupplierManage::deleteContent(int row)
{
    if(!checkRowAvalid(row)) return;
    QSqlQuery sql;
    QString id=model->record(row).value("ID").toString();
    QString q=QString("delete from supplier where supplierID='%1';").arg(id);
    if(sql.exec(q)){
        qDebug()<<"删除成功";
        emit deletesuppliersuccess();
    }
    else qDebug()<<"删除失败";
}

void SupplierManage::on_deletebutton_clicked()
{
    int currentRow = ui->tableView->currentIndex().row();
    deleteContent(currentRow);
}

bool SupplierManage::checkRowAvalid(int row)
{
    if(row<0||row>= ui->tableView->model()->rowCount()){
        qDebug()<<"未选择有效修改条目";
        return false;
    }
    return true;
}



