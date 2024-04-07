#ifndef STASHANDGOODPAGE_H
#define STASHANDGOODPAGE_H

#include <QWidget>
#include <sqlhead.h>

namespace Ui {
class StashAndGoodPage;
}

class StashAndGoodPage : public QWidget
{
    Q_OBJECT

public:
    explicit StashAndGoodPage(QWidget *parent = nullptr);
    ~StashAndGoodPage();
    void InitUi();
private slots:
    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::StashAndGoodPage *ui;
    QSqlTableModel *model;
    void  flashContent();
signals:
    void flash();
};

#endif // STASHANDGOODPAGE_H
