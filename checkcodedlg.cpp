#include "checkcodedlg.h"
#include "ui_checkcodedlg.h"
#include <QDebug>

CheckCodeDlg::CheckCodeDlg(QWidget *parent,Session* session)
    : QDialog(parent),ui(new Ui::CheckCodeDlg)
{
    ui->setupUi(this);
    this->session=session;
    QObject::connect(this,SIGNAL(finishedCode(QString)),session,SLOT(setCheckCode(QString)));
    setFixedSize(width(),height());
    ui->lineEdit->setFocus();
    QPixmap* pixmap=session->getCheckCode();
    ui->label->setPixmap(*pixmap);
}

CheckCodeDlg::~CheckCodeDlg()
{
    delete ui;
}


void CheckCodeDlg::on_btnChange_clicked()
{
    QPixmap* pixmap=session->getCheckCode();
    ui->label->setPixmap(*pixmap);
}

void CheckCodeDlg::on_btnSubmit_clicked()
{
    emit finishedCode(ui->lineEdit->text());
    this->close();
}

