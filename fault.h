#ifndef FAULT_H
#define FAULT_H

#include <QWidget>
#include <login.h>
#include <QModbusDataUnit>
#include <QtSerialPort/QSerialPort>
#include <QRCodeGenerator.h>


QT_BEGIN_NAMESPACE
class QModbusClient;

namespace Ui {
class fault;
}

QT_END_NAMESPACE

class fault : public QWidget
{
    Q_OBJECT

public:
    explicit fault(QWidget *parent = nullptr);
    ~fault();
    //计数开关

    void send16(QString str);
    QString command_factory(QString index);
    void Init();
    bool check_fault(int index,bool &on_off);
signals:
    void showScoreQRCodeString(QString);

private slots:
    void on_closeBtn_clicked();

    void on_meterBtn_clicked();

    void on_mediaBtn_clicked();

    void on_read_fault_btn_clicked();

    void on_score_add_btn_clicked();

    void on_clear_fault_btn_clicked();

    void on_data_reset_btn_clicked();

    void on_logout_btn_clicked();

    void on_bty_fault_1_activated(int index);

    void on_bty_fault_2_activated(int index);

    void on_bty_fault_3_activated(int index);

    void on_bty_fault_4_activated(int index);

    void on_bty_fault_5_activated(int index);

    void on_bty_fault_6_activated(int index);

    void on_bty_fault_7_activated(int index);

    void on_bty_fault_8_activated(int index);

    void on_bty_fault_9_activated(int index);

    void on_bty_fault_10_activated(int index);

    void on_bty_fault_11_activated(int index);

    void on_bty_fault_12_activated(int index);

    void on_bty_fault_13_activated(int index);

    void on_bty_fault_14_activated(int index);

    void on_bty_fault_15_activated(int index);

    void on_bty_fault_16_activated(int index);

    void on_bty_fault_17_activated(int index);

    void on_bty_fault_18_activated(int index);

    void on_bty_fault_19_activated(int index);

    void on_bty_fault_20_activated(int index);

    void on_bty_fault_21_activated(int index);

    void on_bty_fault_22_activated(int index);

    void on_bty_fault_23_activated(int index);

    void on_bty_fault_24_activated(int index);

    void on_submit_btn_clicked();

    void on_fault_stat_clicked();

    void on_background_info_btn_clicked();

    void on_time_set_returnPressed();

    void on_bms_fault_activated(int index);

    void on_batout_fault_activated(int index);

    void on_batin_fault_activated(int index);

    void on_can_bus_fault_activated(int index);

    void showTimelimit();


    void on_set_fault_btn_clicked();

private:
    void serialConnect();
    void modbusPlcConnect();
    QModbusClient *modbusDevice;
    QModbusDataUnit writeUnit = QModbusDataUnit(QModbusDataUnit::Coils,0,4);
    Ui::fault *ui;
    QString user;
    int fault_stat = 0;
    login *lw ;
    int time_back;
    QTimer *timer;
    QSerialPort *serial;
    CQR_Encode qrEncode;
    bool successfulEncoding;
    int encodeImageSize;


};

#endif // FAULT_H
