/********************************************************************************
** Form generated from reading UI file 'graf.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAF_H
#define UI_GRAF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *CloseWindow;
    QTabWidget *tabWidget;
    QWidget *for_year;
    QWidget *for_month;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_3;
    QComboBox *months;
    QGroupBox *groupBox;
    QLabel *airport;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName("Dialog");
        Dialog->resize(527, 477);
        gridLayout = new QGridLayout(Dialog);
        gridLayout->setObjectName("gridLayout");
        CloseWindow = new QPushButton(Dialog);
        CloseWindow->setObjectName("CloseWindow");

        gridLayout->addWidget(CloseWindow, 4, 0, 1, 2);

        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName("tabWidget");
        for_year = new QWidget();
        for_year->setObjectName("for_year");
        tabWidget->addTab(for_year, QString());
        for_month = new QWidget();
        for_month->setObjectName("for_month");
        gridLayout_2 = new QGridLayout(for_month);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName("gridLayout_3");
        months = new QComboBox(for_month);
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->addItem(QString());
        months->setObjectName("months");

        gridLayout_3->addWidget(months, 0, 0, 1, 1);

        groupBox = new QGroupBox(for_month);
        groupBox->setObjectName("groupBox");

        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 0, 0, 1, 1);

        tabWidget->addTab(for_month, QString());

        gridLayout->addWidget(tabWidget, 3, 0, 1, 1);

        airport = new QLabel(Dialog);
        airport->setObjectName("airport");

        gridLayout->addWidget(airport, 0, 0, 1, 1);


        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        CloseWindow->setText(QCoreApplication::translate("Dialog", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(for_year), QCoreApplication::translate("Dialog", "Tab 1", nullptr));
        months->setItemText(0, QCoreApplication::translate("Dialog", "\321\217\320\275\320\262\320\260\321\200\321\214", nullptr));
        months->setItemText(1, QCoreApplication::translate("Dialog", "\321\204\320\265\320\262\321\200\320\260\320\273\321\214", nullptr));
        months->setItemText(2, QCoreApplication::translate("Dialog", "\320\274\320\260\321\200\321\202", nullptr));
        months->setItemText(3, QCoreApplication::translate("Dialog", "\320\260\320\277\321\200\320\265\320\273\321\214", nullptr));
        months->setItemText(4, QCoreApplication::translate("Dialog", "\320\274\320\260\320\271", nullptr));
        months->setItemText(5, QCoreApplication::translate("Dialog", "\320\270\321\216\320\275\321\214", nullptr));
        months->setItemText(6, QCoreApplication::translate("Dialog", "\320\270\321\216\320\273\321\214", nullptr));
        months->setItemText(7, QCoreApplication::translate("Dialog", "\320\260\320\262\320\263\321\203\321\201\321\202", nullptr));
        months->setItemText(8, QCoreApplication::translate("Dialog", "\321\201\320\265\320\275\321\202\321\217\320\261\321\200\321\214", nullptr));
        months->setItemText(9, QCoreApplication::translate("Dialog", "\320\276\320\272\321\202\321\217\320\261\321\200\321\214", nullptr));
        months->setItemText(10, QCoreApplication::translate("Dialog", "\320\275\320\276\321\217\320\261\321\200\321\214", nullptr));
        months->setItemText(11, QCoreApplication::translate("Dialog", "\320\264\320\265\320\272\320\260\320\261\321\200\321\214", nullptr));

        groupBox->setTitle(QString());
        tabWidget->setTabText(tabWidget->indexOf(for_month), QCoreApplication::translate("Dialog", "Tab 2", nullptr));
        airport->setText(QCoreApplication::translate("Dialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAF_H
