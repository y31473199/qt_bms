#include "fault.h"
#include "ui_fault.h"
#include "QMessageBox"
#include "mainwindow.h"
#include "media.h"
#include "trouble_code.h"
#include "score.h"
#include "login.h"
#include "score_recode.h"
#include <QtDebug>
#include <QSqlQuery>
#include <QUuid>
#include <QTimer>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMutex>
#include <QWaitCondition>
#include <QModbusRtuSerialMaster>
#include <QPropertyAnimation>
#include <QDesktopServices>
#include <QUrl>
#include <QSize>

fault::fault(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fault),
    successfulEncoding(false)
{
    ui->setupUi(this);
//    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
//     animation->setDuration(500);
//     animation->setStartValue(0);
//     animation->setEndValue(1);
//     animation->start();
    setWindowIcon(QIcon(":/icon/zz.ico"));
    this->setWindowFlag(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_DeleteOnClose,1);
    Init();
//    connect(ui->bty_fault_1,SIGNAL(clicked()),this,SLOT(send16("01 05 00 00 FF 00 8C 3A")));

}



const QString con_1_0_open = "33 05 00 00 FF 00 88 28";
const QString con_1_1_open = "33 05 00 01 FF 00 D9 E8";
const QString con_1_2_open = "33 05 00 02 FF 00 29 E8";
const QString con_1_3_open = "33 05 00 03 FF 00 78 28";
const QString con_1_close = "33 05 00 FF 0 00 F9 E8";
const QString con_2_0_open = "25 05 00 00 FF 00 8A DE";
const QString con_2_1_open = "25 05 00 01 FF 00 DB 1E";
const QString con_2_2_open = "25 05 00 02 FF 00 2B 1E";
const QString con_2_3_open = "25 05 00 03 FF 00 7A DE";
const QString con_2_close = "25 05 00 FF 00 00 FB 1E";
const QString con_3_0_open = "03 05 00 00 FF 00 8D D8";
const QString con_3_1_open = "03 05 00 01 FF 00 DC 18";
const QString con_3_2_open = "03 05 00 02 FF 00 2C 18";
const QString con_3_3_open = "03 05 00 03 FF 00 7D D8";
const QString con_3_close = "03 05 00 FF 00 00 FC 18";
const QString con_4_0_open = "04 05 00 00 FF 00 8C 6F";
const QString con_4_1_open = "04 05 00 01 FF 00 DD AF";
const QString con_4_2_open = "04 05 00 02 FF 00 2D AF";
const QString con_4_3_open = "04 05 00 03 FF 00 7C 6F";
const QString con_4_close = "04 05 00 FF 00 00 FD AF";
const QString con_5_0_open = "05 05 00 00 FF 00 8D BE";
const QString con_5_1_open = "05 05 00 01 FF 00 DC 7E";
const QString con_5_2_open = "05 05 00 02 FF 00 2C 7E";
const QString con_5_3_open = "05 05 00 03 FF 00 7D BE";
const QString con_5_close = "05 05 00 FF 00 00 FC 7E";
const QString con_6_0_open = "06 05 00 00 FF 00 8D 8D";
const QString con_6_1_open = "06 05 00 01 FF 00 DC 4D";
const QString con_6_2_open = "06 05 00 02 FF 00 2C 4D";
const QString con_6_3_open = "06 05 00 03 FF 00 7D 8D";
const QString con_6_close = "06 05 00 FF 00 00 FC 4D";
const QString con_7_0_open = "07 05 00 00 FF 00 8C 5C";
const QString con_7_1_open = "07 05 00 01 FF 00 DD 9C";
const QString con_7_2_open = "07 05 00 02 FF 00 2D 9C";
const QString con_7_3_open = "07 05 00 03 FF 00 7C 5C";
const QString con_7_close = "07 05 00 FF 00 00 FD 9C";
const QString con_8_0_open = "08 05 00 00 FF 00 8C A3";
const QString con_8_1_open = "08 05 00 01 FF 00 DD 63";
const QString con_8_2_open = "08 05 00 02 FF 00 2D 63";
const QString con_8_3_open = "08 05 00 03 FF 00 7C A3";
const QString con_8_close = "08 05 00 FF 00 00 FD 63";
const QString con_9_0_open = "09 05 00 00 FF 00 8D 72";
const QString con_9_1_open = "09 05 00 01 FF 00 DC B2";
const QString con_9_2_open = "09 05 00 02 FF 00 2C B2";
const QString con_9_3_open = "09 05 00 03 FF 00 7D 72";
const QString con_9_close = "09 05 00 FF 00 00 FC B2";
const QString con_10_0_open = "10 05 00 00 FF 00 8F 7B";
const QString con_10_1_open = "10 05 00 01 FF 00 DE BB";
const QString con_10_2_open = "10 05 00 02 FF 00 2E BB";
const QString con_10_3_open = "10 05 00 03 FF 00 7F 7B";
const QString con_10_close = "10 05 00 FF 00 00 FE BB";
const QString con_11_0_open = "11 05 00 00 FF 00 8E AA";
const QString con_11_1_open = "11 05 00 01 FF 00 DF 6A";
const QString con_11_2_open = "11 05 00 02 FF 00 2F 6A";
const QString con_11_3_open = "11 05 00 03 FF 00 7E AA";
const QString con_11_close = "11 05 00 FF 00 00 FF 6A";
const QString con_12_0_open = "12 05 00 00 FF 00 8E 99";
const QString con_12_1_open = "12 05 00 01 FF 00 DF 59";
const QString con_12_2_open = "12 05 00 02 FF 00 2F 59";
const QString con_12_3_open = "12 05 00 03 FF 00 7E 99";
const QString con_12_close = "12 05 00 FF 00 00 FF 59";
const QString con_13_0_open = "13 05 00 00 FF 00 8F 48";
const QString con_13_1_open = "13 05 00 01 FF 00 DE 88";
const QString con_13_2_open = "13 05 00 02 FF 00 2E 88";
const QString con_13_3_open = "13 05 00 03 FF 00 7F 48";
const QString con_13_close = "13 05 00 FF 00 00 FE 88";
const QString con_14_0_open = "14 05 00 00 FF 00 8E FF";
const QString con_14_1_open = "14 05 00 01 FF 00 DF 3F";
const QString con_14_2_open = "14 05 00 02 FF 00 2F 3F";
const QString con_14_3_open = "14 05 00 03 FF 00 7E FF";
const QString con_14_close = "14 05 00 FF 00 00 FF 3F";
const QString con_15_0_open = "15 05 00 00 FF 00 8F 2E";
const QString con_15_1_open = "15 05 00 01 FF 00 DE EE";
const QString con_15_2_open = "15 05 00 02 FF 00 2E EE";
const QString con_15_3_open = "15 05 00 03 FF 00 7F 2E";
const QString con_15_close = "15 05 00 FF 00 00 FE EE";
const QString con_16_0_open = "16 15 00 00 FF 00 4E DE";
const QString con_16_1_open = "16 15 00 01 FF 00 1F 1E";
const QString con_16_2_open = "16 15 00 02 FF 00 EF 1E";
const QString con_16_3_open = "16 15 00 03 FF 00 BE DE";
const QString con_16_close = "16 15 00 FF 00 00 3F 1E";
const QString con_17_0_open = "17 05 00 00 FF 00 8E CC";
const QString con_17_1_open = "17 05 00 01 FF 00 DF 0C";
const QString con_17_2_open = "17 05 00 02 FF 00 2F 0C";
const QString con_17_3_open = "17 05 00 03 FF 00 7E CC";
const QString con_17_close = "17 05 00 FF 00 00 FF 0C";
const QString con_18_0_open = "18 05 00 00 FF 00 8E 33";
const QString con_18_1_open = "18 05 00 01 FF 00 DF F3";
const QString con_18_2_open = "18 05 00 02 FF 00 2F F3";
const QString con_18_3_open = "18 05 00 03 FF 00 7E 33";
const QString con_18_close = "18 05 00 FF 00 00 FF F3";
const QString con_19_0_open = "19 05 00 00 FF 00 8F E2";
const QString con_19_1_open = "19 05 00 01 FF 00 DE 22";
const QString con_19_2_open = "19 05 00 02 FF 00 2E 22";
const QString con_19_3_open = "19 05 00 03 FF 00 7F E2";
const QString con_19_close = "19 05 00 FF 00 00 FE 22";
const QString con_20_0_open = "20 05 00 00 FF 00 8A 8B";
const QString con_20_1_open = "20 05 00 01 FF 00 DB 4B";
const QString con_20_2_open = "20 05 00 02 FF 00 2B 4B";
const QString con_20_3_open = "20 05 00 03 FF 00 7A 8B";
const QString con_20_close = "20 05 00 FF 00 00 FB 4B";
const QString con_21_0_open = "21 05 00 00 FF 00 8B 5A";
const QString con_21_1_open = "21 05 00 01 FF 00 DA 9A";
const QString con_21_2_open = "21 05 00 02 FF 00 2A 9A";
const QString con_21_3_open = "21 05 00 03 FF 00 7B 5A";
const QString con_21_close = "21 05 00 FF 00 00 FA 9A";
const QString con_22_0_open = "22 05 00 00 FF 00 8B 69";
const QString con_22_1_open = "22 05 00 01 FF 00 DA A9";
const QString con_22_2_open = "22 05 00 02 FF 00 2A A9";
const QString con_22_3_open = "22 05 00 03 FF 00 7B 69";
const QString con_22_close = "22 05 00 FF 00 00 FA A9";
const QString con_23_0_open = "23 05 00 00 FF 00 8A B8";
const QString con_23_1_open = "23 05 00 01 FF 00 DB 78";
const QString con_23_2_open = "23 05 00 02 FF 00 2B 78";
const QString con_23_3_open = "23 05 00 03 FF 00 7A B8";
const QString con_23_close = "23 05 00 FF 00 00 FB 78";
const QString con_24_0_open = "24 05 00 00 FF 00 8B 0F";
const QString con_24_1_open = "24 05 00 01 FF 00 DA CF";
const QString con_24_2_open = "24 05 00 02 FF 00 2A CF";
const QString con_24_3_open = "24 05 00 03 FF 00 7B 0F";
const QString con_24_close = "24 05 00 FF 00 00 FA CF";

const QString con_bms_open = "02 05 00 00 00 00 CD F9";
const QString con_bms_close = "02 05 00 00 FF 00 8C 09";
const QString con_discharge_open = "02 05 00 01 00 00 9C 39";
const QString con_discharge_close = "02 05 00 01 FF 00 DD C9";
const QString con_charge_open = "02 05 00 02 00 00 6C 39";
const QString con_charge_close = "02 05 00 02 FF 00 2D C9";
const QString con_can_bus_open = "02 05 00 03 00 00 3D F9";
const QString con_can_bus_close = "02 05 00 03 FF 00 7C 09";



QString sen_code1 ;
QString sen_code2 ;
QString sen_code3 ;
QString sen_code4 ;
QString sen_code5 ;
QString sen_code6 ;
QString sen_code7 ;
QString sen_code8 ;
QString sen_code9 ;
QString sen_code10 ;
QString sen_code11 ;
QString sen_code12 ;
QString sen_code13 ;
QString sen_code14 ;
QString sen_code15 ;
QString sen_code16 ;
QString sen_code17 ;
QString sen_code18 ;
QString sen_code19 ;
QString sen_code20 ;
QString sen_code21 ;
QString sen_code22 ;
QString sen_code23 ;
QString sen_code24 ;
QString sen_code25 ;
QString sen_code26 ;
QString sen_code27 ;
QString sen_code28 ;

//学生分数
int student_score;
//用户种类
int fault_user_type;
//故障计数器
int addfault = 0;
//故障清单
QStringList fault_score;
QStringList fault_index;
QStringList fault_submit;
//故障状态
int fault_1 = 0;
int fault_2 = 0;
int fault_3 = 0;
int fault_4 = 0;
int fault_5 = 0;
int fault_6 = 0;
int fault_7 = 0;
int fault_8 = 0;
int fault_9 = 0;
int fault_10 = 0;
int fault_11 = 0;
int fault_12 = 0;
int fault_13 = 0;
int fault_14 = 0;
int fault_15 = 0;
int fault_16 = 0;
int fault_17 = 0;
int fault_18 = 0;
int fault_19 = 0;
int fault_20 = 0;
int fault_21 = 0;
int fault_22 = 0;
int fault_23 = 0;
int fault_24 = 0;
int bms_fault_index = 0;
int batout_fault_index = 0;
int batin_fault_index = 0;
int can_bus_fault_index = 0;
bool fault_on_off1 = false;
bool fault_on_off2 = false;
bool fault_on_off3 = false;
bool fault_on_off4 = false;
bool fault_on_off5 = false;
bool fault_on_off6 = false;
bool fault_on_off7 = false;
bool fault_on_off8 = false;
bool fault_on_off9 = false;
bool fault_on_off10 = false;
bool fault_on_off11 = false;
bool fault_on_off12 = false;
bool fault_on_off13 = false;
bool fault_on_off14 = false;
bool fault_on_off15 = false;
bool fault_on_off16 = false;
bool fault_on_off17 = false;
bool fault_on_off18 = false;
bool fault_on_off19= false;
bool fault_on_off20 = false;
bool fault_on_off21 = false;
bool fault_on_off22 = false;
bool fault_on_off23= false;
bool fault_on_off24= false;
bool bms_fault = false;
bool batout_fault = false;
bool batin_fault = false;
bool can_bus_fault = false;

int time_backtime;
int time_usetime;
int base_time_back;
//页面初始化
void fault::Init(){
    timer = new QTimer(this);
    student_score = 0;
    serialConnect();
    ui->time_set->setValidator(new QIntValidator(0, 999, this));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.exec(QString("create table score_(name text,score int)"));
        query.clear();
        query.exec(QString("DROP TABLE IF EXISTS softstate_;"));
        query.clear();
        query.exec(QString("create table softstate_(state int)"));
        query.clear();
        query.exec(QString("select * from user_ where user_name = 'admin';"));
       if(!query.next()){
           query.clear();
           query.exec(QString("INSERT INTO user_ VALUES('admin', 'admin', 1, 1);"));
           query.clear();
       }
        query.exec(QString("select * from login_state"));
        query.last();
        if(query.value(0)=="0"){
            query.exec(QString("insert into softstate_ values(1)"));
            query.clear();
            user = "student";
            query.clear();
            query.exec(QString("select * from fault_"));
            query.last();
            base_time_back = query.value(6).toInt();
            time_backtime = query.value(6).toInt();
            ui->time_set->hide();
            ui->fault_stat->hide();
            ui->test_time_title->hide();
            ui->clear_fault_btn->setDisabled(true);
            ui->data_reset_btn->setDisabled(true);
            ui->test_second->hide();
            ui->score_add_btn->setDisabled(true);
            //考试日期设置（暂未实现）
            ui->set_fault_btn->setText("开始答题");
            ui->submit_btn->setText("提交试卷");
            ui->time_use->show();
            ui->time_back->show();
            time_usetime = 0;
            connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
            timer->start(1000);
        }else if(query.value(0)=="1"){
            query.exec(QString("insert into softstate_ values(0)"));
            query.clear();
            user = "teacher";
            ui->time_set->show();
            ui->fault_stat->show();
            ui->test_time_title->show();
            ui->clear_fault_btn->setDisabled(false);
            ui->data_reset_btn->setDisabled(false);
            ui->test_second->show();
            //考试日期设置（暂未实现）
            ui->score_add_btn->setDisabled(false);
            ui->set_fault_btn->setText("故障设置");
            ui->submit_btn->setText("发布试题");
            ui->time_use->hide();
            ui->time_back->hide();
        }
    }
    QSqlDatabase::removeDatabase("zz_bms.db");
}

//连接单片机
void fault::serialConnect(){
    serial = new QSerialPort;
    //设置串口名
    //Linux
        //modbusDevice->setConnectionParameter(QModbusDevice::SerialPortNameParameter, "ttyUSB0");//串口参数
    serial->setPortName("COM3");
    //打开串口
    serial->open(QIODevice::ReadWrite);
    //设置波特率
    serial->setBaudRate(9600);
    //设置数据位数
    serial->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);
    //设置停止位
    serial->setStopBits(QSerialPort::OneStop);
}

//连接PLC
void fault::modbusPlcConnect(){

}

void fault::showTimelimit()
{
    if(time_backtime != 0)
    {
        time_backtime = time_backtime - 1; //注意字符类型
        time_usetime += 1;
        ui->time_back->setText(QString("剩余时间: %1 分 %2 秒").arg(QString::number(time_backtime/60),QString::number(time_backtime%60)));
        ui->time_use->setText(QString("已用时间: %1 分 %2 秒").arg(QString::number(time_usetime/60),QString::number(time_usetime%60)));
    }
    else
    {
        on_submit_btn_clicked();
        timer->stop();
        ui->time_use->setText("因数据库内时间为0,故停止计时!");
    }
}

fault::~fault()
{
    delete ui;
}

//关闭按钮点击事件
void fault::on_closeBtn_clicked()
{
    if (!(QMessageBox::information(this,tr("请您认真考虑"),tr("退出本程序吗 ?"),tr("退出"),tr("取消")))){
        QApplication* app;
        app->exit(0);
    }
}


//仪表按钮点击事件
void fault::on_meterBtn_clicked()
{
//    on_clear_fault_btn_clicked();
    if(serial){
        serial->disconnect();
    }
    delete serial;
    timer->stop();
    MainWindow *mw = new MainWindow();
    mw->show();
    this->close();
}


//媒体按钮点击事件
void fault::on_mediaBtn_clicked()
{
//    on_clear_fault_btn_clicked();
    serial->disconnect();
    delete serial;
    timer->stop();
    media *mw = new media();
    mw->show();
    this->close();
}

void fault::on_read_fault_btn_clicked()
{
    trouble_code *td = new  trouble_code(this);
    td->show();
}

void fault::on_score_add_btn_clicked()
{
    score *sd = new score(this);
    sd->show();
}

//清除故障
void fault::on_clear_fault_btn_clicked()
{
    ui->bty_fault_1->setCurrentIndex(0);
    ui->bty_fault_2->setCurrentIndex(0);
    ui->bty_fault_3->setCurrentIndex(0);
    ui->bty_fault_4->setCurrentIndex(0);
    ui->bty_fault_5->setCurrentIndex(0);
    ui->bty_fault_6->setCurrentIndex(0);
    ui->bty_fault_7->setCurrentIndex(0);
    ui->bty_fault_8->setCurrentIndex(0);
    ui->bty_fault_9->setCurrentIndex(0);
    ui->bty_fault_10->setCurrentIndex(0);
    ui->bty_fault_11->setCurrentIndex(0);
    ui->bty_fault_12->setCurrentIndex(0);
    ui->bty_fault_13->setCurrentIndex(0);
    ui->bty_fault_14->setCurrentIndex(0);
    ui->bty_fault_15->setCurrentIndex(0);
    ui->bty_fault_16->setCurrentIndex(0);
    ui->bty_fault_17->setCurrentIndex(0);
    ui->bty_fault_18->setCurrentIndex(0);
    ui->bty_fault_19->setCurrentIndex(0);
    ui->bty_fault_20->setCurrentIndex(0);
    ui->bty_fault_21->setCurrentIndex(0);
    ui->bty_fault_22->setCurrentIndex(0);
    ui->bty_fault_23->setCurrentIndex(0);
    ui->bty_fault_24->setCurrentIndex(0);
    ui->batin_fault->setCurrentIndex(0);
    ui->bms_fault->setCurrentIndex(0);
    ui->can_bus_fault->setCurrentIndex(0);
    ui->batout_fault->setCurrentIndex(0);
    fault_stat = 0;
    ui->fault_stat->setText(QString("已设置故障:0"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.clear();
        query.exec(QString("DROP TABLE IF EXISTS fault_;"));
        query.exec(QString("DROP TABLE IF EXISTS fault_code;"));
        query.clear();
        query.exec(QString("CREATE TABLE fault_(fault_1 text,fault_2 text,fault_3 text,fault_4 text,fault_5 text,fault_6 text,fault_date text);"));
        query.exec(QString("CREATE TABLE fault_code(fault_1_code text,fault_2_code text,fault_3_code text,fault_4_code text,fault_5_code text,fault_6_code text);"));
        db.close();
    }
    send16(con_1_close);
    send16(con_2_close);
    send16(con_3_close);
    send16(con_4_close);
    send16(con_5_close);
    send16(con_6_close);
    send16(con_7_close);
    send16(con_8_close);
    send16(con_9_close);
    send16(con_10_close);
    send16(con_11_close);
    send16(con_12_close);
    send16(con_13_close);
    send16(con_14_close);
    send16(con_15_close);
    send16(con_16_close);
    send16(con_17_close);
    send16(con_18_close);
    send16(con_19_close);
    send16(con_20_close);
    send16(con_21_close);
    send16(con_22_close);
    send16(con_23_close);
    send16(con_24_close);
    send16(con_bms_close);
    send16(con_charge_close);
    send16(con_can_bus_close);
    send16(con_discharge_close);
    QMessageBox::about(this, "清除故障", "故障已清除");
}

//数据重置
void fault::on_data_reset_btn_clicked()
{
    ui->bty_fault_1->setCurrentIndex(0);
    ui->bty_fault_2->setCurrentIndex(0);
    ui->bty_fault_3->setCurrentIndex(0);
    ui->bty_fault_4->setCurrentIndex(0);
    ui->bty_fault_5->setCurrentIndex(0);
    ui->bty_fault_6->setCurrentIndex(0);
    ui->bty_fault_7->setCurrentIndex(0);
    ui->bty_fault_8->setCurrentIndex(0);
    ui->bty_fault_9->setCurrentIndex(0);
    ui->bty_fault_10->setCurrentIndex(0);
    ui->bty_fault_11->setCurrentIndex(0);
    ui->bty_fault_12->setCurrentIndex(0);
    ui->bty_fault_13->setCurrentIndex(0);
    ui->bty_fault_14->setCurrentIndex(0);
    ui->bty_fault_15->setCurrentIndex(0);
    ui->bty_fault_16->setCurrentIndex(0);
    ui->bty_fault_17->setCurrentIndex(0);
    ui->bty_fault_18->setCurrentIndex(0);
    ui->bty_fault_19->setCurrentIndex(0);
    ui->bty_fault_20->setCurrentIndex(0);
    ui->bty_fault_21->setCurrentIndex(0);
    ui->bty_fault_22->setCurrentIndex(0);
    ui->bty_fault_23->setCurrentIndex(0);
    ui->bty_fault_24->setCurrentIndex(0);
    ui->batin_fault->setCurrentIndex(0);
    ui->bms_fault->setCurrentIndex(0);
    ui->can_bus_fault->setCurrentIndex(0);
    ui->batout_fault->setCurrentIndex(0);
    fault_stat = 0;
    student_score = 0;
    time_backtime = base_time_back;
    time_usetime = 0;
    timer->start();
//    connect(timer, SIGNAL(timeout()), this, SLOT(showTimelimit()));
    ui->fault_stat->setText(QString("已设置故障:0"));
    QMessageBox::about(this, "数据重置", "数据已重置");
}

void fault::on_background_info_btn_clicked()
{
//    QMessageBox::about(this, "抱歉", "背景资料功能我们正在拼命实现中");
    score_recode *sd = new score_recode(this);
    sd->show();
}

void  fault::send16(QString str){
    if(user == "teacher"){
//        qDebug()<<"教师设置故障";
        QByteArray buf;
            bool ok;
            char data;
            QStringList list;
            list = str.split(" ");
            for(int i = 0; i < list.count(); i++){
                if(list.at(i) == " ")
                    continue;
                if(list.at(i).isEmpty())
                    continue;
                data = (char)list.at(i).toInt(&ok, 16);
                buf.append(data);
            }
            serial->flush();
            QMutex mutex;
            QWaitCondition sleep;
            mutex.lock();
            sleep.wait(&mutex, 100);
            mutex.unlock();
            serial->write(buf);
    }
}
QStringList noScoreQrc;

//试题发布
void fault::on_submit_btn_clicked()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.clear();
        query.exec(QString("select * from login_state"));
        query.last();
//        qDebug()<<query.value(0);
        if(query.value(0)=="1"){
            //教师设置故障并存储到数据库
            query.clear();
            query.exec(QString("DROP TABLE IF EXISTS fault_;"));
            query.clear();
            query.exec(QString("CREATE TABLE fault_(fault_1 text,fault_2 text,fault_3 text,fault_4 text,fault_5 text,fault_6 text,fault_date text);"));
            query.prepare(QString("insert into fault_ values(:fault_1,:fault_2,:fault_3,:fault_4,:fault_5,:fault_6,:fault_date);"));
            QStringList really_fault;
            if (fault_index.size()>=1) {
                QString fault_index_1 = fault_index.value(0);
                query.bindValue(":fault_1", fault_index_1);
            }
            if (fault_index.size()>=2) {
                QString fault_index_2 = fault_index.value(1);
                query.bindValue(":fault_2", fault_index_2);
            }
            if (fault_index.size()>=3) {
                QString fault_index_3 = fault_index.value(2);
                query.bindValue(":fault_3", fault_index_3);
            }
            if (fault_index.size()>=4) {
                QString fault_index_4 = fault_index.value(3);
                query.bindValue(":fault_4", fault_index_4);
            }
            if (fault_index.size()>=5) {
                QString fault_index_5 = fault_index.value(4);
                query.bindValue(":fault_5", fault_index_5);
            }
            if (fault_index.size()>=6) {
                QString fault_index_6 = fault_index.value(5);
                query.bindValue(":fault_6", fault_index_6);
            }
            //考试时间
            if(ui->time_set->text()!=""){
                if(fault_index.size()==0){
                    QMessageBox::about(this, "操作状态", "您还未设置故障！");
                }else {
                    query.bindValue(":fault_date", QString::number(ui->time_set->text().toInt()*60));
                    query.exec();
                    QMessageBox::about(this, "操作状态", "成功！");
                }

            }else {
                QMessageBox::about(this, "错误", "请输入考试时间！");
            }

        }else {
            //学生答题
            query.clear();
            query.exec(QString("select * from fault_ ;"));
            query.last();
            if(fault_submit.size()==0){
                QMessageBox::about(this, "操作状态", "您还未答题！");
            }
            if (fault_submit.size()>=1) {
                for(int i = 0;i<6;i++){
//                    qDebug()<<query.value(i)<<"qDebug()<<query.value(i);";
                    if(fault_submit.indexOf(query.value(i).toString())!=-1){
                        //有题答对
                        student_score += 1;
                        //学生序号

                        fault_score.append(query.value(i).toString());
                    }else {
                        QStringList noScore = query.value(i).toString().split(",");
                        if(noScore.at(0)!="") noScoreQrc.append(noScore.at(0));
                    }
                }
                QUuid id = QUuid::createUuid();
                QString name_uuid = id.toString();
                query.clear();
                query.prepare(QString("insert into score_ values(:name,:score);"));
                query.bindValue(":name",name_uuid);
                query.bindValue(":score",student_score);
                query.exec();
                db.close();
                timer->stop();

                int levelIndex = 1;
                int versionIndex = 0;
                bool bExtent = true;
                int maskIndex = -1;
                QString noScor;
                noScor.clear();
                foreach(QString s ,noScoreQrc){
                    noScor.append(s+",");
                }
                QString encodeString = "您的分数为："+QString::number(student_score)+"\n您做错的题目为："+noScor+"\n您的考分序列号为："+name_uuid;

                successfulEncoding = qrEncode.EncodeData( levelIndex, versionIndex, bExtent, maskIndex, encodeString.toUtf8().data() );
                if ( !successfulEncoding )
                {
                    //创建失败
                    return;
                }

                int qrImageSize = qrEncode.m_nSymbleSize;

                encodeImageSize = qrImageSize + ( QR_MARGIN * 2 );
                QImage encodeImage( encodeImageSize, encodeImageSize, QImage::Format_Mono );
                encodeImage.fill( 1 );

                for ( int i = 0; i < qrImageSize; i++ )
                    for ( int j = 0; j < qrImageSize; j++ )
                        if ( qrEncode.m_byModuleData[i][j] )
                            encodeImage.setPixel( i + QR_MARGIN, j + QR_MARGIN, 0 );

                QMessageBox message(QMessageBox::NoIcon, "答题成功", "请扫描这个二维码查看分数！\n然后截图记录");
                QPixmap scoreQRCodeRes = QPixmap::fromImage( encodeImage );
                QSize picSize(200,200);
                QPixmap scoreQRCode = scoreQRCodeRes.scaled(picSize);
                message.setIconPixmap(QPixmap(scoreQRCode));
                message.exec();


//                if(!(QMessageBox::information(this,tr("答题成功"),tr("分数已提交至数据库，请牢记您的分数序列号！\n分数序列号:"+name_uuid.toLatin1()),tr("返回"),tr("取消")))){
//                    login *lw = new login(this);
//                    lw->show();
//                }
            }

        }
    }else {
        QMessageBox::about(this, "错误", "数据库未打开！");
    }
    QSqlDatabase::removeDatabase("zz_bms.db");

}


void fault::on_fault_stat_clicked()
{
    trouble_code *td = new  trouble_code(this);
    td->show();
}


void fault::on_logout_btn_clicked()
{
    if(!(QMessageBox::information(this,tr("请确认"),tr("请确认是否返回登录界面?"),tr("确认"),tr("取消")))){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("zz_bms.db");
        QSqlQuery query(db);
        if (db.open()) {
                query.clear();
                    query.exec(QString("CREATE TABLE login_state (login text);"));
                    query.clear();
                    query.exec(QString("insert into login_state values('2')"));
                    query.clear();
                    db.close();
                    //发送用户类型
                    if(timer!=NULL) timer->stop();
                    login *lw = new login(this);
                    lw->show();
            }else {
            QMessageBox::about(this, "错误", "数据库未打开");
        }
    }
}

void fault::on_time_set_returnPressed()
{
    QMessageBox::about(this, "考试时间设置", "成功！");
}

//QString加工工厂
void fault_factory(QString fault_s,int index){
    bool of = false;
    //如果故障存在则替换
    for(int i = 0 ;i<6;i++){
        if(fault_index.contains(fault_s+QString::number(i))){
            int temp = fault_index.indexOf(fault_s+QString::number(i));
            if(index == 0){
                fault_index.removeAt(temp);
                fault_submit.removeAt(temp);
                break;
            }else {
                fault_index.replace(temp,fault_s+QString::number(index));
                fault_submit.replace(temp,fault_s+QString::number(index));
                of = true;
                break;
            }
        }
    }

    int con = fault_s.mid(0,fault_s.length()-1).toInt();
    if(con == 1){
        if(index == 0) sen_code1 = con_1_close;
        if(index == 1) sen_code1 = con_1_0_open;
        if(index == 2) sen_code1 = con_1_1_open;
        if(index == 3) sen_code1 = con_1_2_open;
        if(index == 5) sen_code1 = con_1_3_open;
        if(index == 4) sen_code1 = con_1_close;
    }else if (con == 2) {
        if(index == 0) sen_code2 = con_2_close;
        if(index == 1) sen_code2 = con_2_0_open;
        if(index == 2) sen_code2 = con_2_1_open;
        if(index == 3) sen_code2 = con_2_2_open;
        if(index == 5) sen_code2 = con_2_3_open;
        if(index == 4) sen_code2 = con_2_close;
    }else if (con == 3) {
        if(index == 0) sen_code3 = con_3_close;
        if(index == 1) sen_code3 = con_3_0_open;
        if(index == 2) sen_code3 = con_3_1_open;
        if(index == 3) sen_code3 = con_3_2_open;
        if(index == 5) sen_code3 = con_3_3_open;
        if(index == 4) sen_code3 = con_3_close;
    }else if (con == 4) {
        if(index == 0) sen_code4 = con_4_close;
        if(index == 1) sen_code4 = con_4_0_open;
        if(index == 2) sen_code4 = con_4_1_open;
        if(index == 3) sen_code4 = con_4_2_open;
        if(index == 5) sen_code4 = con_4_3_open;
        if(index == 4) sen_code4 = con_4_close;
    }else if (con == 5) {
        if(index == 0) sen_code5 = con_5_close;
        if(index == 1) sen_code5 = con_5_0_open;
        if(index == 2) sen_code5 = con_5_1_open;
        if(index == 3) sen_code5 = con_5_2_open;
        if(index == 5) sen_code5 = con_5_3_open;
        if(index == 4) sen_code5 = con_5_close;
    }else if (con == 6) {
        if(index == 0) sen_code6 = con_6_close;
        if(index == 1) sen_code6 = con_6_0_open;
        if(index == 2) sen_code6 = con_6_1_open;
        if(index == 3) sen_code6 = con_6_2_open;
        if(index == 5) sen_code6 = con_6_3_open;
        if(index == 4) sen_code5 = con_5_close;
    }else if (con == 7) {
        if(index == 0) sen_code7 = con_7_close;
        if(index == 1) sen_code7 = con_7_0_open;
        if(index == 2) sen_code7 = con_7_1_open;
        if(index == 3) sen_code7 = con_7_2_open;
        if(index == 4) sen_code7 = con_7_3_open;
    }else if (con == 8) {
        if(index == 0) sen_code8 = con_8_close;
        if(index == 1) sen_code8 = con_8_0_open;
        if(index == 2) sen_code8 = con_8_1_open;
        if(index == 3) sen_code8 = con_8_2_open;
        if(index == 5) sen_code8 = con_8_3_open;
        if(index == 4) sen_code8 = con_8_close;
    }else if (con == 9) {
        if(index == 0) sen_code9 = con_9_close;
        if(index == 1) sen_code9 = con_9_0_open;
        if(index == 2) sen_code9 = con_9_1_open;
        if(index == 3) sen_code9 = con_9_2_open;
        if(index == 5) sen_code9 = con_9_3_open;
        if(index == 4) sen_code9 = con_9_close;
    }else if (con == 10) {
        if(index == 0) sen_code10 = con_10_close;
        if(index == 1) sen_code10 = con_10_0_open;
        if(index == 2) sen_code10 = con_10_1_open;
        if(index == 3) sen_code10 = con_10_2_open;
        if(index == 5) sen_code10 = con_10_3_open;
        if(index == 4) sen_code10 = con_10_close;
    }else if (con == 11) {
        if(index == 0) sen_code11 = con_11_close;
        if(index == 1) sen_code11 = con_11_0_open;
        if(index == 2) sen_code11 = con_11_1_open;
        if(index == 3) sen_code11 = con_11_2_open;
        if(index == 5) sen_code11 = con_11_3_open;
        if(index == 4) sen_code11 = con_11_close;
    }else if (con == 12) {
        if(index == 0) sen_code12 = con_12_close;
        if(index == 1) sen_code12 = con_12_0_open;
        if(index == 2) sen_code12 = con_12_1_open;
        if(index == 3) sen_code12 = con_12_2_open;
        if(index == 5) sen_code12 = con_12_3_open;
        if(index == 4) sen_code12 = con_12_close;
    }else if (con == 13) {
        if(index == 0) sen_code13 = con_13_close;
        if(index == 1) sen_code13 = con_13_0_open;
        if(index == 2) sen_code13 = con_13_1_open;
        if(index == 3) sen_code13 = con_13_2_open;
        if(index == 5) sen_code13 = con_13_3_open;
        if(index == 4) sen_code13 = con_13_close;
    }else if (con == 14) {
        if(index == 0) sen_code14 = con_14_close;
        if(index == 1) sen_code14 = con_14_0_open;
        if(index == 2) sen_code14 = con_14_1_open;
        if(index == 3) sen_code14 = con_14_2_open;
        if(index == 5) sen_code14 = con_14_3_open;
        if(index == 4) sen_code14 = con_14_close;
    }else if (con == 15) {
        if(index == 0) sen_code15 = con_15_close;
        if(index == 1) sen_code15 = con_15_0_open;
        if(index == 2) sen_code15 = con_15_1_open;
        if(index == 3) sen_code15 = con_15_2_open;
        if(index == 5) sen_code15 = con_15_3_open;
        if(index == 4) sen_code15 = con_15_close;
    }else if (con == 16) {
        if(index == 0) sen_code16 = con_16_close;
        if(index == 1) sen_code16 = con_16_0_open;
        if(index == 2) sen_code16 = con_16_1_open;
        if(index == 3) sen_code16 = con_16_2_open;
        if(index == 5) sen_code16 = con_16_3_open;
        if(index == 4) sen_code16 = con_16_close;
    }else if (con == 17) {
        if(index == 0) sen_code17 = con_17_close;
        if(index == 1) sen_code17 = con_17_0_open;
        if(index == 2) sen_code17 = con_17_1_open;
        if(index == 3) sen_code17 = con_17_2_open;
        if(index == 5) sen_code17 = con_17_3_open;
        if(index == 4) sen_code17 = con_17_close;
    }else if (con == 18) {
        if(index == 0) sen_code18 = con_18_close;
        if(index == 1) sen_code18 = con_18_0_open;
        if(index == 2) sen_code18 = con_18_1_open;
        if(index == 3) sen_code18 = con_18_2_open;
        if(index == 5) sen_code18 = con_18_3_open;
        if(index == 4) sen_code18 = con_18_close;
    }else if (con == 19) {
        if(index == 0) sen_code19 = con_19_close;
        if(index == 1) sen_code19 = con_19_0_open;
        if(index == 2) sen_code19 = con_19_1_open;
        if(index == 3) sen_code19 = con_19_2_open;
        if(index == 5) sen_code19 = con_19_3_open;
        if(index == 4) sen_code19 = con_19_close;
    }else if (con == 20) {
        if(index == 0) sen_code20 = con_20_close;
        if(index == 1) sen_code20 = con_20_0_open;
        if(index == 2) sen_code20 = con_20_1_open;
        if(index == 3) sen_code20 = con_20_2_open;
        if(index == 5) sen_code20 = con_20_3_open;
        if(index == 4) sen_code20 = con_20_close;
    }else if (con == 21) {
        if(index == 0) sen_code21 = con_21_close;
        if(index == 1) sen_code21 = con_21_0_open;
        if(index == 2) sen_code21 = con_21_1_open;
        if(index == 3) sen_code21 = con_21_2_open;
        if(index == 5) sen_code21 = con_21_3_open;
        if(index == 4) sen_code21 = con_21_close;
    }else if (con == 22) {
        if(index == 0) sen_code22 = con_22_close;
        if(index == 1) sen_code22 = con_22_0_open;
        if(index == 2) sen_code22 = con_22_1_open;
        if(index == 3) sen_code22 = con_22_2_open;
        if(index == 5) sen_code22 = con_22_3_open;
        if(index == 4) sen_code22 = con_22_close;
    }else if (con == 23) {
        if(index == 0) sen_code23 = con_23_close;
        if(index == 1) sen_code23 = con_23_0_open;
        if(index == 2) sen_code23 = con_23_1_open;
        if(index == 3) sen_code23 = con_23_2_open;
        if(index == 5) sen_code23 = con_23_3_open;
        if(index == 4) sen_code23 = con_23_close;
    }else if (con == 24) {
        if(index == 0) sen_code24 = con_24_close;
        if(index == 1) sen_code24 = con_24_0_open;
        if(index == 2) sen_code24 = con_24_1_open;
        if(index == 3) sen_code24 = con_24_2_open;
        if(index == 5) sen_code24 = con_24_3_open;
        if(index == 4) sen_code24 = con_24_close;
    }else if (con == 25) {
        if(index == 0) sen_code25 = con_bms_close;
        if(index == 1) sen_code25 = con_bms_open;
    }else if (con == 26) {
        if(index == 0) sen_code26 = con_discharge_close;
        if(index == 1) sen_code26 = con_discharge_open;
    }else if (con == 27) {
        if(index == 0) sen_code27 = con_charge_close;
        if(index == 1) sen_code27 = con_charge_open;
    }else if (con == 28) {
        if(index == 0) sen_code28 = con_can_bus_close;
        if(index == 1) sen_code28 = con_can_bus_open;
    }



    if(! of && index != 0){
        fault_index.append(fault_s+QString::number(index));
        fault_submit.append(fault_s+QString::number(index));
    }
}

//故障计数器与故障验证
bool fault::check_fault(int index, bool &fault_on_off){
    if(index != 0){
        if(!fault_on_off){
            if(fault_stat>=6){
                QMessageBox::about(this, "抱歉", "电池故障设置暂只支持6个！");
                return true;
            }else {
                fault_stat += 1;
                fault_on_off = true;
            }
        }
    }else {
        if(index == 0){
            if(fault_on_off){
                fault_stat -= 1;
                fault_on_off = false;
            }
        }
    }
    return false;
}




void fault::on_bty_fault_1_activated(int index)
{
    if(check_fault(index,fault_on_off1))ui->bty_fault_1->setCurrentIndex(0);
    fault_factory("1,",index);
    send16(con_1_close);
    send16(sen_code1);
    fault_1 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_2_activated(int index)
{
    if(check_fault(index,fault_on_off2))ui->bty_fault_2->setCurrentIndex(0);
    fault_factory("2,",index);
    send16(con_2_close);
    send16(sen_code2);
    fault_2 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_3_activated(int index)
{
    if(check_fault(index,fault_on_off3))ui->bty_fault_3->setCurrentIndex(0);
    fault_factory("3,",index);
    send16(con_3_close);
    send16(sen_code3);
    fault_3 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_4_activated(int index)
{
    if(check_fault(index,fault_on_off4))ui->bty_fault_4->setCurrentIndex(0);
    fault_factory("4,",index);
    send16(con_4_close);
    send16(sen_code4);
    fault_4 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_5_activated(int index)
{
    if(check_fault(index,fault_on_off5))ui->bty_fault_5->setCurrentIndex(0);
    fault_factory("5,",index);
    send16(con_5_close);
    send16(sen_code5);
    fault_5 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_6_activated(int index)
{
    if(check_fault(index,fault_on_off6))ui->bty_fault_6->setCurrentIndex(0);
    fault_factory("6,",index);
    send16(con_6_close);
    send16(sen_code6);
    fault_6 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_7_activated(int index)
{
    if(check_fault(index,fault_on_off7))ui->bty_fault_7->setCurrentIndex(0);
    fault_factory("7,",index);
    send16(con_7_close);
    send16(sen_code7);
    fault_7 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_8_activated(int index)
{
    if(check_fault(index,fault_on_off8))ui->bty_fault_8->setCurrentIndex(0);
    fault_factory("8,",index);
    send16(con_8_close);
    send16(sen_code8);
    fault_8 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_9_activated(int index)
{
    if(check_fault(index,fault_on_off9))ui->bty_fault_9->setCurrentIndex(0);
   fault_factory("9,",index);
   send16(con_9_close);
   send16(sen_code9);
    fault_9 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_10_activated(int index)
{
    if(check_fault(index,fault_on_off10))ui->bty_fault_10->setCurrentIndex(0);
    fault_factory("10,",index);
    send16(con_10_close);
    send16(sen_code10);
    fault_10 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_11_activated(int index)
{
    if(check_fault(index,fault_on_off11))ui->bty_fault_11->setCurrentIndex(0);
    fault_factory("11,",index);
    send16(con_11_close);
    send16(sen_code11);
    fault_11 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_12_activated(int index)
{
    if(check_fault(index,fault_on_off12))ui->bty_fault_12->setCurrentIndex(0);
    fault_factory("12,",index);
    send16(con_12_close);
    send16(sen_code12);
    fault_12 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_13_activated(int index)
{
    if(check_fault(index,fault_on_off13))ui->bty_fault_13->setCurrentIndex(0);
    fault_factory("13,",index);
    send16(con_13_close);
    send16(sen_code13);
    fault_13 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_14_activated(int index)
{
    if(check_fault(index,fault_on_off14))ui->bty_fault_14->setCurrentIndex(0);
    fault_factory("14,",index);
    send16(con_14_close);
    send16(sen_code14);
    fault_14 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_15_activated(int index)
{
    if(check_fault(index,fault_on_off15))ui->bty_fault_15->setCurrentIndex(0);
    fault_factory("15,",index);
    send16(con_15_close);
    send16(sen_code15);
    fault_15 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_16_activated(int index)
{
    if(check_fault(index,fault_on_off16))ui->bty_fault_16->setCurrentIndex(0);
    fault_factory("16,",index);
    send16(con_16_close);
    send16(sen_code16);
    fault_16 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_17_activated(int index)
{
    if(check_fault(index,fault_on_off17))ui->bty_fault_17->setCurrentIndex(0);
    fault_factory("17,",index);
    send16(con_17_close);
    send16(sen_code17);
    fault_17 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_18_activated(int index)
{
    if(check_fault(index,fault_on_off18))ui->bty_fault_18->setCurrentIndex(0);
    fault_factory("18,",index);
    send16(con_18_close);
    send16(sen_code18);
    fault_18 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_19_activated(int index)
{
    if(check_fault(index,fault_on_off19))ui->bty_fault_19->setCurrentIndex(0);
    fault_factory("19,",index);
    send16(con_19_close);
    send16(sen_code19);
    fault_19 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_20_activated(int index)
{
    if(check_fault(index,fault_on_off20))ui->bty_fault_20->setCurrentIndex(0);
    fault_factory("20,",index);
    send16(con_20_close);
    send16(sen_code20);
    fault_20 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_21_activated(int index)
{
    if(check_fault(index,fault_on_off21))ui->bty_fault_21->setCurrentIndex(0);
    fault_factory("21,",index);
    send16(con_21_close);
    send16(sen_code21);
    fault_21 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_22_activated(int index)
{
    if(check_fault(index,fault_on_off22))ui->bty_fault_22->setCurrentIndex(0);
    fault_factory("22,",index);
    send16(con_22_close);
    send16(sen_code22);
    fault_22 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_23_activated(int index)
{
    if(check_fault(index,fault_on_off23))ui->bty_fault_23->setCurrentIndex(0);
    fault_factory("23,",index);
    send16(con_23_close);
    send16(sen_code23);
    fault_23 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_bty_fault_24_activated(int index)
{
    if(check_fault(index,fault_on_off24))ui->bty_fault_24->setCurrentIndex(0);
    fault_factory("24,",index);
    send16(con_24_close);
    send16(sen_code24);
    fault_24 = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}


void fault::on_bms_fault_activated(int index)
{
    if(check_fault(index,bms_fault))ui->bms_fault->setCurrentIndex(0);
    fault_factory("25,",index);
    send16(con_bms_close);
    send16(sen_code25);
    bms_fault_index = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));

}

void fault::on_batout_fault_activated(int index)
{
    if(check_fault(index,batout_fault))ui->bms_fault->setCurrentIndex(0);
    fault_factory("26,",index);
    send16(con_discharge_close);
    send16(sen_code26);
    batout_fault_index = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_batin_fault_activated(int index)
{
    if(check_fault(index,batin_fault))ui->bms_fault->setCurrentIndex(0);
    fault_factory("27,",index);
    send16(con_charge_close);
    send16(sen_code27);
    batin_fault_index = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_can_bus_fault_activated(int index)
{
    if(check_fault(index,can_bus_fault))ui->bms_fault->setCurrentIndex(0);
    fault_factory("28,",index);
    send16(con_can_bus_close);
    send16(sen_code28);
    can_bus_fault_index = index;
    ui->fault_stat->setText(QString("已设置故障:%1").arg(fault_stat));
}

void fault::on_set_fault_btn_clicked()
{
    on_data_reset_btn_clicked();
}
