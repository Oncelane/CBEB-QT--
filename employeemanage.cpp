#include "employeemanage.h"
#include "ui_employeemanage.h"

EmployeeManage::EmployeeManage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeManage)
{
    ui->setupUi(this);
}

EmployeeManage::~EmployeeManage()
{
    delete ui;
}
