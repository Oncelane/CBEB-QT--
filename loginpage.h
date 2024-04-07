#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <sqlhead.h>
namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:

    void on_loginButton_clicked();

private:
    Ui::LoginPage *ui;
signals:
    void LoginSuccess(int id);
};

#endif // LOGINPAGE_H
