#ifndef QODBCEXCEL_H
#define QODBCEXCEL_H

#include <QObject>
#include <QStringList>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>

class QOdbcExcel : public QObject
{
public:
    QOdbcExcel();
    bool static save(QString filePath,QStringList headers,QList<QStringList> data,QString comment="");
    QString static getError(){return error;}
private:
    void static printError( QSqlError error);
    bool static insert(QSqlQuery& query, QString sheetName, QStringList slist);
    static QString error;
};





#endif // QODBCEXCEL_H
