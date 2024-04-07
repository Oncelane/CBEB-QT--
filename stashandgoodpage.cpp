#include "stashandgoodpage.h"
#include "ui_stashandgoodpage.h"

StashAndGoodPage::StashAndGoodPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StashAndGoodPage)
{
    ui->setupUi(this);

    model = new QSqlTableModel;
    model->setTable("stashandgood");
    ui->tableView->setModel(model);
    model->select();

    connect(this,&StashAndGoodPage::flash,this,&StashAndGoodPage::flashContent);

}

StashAndGoodPage::~StashAndGoodPage()
{
    delete ui;
}

void StashAndGoodPage::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1=="所有"){
        model->setFilter("");
    }
    else {
        QString stash=arg1,q;
        q="仓库 =  '" + stash.section('-',1,1)+"'";
        model->setFilter(q);
        model->select();
    }
    emit flash();
}

void StashAndGoodPage::InitUi()
{
    //添加入库仓库可选的仓库选项
    QSqlQuery sql;
    QString q;
    ui->comboBox->clear();
    ui->comboBox->addItem("所有");
    q = QString("select stashID,stashName from stash;");
    sql.exec(q);
    while(sql.next()){
        QString temp = sql.value(0).toString()+"-"+sql.value(1).toString();
        ui->comboBox->addItem(temp);
    }
}

void StashAndGoodPage::flashContent()
{
    model->select();
}
