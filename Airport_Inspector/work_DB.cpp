#include "work_DB.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    tv = new QTableView;

    dataBase = new QSqlDatabase();

    queryModel_for_airports = new QSqlQueryModel;
    tableModel = new QSqlTableModel(this, *dataBase);

    dates.push_back("2017-01-01");
    dates.push_back("2017-02-01");
    dates.push_back("2017-03-01");
    dates.push_back("2017-04-01");
    dates.push_back("2017-05-01");
    dates.push_back("2017-06-01");
    dates.push_back("2017-07-01");
    dates.push_back("2017-08-01");
    dates.push_back("2016-09-01");
    dates.push_back("2016-10-01");
    dates.push_back("2016-11-01");
    dates.push_back("2016-12-01");

}
DataBase::~DataBase()
{
    dataBase->close();
    delete dataBase;
    delete queryModel_for_airports;
    delete tableModel;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase()
{

    *dataBase = QSqlDatabase::addDatabase(POSTGRE_DRIVER, DB_NAME);

}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase()
{

    dataBase->setHostName("981757-ca08998.tmweb.ru");
    dataBase->setDatabaseName("demo");
    dataBase->setUserName("netology_usr_cpp");
    dataBase->setPassword("CppNeto3");
    dataBase->setPort(5432);

    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);

}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{

    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();

}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::getAirports(QComboBox *CB)
{
    queryModel_for_airports->setQuery("SELECT airport_name->>'ru' as \"airportName\", airport_code FROM bookings.airports_data", *dataBase);
    if (queryModel_for_airports->lastError().isValid()){
          qDebug() << "Error executing query: " << queryModel_for_airports->lastError().text();
          return;
    }
    int air_index = queryModel_for_airports->record().indexOf("airportName");
    int code_index = queryModel_for_airports->record().indexOf("airport_code");
    if (air_index == -1) {
        qDebug() << "Column 'airportName' not found!";
    }
    if(code_index == -1){
           qDebug() << "Column 'airport_code' not found!";
           delete queryModel_for_airports;
           return;
        }
    for (int row = 0; row < queryModel_for_airports->rowCount(); ++row) {
        QModelIndex airport_index = queryModel_for_airports->index(row, air_index); // Получаем индекс
        QModelIndex codes_index = queryModel_for_airports->index(row, code_index); // Получаем индекс

        QString airportName = queryModel_for_airports->data(airport_index).toString(); // Получаем значение
        QString airportCode = queryModel_for_airports->data(codes_index).toString(); // Получаем значение

        airports_code[airportName] = airportCode;

        CB->addItem(airportName);
    }
}

QSqlQueryModel* DataBase::arrival_planes(const QString &airport, const QDate &date, QTableView* TV) {
    QString airportCode = airports_code.value(airport);
    QString dateString = date.toString("yyyy-MM-dd");

    QSqlQuery query(*dataBase);

    query.prepare("SELECT flight_no, scheduled_arrival, ad.airport_name->>'ru' as Name "
                  "FROM bookings.flights f "
                  "JOIN bookings.airports_data ad ON ad.airport_code = f.departure_airport "
                  "WHERE f.arrival_airport = ? AND DATE(scheduled_arrival) = ?");

    query.bindValue(0, airportCode);
    query.bindValue(1, dateString);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return nullptr;
    }

    QSqlQueryModel *queryModel = new QSqlQueryModel();
    queryModel->setQuery(query);

    if (queryModel->lastError().isValid()) {
        qDebug() << "Error executing query: " << queryModel->lastError().text();
        delete queryModel;
        return nullptr;
    }

    queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер рейса"));
    queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Время вылета"));
    queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Аэропорт отправления"));

    return queryModel;
}

QSqlQueryModel* DataBase::flight_planes(const QString &airport, const QDate &date, QTableView *TV){
    QString airportCode = airports_code.value(airport);
    QString dateString = date.toString("yyyy-MM-dd");

    QSqlQuery query(*dataBase);

    query.prepare("SELECT flight_no, scheduled_departure, ad.airport_name->>'ru' as Name "
                  "from bookings.flights f "
                  "JOIN bookings.airports_data ad on ad.airport_code = f.arrival_airport "
                  "WHERE f.departure_airport  = ? AND DATE(scheduled_arrival) = ?");

    query.bindValue(0, airportCode);
    query.bindValue(1, dateString);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return nullptr;
    }

    QSqlQueryModel *queryModel = new QSqlQueryModel();
    queryModel->setQuery(query);

    if (queryModel->lastError().isValid()) {
        qDebug() << "Error executing query: " << queryModel->lastError().text();
        delete queryModel;
        return nullptr;
    }

    queryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер рейса"));
    queryModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Время вылета"));
    queryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Аэропорт отправления"));

    return queryModel;
}

void DataBase::info_per_year(const QString &airport){
    QString airportCode = airports_code.value(airport);

    QSqlQuery query(*dataBase);
    query.prepare(R"(
        SELECT
            COUNT(flight_no) AS flight_count,
            DATE_TRUNC('month', scheduled_departure) AS month
        FROM
            bookings.flights f
        WHERE
            scheduled_departure::date > DATE '2016-08-31'
            AND scheduled_departure::date <= DATE '2017-08-31'
            AND (departure_airport = :airportCode OR arrival_airport = :airportCode)
        GROUP BY
            month
        ORDER BY
            month
    )");

    query.bindValue(":airportCode", airportCode);

    QVector<int> counts;
    QStringList months;

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError(); // Вывод ошибок
    }
    while (query.next()) {
        int count = query.value(0).toInt();
        QString month = query.value(1).toString();
        counts.append(count);
        months.append(month);
    }
    qDebug() << "YearCount:" << counts.size();
    emit sig_readyYearGraf(counts, months);
    qDebug() << "YearSignal emitted with counts:" << counts << "and months:" << months;
}

void DataBase::info_per_month(const QString &airport, int index, int num) {
    QString airportCode = airports_code.value(airport);

    int year;
    if (index < 8) {
        year = 2017;
    } else {
        year = 2016;
    }

    if(num == 0){
        counts.clear();
        days.clear();

        QSqlQuery query(*dataBase);

        // Подготовка запроса с явным указанием всех параметров
        query.prepare("SELECT COUNT(flight_no) AS flight_count, "
                      "DATE_TRUNC('day', scheduled_departure) AS \"Day\" "
                      "FROM bookings.flights f "
                      "WHERE scheduled_departure::date > DATE('2016-08-31') "
                      "AND scheduled_departure::date <= DATE('2017-09-01') "
                      "AND (departure_airport = :airport OR arrival_airport = :airport) "
                      "GROUP BY \"Day\" ORDER BY \"Day\"");

        // Привязка параметров
        query.bindValue(":airport", airportCode);

        // Исполняем запрос
        if (!query.exec()) {
            qDebug() << "Error executing query: " << query.lastError().text();
            return;
        }

        // Получение результатов запроса
        while (query.next()) {
            int count = query.value(0).toInt(); // Получаем количество рейсов
            QDate dayDate = query.value(1).toDate(); // Получаем дату как QDate
            QString day = dayDate.toString("yyyy-MM-dd"); // Получаем дату
            counts.append(count);
            days.append(day); // Добавляем день в QStringList
        }
    }

    QDate startMonth = QDate::fromString(dates[index], "yyyy-MM-dd");
    QDate finishMonth = startMonth.addMonths(1);
    QString SD = startMonth.toString("yyyy-MM-dd");
    QString FD = finishMonth.toString("yyyy-MM-dd");

    qDebug() << "MonthCount:" << counts.size();
    emit sig_readyMonthGraf(counts, days, SD, FD); // Эмитируем сигнал с полученной информацией
    qDebug() << "MonthSignal emitted with counts:" << counts << "and days:" << days << "and SM" << SD << "FM" << FD;
}

QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
