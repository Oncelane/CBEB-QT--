#ifndef CUSTOMEDIT_H
#define CUSTOMEDIT_H

#include <QWidget>
#include <sqlhead.h>
namespace Ui {
class CustomEdit;
}

class CustomEdit : public QWidget
{
    Q_OBJECT

public:
    explicit CustomEdit(QWidget *parent = nullptr);
    ~CustomEdit();
    void Init(QSqlTableModel*,int);
private slots:
    void on_doneButton_clicked();

private:
    Ui::CustomEdit *ui;

signals:
    void success();
};

#endif // CUSTOMEDIT_H
