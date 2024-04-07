#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <homepage.h>
#include <goodmanage.h>
#include <ordermanage.h>
#include <stashmanage.h>
#include <suppliermanage.h>
#include <custommanage.h>
#include <loginpage.h>
#include <qtimer.h>
#include <stashandgoodpage.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackWidget;
    HomePage * homepage;
    GoodManage *goodmanage;
    StashManage *stashmanage;
    OrderManage *ordermanage;
    SupplierManage *suppliermanage;
    CustomManage *custommanage;
    LoginPage *loginpage;
    UserInfo userinfo;
    StashAndGoodPage *stashandgoodpage;
    QTimer *timer = new QTimer;

    void switchPages();
    void InitDatabase();
    void userInit(int ID);
    void Init();
    void setIndexUP(int index);
};
#endif // MAINWINDOW_H
