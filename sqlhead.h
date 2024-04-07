#ifndef SQLHEAD_H
#define SQLHEAD_H


#include <qdebug.h>
#include <qsqlerror.h>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QDateTime>

class UserInfo
{
public:
    int id;
    QString name;
    QString identity;

};

#endif // SQLHEAD_H
