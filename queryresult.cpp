#include "queryresult.h"
#include "ui_queryresult.h"
#include <QDebug>

QueryResult::QueryResult(QWidget *parent,QList<QStringList> list) :

    ui(new Ui::QueryResult)
{
    this->parent=parent;
    ui->setupUi(this);
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
    str.append(point+"\t");

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


