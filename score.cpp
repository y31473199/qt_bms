#include "score.h"
#include "ui_score.h"

#include <QSqlQuery>
#include "QMessageBox"
#include <QStandardItemModel>
#include <QtDebug>

QStringList student_name;
QStringList score_detials;

score::score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::score)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/zz.ico"));
    this->setWindowFlag(Qt::FramelessWindowHint);
    fault_modle = new QStandardItemModel(this);
    fault_score = new QStandardItemModel(this);
    fault_modle->clear();
    fault_score->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    bool on_off = false;
    if (db.open()) {
        query.clear();
        query.exec(QString("select * from score_"));
        while (query.next()) {
            student_name.append(query.value(0).toString());
            score_detials.append(query.value(1).toString());
            on_off = true;
        }
    }
    if(on_off){
        for(int i = 0; i < student_name.size(); i++)
           {
               QString name = static_cast<QString>(student_name.at(i));
               QString score_str = static_cast<QString>(score_detials.at(i));
               QStandardItem *item = new QStandardItem(name);
               QStandardItem *sco = new QStandardItem(score_str);
               if(i % 2 == 1)
               {
                   QLinearGradient linearGrad(QPointF(0, 0), QPointF(200, 200));
                   linearGrad.setColorAt(0, Qt::darkGreen);
                   linearGrad.setColorAt(1, Qt::yellow);
                   QBrush brush(linearGrad);
                   item->setBackground(brush);
                   sco->setBackground(brush);
               }
               fault_modle->appendRow(item);
               fault_score->appendRow(sco);
           }
        student_name.clear();
        score_detials.clear();
    }
    ui->score_detiles->setModel(fault_score);
    ui->student_name->setModel(fault_modle);

}


score::~score()
{
    delete ui;
}

void score::on_cancle_clicked()
{

    this->close();
}

void score::on_clear_score_clicked()
{
    fault_modle->clear();
    fault_score->clear();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.clear();
        query.exec(QString("drop table score_;"));
    }
    ui->student_name->setModel(fault_modle);
    ui->score_detiles->setModel(fault_score);
    QMessageBox::about(this, "清除分数", "成功！");
}
