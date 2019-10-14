#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModbusDataUnit>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QModbusRtuSerialMaster>

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
    void connentModbus();

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

    void check_modbus();

    void check_fault(QString);

    void changeWindow();

    void on_pushButton_clicked();

private:
    QMovie *movie;
    QMovie *charge_movie;
    QTimer *con_button;
    QTimer *timer;
    Ui::MainWindow *ui;
    QSqlDatabase db;
    bool charge_state = false;
    bool discharge_state = false;
    QModbusClient *modbusDevice;
    QModbusDataUnit readUnit = QModbusDataUnit(QModbusDataUnit::HoldingRegisters ,0,87);
    QModbusDataUnit writeUnit = QModbusDataUnit(QModbusDataUnit::Coils,0,4);
    QModbusDataUnit writeUnitpress = QModbusDataUnit(QModbusDataUnit::Coils,0,4);
    bool temp_state = false;
    bool vol_state = false;
    bool started = false;
    bool timerStarted = false;
    QString fault_1;
    QString fault_2;
    QString fault_3;
    QString fault_4;
    QString fault_5;
    QString fault_6;
    bool acceptRun = false;
    QModbusReply *replyreade;

};

#endif // MAINWINDOW_H
