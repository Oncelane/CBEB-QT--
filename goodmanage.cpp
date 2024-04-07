#include "goodmanage.h"
#include "ui_goodmanage.h"


GoodManage::GoodManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GoodManage)
{
    ui->setupUi(this);

    goodadd = new GoodAdd;
    goodedit = new GoodEdit;
    model = new QSqlTableModel;
    model->setTable("ProductInventoryView");
    ui->tableView->setModel(model);
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(goodadd,&GoodAdd::success,this,&GoodManage::flashContent);
    connect(goodedit,&GoodEdit::success,this,&GoodManage::flashContent);
    connect(this,&GoodManage::deletegoodsuccess,this,&GoodManage::flashContent);

    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    ui->tableView->setSelectionModel(selectionModel);
}

GoodManage::~GoodManage()
{
    delete ui;
}

void GoodManage::on_addGood_clicked()
{
    goodadd->InitUi();
    goodadd->show();
}


void GoodManage::flashContent()
{
    model->select();
}

void GoodManage::on_editGood_clicked()
{
    int row=ui->tableView->currentIndex().row();
    if(row<0||row>=ui->tableView->model()->rowCount()){
        return;
    }
    goodedit->InitUi();
    goodedit->InitEdit(model,row);
    goodedit->show();
}

void GoodManage::Init()
{
    flashContent();
}



void GoodManage::on_deleteGood_clicked()
{
    int row = ui->tableView->currentIndex().row();
    if(row<0||row>=ui->tableView->model()->rowCount()){
        return;
    }
    QSqlQuery sql;
    QString id=model->record(row).value("货品编码").toString();
    QString q=QString("delete from goods where goodID='%1';").arg(id);
    if(sql.exec(q)){
        qDebug()<<"删除成功";
        emit deletegoodsuccess();
    }
    else qDebug()<<"删除失败";
}



void GoodManage::on_query_clicked()
{
    bool allempty = true;
    QString id = ui->IDEdit->text();
    allempty &=ui->IDEdit->text().isEmpty();

    QString name = ui->nameEdit->text();
    allempty &=ui->nameEdit->text().isEmpty();

    QString price = ui->priceEdit->text();
    QString priceSelect="=";
    if(!ui->priceEdit->text().isEmpty()){
            allempty=0;
        if(ui->priceCombox->currentText()=="大于等于"){
            priceSelect=">=";
        }
        else if(ui->priceCombox->currentText() =="小于等于"){
            priceSelect="<=";
        }
    }

    QString inprice = ui->inpriceEdit->text();
    QString inpriceSelect="=";
    if(!ui->inpriceEdit->text().isEmpty()){
            allempty=0;
        if(ui->inpriceCombox->currentText()=="大于等于"){
            inpriceSelect=">=";
        }
        else if(ui->inpriceCombox->currentText() =="小于等于"){
            inpriceSelect="<=";
        }
    }
    QString outprice = ui->outpriceEdit->text();
    QString outpriceSelect="=";
    if(!ui->outpriceEdit->text().isEmpty()){
            allempty=0;
        if(ui->outpirceCombox->currentText()=="大于等于"){
            outpriceSelect=">=";
        }
        else if(ui->outpirceCombox->currentText() =="小于等于"){
            outpriceSelect="<=";
        }
    }

    QString q;
    model->setFilter("");
    if(allempty){
        model->select();
        qDebug()<<"搜索条件全空";
    }
    else{
        qDebug()<<"含有搜索条件";
        bool isfirst = true;
        if(!ui->IDEdit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("货品编码= %1 ").arg(id);
        }
        if(!ui->nameEdit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("货品名称 = '%1' ").arg(name);
        }
        if(!ui->priceEdit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("参考价格 %1 %2").arg(priceSelect).arg(price);
        }
        if(!ui->inpriceEdit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("平均购入价格 %1 %2").arg(inpriceSelect).arg(inprice);
        }
        if(!ui->outpriceEdit->text().isEmpty()){
            if(!isfirst) q+="and ";
            else isfirst = false;
            q+=QString("平均出售价格 %1 %2").arg(outpriceSelect).arg(outprice);
        }
        //按商品搜索暂未实现
        model->setFilter(q);
        model->select();
    }
}
