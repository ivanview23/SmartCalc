#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , controller_(new s21::ControllerCalc)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(GrapfButtonClicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(CalcExprasion()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(Clean()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(CreditCalcClicked()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DebitCalcClicked()));
}

MainWindow::~MainWindow()
{
    delete controller_;
    delete ui;
}

void MainWindow::CalcExprasion()
{
    ui->lineEdit_2->setText
            (QString::fromStdString
             (controller_->Calculate(
              ui->lineEdit->text().toStdString(), ui->doubleSpinBox->value())));
}

void MainWindow::Clean()
{
    ui->lineEdit_2->setText("");
    ui->lineEdit->setText("");
    ui->widget->clearGraphs();
    ui->widget->replot();
}

void MainWindow::GrapfButtonClicked()
{
  std::pair<std::string, std::pair<std::vector<double>, std::vector<double>>>
      graphData = controller_->CalculateGraphData(
          ui->lineEdit->text().toStdString(), s21::CalcData::GrapfData(
              ui->doubleSpinBoxXBegin->value(), ui->doubleSpinBoxXEnd->value(),
              ui->doubleSpinBoxXStep->value()));

    DrowGrapf(graphData);
}

void MainWindow::DrowGrapf(
        std::pair<std::string, std::pair<std::vector<double>, std::vector<double>>> graphData)
{
    ui->lineEdit_2->setText(QString::fromStdString(graphData.first));

    ui->widget->xAxis->setRange(ui->doubleSpinBoxXBegin->value(),
                                ui->doubleSpinBoxXEnd->value());
    ui->widget->yAxis->setRange(ui->doubleSpinBoxYBegin->value(),
                                ui->doubleSpinBoxYEnd->value());

    QVector<double> graphX(graphData.second.first.begin(),
                           graphData.second.first.end());

    QVector<double> graphY(graphData.second.second.begin(),
                           graphData.second.second.end());

    ui->widget->clearGraphs();

    QCPGraph *graph = ui->widget->addGraph();

    graph->setData(graphX, graphY);

    ui->widget->replot();
}

void MainWindow::CreditCalcClicked()
{
    std::pair<std::string, std::pair<std::pair<std::list<double>, std::list<double>>,
                            std::pair<std::list<double>, std::list<double>>>>
        creditData = controller_->CalculateCreditData(
                s21::CalcData::CreditData(ui->doubleSpinBox_5->text().toStdString(),
                                          ui->doubleSpinBox_2->text().toStdString(),
                                          ui->spinBox_2->text().toStdString(),
                                          ui->radioButton->isChecked()));
    DrowCreditAnswer(creditData);
    DrowCreditTable(creditData);
}

void MainWindow::DrowCreditAnswer(
        std::pair<std::string, std::pair<std::pair<std::list<double>, std::list<double>>,
                                          std::pair<std::list<double>, std::list<double>>>> creditData)
{
    double summ_plat = 0;
    for (auto it = creditData.second.first.first.begin(); it != creditData.second.first.first.end(); it++ ){
        summ_plat += *it;
    }
    ui->label_4->setText(QString::number(summ_plat, 'f', 2));

    double summ_proc_plat = 0;
    for (auto it = creditData.second.second.first.begin(); it != creditData.second.second.first.end(); it++ ){
        summ_proc_plat += *it;
    }
    ui->label_40->setText(QString::number(summ_proc_plat, 'f', 2));

    if (ui->radioButton->isChecked()) {
        ui->label_30->setNum(*creditData.second.first.first.begin());
    } else {
        std::list<double> plat_sort = creditData.second.first.first;
        plat_sort.sort();
        ui->label_30->setText( QString::number(plat_sort.front(), 'f', 2) + "..." + QString::number(plat_sort.back(), 'f', 2));
    }
}

void MainWindow::DrowCreditTable(
        std::pair<std::string, std::pair<std::pair<std::list<double>, std::list<double>>,
                                          std::pair<std::list<double>, std::list<double>>>> creditData)
{
    ui->tableWidget->setRowCount(ui->spinBox_2->value());
    ui->tableWidget->setColumnCount(4);

    for (size_t i = 0; i < ui->spinBox_2->value(); i++) {
      QTableWidgetItem *newItem[] = {
          new QTableWidgetItem(QString::number(creditData.second.first.first.front(), 'f', 2)),
          new QTableWidgetItem(QString::number(creditData.second.first.second.front(), 'f', 2)),
          new QTableWidgetItem(QString::number(creditData.second.second.first.front(), 'f', 2)),
          new QTableWidgetItem(QString::number(creditData.second.second.second.front(), 'f', 2)),
      };

      creditData.second.first.first.pop_front();
      creditData.second.first.second.pop_front();
      creditData.second.second.first.pop_front();
      creditData.second.second.second.pop_front();

      for (size_t col = 0; col < 4; col++) {
        ui->tableWidget->setItem(i, col, newItem[col]);
      }
    }
    for (int i = 0; i < ui->tabWidget->colorCount(); i += 1) {
      ui->tableWidget->setColumnWidth(
          i, ui->tableWidget->width() / ui->tableWidget->columnCount());
    }

    QStringList headers = QStringList();
    headers.append("Сумма платежа");
    headers.append("Платеж по \nосновному долгу");
    headers.append("Платеж по \nпроцентам");
    headers.append("Остаток долга");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

void MainWindow::DebitCalcClicked()
{
    std::pair<std::pair<std::string, std::list<double>>, std::pair<std::list<double>, std::list<double>>>
        debitData = controller_->CalculateDebitData(
                s21::CalcData::DebitData(ui->doubleSpinBox_4->value(),
                                          ui->doubleSpinBox_3->value(),
                                          ui->spinBox_4->value(),
                                          ui->comboBox->currentData().toInt(),
                                          ui->checkBox->isChecked(),
                                          GetChangeDep()));
    if (debitData.first.first == "q") {
        DrowDebitAnswer(debitData);
        DrowDebitTable(debitData);
    }
}

void MainWindow::DrowDebitAnswer(
        std::pair<std::pair<std::string, std::list<double> >,
                    std::pair<std::list<double>, std::list<double> > > debitData)
{
        double summ_viplat = 0;

        for (auto it = debitData.second.second.begin(); it != debitData.second.second.end(); it++ ){
            summ_viplat += *it;
        }
        ui->label_27->setText(QString::number(summ_viplat, 'f', 2));

        if(ui->checkBox->isChecked()) {
             ui->label_20->setText(QString::number(debitData.second.first.back(), 'f', 2));
        } else
            ui->label_20->setText(QString::number(summ_viplat + debitData.second.first.back(), 'f', 2));
}

void MainWindow::DrowDebitTable(
        std::pair<std::pair<std::string, std::list<double> >,
                    std::pair<std::list<double>, std::list<double> > > debitData)
{
    ui->tableWidget_2->setRowCount(ui->spinBox_4->value()+1);
    ui->tableWidget_2->setColumnCount(3);

    for (size_t i = 0; i < ui->spinBox_4->value()+1; i++) {

        QTableWidgetItem *newItem2[] = {
            new QTableWidgetItem(QString::number(debitData.second.second.front(), 'f', 2)),
            new QTableWidgetItem(QString::number(debitData.first.second.front(), 'f', 2)),
            new QTableWidgetItem(QString::number(debitData.second.first.front(), 'f', 2)),
        };
        debitData.second.second.pop_front();
        debitData.second.first.pop_front();
        debitData.first.second.pop_front();

        for (size_t col = 0; col < 3; col++) {
            ui->tableWidget_2->setItem(i, col, newItem2[col]);
        }
    }
    for (int i = 0; i < ui->tabWidget->colorCount(); i += 1) {
        ui->tableWidget_2->setColumnWidth(
                    i, ui->tableWidget_2->width() / ui->tableWidget_2->columnCount());
    }

    QStringList headers = QStringList();
    headers.append("Начислено процентов");
    headers.append("Вклад пополнен");
    headers.append("Остаток на вкладе");
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);
}

std::vector<std::string> MainWindow::GetChangeDep()
{
    std::vector<std::string> change_dep;

    for (int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        std::string itemText = item->text().toStdString();
        change_dep.push_back(itemText);
    }
    return change_dep;
}

void MainWindow::on_pushButton_6_clicked()
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText("+ | " + ui->spinBox_5->text() + " | " + ui->doubleSpinBox_6->text());
    ui->listWidget->addItem(item);
}


void MainWindow::on_pushButton_7_clicked()
{
    QListWidgetItem* item = new QListWidgetItem;
    item->setText("- | " + ui->spinBox_6->text() + " | " + ui->doubleSpinBox_7->text());
    ui->listWidget->addItem(item);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
}

