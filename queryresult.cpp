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
    float sGpa=0;          //总绩点
    float sScore=0;       //总学分
    bool ok=true;
    QStringList exclude;
    for(int i=0;i<list.length();i++)
    {
        for(int j=0;j<16;j++)
        {
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(list.at(i).at(j)));
            item=ui->tableWidget->item(i ,j);
            item->setBackgroundColor(Qt::white);
            item->setFlags(item->flags()&(~Qt::ItemIsEditable));
        }
    }
    for(int i=0;i<list.length();i++)
    {
        for(int j=0;j<16;j++)
        {
            if(j==6)
            {
                float score=list.at(i).at(6).toFloat();     //学分
                float gpa=getGpa(list.at(i).at(11).toFloat(&ok));       //绩点
                if(!ok){
                    item=ui->tableWidget->item(i ,11);
                    item->setBackgroundColor(Qt::red);
                    item->setFlags(item->flags()&(Qt::ItemIsEditable));
                    exclude<<list.at(i).at(3);
                    continue;
                }
                sScore+=score;
                sGpa+=score*gpa;
            }
        }
    }
    ui->tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
    ui->tableWidget->resizeColumnsToContents();
    setFixedSize(width(),height());
    QString str=ui->label->text();
    QString point;
    point.sprintf("%.4f",sGpa/sScore);
    str.append(point+"\t");

    QString str2;
    foreach (QString tmp, exclude) {
        str2=str2+tmp+" ";
    }
    str.append(trUtf8("未加入计算科目：")+str2);
    ui->label->setText(str);
}

void QueryResult::closeEvent(QCloseEvent *)
{
    parent->show();
    delete this;
}

QueryResult::~QueryResult()
{
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
        return 0;
    a=a-50;
    return a/10;
}
