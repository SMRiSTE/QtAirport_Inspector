#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "work_DB.h"
#include "graf.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent>
#include <QPushButton>
#include <QDialog>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sig_correct_con_to_DB();

public slots:
    void ReceiveStatusConnectionToDB(bool status);

private:
    Ui::MainWindow *ui;
    DataBase* DB;
    Dialog* graf;
    QMessageBox* msg;

};
#endif // MAINWINDOW_H
