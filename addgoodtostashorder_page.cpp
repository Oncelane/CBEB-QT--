#include "addgoodtostashorder_page.h"
#include "ui_addgoodtostashorder_page.h"

addgoodToStashOrder_page::addgoodToStashOrder_page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addgoodToStashOrder_page)
{
    ui->setupUi(this);
}

addgoodToStashOrder_page::~addgoodToStashOrder_page()
{
    delete ui;
}
