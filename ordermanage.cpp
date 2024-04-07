#include "ordermanage.h"
#include "ui_ordermanage.h"

OrderManage::OrderManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderManage)
{
    ui->setupUi(this);
    orderadd = new OrderAdd;

    modelin =new QSqlTableModel;
    modelout = new QSqlTableModel;
    modelin->setTable("inorderView");
    modelout->setTable("outorderView");
    ui->intableView->setModel(modelin);
    ui->outtableView->setModel(modelout);
    modelin->select();
    modelout->select();
    index=0;
    ui->stackedWidget->setCurrentIndex(0);

    connect(orderadd,&OrderAdd::editSuccessSignal,this,&OrderManage::flashContent);
    ui->intableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->outtableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    flashContent();
}

OrderManage::~OrderManage()
{
    delete ui;
}

void OrderManage::on_switchOrder_currentIndexChanged(int index)
{
    this->index=index;
    ui->stackedWidget->setCurrentIndex(index);
    emit indexChange(index);
}

void OrderManage::InitUi(UserInfo uinfo)
{

    userinfo = uinfo;

    //初始化订单管理的客户box
    ui->custombox->clear();
    ui->custombox->addItem("所有");
    QSqlQuery sql;
    QString q = QString("select customID,customName from custom;");
    if(!sql.exec(q)){
        return;
    }
    int row=0;
    while(sql.next()){
        QString temp=sql.value(0).toString()+"-"+sql.value(1).toString();
        ui->custombox->addItem(temp);
        row++;
    }

    ui->supplierCombox->clear();
    ui->supplierCombox->addItem("所有");
    q = QString("select supplierID,supplierCompany from supplier;");
    if(!sql.exec(q)){
        return;
    }
    row=0;
    while(sql.next()){
        QString temp=sql.value(0).toString()+"-"+sql.value(1).toString();
        ui->supplierCombox->addItem(temp);
        row++;
    }
    //初始化类别

    flashContent();
}

void OrderManage::on_addOrder_clicked()
{
    orderadd->InitUi(userinfo,index);
    orderadd->show();
}

void OrderManage::flashContent()
{
    modelin->select();
    modelout->select();
}

void OrderManage::on_deleteOrder_clicked()
{
    int currentRow;
    QTableView * currentWidget=nullptr;

    if(ui->switchOrder->currentIndex()==0){
        currentWidget=ui->intableView;

    }
    else if(ui->switchOrder->currentIndex()==1){
        currentWidget=ui->outtableView;
    }
    if(currentWidget==nullptr) return;
    currentRow=currentWidget->currentIndex().row();
    if(currentRow<0||currentRow>=currentWidget->model()->rowCount()){
        return;
    }
    QSqlQuery sql;
    QString temp1;
    QString temp2;
    if(index==0){
        temp1="in";
        temp2=modelin->record(currentRow).value("采购单号").toString();
    }
    else {
        temp1="out";
        temp2=modelin->record(currentRow).value("销售单号").toString();
    }
    QString q = QString("delete from %1order where %1orderID = '%2'").arg(temp1).arg(temp2);
    if(!sql.exec(q)){
        return;
    }
    this->flashContent();
}

void OrderManage::on_query_clicked()
{
        bool allempty1 = true;
        bool allempty2 = true;
        QString id1 = ui->IDorderEdit->text();
        QString id2 = ui->IDorderEdit_2->text();
        allempty1 &=ui->IDorderEdit->text().isEmpty();
        allempty2 &=ui->IDorderEdit_2->text().isEmpty();



        allempty1 &=ui->supplierCombox->currentText().isEmpty();
        allempty2 &=ui->custombox->currentText().isEmpty();

        QString supplierID = ui->supplierCombox->currentText();
        QString customID = ui->supplierCombox->currentText();
        if(supplierID!="所有") allempty1=0;
        if(customID!="所有") allempty2=0;

        QString amount1 = ui->numberEdit->text();
        QString amountSelect1;
        allempty1 &=ui->numberEdit->text().isEmpty();
        if(!ui->numberEdit->text().isEmpty()){
            if(ui->numberCombox->currentText()=="所有"){
                amountSelect1="=";
            }
            else if(ui->numberCombox->currentText()=="大于等于"){
                amountSelect1=">=";
            }
            else {
                amountSelect1="<=";
            }

        }

        QString amount2 = ui->numberEdit_2->text();
        QString amountSelect2;
        allempty1 &=ui->numberEdit_2->text().isEmpty();
        if(!ui->numberEdit_2->text().isEmpty()){
            if(ui->numberCombox_2->currentText()=="所有"){
                amountSelect2="=";
            }
            else if(ui->numberCombox_2->currentText()=="大于等于"){
                amountSelect2=">=";
            }
            else {
                amountSelect2="<=";
            }

        }

        QString value1 = ui->valueEdit->text();
        QString valueSelect1;
        allempty1 &=ui->valueEdit->text().isEmpty();
        if(!ui->valueEdit->text().isEmpty()){
            if(ui->valueCombox->currentText()=="所有"){
                valueSelect1="=";
            }
            else if(ui->valueCombox->currentText()=="大于等于"){
                valueSelect1=">=";
            }
            else {
                valueSelect1="<=";
            }

        }

        QString value2 = ui->valueEdit_2->text();
        QString valueSelect2;
        allempty2 &=ui->valueEdit_2->text().isEmpty();
        if(!ui->valueEdit_2->text().isEmpty()){
            if(ui->valueCombox_2->currentText()=="所有"){
                valueSelect2="=";
            }
            else if(ui->valueCombox_2->currentText()=="大于等于"){
                valueSelect2=">=";
            }
            else {
                valueSelect2="<=";
            }

        }


        QString q1,q2;
        modelin->setFilter("");
        modelout->setFilter("");

        if(allempty1){
            modelin->select();
            qDebug()<<"in搜索条件全空";
        }
        else{
            qDebug()<<"in含有搜索条件";
            bool isfirst = true;
            if(!ui->IDorderEdit->text().isEmpty()){
                if(!isfirst) q1+="and ";
                else isfirst = false;
                q1+=QString(" ID = %1 ").arg(id1);
            }
            if(!ui->numberEdit->text().isEmpty()){
                if(!isfirst) q1+="and ";
                else isfirst = false;
                q1+=QString("入库数量 %2 '%1' ").arg(amount1).arg(amountSelect1);
            }

            if(!ui->valueEdit->text().isEmpty()){
                if(!isfirst) q1+="and ";
                else isfirst = false;
                q1+=QString("采购金额 %2 '%1' ").arg(value1).arg(valueSelect1);
            }

            //按商品搜索暂未实现
            modelin->setFilter(q1);
            modelin->select();
            modelout->setFilter(q2);
            modelout->select();
        }
}

void OrderManage::on_query_2_clicked()
{
    on_query_clicked();
}

void OrderManage::on_detailButton_clicked()
{
    int row;
    if(index==0){
        row=ui->intableView->currentIndex().row();
        if(row<0||row>=ui->intableView->model()->rowCount()){
            return;
        }

    }
    else if(index==1){
        row=ui->outtableView->currentIndex().row();
        if(row<0||row>=ui->outtableView->model()->rowCount()){
            return;
        }
    }

}
