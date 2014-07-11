#include "qgpa.h"
#include "ui_qgpa.h"
#include <QDate>
#include <QMessageBox>
#include <QDebug>
#include "session.h"
#include "queryresult.h"
#include <QSettings>
#include <QTextCodec>
#include "encrypt.h"

QGpa::QGpa(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QGpa)
{

    ui->setupUi(this);
    setWindowFlags(Qt::WindowMinimizeButtonHint);
    setFixedSize(width(),height());
    ui->comboBox->addItem(tr("全部"));
    QDate date=QDate::currentDate();
    int maxYear=date.year();
    if(date.month()<=9)maxYear--;
    for(int i=2001;i<=maxYear;i++)
    {
        QString years;
        years.sprintf("%d-%d",i,i+1);
        ui->comboBox->addItem(years);
    }
    ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
    connect(ui->label_6,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
    load();
}

QGpa::~QGpa()
{
    delete ui;
}

void QGpa::on_btnQuery_clicked()
{
    if(ui->checkBox->isChecked())
        save();
    ui->btnQuery->setEnabled(false);
    if(ui->editUrl->text().isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("网址不能为空!"));
        ui->editUrl->setFocus();
        ui->btnQuery->setEnabled(true);
        return;
    }
    if(ui->editId->text().isEmpty()||ui->editPass->text().isEmpty())
    {
        QMessageBox::critical(this,tr("错误"),tr("账号或密码不能为空!"));
        ui->btnQuery->setEnabled(true);
        return;
    }
    Session session(ui->editUrl->text(),ui->editId->text(),ui->editPass->text());
    if(!session.preLogin())
    {
        QMessageBox::critical(this,tr("错误"),tr("无法建立网络连接！"));
        ui->btnQuery->setEnabled(true);
        return;
    }
    Session::ErrorType errorType=session.createLogin();
    switch (errorType) {
    case Session::CheckCodeError:QMessageBox::critical(this,tr("错误"),tr("验证码有误！"));break;
    case Session::NoUserError:QMessageBox::critical(this,tr("错误"),tr("用户名不存在或未按照要求参加教学活动！！"));break;
    case Session::PasswordError:QMessageBox::critical(this,tr("错误"),tr("密码错误！"));break;
    case Session::OtherError:QMessageBox::critical(this,tr("错误"),tr("登陆失败！"));break;
    default:break;
    }
    if(errorType!=Session::NoError)
    {
        ui->btnQuery->setEnabled(true);
        return;
    }

    // 查询成功
    QList<QStringList> list=session.query(ui->comboBox->currentText(),ui->comboBox_2->currentText());
    QueryResult *result=new QueryResult(this,list);
    this->hide();
    result->show();
    ui->btnQuery->setEnabled(true);
}

void QGpa::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}


void QGpa::save()
{
    QString account=ui->editId->text();
    QString password=ui->editPass->text();

    char cipher[MAX_LEN],plain[MAX_LEN];
    strcpy(plain,password.toLatin1().data());
    encrypt(plain,cipher);
    password=QString(cipher);

    QSettings config("data.ini", QSettings::IniFormat);
    config.setIniCodec(QTextCodec::codecForName("utf-8"));
    config.setValue("/account",account);
    config.setValue("/password",password);
}

void QGpa::load()
{
    QSettings config("data.ini", QSettings::IniFormat);
    config.setIniCodec(QTextCodec::codecForName("utf-8"));
    QString account=config.value("/account").toString();
    QString password=config.value("/password").toString();

    char cipher[MAX_LEN],plain[MAX_LEN];
    strcpy(cipher,password.toLatin1().data());
    decrypt(cipher,  plain);
    password=QString(plain);
    ui->editId->setText(account);
    ui->editPass->setText(password);

}


void QGpa::on_btnUrl1_clicked()
{
    ui->editUrl->setText("jwxt.gdufe.edu.cn");
}

void QGpa::on_btnUrl2_clicked()
{
    ui->editUrl->setText("jwxt2.gdufe.edu.cn:8080");
}
