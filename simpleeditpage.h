#ifndef SIMPLEEDITPAGE_H
#define SIMPLEEDITPAGE_H

#include <QWidget>

namespace Ui {
class simpleEditPage;
}

class simpleEditPage : public QWidget
{
    Q_OBJECT

public:
    explicit simpleEditPage(QWidget *parent = nullptr);
    ~simpleEditPage();
    int getamount();
    float getvalue();
    void Init(int row,QString amount, QString value);
private slots:
    void on_doneButton_clicked();

private:
    Ui::simpleEditPage *ui;
    QString amount;
    QString value;
    int row;
signals:
    void EditSuccess(int row,QString amount,QString value);
};

#endif // SIMPLEEDITPAGE_H
