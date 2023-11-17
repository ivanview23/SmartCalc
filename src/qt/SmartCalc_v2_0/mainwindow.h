#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

#include "../../backend/controllerCalc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void CalcExprasion();
    void Clean();
    void GrapfButtonClicked();
    void DrowGrapf(
            std::pair<std::string,
                      std::pair<std::vector<double>, std::vector<double>>> graphData);
    void CreditCalcClicked();
    void DrowCreditAnswer(
            std::pair<std::string,
                      std::pair<std::pair<std::list<double>, std::list<double>>,
                                std::pair<std::list<double>, std::list<double>>>> creditData);
    void DrowCreditTable(
            std::pair<std::string,
                      std::pair<std::pair<std::list<double>, std::list<double>>,
                                std::pair<std::list<double>, std::list<double>>>> creditData);
    void DebitCalcClicked();
    void DrowDebitAnswer(
            std::pair<std::pair<std::string, std::list<double>>,
                        std::pair<std::list<double>, std::list<double>>> debitData);
    void DrowDebitTable(
            std::pair<std::pair<std::string, std::list<double>>,
                        std::pair<std::list<double>, std::list<double>>> debitData);
    std::vector<std::string> GetChangeDep();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    s21::ControllerCalc *controller_;
};
#endif // MAINWINDOW_H
