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
    connect(DB, DataBase::sig_readyMonthGraf, this, &Dialog::fill_MonthChart);
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

void Dialog::fill_MonthChart(const QVector<int> &counts, const QStringList &days, const QString& startDay, const QString& finishDay) {
    qDebug() << "SM = " << startDay << " FM = " << finishDay;

    if (counts.isEmpty()) {
        qDebug() << "No YearData to display";
        return;
    }

    // Очистка предыдущих элементов графика
    while (layout2->count() > 0) {
        QLayoutItem *item = layout2->takeAt(0);
        delete item->widget();
        delete item;
    }

    QLineSeries *series = new QLineSeries();
    int num_start = -1; // Инициализируем как -1 чтобы обрабатывать ошибки
    int num_finish = -1;

    // Находим индексы для начала и конца
    for (int i = 0; i < days.size(); i++) {
        if (days[i] == startDay) {
            num_start = i;
        }
        if (days[i] == finishDay) {
            num_finish = i; // Обновляем только когда нашли finishDay
        }
    }
    qDebug() << "OK!";

    // Проверка на корректные индексы
    if (num_start == -1) {
        qDebug() << "Start day not found;";
        return;
    }
    if (num_finish == -1) {
        qDebug() << "Finish day not found;";
        return; // Корректируем, чтобы не продолжать работу при ошибке
    }

    // Добавляем данные в серию
    for (int i = num_start; i <= num_finish; i++) {
        series->append(i, counts.at(i));
    }

    QChart *chart = new QChart(); // Создаем новый график

    // Настройка осей
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Flight Count");
    axisY->setRange(0, *std::max_element(counts.begin(), counts.end()) + 1); // Установка диапазона по Y

    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->setTitleText("Days");
    axisX->setRange(num_start, num_finish); // Устанавливаем диапазон по X

    for (int i = num_start; i <= num_finish; i++) { // Присоединяем ось X
        QString dayLabel = days.at(i).split('-').last();
        axisX->append(dayLabel, i); // Добавляем метки для X оси
    }

    // Добавляем серию и оси в график
    chart->addSeries(series);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->addAxis(axisX, Qt::AlignBottom);

    // Присоединяем оси к серии
    series->attachAxis(axisY);
    series->attachAxis(axisX);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout2->addWidget(chartView);

    chart->update(); // Обновляем график
}

Dialog::ret_index(){
    return ui->months->currentIndex();
}

Dialog::~Dialog()
{
    delete ui;
}
