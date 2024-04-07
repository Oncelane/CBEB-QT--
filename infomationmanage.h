#ifndef INFOMATIONMANAGE_H
#define INFOMATIONMANAGE_H

#include <QWidget>

namespace Ui {
class InfomationManage;
}

class InfomationManage : public QWidget
{
    Q_OBJECT

public:
    explicit InfomationManage(QWidget *parent = nullptr);
    ~InfomationManage();

private:
    Ui::InfomationManage *ui;
};

#endif // INFOMATIONMANAGE_H
