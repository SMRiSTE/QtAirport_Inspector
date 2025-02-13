#ifndef GRAF_H
#define GRAF_H

#include "work_DB.h"
#include <QDialog>
#include <QPushButton>
#include <QValueAxis>
#include <QCategoryAxis>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    int ret_index();
    ~Dialog();

public slots:
    void fill_YearChart(const QVector<int>& counts, const QStringList& months);
    void fill_MonthChart(const QVector<int>& counts, const QStringList& days, const QString& startDay, const QString& finishDay);

signals:
    void sig_open_DialogWindow(QString airport);
    void changed_month();

private:
    Ui::Dialog *ui;
    DataBase* DB;
    QString airport;
    QLayout* layout1;
    QLayout* layout2;
    int num = 0;
};

#endif // GRAF_H
