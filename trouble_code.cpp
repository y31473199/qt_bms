#include "trouble_code.h"
#include "ui_trouble_code.h"

#include <QSqlQuery>
#include "QMessageBox"
#include <QtDebug>
#include "fault.h"

trouble_code::trouble_code(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trouble_code)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/icon/zz.ico"));
    Init();
}

//故障状态
extern int fault_1;
extern int fault_2;
extern int fault_3;
extern int fault_4;
extern int fault_5;
extern int fault_6;
extern int fault_7;
extern int fault_8;
extern int fault_9;
extern int fault_10;
extern int fault_11;
extern int fault_12;
extern int fault_13;
extern int fault_14;
extern int fault_15;
extern int fault_16;
extern int fault_17;
extern int fault_18;
extern int fault_19;
extern int fault_20;
extern int fault_21;
extern int fault_22;
extern int fault_23;
extern int fault_24;
extern int bms_fault_index;
extern int batout_fault_index;
extern int batin_fault_index;
extern int can_bus_fault_index;
trouble_code::~trouble_code()
{
    delete ui;
}

void trouble_code::Init(){
    fault_modle = new QStandardItemModel(this);
    fault_modle_code = new QStandardItemModel(this);
    fault_modle_code->clear();
    fault_modle->clear();
    QStringList strList;
    QStringList fault_code;
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
        query.exec(QString("select * from login_state"));
        query.last();
        if(query.value(0)!="1"){
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
            if(fault_index_1.at(0) != ""){
                fault_code.append("ZZFC"+fault_index_1.at(0)+"ap"+fault_index_1.at(1));
            }
            if(fault_index_2.at(0) != ""){
                fault_code.append("ZZFC"+fault_index_2.at(0)+"ap"+fault_index_2.at(1));
            }
            if(fault_index_3.at(0) != ""){
                fault_code.append("ZZFC"+fault_index_3.at(0)+"ap"+fault_index_3.at(1));
            }
            if(fault_index_4.at(0) != ""){
                fault_code.append("ZZFC"+fault_index_4.at(0)+"ap"+fault_index_4.at(1));
            }
            if(fault_index_5.at(0) != ""){
                fault_code.append("ZZFC"+fault_index_5.at(0)+"ap"+fault_index_5.at(1));
            }
            if(fault_index_6.at(0) != ""){
                fault_code.append("ZZFC"+fault_index_6.at(0)+"ap"+fault_index_6.at(1));
            }
            query.clear();
            int nCount = fault_code.size();
            for(int i = 0; i < nCount; i++)
               {
                   QString fault_code_str = static_cast<QString>(fault_code.at(i));
                   QStandardItem *item_code = new QStandardItem(fault_code_str);
                   if(i % 2 == 1)
                   {
                       QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                       linearGrad.setColorAt(0, Qt::darkGreen);
                       linearGrad.setColorAt(1, Qt::yellow);
                       QBrush brush(linearGrad);
                   }
                   fault_modle_code->appendRow(item_code);
               }
            ui->clear_fault->hide();
            ui->fault_code_list->setModel(fault_modle_code);
        }else if (query.value(0)=="1") {
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
            if(fault_index_1.at(0) != ""){
                if(fault_index_1.at(1)=="1") strList.append("第"+fault_index_1.at(0)+"串电池：过放！");
                else if(fault_index_1.at(1)=="2") strList.append("第"+fault_index_1.at(0)+"串电池：漏电！");
                else if(fault_index_1.at(1)=="3") strList.append("第"+fault_index_1.at(0)+"串电池：高温！");
                else if(fault_index_1.at(1)=="4") strList.append("第"+fault_index_1.at(0)+"串电池：短路！");
                else if(fault_index_1.at(1)=="5") strList.append("第"+fault_index_1.at(0)+"串电池：断路！");
                fault_code.append("ZZFC"+fault_index_1.at(0)+"ap"+fault_index_1.at(1));
            }
            if(fault_index_2.at(0) != ""){
                if(fault_index_2.at(1)=="1") strList.append("第"+fault_index_2.at(0)+"串电池：过放！");
                else if(fault_index_2.at(1)=="2") strList.append("第"+fault_index_2.at(0)+"串电池：漏电！");
                else if(fault_index_2.at(1)=="3") strList.append("第"+fault_index_2.at(0)+"串电池：高温！");
                else if(fault_index_2.at(1)=="4") strList.append("第"+fault_index_2.at(0)+"串电池：短路！");
                else if(fault_index_2.at(1)=="5") strList.append("第"+fault_index_2.at(0)+"串电池：断路！");
                fault_code.append("ZZFC"+fault_index_2.at(0)+"ap"+fault_index_2.at(1));
            }
            if(fault_index_3.at(0) != ""){
                if(fault_index_3.at(1)=="1") strList.append("第"+fault_index_3.at(0)+"串电池：过放！");
                else if(fault_index_3.at(1)=="2") strList.append("第"+fault_index_3.at(0)+"串电池：漏电！");
                else if(fault_index_3.at(1)=="3") strList.append("第"+fault_index_3.at(0)+"串电池：高温！");
                else if(fault_index_3.at(1)=="4") strList.append("第"+fault_index_3.at(0)+"串电池：短路！");
                else if(fault_index_3.at(1)=="5") strList.append("第"+fault_index_3.at(0)+"串电池：断路！");
                fault_code.append("ZZFC"+fault_index_3.at(0)+"ap"+fault_index_3.at(1));
            }
            if(fault_index_4.at(0) != ""){
                if(fault_index_4.at(1)=="1") strList.append("第"+fault_index_4.at(0)+"串电池：过放！");
                else if(fault_index_4.at(1)=="2") strList.append("第"+fault_index_4.at(0)+"串电池：漏电！");
                else if(fault_index_4.at(1)=="3") strList.append("第"+fault_index_4.at(0)+"串电池：高温！");
                else if(fault_index_4.at(1)=="4") strList.append("第"+fault_index_4.at(0)+"串电池：短路！");
                else if(fault_index_4.at(1)=="5") strList.append("第"+fault_index_4.at(0)+"串电池：断路！");
                fault_code.append("ZZFC"+fault_index_4.at(0)+"ap"+fault_index_4.at(1));
            }
            if(fault_index_5.at(0) != ""){
                if(fault_index_5.at(1)=="1") strList.append("第"+fault_index_5.at(0)+"串电池：过放！");
                else if(fault_index_5.at(1)=="2") strList.append("第"+fault_index_5.at(0)+"串电池：漏电！");
                else if(fault_index_5.at(1)=="3") strList.append("第"+fault_index_5.at(0)+"串电池：高温！");
                else if(fault_index_5.at(1)=="4") strList.append("第"+fault_index_5.at(0)+"串电池：短路！");
                else if(fault_index_5.at(1)=="5") strList.append("第"+fault_index_5.at(0)+"串电池：断路！");
                fault_code.append("ZZFC"+fault_index_5.at(0)+"ap"+fault_index_5.at(1));
            }
            if(fault_index_6.at(0) != ""){
                if(fault_index_6.at(1)=="1") strList.append("第"+fault_index_6.at(0)+"串电池：过放！");
                else if(fault_index_6.at(1)=="2") strList.append("第"+fault_index_6.at(0)+"串电池：漏电！");
                else if(fault_index_6.at(1)=="3") strList.append("第"+fault_index_6.at(0)+"串电池：高温！");
                else if(fault_index_6.at(1)=="4") strList.append("第"+fault_index_6.at(0)+"串电池：短路！");
                else if(fault_index_6.at(1)=="5") strList.append("第"+fault_index_6.at(0)+"串电池：断路！");
                fault_code.append("ZZFC"+fault_index_6.at(0)+"ap"+fault_index_6.at(1));
            }
            query.clear();
            int nCount = strList.size();
            for(int i = 0; i < nCount; i++)
               {
                   QString string = static_cast<QString>(strList.at(i));
                   QString fault_code_str = static_cast<QString>(fault_code.at(i));
                   QStandardItem *item = new QStandardItem(string);
                   QStandardItem *item_code = new QStandardItem(fault_code_str);
                   if(i % 2 == 1)
                   {
                       QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                       linearGrad.setColorAt(0, Qt::darkGreen);
                       linearGrad.setColorAt(1, Qt::yellow);
                       QBrush brush(linearGrad);
                       item->setBackground(brush);
                   }
                   fault_modle->appendRow(item);
                   fault_modle_code->appendRow(item_code);
               }
            ui->fault_code_list->setModel(fault_modle_code);
            ui->fault_desc->setModel(fault_modle);
        }
    }
}

void trouble_code::on_cancle_clicked()
{
    this->close();

}


void trouble_code::on_clear_fault_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.clear();
        query.exec(QString("DROP TABLE IF EXISTS fault_;"));
        query.clear();
        query.exec(QString("CREATE TABLE fault_(fault_1 text,fault_2 text,fault_3 text,fault_4 text,fault_5 text,fault_6 text,fault_date text);"));
        query.exec(QString("CREATE TABLE fault_code(fault_1_code text,fault_2_code text,fault_3_code text,fault_4_code text,fault_5_code text,fault_6_code text);"));
        db.close();
    }
    QMessageBox::about(this, "清除故障码", "成功！");
    this->close();
}

