#ifndef SUPPLIEREDIT_H
#define SUPPLIEREDIT_H

#include <QWidget>
#include <sqlhead.h>

namespace Ui {
class SupplierEdit;
}

class SupplierEdit : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierEdit(QWidget *parent = nullptr);
    ~SupplierEdit();
    void InitEdit(QSqlTableModel *,int );

private slots:
    void on_doneButton_clicked();

private:
    Ui::SupplierEdit *ui;

signals:
    void editsuppliersuccess();

};

#endif // SUPPLIEREDIT_H
