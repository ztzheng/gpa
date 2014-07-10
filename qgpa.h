#ifndef QGPA_H
#define QGPA_H

#include <QWidget>
#include <QDesktopServices>

namespace Ui {
class QGpa;
}

class QGpa : public QWidget
{
    Q_OBJECT

public:
    explicit QGpa(QWidget *parent = 0);
    ~QGpa();

private slots:
    void on_btnQuery_clicked();
    void openUrl(QString url);

private:
    Ui::QGpa *ui;
    void save();
    void load();
};

#endif // QGPA_H
