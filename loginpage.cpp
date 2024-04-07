#include "loginpage.h"
#include "ui_loginpage.h"

LoginPage::LoginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}



void LoginPage::on_loginButton_clicked()
{
    if(ui->nameEdit->text().isEmpty()){
        qDebug()<<"请输入有效用户名";
        return;
    }
    QSqlQuery sql;
    QString q;
    q=QString("select userPassword,userID,userIdentity from login_user where userName = '%1';").arg(ui->nameEdit->text());
    if(!sql.exec(q)) return;
    sql.next();
    QString passwordB=sql.value(0).toString();
    if(passwordB==ui->passwordEdit->text()){
        qDebug()<<"成功登录";
        this->hide();
        emit LoginSuccess(sql.value(1).toInt());
    }
    else qDebug()<<"密码错误";


}
