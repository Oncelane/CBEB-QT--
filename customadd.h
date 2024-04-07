#ifndef CUSTOMADD_H
#define CUSTOMADD_H

#include <QWidget>
#include <sqlhead.h>

namespace Ui {
class CustomAdd;
}

class CustomAdd : public QWidget
{
    Q_OBJECT

public:
    explicit CustomAdd(QWidget *parent = nullptr);
    ~CustomAdd();

private slots:
    void on_doneButton_clicked();

private:
    Ui::CustomAdd *ui;
signals:
    void success();
};

#endif // CUSTOMADD_H
