#ifndef ADDGOODTOSTASHORDER_PAGE_H
#define ADDGOODTOSTASHORDER_PAGE_H

#include <QWidget>

namespace Ui {
class addgoodToStashOrder_page;
}

class addgoodToStashOrder_page : public QWidget
{
    Q_OBJECT

public:
    explicit addgoodToStashOrder_page(QWidget *parent = nullptr);
    ~addgoodToStashOrder_page();

private:
    Ui::addgoodToStashOrder_page *ui;
};

#endif // ADDGOODTOSTASHORDER_PAGE_H
