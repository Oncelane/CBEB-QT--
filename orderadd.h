#ifndef ORDERADD_H
#define ORDERADD_H

#include <QWidget>
#include <sqlhead.h>
#include <simpleeditpage.h>
namespace Ui {
class OrderAdd;
}

class OrderAdd : public QWidget
{
    Q_OBJECT

public:
    explicit OrderAdd(QWidget *parent = nullptr);
    ~OrderAdd();
    void InitUi(UserInfo,int);
private:
    Ui::OrderAdd *ui;
    UserInfo userinfo;
    int index;
    simpleEditPage *simpleeditpage;
    void updateDownPrice();
    void updateTotalPrice(int row);
    bool checkrightrow(int);
signals:
    void priceChangeSignal();
    void editSuccessSignal();

private slots:
    void on_addButton_clicked();
    void on_editButton_clicked();
    void on_deleteButton_clicked();
    void on_doneButton_clicked();

    void on_cancelButton_clicked();

    void on_clearAllButton_clicked();

public slots:
    void getedit(int row,QString amount,QString value);
    void updatetime();
};

#endif // ORDERADD_H
