#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //页面设置
    Init();

    homepage = new HomePage;
    ordermanage = new OrderManage;
    goodmanage = new GoodManage;
    stashmanage = new StashManage;
    stashandgoodpage = new StashAndGoodPage;
    suppliermanage = new SupplierManage;
    custommanage = new CustomManage;
    loginpage = new  LoginPage;



    ui->stackedWidget->insertWidget(0,homepage);
    ui->stackedWidget->insertWidget(1,ordermanage);
    ui->stackedWidget->insertWidget(2,goodmanage);
    ui->stackedWidget->insertWidget(3,stashmanage);
    ui->stackedWidget->insertWidget(4,stashandgoodpage);
    ui->stackedWidget->insertWidget(5,suppliermanage);
    ui->stackedWidget->insertWidget(6,custommanage);
    ui->stackedWidget->setCurrentIndex(0);

    //用户配置
    userinfo.name="root";
    userinfo.id=58;
    userinfo.identity="root";

    //用户信息传入主窗口
    connect(loginpage,&LoginPage::LoginSuccess,this,&MainWindow::userInit);
    //切换
    connect(ui->actionhomepage,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->actiongoodmanege,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->actionstashmanage,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->actionStashAndGood,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->actionordermanage,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->actionsuppliermanage,&QAction::triggered,this,&MainWindow::switchPages);
    connect(ui->actioncustommanage,&QAction::triggered,this,&MainWindow::switchPages);

    //绑定一下计时器，给stashadd更新时间
    auto timeupdate = [&](){
        MainWindow::stashmanage->stashaddpage->updatetime();
        MainWindow::ordermanage->orderadd->updatetime();
    };
    connect(timer,&QTimer::timeout,this,timeupdate);
    connect(loginpage,&LoginPage::LoginSuccess,this,[&](){
        showMaximized();
    });
    //进入登录界面

    showMinimized();

    loginpage->show();

    }

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setIndexUP(int index){
    if(index==0) ui->actionhomepage->setChecked(1);
    else ui->actionhomepage->setChecked(0);
    if(index==2) ui->actiongoodmanege->setChecked(1);
    else ui->actiongoodmanege->setChecked(0);
    if(index==3) ui->actionstashmanage->setChecked(1);
    else ui->actionstashmanage->setChecked(0);
    if(index==4) ui->actionStashAndGood->setChecked(1);
    else ui->actionStashAndGood->setChecked(0);
    if(index==1) ui->actionordermanage->setChecked(1);
    else ui->actionordermanage->setChecked(0);
    if(index==5) ui->actionsuppliermanage->setChecked(1);
    else ui->actionsuppliermanage->setChecked(0);
    if(index==6) ui->actioncustommanage->setChecked(1);
    else ui->actioncustommanage->setChecked(0);

}
void MainWindow::switchPages()
{
QAction *action = qobject_cast<QAction *>(sender());
if(action->text() == "主页介绍"){
   ui->stackedWidget->setCurrentIndex(0);
   setIndexUP(0);
}

else if(action->text() == "订单管理"){
    ordermanage->InitUi(userinfo);
    ui->stackedWidget->setCurrentIndex(1);
    setIndexUP(1);
}

else if(action->text() == "货品管理"){
    goodmanage->Init();
    ui->stackedWidget->setCurrentIndex(2);
    setIndexUP(2);
}
else if(action->text() == "仓库出入管理"){
    stashmanage->Init(userinfo);
    ui->stackedWidget->setCurrentIndex(3);
    setIndexUP(3);
}

else if(action->text() == "仓库信息")
{
    stashandgoodpage->InitUi();
    ui->stackedWidget->setCurrentIndex(4);
    setIndexUP(4);
}
else if(action->text() == "供应商管理"){
     ui->stackedWidget->setCurrentIndex(5);
     setIndexUP(5);
}

else if(action->text() == "客户管理"){
     ui->stackedWidget->setCurrentIndex(6);
     setIndexUP(6);
}

}

void MainWindow::InitDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    if(db.isValid())
    {
//        QMessageBox::information(this, "conn", "ok");
    }
    else
    {
//        QMessageBox::information(this, "conn", "error");
    }
    db.setHostName("localhost"); // 本地连接
    db.setPort(3306);       // 如果使用的是默认端口可以不设置
    db.setUserName("root");	// 数据库用户名
    db.setPassword("xxx"); // 数据库密码
    db.setDatabaseName("cbebusiness"); // 数据库名字
    if(db.open())
    {
//        QMessageBox::information(this, "打开数据库", "数据库打开成功, 可以读写数据了......");
    }
    else
    {
//        QString msg = "数据库打开失败: " + db.lastError().text();
//        QMessageBox::information(this, "打开数据库", msg);
    }

}

void MainWindow::userInit(int ID)
{
    userinfo.id=ID;
    QSqlQuery sql;
    QString q = QString("select userName,userIdentity from login_user where userID = '%1';").arg(ID);
    if(!sql.exec(q)) qDebug()<<"查询失败";
    sql.next();
    userinfo.name=sql.value(0).toString();
    userinfo.identity=sql.value(1).toString();
}

void MainWindow::Init()
{
    InitDatabase();
    timer->start(1000);
}
