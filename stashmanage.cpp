#include "stashmanage.h"
#include "ui_stashmanage.h"

StashManage::StashManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StashManage)
{
    ui->setupUi(this);
    stashaddpage = new stashadd;
    connect(stashaddpage,&stashadd::editSuccessSignal,this,&StashManage::flashContent);
    ui->intableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->outtableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

StashManage::~StashManage()
{
    delete ui;
}

void StashManage::on_switchStash_currentIndexChanged(int index)
{
    stashaddpage->index=index;
    currentIndex=index;
    ui->stackedWidget->setCurrentIndex(index);
}

void StashManage::on_addStash_clicked()
{
    stashaddpage->InitUI(userinfo,currentIndex);
    stashaddpage->show();
}

void StashManage::Init(UserInfo userinfo)
{
    this->userinfo = userinfo;
    flashContent();
}

void StashManage::on_deleteStash_clicked()
{
    int currentRow;
    QTableWidget * currentWidget=nullptr;

    if(ui->switchStash->currentIndex()==0){
        currentWidget=ui->intableWidget;

    }
    else if(ui->switchStash->currentIndex()==1){
        currentWidget=ui->outtableWidget;
    }
    if(currentWidget==nullptr) return;
    currentRow=currentWidget->currentRow();
    if(currentRow<0||currentRow>=currentWidget->rowCount()){
        return;
    }
    QSqlQuery sql;
    QString q = QString("delete from %1stashorder where %1stashorderID = '%2'").arg(currentIndex==0?"in":"out").arg(currentWidget->item(currentRow,0)->text());
    if(!sql.exec(q)){
        return;
    }
    this->flashContent();
}

void StashManage::flashContent()
{
    QSqlQuery sql;
    QString q="select * from instashorderView";
    sql.exec(q);
    ui->intableWidget->setRowCount(0);
    int row=0;
    while(sql.next()){
        ui->intableWidget->insertRow(row);
        for(int i=0;i<sql.record().count();i++){
            QTableWidgetItem *item= new QTableWidgetItem(sql.value(i).toString());
            ui->intableWidget->setItem(row,i,item);
        }
        row++;
    }
    q="select * from outstashorderView";
    sql.exec(q);
    ui->outtableWidget->setRowCount(0);
    row=0;
    while(sql.next()){
        ui->outtableWidget->insertRow(row);
        for(int i=0;i<sql.record().count();i++){
            QTableWidgetItem *item= new QTableWidgetItem(sql.value(i).toString());
            ui->outtableWidget->setItem(row,i,item);
        }
        row++;
    }
}
