#ifndef EMPLOYEEMANAGE_H
#define EMPLOYEEMANAGE_H

#include <QWidget>

namespace Ui {
class EmployeeManage;
}

class EmployeeManage : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeManage(QWidget *parent = nullptr);
    ~EmployeeManage();

private:
    Ui::EmployeeManage *ui;
};

#endif // EMPLOYEEMANAGE_H
