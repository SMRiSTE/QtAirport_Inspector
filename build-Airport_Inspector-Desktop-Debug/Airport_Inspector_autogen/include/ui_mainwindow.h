/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *status_con;
    QTableView *tableView;
    QGroupBox *groupBox_1;
    QGridLayout *gridLayout_2;
    QDateEdit *dateEdit;
    QComboBox *combo_airports;
    QPushButton *arrival_btn;
    QPushButton *flight_btn;
    QLabel *airport;
    QPushButton *get_result_btn;
    QPushButton *workload_btn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(971, 587);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        status_con = new QLabel(centralwidget);
        status_con->setObjectName("status_con");

        gridLayout->addWidget(status_con, 2, 0, 1, 3);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");

        gridLayout->addWidget(tableView, 1, 0, 1, 2);

        groupBox_1 = new QGroupBox(centralwidget);
        groupBox_1->setObjectName("groupBox_1");
        groupBox_1->setEnabled(true);
        gridLayout_2 = new QGridLayout(groupBox_1);
        gridLayout_2->setObjectName("gridLayout_2");
        dateEdit = new QDateEdit(groupBox_1);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setMaximumDateTime(QDateTime(QDate(2017, 9, 14), QTime(17, 55, 0)));
        dateEdit->setMinimumDateTime(QDateTime(QDate(2016, 8, 15), QTime(23, 45, 0)));
        dateEdit->setMinimumDate(QDate(2016, 8, 15));

        gridLayout_2->addWidget(dateEdit, 5, 0, 1, 2);

        combo_airports = new QComboBox(groupBox_1);
        combo_airports->setObjectName("combo_airports");

        gridLayout_2->addWidget(combo_airports, 3, 1, 1, 1);

        arrival_btn = new QPushButton(groupBox_1);
        arrival_btn->setObjectName("arrival_btn");

        gridLayout_2->addWidget(arrival_btn, 4, 0, 1, 1);

        flight_btn = new QPushButton(groupBox_1);
        flight_btn->setObjectName("flight_btn");

        gridLayout_2->addWidget(flight_btn, 4, 1, 1, 1);

        airport = new QLabel(groupBox_1);
        airport->setObjectName("airport");

        gridLayout_2->addWidget(airport, 3, 0, 1, 1);

        get_result_btn = new QPushButton(groupBox_1);
        get_result_btn->setObjectName("get_result_btn");

        gridLayout_2->addWidget(get_result_btn, 6, 0, 1, 2);


        gridLayout->addWidget(groupBox_1, 1, 2, 1, 1);

        workload_btn = new QPushButton(centralwidget);
        workload_btn->setObjectName("workload_btn");

        gridLayout->addWidget(workload_btn, 0, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 971, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        status_con->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\320\273\321\216\321\207\320\265\320\275\320\276", nullptr));
        groupBox_1->setTitle(QString());
        arrival_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\273\320\265\321\202", nullptr));
        flight_btn->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\273\320\265\321\202", nullptr));
        airport->setText(QCoreApplication::translate("MainWindow", "\320\220\321\215\321\200\320\276\320\277\320\276\321\200\321\202", nullptr));
        get_result_btn->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\321\203\321\207\320\270\321\202\321\214 \321\200\320\265\320\271\321\201\321\213", nullptr));
        workload_btn->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\267\320\260\320\263\321\200\321\203\320\266\320\265\320\275\320\275\320\276\321\201\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
