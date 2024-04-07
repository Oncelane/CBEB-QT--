#ifndef STASHADD_H
#define STASHADD_H

#include <QWidget>
#include <sqlhead.h>
#include <simpleeditpage.h>


namespace Ui {
class stashadd;
}

class stashadd : public QWidget
{
    Q_OBJECT

public:
    explicit stashadd(QWidget *parent = nullptr);
    ~stashadd();
    void InitUI(UserInfo userinfo,int);
    int index;
public slots:
    void getedit(int row,QString amount,QString value);
    void updatetime();
private slots:
    void on_cancelButton_clicked();

    void on_addButton_clicked();

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_clearAllButton_clicked();

    void on_doneButton_clicked();

    void on_selectstashCombox_currentTextChanged(const QString &arg1);

private:
    Ui::stashadd *ui;
    bool checkrightrow(int row);
    simpleEditPage *simpleeditpage;
    void updateTotalPrice(int row);
    UserInfo userinfo;
    void updateDownPrice();
signals:
    void priceChangeSignal();
    void editSuccessSignal();
};

#endif // STASHADD_H
