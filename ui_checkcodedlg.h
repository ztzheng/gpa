/********************************************************************************
** Form generated from reading UI file 'checkcodedlg.ui'
**
** Created: Thu Jan 30 10:58:36 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKCODEDLG_H
#define UI_CHECKCODEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CheckCodeDlg
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *btnChange;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *btnSubmit;

    void setupUi(QDialog *CheckCodeDlg)
    {
        if (CheckCodeDlg->objectName().isEmpty())
            CheckCodeDlg->setObjectName(QString::fromUtf8("CheckCodeDlg"));
        CheckCodeDlg->resize(207, 76);
        verticalLayout = new QVBoxLayout(CheckCodeDlg);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(CheckCodeDlg);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        btnChange = new QPushButton(CheckCodeDlg);
        btnChange->setObjectName(QString::fromUtf8("btnChange"));
        btnChange->setAutoDefault(false);

        horizontalLayout_2->addWidget(btnChange);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit = new QLineEdit(CheckCodeDlg);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QFont font;
        font.setPointSize(10);
        lineEdit->setFont(font);

        horizontalLayout->addWidget(lineEdit);

        btnSubmit = new QPushButton(CheckCodeDlg);
        btnSubmit->setObjectName(QString::fromUtf8("btnSubmit"));

        horizontalLayout->addWidget(btnSubmit);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(CheckCodeDlg);

        QMetaObject::connectSlotsByName(CheckCodeDlg);
    } // setupUi

    void retranslateUi(QDialog *CheckCodeDlg)
    {
        CheckCodeDlg->setWindowTitle(QApplication::translate("CheckCodeDlg", "\350\257\267\350\276\223\345\205\245\351\252\214\350\257\201\347\240\201", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        btnChange->setText(QApplication::translate("CheckCodeDlg", "\346\215\242\344\270\200\345\274\240", 0, QApplication::UnicodeUTF8));
        btnSubmit->setText(QApplication::translate("CheckCodeDlg", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CheckCodeDlg: public Ui_CheckCodeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKCODEDLG_H
