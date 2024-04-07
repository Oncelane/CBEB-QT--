#ifndef SUPPLIERMANAGE_H
#define SUPPLIERMANAGE_H

#include <QWidget>
#include <supplieradd.h>
#include <supplieredit.h>

namespace Ui {
class SupplierManage;
}

class SupplierManage : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierManage(QWidget *parent = nullptr);
    ~SupplierManage();

private slots:
    void on_addbutton_clicked();

    void on_editbutton_clicked();

    void on_query_clicked();

    void on_deletebutton_clicked();


private:
    Ui::SupplierManage *ui;
    SupplierAdd *supplieradd;
    SupplierEdit *supplieredit;

    QSqlTableModel *model;

    void flashContent();
    void deleteContent(int row);
    void editContent();
    bool checkRowAvalid(int row);
signals:
    void deletesuppliersuccess();
    void searchChange();

};

#endif // SUPPLIERMANAGE_H
