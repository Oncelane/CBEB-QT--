#ifndef CUSTOMMANAGE_H
#define CUSTOMMANAGE_H

#include <QWidget>
#include <sqlhead.h>
#include <customadd.h>
#include <customedit.h>
namespace Ui {
class CustomManage;
}

class CustomManage : public QWidget
{
    Q_OBJECT

public:
    explicit CustomManage(QWidget *parent = nullptr);
    ~CustomManage();

private:
    Ui::CustomManage *ui;
    QSqlTableModel *model;
    CustomAdd *customadd;
    CustomEdit *customedit;
    void flashContent();
    void deleteContent(int row);
    void editContent();
    bool checkRowAvalid(int row);
signals:
    void deletesuppliersuccess();
    void searchChange();

private slots:
    void on_addbutton_clicked();
    void on_editbutton_clicked();
    void on_deletebutton_clicked();
    void on_query_clicked();
};

#endif // CUSTOMMANAGE_H
