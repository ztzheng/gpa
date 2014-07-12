#ifndef CHECKCODEDLG_H
#define CHECKCODEDLG_H

#include <QDialog>
#include "session.h"
namespace Ui {
class CheckCodeDlg;
}

class CheckCodeDlg : public QDialog
{
    Q_OBJECT

public:
    CheckCodeDlg(QWidget *parent = 0,Session* session=NULL);
    ~CheckCodeDlg();

signals:
    void finishedCode(QString code);

private:
    Ui::CheckCodeDlg *ui;
    Session *session;

private slots:
    void on_btnChange_clicked();
    void on_btnSubmit_clicked();
};

#endif // CHECKCODEDLG_H
