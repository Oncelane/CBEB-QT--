#ifndef CHOOSEAMOUNT_H
#define CHOOSEAMOUNT_H

#include <QWidget>

namespace Ui {
class ChooseAmount;
}

class ChooseAmount : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseAmount(QWidget *parent = nullptr);
    ~ChooseAmount();

private:
    Ui::ChooseAmount *ui;
};

#endif // CHOOSEAMOUNT_H
