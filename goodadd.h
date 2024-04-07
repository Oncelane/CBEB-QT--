#ifndef GOODADD_H
#define GOODADD_H

#include <QWidget>
#include <sqlhead.h>
namespace Ui {
class GoodAdd;
}

class GoodAdd : public QWidget
{
    Q_OBJECT

public:
    explicit GoodAdd(QWidget *parent = nullptr);
    ~GoodAdd();
    void InitUi();

private slots:
    void on_editButton_clicked();

    void on_doneButton_clicked();

private:
    Ui::GoodAdd *ui;

signals:
    void success();

};

#endif // GOODADD_H
