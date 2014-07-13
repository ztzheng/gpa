#include "qodbcexcel.h"
#include <QDebug>

QOdbcExcel::QOdbcExcel()
{
}
QString QOdbcExcel::error;

bool QOdbcExcel::save(QString filePath, QStringList headers, QList<QStringList> data,QString comment)
{
    QString sheetName = "Sheet1";

//    qDebug()<<headers<<endl<<data<<endl<<comment;

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC","excelexport");
    if( !db.isValid())
    {
        error="数据库驱动异常";
        return false;   //! type error
    }

    QString dsn = "DRIVER={Microsoft Excel Driver (*.xls)};"
            "DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\""+filePath+"\";DBQ="+filePath;
    db.setDatabaseName( dsn);

    // open connection
    if( !db.open())
    {
        error="无法打开数据库";
        return false;  //! db error
    }

    QSqlQuery query(db);
    QString sSql;
    bool state;

    // drop the table if it's already exists
    sSql = QString("DROP TABLE [%1]").arg(sheetName);
    query.exec( sSql);
    //create the table (sheet in Excel file)
    sSql = QString("CREATE TABLE [%1] (").arg(sheetName);
    foreach (QString name, headers) {
        sSql +=QString("[%1] varchar(200)").arg(name);
        if(name!=headers.last())
            sSql +=",";
    }
    sSql += ")";
    state = query.prepare( sSql);
    if( !query.exec()) {
        QOdbcExcel::printError( query.lastError());
        db.close();
        return false;
    }
    foreach (QStringList slist, data) {
        insert(query,sheetName,slist);
    }

    if(!comment.isEmpty())
    {
        QStringList slist;
        slist<<comment;
        for(int i=0,n=headers.size()-1;i<n;i++)
        {
            slist<<"";
        }
        insert(query,sheetName,slist);
    }

    db.close();
    return true;
}

void QOdbcExcel::printError(QSqlError error)
{
    QString sqlerr = error.text();
    error=sqlerr;
    qDebug()<<sqlerr;
}

bool QOdbcExcel::insert(QSqlQuery &query, QString sheetName, QStringList slist)
{
    QString sSql = QString("INSERT INTO [%1] VALUES(").arg( sheetName);
    for(int i=0,n=slist.size();i<n;i++)
    {
        sSql+=QString(":%1").arg(i);
        if(i!=n-1)
            sSql+=",";
        else
            sSql+=")";
    }
    query.prepare( sSql);
    for(int i=0,n=slist.size();i<n;i++)
    {
        query.bindValue(QString(":%1").arg(i),slist.at(i));
    }
    if( !query.exec()) {
        printError( query.lastError());
        return false;
    }
    return true;
}

