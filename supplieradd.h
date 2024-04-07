#ifndef SUPPLIERADD_H
#define SUPPLIERADD_H

#include <QWidget>
#include <sqlhead.h>

namespace Ui {
class SupplierAdd;
}

class SupplierAdd : public QWidget
{
    Q_OBJECT

public:
    explicit SupplierAdd(QWidget *parent = nullptr);
    ~SupplierAdd();

private slots:

    void on_doneButton_clicked();

private:
    Ui::SupplierAdd *ui;
signals:
    void addsuppliersuccess();
};

#endif // SUPPLIERADD_H
