#ifndef WORK_DB_H
#define WORK_DB_H

#include <QTableWidget>
#include <QComboBox>
#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QSqlRecord>
#include<QDate>
#include <QMap>
#include <QVector>
#include <QStringList>
#include <QChart>
#include <QChartView>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QVBoxLayout>
#include <QLineSeries>
#include <QFuture>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "MyDB"

class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase();
    void DisconnectFromDataBase(QString nameDb = "");
    void getAirports(QComboBox *CB);
    QSqlQueryModel* arrival_planes(const QString &airport, const QDate &date, QTableView* TV);
    QSqlQueryModel* flight_planes(const QString &airport, const QDate &date, QTableView* TV);
    QSqlError GetLastError(void);
    void ConnectToDataBase();

public slots:
    void info_per_year(const QString &airport);
    void info_per_month(const QString &airport, int index, int num);

signals:

   void sig_SendDataFromDB(QAbstractItemModel *model, int typeR);
   void sig_SendStatusConnection(bool);
   void sig_readyYearGraf(const QVector<int>& counts, const QStringList& months);
   void sig_readyMonthGraf(const QVector<int>& counts, const QStringList& months, const QString &startDay, const QString &finishDay);


private:

    QSqlDatabase* dataBase;
    QSqlQueryModel* queryModel_for_airports;
    QMap<QString, QString> airports_code;
    QVector<int> counts;
    QStringList days;
    QVector<QString> dates;
    QSqlTableModel* tableModel;
    QTableView* tv;

};
#endif // WORK_DB_H
