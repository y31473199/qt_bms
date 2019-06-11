#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fault.h"
#include "QMessageBox"
#include "media.h"
#include "login.h"
#include <QMovie>

#include <QModbusRtuSerialMaster>
#include <QStatusBar>
#include <QSqlQuery>
#include <QtDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QSerialPortInfo>
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    modbusDevice(nullptr)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/zz.ico"));
    this->setWindowFlag(Qt::FramelessWindowHint);
    Init();
    timer = new QTimer(this);
    timer->start(800);
//    connect(timer, SIGNAL(timeout()), this, SLOT(do_conn()));
}

MainWindow::~MainWindow()
{
    delete ui;
}



//页面初始化
void MainWindow::Init(){



    if (modbusDevice)
        modbusDevice->disconnectDevice();
    delete modbusDevice;
    modbusDevice = nullptr;
    modbusDevice = new QModbusRtuSerialMaster(this);
    //Linux
        //modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "ttyUSB0");//串口参数
    //Windows
    modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "COM3");//串口参数
    modbusDevice->setConnectionParameter(QModbusDevice::SerialParityParameter,
        0);//校检方式
    modbusDevice->setConnectionParameter(QModbusDevice::SerialBaudRateParameter,
        9600);//波特率
    modbusDevice->setConnectionParameter(QModbusDevice::SerialDataBitsParameter,
        8);//数据位数
    modbusDevice->setConnectionParameter(QModbusDevice::SerialStopBitsParameter,
        1);//停止位


    movie = new QMovie(":/res/charge.gif");
    QStringList fault_index_1;
    QStringList fault_index_2;
    QStringList fault_index_3;
    QStringList fault_index_4;
    QStringList fault_index_5;
    QStringList fault_index_6;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if(db.open()){
            query.exec(QString("select * from fault_"));
            query.last();
            //故障读取
            QString fault_1 = query.value(0).toString();
            QString fault_2 = query.value(1).toString();
            QString fault_3 = query.value(2).toString();
            QString fault_4 = query.value(3).toString();
            QString fault_5 = query.value(4).toString();
            QString fault_6 = query.value(5).toString();

            //故障码生成
            fault_index_1 = fault_1.split(",");
            fault_index_2 = fault_2.split(",");
            fault_index_3 = fault_3.split(",");
            fault_index_4 = fault_4.split(",");
            fault_index_5 = fault_5.split(",");
            fault_index_6 = fault_6.split(",");
            QString fault_num = ","+fault_index_1.at(0)+",";
            fault_num.append(","+fault_index_2.at(0)+",");
            fault_num.append(","+fault_index_3.at(0)+",");
            fault_num.append(","+fault_index_4.at(0)+",");
            fault_num.append(","+fault_index_5.at(0)+",");
            fault_num.append(","+fault_index_6.at(0)+",");
            if(fault_num.contains(",1,")){
                ui->chargeing->setStyleSheet("background-color:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing->setMovie(movie);
            }
            if(fault_num.contains(",2,")){
                ui->chargeing_2->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_2->setMovie(movie);
            }
            if(fault_num.contains(",3,")){
                ui->chargeing_3->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_3->setMovie(movie);
            }
            if(fault_num.contains(",4,")){
                ui->chargeing_4->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_4->setMovie(movie);
            }
            if(fault_num.contains(",5,")){
                ui->chargeing_5->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_5->setMovie(movie);
            }
            if(fault_num.contains(",6,")){
                ui->chargeing_6->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_6->setMovie(movie);
            }
            if(fault_num.contains(",7,")){
                ui->chargeing_7->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_7->setMovie(movie);
            }
            if(fault_num.contains(",8,")){
                ui->chargeing_8->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_8->setMovie(movie);
            }
            if(fault_num.contains(",9,")){
                ui->chargeing_9->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_9->setMovie(movie);
            }
            if(fault_num.contains(",10,")){
                ui->chargeing_10->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_10->setMovie(movie);
            }
            if(fault_num.contains(",11,")){
                ui->chargeing_11->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_11->setMovie(movie);
            }
            if(fault_num.contains(",12,")){
                ui->chargeing_12->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_12->setMovie(movie);
            }
            if(fault_num.contains(",13,")){
                ui->chargeing_13->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_13->setMovie(movie);
            }
            if(fault_num.contains(",14,")){
                ui->chargeing_14->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_14->setMovie(movie);
            }
            if(fault_num.contains(",15,")){
                ui->chargeing_15->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_15->setMovie(movie);
            }
            if(fault_num.contains(",16,")){
                ui->chargeing_16->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_16->setMovie(movie);
            }
            if(fault_num.contains(",17,")){
                ui->chargeing_17->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_17->setMovie(movie);
            }
            if(fault_num.contains(",18,")){
                ui->chargeing_18->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_18->setMovie(movie);
            }
            if(fault_num.contains(",19,")){
                ui->chargeing_19->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_19->setMovie(movie);
            }
            if(fault_num.contains(",20,")){
                ui->chargeing_20->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_20->setMovie(movie);
            }
            if(fault_num.contains(",21,")){
                ui->chargeing_21->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_21->setMovie(movie);
            }
            if(fault_num.contains(",22,")){
                ui->chargeing_22->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_22->setMovie(movie);
            }
            if(fault_num.contains(",23,")){
                ui->chargeing_23->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_23->setMovie(movie);
            }
            if(fault_num.contains(",24")){
                ui->chargeing_24->setStyleSheet("background:red");
                ui->temp_title_10->setText("高温");
            }else {
                ui->chargeing_24->setMovie(movie);
            }
    }
    ui->tem_value->hide();
    ui->tem_value_2->hide();
            query.clear();
    QMovie *charge_movie = new QMovie(":/res/charge_movie.gif");
    ui->charge_movie->setMovie(charge_movie);
    charge_movie->start();
    movie->start();
    if (!modbusDevice->connectDevice()) {
        if (!(QMessageBox::information(this,tr("错误"),tr("设备未连接 ?"),tr("取消"),tr("确认")))){
            on_closeBtn_clicked();
        }
    }
}

void MainWindow::do_conn(){
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex, 100);
    mutex.unlock();
    if(modbusDevice->state() == QModbusDevice::ConnectedState){
        auto reply  = modbusDevice->sendReadRequest(readUnit,1);
            if(!reply->isFinished()){
                connect(reply, &QModbusReply::finished, this, &MainWindow::do_dec);
            }
    }
}

//读取电池状态参数
void MainWindow::do_dec(){
    QMovie *charge = new QMovie(":/res/charge.gif");
    auto reply  = qobject_cast<QModbusReply *>(sender());
    if (reply->error() == QModbusDevice::NoError) {
      const QModbusDataUnit unit = reply->result();
      for (uint i = 0; i < unit.valueCount(); i++) {
          const QString entry = tr("地址: %1, 16进制值: %2").arg(unit.startAddress() + i).arg(QString::number(unit.value(i),
                                                                                                         unit.registerType() <= QModbusDataUnit::Coils ? 10 : 16));
          bool ok;
          double dec = QString::number(unit.value(i)).toInt(&ok, 10);
          double value = dec/1000;
          if(i == 23) ui->fute_1->setText(QString::number(value,10,3));
          else if (i == 24) ui->fute_2->setText(QString::number(value,10,3));
          else if (i == 25) ui->fute_3->setText(QString::number(value,10,3));
          else if (i == 26) ui->fute_4->setText(QString::number(value,10,3));
          else if (i == 27) ui->fute_5->setText(QString::number(value,10,3));
          else if (i == 28) ui->fute_6->setText(QString::number(value,10,3));
          else if (i == 29) ui->fute_7->setText(QString::number(value,10,3));
          else if (i == 30) ui->fute_8->setText(QString::number(value,10,3));
          else if (i == 31) ui->fute_9->setText(QString::number(value,10,3));
          else if (i == 32) ui->fute_10->setText(QString::number(value,10,3));
          else if (i == 33) ui->fute_11->setText(QString::number(value,10,3));
          else if (i == 34) ui->fute_12->setText(QString::number(value,10,3));
          else if (i == 35) ui->fute_131->setText(QString::number(value,10,3));
          else if (i == 36) ui->fute_141->setText(QString::number(value,10,3));
          else if (i == 37) ui->fute_151->setText(QString::number(value,10,3));
          else if (i == 38) ui->fute_161->setText(QString::number(value,10,3));
          else if (i == 39) ui->fute_171->setText(QString::number(value,10,3));
          else if (i == 40) ui->fute_181->setText(QString::number(value,10,3));
          else if (i == 68) ui->fute_191->setText(QString::number(value,10,3));
          else if (i == 69) ui->fute_201->setText(QString::number(value,10,3));
          else if (i == 70) ui->fute_211->setText(QString::number(value,10,3));
          else if (i == 71) ui->fute_221->setText(QString::number(value,10,3));
          else if (i == 72) ui->fute_231->setText(QString::number(value,10,3));
          else if (i == 73) ui->fute_241->setText(QString::number(value,10,3));
          else if (i == 12) ui->temp_title_9->setText(QString::number(value,10,3)+"V");
          else if (i == 14) ui->temp_title_8->setText(QString::number(value,10,3)+"A");
          else if (i == 16) ui->temp_title_6->setText(QString::number(value,10,2)+"℃"),ui->tem_value->setText(QString::number(value,10,2)),ui->tem_value_2->setText(QString::number(value,10,2));
      }
    }else {
        timer->stop();
    }
}

//故障按钮点击事件
void MainWindow::on_faultBtn_clicked()
{
    timer->stop();
    modbusDevice->disconnectDevice();
    delete modbusDevice;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.clear();
        query.exec(QString("select * from login_state"));
        query.last();
        if(query.value(0)!="2"){
            fault *fw = new fault(this);
            fw->show();
        }else {
            login *lw = new login(this);
            lw->show();
        }
    }
    QSqlDatabase::removeDatabase("zz_bms.db");
    //检查登录状态

}

//关闭按钮点击事件
void MainWindow::on_closeBtn_clicked()
{
    if (!(QMessageBox::information(this,tr("请您认真考虑"),tr("退出本程序吗 ?"),tr("退出"),tr("取消")))){
        timer->stop();
        modbusDevice->disconnectDevice();
        delete modbusDevice;
        QApplication* app;
        app->exit(0);
    }
}

//每体按钮点击事件
void MainWindow::on_mediaBtn_clicked()
{
    timer->stop();
    modbusDevice->disconnectDevice();
    delete modbusDevice;
    media *mw = new media(this);
    mw->show();
}

void MainWindow::on_chargeBtn_pressed()
{
    timer->stop();
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex, 200);
    mutex.unlock();
            if(charge_state){
                charge_state = false;
                writeUnit.setValue(1,false);
                ui->chargeBtn->setStyleSheet("border-image:url(:/btn/chargeBtn.jpg);border:none");
            }else {
                charge_state = true;
                if(discharge_state == true){
                    discharge_state = false;
                    writeUnit.setValue(0,false);
                    ui->dischargeBtn->setStyleSheet("border-image:url(:/btn/discharge.jpg);border:none");
                    modbusDevice->sendWriteRequest(writeUnit,4);
                    QMutex mutex;
                    QWaitCondition sleep;
                    mutex.lock();
                    sleep.wait(&mutex, 200);
                    mutex.unlock();
                }
                writeUnit.setValue(1,true);
                ui->chargeBtn->setStyleSheet("border-image:url(:/btn/chargeBtnPushed.jpg);border:none");
            }
            modbusDevice->sendWriteRequest(writeUnit,4);
    timer->start();
}

void MainWindow::on_dischargeBtn_pressed()
{
    timer->stop();
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex, 100);
    mutex.unlock();
            if(discharge_state){
                discharge_state = false;
                writeUnit.setValue(0,false);
                ui->dischargeBtn->setStyleSheet("border-image:url(:/btn/discharge.jpg);border:none");
            }else {
                discharge_state = true;
                if(charge_state == true){
                    charge_state = false;
                    writeUnit.setValue(1,false);
                    ui->chargeBtn->setStyleSheet("border-image:url(:/btn/chargeBtn.jpg);border:none");
                    modbusDevice->sendWriteRequest(writeUnit,4);
                    QMutex mutex;
                    QWaitCondition sleep;
                    mutex.lock();
                    sleep.wait(&mutex, 200);
                    mutex.unlock();
                }
                writeUnit.setValue(0,true);
                ui->dischargeBtn->setStyleSheet("border-image:url(:/btn/dischargeBtnPushed.jpg);border:none");
            }
            modbusDevice->sendWriteRequest(writeUnit,4);
    timer->start();
}

void MainWindow::on_temperBtn_pressed()
{

    if(temp_state){
//        temp_state = false;
//        ui->temperBtn->setStyleSheet("background-image:url(:/btn/temper_btn.png);border:none;");
    }else {
        temp_state = true;
        ui->fute_1->hide();
        ui->fute_2->hide();
        ui->fute_3->hide();
        ui->fute_4->hide();
        ui->fute_5->hide();
        ui->fute_6->hide();
        ui->fute_7->hide();
        ui->fute_8->hide();
        ui->fute_9->hide();
        ui->fute_10->hide();
        ui->fute_11->hide();
        ui->fute_12->hide();
        ui->fute_131->hide();
        ui->fute_141->hide();
        ui->fute_151->hide();
        ui->fute_161->hide();
        ui->fute_171->hide();
        ui->fute_181->hide();
        ui->fute_191->hide();
        ui->fute_201->hide();
        ui->fute_211->hide();
        ui->fute_221->hide();
        ui->fute_231->hide();
        ui->fute_241->hide();
        vol_state = false;
        ui->label_2->setText("温度/℃");
        ui->label_7->setText("温度/℃");
        ui->tem_value->show();
        ui->tem_value_2->show();
        ui->temperBtn->setStyleSheet("background-image:url(:/btn/temper_btn_pushed.png);border:none;");
        ui->voltageBtn->setStyleSheet("background-image:url(:/btn/voltage_btn.png);border:none;");
    }
}

void MainWindow::on_voltageBtn_pressed()
{
    if(vol_state){
//        vol_state = false;
//        ui->voltageBtn->setStyleSheet("background-image:url(:/btn/voltage_btn.png);border:none;");
    }else {
        vol_state = true;
        ui->fute_1->show();
        ui->fute_2->show();
        ui->fute_3->show();
        ui->fute_4->show();
        ui->fute_5->show();
        ui->fute_6->show();
        ui->fute_7->show();
        ui->fute_8->show();
        ui->fute_9->show();
        ui->fute_10->show();
        ui->fute_11->show();
        ui->fute_12->show();
        ui->fute_131->show();
        ui->fute_141->show();
        ui->fute_151->show();
        ui->fute_161->show();
        ui->fute_171->show();
        ui->fute_181->show();
        ui->fute_191->show();
        ui->fute_201->show();
        ui->fute_211->show();
        ui->fute_221->show();
        ui->fute_231->show();
        ui->fute_241->show();
        temp_state = false;
        ui->label_7->setText("电压/伏特(v)");
        ui->label_2->setText("电压/伏特(v)");
        ui->tem_value->hide();
        ui->tem_value_2->hide();
        ui->temperBtn->setStyleSheet("background-image:url(:/btn/temper_btn.png);border:none;");
        ui->voltageBtn->setStyleSheet("background-image:url(:/btn/voltage_btn_pushed.png);border:none;");
    }
}

void MainWindow::on_title_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://zzvta.com")));
}
