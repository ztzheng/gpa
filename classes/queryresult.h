#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <QList>
#include <QStringList>
#include <QWidget>

namespace Ui {
class QueryResult;
}

class QueryResult : public QWidget
{
    Q_OBJECT
    
public:
    explicit QueryResult(QWidget *parent,QList<QStringList> list,QString year="",QString term="",QString id="");
    void closeEvent(QCloseEvent *);
    ~QueryResult();
    
private slots:
    void on_pushButton_clicked();
    void calculate();
    void on_btnSave_clicked();

private:
    Ui::QueryResult *ui;
    QWidget *parent;
    float getGpa(float a);
    QString year;
    QString term;
    QString id;

};

#endif // QUERYRESULT_H
