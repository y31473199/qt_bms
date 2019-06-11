#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDataUnit>
#include <QSqlDatabase>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE

class QModbusClient;

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_faultBtn_clicked();

    void on_closeBtn_clicked();

    void on_mediaBtn_clicked();

    void on_chargeBtn_pressed();

    void on_dischargeBtn_pressed();

    void on_temperBtn_pressed();

    void on_voltageBtn_pressed();

    void on_title_clicked();

    void Init();

    void do_dec();

    void do_conn();

private:
    QMovie *movie;
    QTimer *con_button;
    QTimer *timer;
    Ui::MainWindow *ui;
    bool charge_state = false;
    bool discharge_state = false;
    QModbusClient *modbusDevice;
    QModbusDataUnit readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters ,0,87);
    QModbusDataUnit writeUnit = QModbusDataUnit(QModbusDataUnit::Coils,0,4);
    bool temp_state = false;
    bool vol_state = false;

};

#endif // MAINWINDOW_H
