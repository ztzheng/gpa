#include "queryresult.h"
#include "../ui_queryresult.h"
#include <QDebug>
#include <QFileDialog>
#include <QDesktopServices>
#include "qodbcexcel.h"
#include <QMessageBox>

QueryResult::QueryResult(QWidget *parent, QList<QStringList> list, QString year, QString term,QString id) :

    ui(new Ui::QueryResult)
{
    this->parent=parent;
    ui->setupUi(this);
    this->year=year;
    this->term=term;
    this->id=id;
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    ui->tableWidget->setRowCount(list.length());
    ui->tableWidget->setColumnCount(16);
    QTableWidgetItem* item;

    for(int i=0;i<list.length();i++)
    {
        for(int j=0;j<16;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(list.at(i).at(j)));
            item=ui->tableWidget->item(i ,j);
            item->setFlags(item->flags()&(~Qt::ItemIsEditable));
        }
    }
    ui->tableWidget->resizeColumnsToContents();
    setFixedSize(width(),height());
    this->calculate();
    connect(ui->reCal,SIGNAL(clicked()),this,SLOT(calculate()));
}


void QueryResult::calculate()
{
    float sGpa=0;          //总绩点
    float sScore=0;       //总学分
    bool ok=true;
    QStringList exclude;
    QTableWidgetItem* item;
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0;j<16;j++)
        {
            if(j==6)
            {
                float score=ui->tableWidget->item(i,6)->text().toFloat();     //学分
                float gpa=getGpa(ui->tableWidget->item(i,11)->text().toFloat(&ok));       //绩点
                if(!ok){
                    item=ui->tableWidget->item(i,11);
                    item->setFlags(item->flags()|Qt::ItemIsEditable);
                    item->setBackgroundColor(QColor(qRgb(0,255,255)));
                    exclude<<ui->tableWidget->item(i,3)->text();
                    continue;
                }
                sScore+=score;
                sGpa+=score*gpa;
            }
        }
    }

    QString str=tr("平均绩点：");
    QString point;
    point.sprintf("%.4f",sGpa/sScore);
    str.append(point+"   ");

    QString str2;
    foreach (QString tmp, exclude) {
        str2=str2+tmp+" ";
    }
    str.append(tr("未加入计算科目：")+str2);
    ui->label->setText(str);
}

void QueryResult::closeEvent(QCloseEvent *)
{
    parent->show();
    delete this;
}

QueryResult::~QueryResult()
{
    ui->tableWidget->clearContents();
    delete ui;
}

void QueryResult::on_pushButton_clicked()
{
    parent->show();
    delete this;
}

float QueryResult::getGpa(float a)
{
    if(a<60)
        return 1;
    a=a-50;
    return a/10;
}



void QueryResult::on_btnSave_clicked()
{
//    QString filePath=QFileDialog::getSaveFileName(this,""
//                                                  ,QDesktopServices::storageLocation(QDesktopServices::DesktopLocation)+"/"+id+" "+year+" "+term+".xls"
//                                                  ,"*.xls");
    QFileDialog dlg;
    dlg.setAcceptMode(QFileDialog::AcceptSave);
    dlg.setDirectory(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation));
    dlg.setNameFilter("*.xls");
    dlg.selectFile(id+" "+year+" "+term+".xls");
    if(dlg.exec()!= QDialog::Accepted)
        return;
    QString filePath=dlg.selectedFiles()[0];
    QStringList headers;
    int n=ui->tableWidget->columnCount();
    for(int i=0;i<n;i++)
    {
        QTableWidgetItem *item=ui->tableWidget->horizontalHeaderItem(i);
        headers<<item->text();
    }
    QList<QStringList> data;
    QStringList slist;
    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        slist.clear();
        for(int j=0;j<n;j++)
        {
            slist<<ui->tableWidget->item(i,j)->text();
        }
        data<<slist;
    }
    QString comment=ui->label->text();
    if(QOdbcExcel::save(filePath,headers,data,comment))
        QMessageBox::information(this,tr("提示"),tr("保存成功"));
    else{
        QString msg="保存失败！\n\r"+QOdbcExcel::getError();
        QMessageBox::critical(this,tr("错误"),tr(msg.toLatin1()));
    }
}
