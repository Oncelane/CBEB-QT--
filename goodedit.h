#ifndef GOODEDIT_H
#define GOODEDIT_H

#include <QWidget>
#include <sqlhead.h>
namespace Ui {
class GoodEdit;
}

class GoodEdit : public QWidget
{
    Q_OBJECT

public:
    explicit GoodEdit(QWidget *parent = nullptr);
    ~GoodEdit();
    void InitUi();
    void InitEdit(QSqlTableModel *,int);

private:
    Ui::GoodEdit *ui;

signals:
    void success();

private slots:
    void on_doneButton_clicked();
};

#endif // GOODEDIT_H
