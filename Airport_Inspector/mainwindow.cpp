#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graf = new Dialog();

    ui->arrival_btn->setCheckable(true);
    ui->flight_btn->setCheckable(true);

    DB = new DataBase();

    DB->AddDataBase();
    ui->status_con->setText("Подключение");
    ui->status_con->setStyleSheet("color : black");

    setEnabled(false);

    auto conn = [&]{DB->ConnectToDataBase();};
    QtConcurrent::run(conn);

    connect(DB, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);

    connect(this, &MainWindow::sig_correct_con_to_DB, this, [&]{
        setEnabled(true);
        auto get_air = [&]{DB->getAirports(ui->combo_airports);};
        QtConcurrent::run(get_air);
    });

    connect(ui->arrival_btn, &QPushButton::toggled, [=](bool checked){
        if(checked){
            ui->flight_btn->setChecked(false);
        }
    });
    connect(ui->flight_btn, &QPushButton::toggled, [=](bool checked){
        if(checked){
            ui->arrival_btn->setChecked(false);
        }
    });

    connect(ui->get_result_btn, &QPushButton::clicked, [&](){
        if(ui->arrival_btn->isChecked()) {
            auto arr_planes = [this]() {
                return DB->arrival_planes(ui->combo_airports->currentText(), ui->dateEdit->date(), ui->tableView);
            };

            QFuture<QSqlQueryModel*> future = QtConcurrent::run(arr_planes);
            QFutureWatcher<QSqlQueryModel*> *watcher = new QFutureWatcher<QSqlQueryModel*>(this);

            connect(watcher, &QFutureWatcher<QSqlQueryModel*>::finished, [=]() {
                auto queryModel = future.result();
                if (queryModel) {
                    ui->tableView->setModel(queryModel);
                } else {
                    qDebug() << "Не удалось получить данные для рейсов.";
                }
                watcher->deleteLater();
            });

            watcher->setFuture(future);
        }
        else if(ui->flight_btn->isChecked()){
            auto flight_planes = [this](){
                return DB->flight_planes(ui->combo_airports->currentText(), ui->dateEdit->date(), ui->tableView);
            };

            QFuture<QSqlQueryModel*> future = QtConcurrent::run(flight_planes);
            QFutureWatcher<QSqlQueryModel*> *watcher = new QFutureWatcher<QSqlQueryModel*>(this);

            connect(watcher, &QFutureWatcher<QSqlQueryModel*>::finished, [=]() {
                auto queryModel = future.result();
                if (queryModel) {
                    ui->tableView->setModel(queryModel);
                } else {
                    qDebug() << "Не удалось получить данные для рейсов.";
                }
                watcher->deleteLater();
            });

            watcher->setFuture(future);
        }
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    });

    connect(ui->workload_btn, &QPushButton::clicked, this, [&]{
        graf->show();
        setEnabled(false);
        emit graf->sig_open_DialogWindow(ui->combo_airports->currentText());
    });
    connect(graf, &QDialog::finished, this, [=](int result){
        setEnabled(true);
    });

    connect(ui->workload_btn, &QPushButton::clicked, this, [&]{
        auto info_per_year = [&]{DB->info_per_year(ui->combo_airports->currentText());
        DB->info_per_month(ui->combo_airports->currentText(), graf->ret_index(), 0);};
        QtConcurrent::run(info_per_year);
    });

    connect(DB, DataBase::sig_readyYearGraf, graf, &Dialog::fill_YearChart);
    connect(DB, DataBase::sig_readyMonthGraf, graf, &Dialog::fill_MonthChart);
    connect(graf, Dialog::changed_month, this, [&]{
        auto info = [&]{DB->info_per_month(ui->combo_airports->currentText(), graf->ret_index(), 1);};
        QtConcurrent::run(info);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReceiveStatusConnectionToDB(bool status){
    if(status){
        ui->status_con->setText("Подключено к БД");
        ui->status_con->setStyleSheet("color:green");
        ui->status_con->setStyleSheet("color:green");
        emit sig_correct_con_to_DB();
        //ui->pb_request->setEnabled(true);
    }
    else{
        DB->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(DB->GetLastError().text());
        ui->status_con->setText("Отключено");
        ui->status_con->setStyleSheet("color:red");
        msg->exec();
        QThread::sleep(5);
        auto conn = [&]{DB->ConnectToDataBase();};
        QtConcurrent::run(conn);
    }
}

