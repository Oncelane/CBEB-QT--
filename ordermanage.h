#ifndef ORDERMANAGE_H
#define ORDERMANAGE_H

#include <QWidget>
#include <sqlhead.h>
#include <orderadd.h>

namespace Ui {
class OrderManage;
}

class OrderManage : public QWidget
{
    Q_OBJECT

public:
    explicit OrderManage(QWidget *parent = nullptr);
    ~OrderManage();
    void InitUi(UserInfo);
    OrderAdd *orderadd;
private slots:
    void on_switchOrder_currentIndexChanged(int index);

    void on_addOrder_clicked();

    void on_deleteOrder_clicked();

    void on_query_clicked();

    void on_query_2_clicked();

    void on_detailButton_clicked();

private:
    Ui::OrderManage *ui;
    QSqlTableModel *modelin,*modelout;
    int index;
    UserInfo userinfo;
    void flashContent();

signals:
    void indexChange(int index);

};

#endif // ORDERMANAGE_H
