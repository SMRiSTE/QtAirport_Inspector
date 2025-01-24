#include "graf.h"
#include "ui_graf.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


    DB = new DataBase();

    ui->tabWidget->setTabText(0, "Год");
    ui->tabWidget->setTabText(1, "Месяц");

    layout1 = new QVBoxLayout(ui->for_year);
    layout2 = new QVBoxLayout(ui->groupBox);

    //ui->foe_month->boxForMonths->setLayout(layout2);

    connect(this, Dialog::sig_open_DialogWindow, this, [&](QString airport){
        this->airport = airport;
        ui->airport->setText(airport);
    });


    connect(ui->CloseWindow, QPushButton::clicked, this, [&]{
        close();
    });

    connect(DB, DataBase::sig_readyYearGraf, this, &Dialog::fill_YearChart);
    connect(ui->months, QComboBox::currentIndexChanged, this, [&]{
        emit changed_month();
    });
}

void Dialog::fill_YearChart(const QVector<int>& counts, const QStringList& months){
    if (counts.isEmpty()) {
            qDebug() << "No YearData to display";
            return;
        }
    else{
        qDebug() << "Ok";
    }

    if (layout1->count() > 0) {
        QLayoutItem *item;
        while ((item = layout1->takeAt(0))) {
            delete item->widget();
            delete item;
        }
    }

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Количество рейсов");

    for (int i = 0; i < counts.size(); ++i) {
        *set << counts[i];
    }
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Количество рейсов по месяцам");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setTitleText("Количество рейсов");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    qDebug()<<"norm";
    layout1->addWidget(chartView);
    ui->for_year->setLayout(layout1);

    ui->for_year->update();
    qDebug() << "Chart added";

}

void Dialog::fill_MonthChart(const QVector<int> &counts, const QStringList &days){
    if (counts.isEmpty()) {
            qDebug() << "No YearData to display";
            return;
        }
    else{
        qDebug() << "Ok";
    }
    if (layout2->count() > 0) {
        QLayoutItem *item;
        while ((item = layout2->takeAt(0))) {
            delete item->widget();
            delete item;
        }
    }

    QLineSeries *series = new QLineSeries();
    for(int i = 0; i < days.size(); i++){
        series->append(i, counts[i]);
    }

    QChart *chart = new QChart();
        chart->addSeries(series);

    QCategoryAxis *axisX = new QCategoryAxis(); // Используем QCategoryAxis для текстовых меток
    QValueAxis *axisY = new QValueAxis();

    axisY->setTitleText("Flight Count");
    axisY->setRange(0, *std::max_element(counts.begin(), counts.end()) + 1); // Максимум + 1 для лучшего отображения

    // Установка оси по Y
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QStringList list;
    for(int i = 0; i < days.size(); i++) {
        QString str = QString::number(i);
        list.append(str);
    }

    for (int i = 0; i < days.size(); i++) {
        QString day = days.at(i).split('-').last();
        axisX->append(day, i);
    }

    // Установка диапазона по X
    axisX->setRange(0, days.size() - 1);

    // Установка заголовка оси X
    axisX->setTitleText("Days");

    // Установка оси по X на график
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout2->addWidget(chartView);
}

Dialog::ret_index(){
    return ui->months->currentIndex();
}

Dialog::~Dialog()
{
    delete ui;
}
