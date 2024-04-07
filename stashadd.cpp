#include "stashadd.h"
#include "ui_stashadd.h"



stashadd::stashadd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stashadd)
{
    ui->setupUi(this);
    simpleeditpage = new simpleEditPage;
    //修改一个条目的数量和价格
    connect(simpleeditpage,&simpleEditPage::EditSuccess,this,&stashadd::getedit);
    //修改金额总数
    connect(this,&stashadd::priceChangeSignal,this,&stashadd::updateDownPrice);

    ui->availableTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->selectGoodTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

stashadd::~stashadd()
{
    delete ui;
}

void stashadd::on_cancelButton_clicked()
{
    this->hide();
}
    //页面初始化
void stashadd::InitUI(UserInfo uinfo,int index)
{
    //修改实现入库，出库页面切换
    this->index=index;
    if(index==0){
        ui->IDLable->setText("入库单号");
        ui->StashLable->setText("入库仓库");
    }
    else if (index==1){
        ui->IDLable->setText("出库单号");
        ui->StashLable->setText("出库仓库");
    }

    //清除上次留下的信息
    ui->selectGoodTableWidget->setRowCount(0);
    ui->amountEdit->setText(nullptr);
    ui->valueEdit->setText(nullptr);
    ui->totalPriceEdit->setText(nullptr);

    QSqlQuery sql;
    QString q;



   if(index==0){
       //添加入库仓库可选的仓库选项
       ui->selectstashCombox->clear();
       q = QString("select stashID,stashName from stash;");
       sql.exec(q);
       while(sql.next()){
           QString temp = sql.value(0).toString()+"-"+sql.value(1).toString();
           ui->selectstashCombox->addItem(temp);
       }
       //添加可选商品的商品选项
       ui->availableTableWidget->setRowCount(0);
       q = QString("select * from InStashAvailableGood");
       sql.exec(q);
       int row=0;
       while(sql.next()){
           ui->availableTableWidget->insertRow(row);
           for(int i=0;i<sql.record().count();i++){
               QTableWidgetItem *item= new QTableWidgetItem(sql.value(i).toString());
               ui->availableTableWidget->setItem(row,i,item);
           }
           row++;
       }
   }
    else{
       //添加出库仓库可选的仓库选项
       ui->selectstashCombox->clear();
       ui->selectstashCombox->addItem("所有");
       q = QString("select DISTINCT stashID,所属仓库 from stash,OutStashAvailableGood where stash.stashName=OutStashAvailableGood.所属仓库;");
       sql.exec(q);
       while(sql.next()){
           QString temp = sql.value(0).toString()+"-"+sql.value(1).toString();
           ui->selectstashCombox->addItem(temp);
       }
       //添加可选商品的商品选项
       ui->availableTableWidget->setRowCount(0);
       q = QString("select * from OutStashAvailableGood");
       sql.exec(q);
       int row=0;
       while(sql.next()){
           ui->availableTableWidget->insertRow(row);
           for(int i=0;i<sql.record().count();i++){
               QTableWidgetItem *item= new QTableWidgetItem(sql.value(i).toString());
               ui->availableTableWidget->setItem(row,i,item);
           }
           row++;
       }
   }
    //初始化制单人信息
    userinfo = uinfo;

    //修改制单人
    ui->userNameEdit->setText(userinfo.name);


}
    //添加商品
void stashadd::on_addButton_clicked()
{
    auto checkleftrow = [&](int row){
        if(row<0||row>ui->availableTableWidget->rowCount()){
            qDebug()<<"未选择有效修改条目";
            return false;
        }
        return true;
    };
    int row=ui->availableTableWidget->currentRow();
    //判断选择生效
    if(!checkleftrow(row)) return;
    //获取数量
    int amount = 1;
    if(!ui->amountEdit->text().isEmpty()){
         amount = ui->amountEdit->text().toInt();
    }
    //获取商品ID
    QTableWidgetItem *a= new QTableWidgetItem(ui->availableTableWidget->item(row,0)->text());
    QTableWidgetItem *b= new QTableWidgetItem(ui->availableTableWidget->item(row,1)->text());
    QTableWidgetItem *c= new QTableWidgetItem(ui->availableTableWidget->item(row,2)->text());
    QTableWidgetItem *d= new QTableWidgetItem(ui->availableTableWidget->item(row,4)->text());
    //并且添加到right表中
    int newrow = ui->selectGoodTableWidget->rowCount();
    ui->selectGoodTableWidget->insertRow(newrow);
    ui->selectGoodTableWidget->setItem(newrow,0,a);
    ui->selectGoodTableWidget->setItem(newrow,1,b);
    ui->selectGoodTableWidget->setItem(newrow,2,c);
    ui->selectGoodTableWidget->setItem(newrow,4,d);

    //设置已选商品数量 商品单价 总价
    QTableWidgetItem *item = new QTableWidgetItem;
    QString amountstring = QString("%1").arg(amount);
    item->setText(amountstring);
    ui->selectGoodTableWidget->setItem(newrow,3,item);

    //设置单价
    QString value;
    if(ui->valueEdit->text().isEmpty()){
        value=ui->availableTableWidget->item(row,5)->text();
    }
    else value=ui->valueEdit->text();
    QTableWidgetItem *item2 = new QTableWidgetItem(value);
    ui->selectGoodTableWidget->setItem(newrow,5,item2);

    //设置总价
    float totalvalue;
    float valuef;
    valuef=value.toFloat();
    totalvalue = amount * valuef;
    QString temp = QString("%1").arg(totalvalue);
    QTableWidgetItem *item3 = new QTableWidgetItem(temp);
    ui->selectGoodTableWidget->setItem(newrow,6,item3);

    emit priceChangeSignal();
}

    //打开修改界面
void stashadd::on_editButton_clicked()
{
    //检查选择条目有效
    int row = ui->selectGoodTableWidget->currentRow();
    if(!checkrightrow(row)) return;
    //修改开始
    QString amount,value;
    amount = ui->selectGoodTableWidget->item(row,3)->text();
    value = ui->selectGoodTableWidget->item(row,5)->text();
    simpleeditpage->Init(row,amount,value);
    simpleeditpage->show();
    //修改结束，更新总价格
}

    //修改一个条目的单价和数量
void stashadd::getedit(int row,QString amount,QString value)
{
    ui->selectGoodTableWidget->item(row,3)->setText(amount);
    ui->selectGoodTableWidget->item(row,5)->setText(value);
    updateTotalPrice(row);
}
    //更新一个条目的总价格
void stashadd::updateTotalPrice(int row)
{
    int amount=ui->selectGoodTableWidget->item(row,3)->text().toInt();
    float value=ui->selectGoodTableWidget->item(row,5)->text().toFloat();
    QString temp = QString("%1").arg(amount*value);
    ui->selectGoodTableWidget->item(row,6)->setText(temp);
    emit priceChangeSignal();
}
    //删除一个商品
void stashadd::on_deleteButton_clicked()
{
    //检查选择条目有效
    int row = ui->selectGoodTableWidget->currentRow();
    if(!checkrightrow(row)) return;
    //删除操作
    ui->selectGoodTableWidget->removeRow(row);
    emit priceChangeSignal();
}
    //检查选择条目
bool stashadd::checkrightrow(int row)
{
    if(row<0||row>ui->selectGoodTableWidget->rowCount()){
        qDebug()<<"未选择有效修改条目";
        return false;
     }
    return true;
}
    //清空商品
void stashadd::on_clearAllButton_clicked()
{
    int row=ui->selectGoodTableWidget->rowCount();
    for(int i=0;i<row;i++){
        ui->selectGoodTableWidget->removeRow(0);
    }
    emit priceChangeSignal();
}
    //将当前页面信息加入到in、out数据库中
void stashadd::on_doneButton_clicked()
{
    QSqlQuery sql;
    QString q;
    if(index==0){
        //创建入库单
        QString stashID,createTime;
        stashID=ui->selectstashCombox->currentText().section('-',0,0);
        int userID = userinfo.id;
        createTime = ui->timeEdit->text().section(' ',0,1);
        q=QString("insert into instashorder(stashID, userID, createTime) values('%1','%2',STR_TO_DATE('%3', '%Y-%m-%d %H:%i:%s'));").arg(stashID).arg(userID).arg(createTime);
        if(!sql.exec(q)){
             //emit sqlfail();
            return ;
        }
        //拿到入库单号
        q=QString("select instashorderID  from instashorder order by createTime DESC limit 1;");
        sql.exec(q);
        sql.next();
        QString instashorederID =sql.value(0).toString();

        //创建入库单子单
        int rowCount = ui->selectGoodTableWidget->rowCount();
        for(int i=0;i<rowCount;i++){
            QString goodid=ui->selectGoodTableWidget->item(i,0)->text();
            QString amount=ui->selectGoodTableWidget->item(i,3)->text();
            QString value=ui->selectGoodTableWidget->item(i,5)->text();
            QString q=QString("insert into instashorderlinkgood (instashorderID, goodid, amount, value) values ('%1','%2','%3','%4');").arg(instashorederID).arg(goodid).arg(amount).arg(value);
            sql.exec(q);
        }
    }
    else if (index==1){
        //创建出库单
        QString stashID,createTime;
        stashID=ui->selectstashCombox->currentText().section('-',0,0);
        int userID = userinfo.id;
        createTime = ui->timeEdit->text().section(' ',0,1);
        q=QString("insert into outstashorder(stashID, userID, createTime) values('%1','%2',STR_TO_DATE('%3', '%Y-%m-%d %H:%i:%s'));").arg(stashID).arg(userID).arg(createTime);
        if(!sql.exec(q)){
             //emit sqlfail();
            return ;
        }
        //拿到出库单号
        q=QString("select outstashorderID  from outstashorder order by createTime DESC limit 1;");
        sql.exec(q);
        sql.next();
        QString outstashorederID =sql.value(0).toString();

        //创建出库单子单
        int rowCount = ui->selectGoodTableWidget->rowCount();
        for(int i=0;i<rowCount;i++){
            QString goodid=ui->selectGoodTableWidget->item(i,0)->text();
            QString amount=ui->selectGoodTableWidget->item(i,3)->text();
            QString value=ui->selectGoodTableWidget->item(i,5)->text();
            QString q=QString("insert into outstashorderlinkgood (outstashorderID, goodid, amount, value) values ('%1','%2','%3','%4');").arg(outstashorederID).arg(goodid).arg(amount).arg(value);
            sql.exec(q);
        }
    }
    emit editSuccessSignal();
    this->hide();
}
    //修改时间
void stashadd::updatetime()
{
    ui->timeEdit->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd"));
}
    //修改总价格
void stashadd::updateDownPrice()
{
    int row=ui->selectGoodTableWidget->rowCount();
    float totalprice=0;
    for(int i=0;i<row;i++){
        totalprice+=ui->selectGoodTableWidget->item(i,6)->text().toFloat();
    }
    ui->totalPriceEdit->setText(QString("%1").arg(totalprice));
}

void stashadd::on_selectstashCombox_currentTextChanged(const QString &arg1)
{
    if(index==0) return;
    QString stash=arg1;
    if(arg1=="所有"){
        //添加可选商品的商品选项
        ui->availableTableWidget->setRowCount(0);
        QSqlQuery sql;
        QString q = QString("select * from OutStashAvailableGood");
        sql.exec(q);
        int row=0;
        while(sql.next()){
            ui->availableTableWidget->insertRow(row);
            for(int i=0;i<sql.record().count();i++){
                QTableWidgetItem *item= new QTableWidgetItem(sql.value(i).toString());
                ui->availableTableWidget->setItem(row,i,item);
            }
            row++;
        }
    }
    else{
        QString stashName=stash.section('-',1,1);
        //添加可选商品的商品选项
        ui->availableTableWidget->setRowCount(0);
        QSqlQuery sql;
        QString q = QString("select * from OutStashAvailableGood where 所属仓库 = '%1'").arg(stashName);
        sql.exec(q);
        int row=0;
        while(sql.next()){
            ui->availableTableWidget->insertRow(row);
            for(int i=0;i<sql.record().count();i++){
                QTableWidgetItem *item= new QTableWidgetItem(sql.value(i).toString());
                ui->availableTableWidget->setItem(row,i,item);
            }
            row++;
        }
    }
}
