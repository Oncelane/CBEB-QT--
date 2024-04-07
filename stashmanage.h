#ifndef STASHMANAGE_H
#define STASHMANAGE_H

#include <QWidget>
#include <sqlhead.h>
#include <stashadd.h>

namespace Ui {
class StashManage;
}

class StashManage : public QWidget
{
    Q_OBJECT

public:
    explicit StashManage(QWidget *parent = nullptr);
    ~StashManage();
    stashadd *stashaddpage;
    void Init(UserInfo);
private slots:
    void on_switchStash_currentIndexChanged(int index);

    void on_addStash_clicked();

    void on_deleteStash_clicked();
private:
    Ui::StashManage *ui;

    UserInfo userinfo;
    int currentIndex;
    void flashContent();
};

#endif // STASHMANAGE_H
