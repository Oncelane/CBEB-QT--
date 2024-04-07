#ifndef GOODMANAGE_H
#define GOODMANAGE_H

#include <QWidget>
#include <goodadd.h>
#include <goodedit.h>


namespace Ui {
class GoodManage;
}

class GoodManage : public QWidget
{
    Q_OBJECT

public:
    explicit GoodManage(QWidget *parent = nullptr);
    ~GoodManage();

    void Init();
private slots:
    void on_addGood_clicked();

    void on_editGood_clicked();

    void on_deleteGood_clicked();

    void on_query_clicked();

private:
    Ui::GoodManage *ui;
    GoodAdd *goodadd;
    GoodEdit *goodedit;
    QSqlTableModel *model;
    void flashContent();
    void deleteContent(int row);
    void editContent();
    bool checkRowAvalid(int row);

signals:
    void deletegoodsuccess();
    void turntoGoodManage();
};

#endif // GOODMANAGE_H
