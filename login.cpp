#include "login.h"
#include "ui_login.h"
#include "fault.h"
#include "qdebug.h"
#include "media.h"
#include "mainwindow.h"
#include "qmessagebox.h"
#include <QSqlQuery>

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)

{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/icon/zz.ico"));
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
     db.setDatabaseName("zz_bms.db");
     QSqlQuery query(db);
     if (db.open()) {
         query.clear();
         query.exec(QString("DROP TABLE IF EXISTS 'user_'"));
         query.clear();
         query.exec(QString("CREATE TABLE user_ (user_name TEXT NOT NULL,user_pwd TEXT NOT NULL,user_state integer,user_type integer);"));
         query.clear();
         query.exec(QString("select * from user_ where user_name = 'admin';"));
        if(!query.next()){
            query.clear();
            query.exec(QString("INSERT INTO user_ VALUES('admin', 'admin', 1, 1);"));
        }
     }
     query.clear();
}

login::~login()
{
    delete ui;
}

//登录按钮点击
void login::on_submit_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.clear();
        query.prepare(QString("select * from user_ where user_name = :user_name and user_pwd = :user_pwd ;"));
        query.bindValue(":user_name", ui->user->text());
        query.bindValue(":user_pwd", ui->password->text());
        query.exec();
        if(query.next()){
            query.exec(QString("CREATE TABLE login_state (login text);"));
            query.clear();
            query.exec(QString("insert into login_state values('1')"));
            query.clear();
            db.close();
            fault *fw = new fault(this);
            fw->show();
            //发送用户类型
        }else {
            QMessageBox::about(this, "登录失败", "账号或密码错误");
        }
    }else {
        QMessageBox::about(this, "错误", "数据库未打开");
    }
    QSqlDatabase::removeDatabase("zz_bms.db");
}

void login::on_mediaBtn_clicked()
{
    media *mw = new media(this);
    mw->show();
}

void login::on_meterBtn_clicked()
{
    MainWindow *mw = new MainWindow(this);
    mw->show();
}

void login::on_closeBtn_clicked()
{
    if (!(QMessageBox::information(this,tr("请您认真考虑"),tr("退出本程序吗 ?"),tr("退出"),tr("取消")))){
        QApplication* app;
        app->exit(0);
    }
}
//学生按钮点击
void login::on_account_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if(db.open()){
        query.exec(QString("CREATE TABLE login_state (login text);"));
        query.clear();
        query.exec(QString("insert into login_state values('0')"));
        query.clear();
        db.close();
        fault *fw = new fault(this);
        fw->show();
    }else {
        QMessageBox::about(this, "错误", "数据库未打开");
    }
    QSqlDatabase::removeDatabase("zz_bms.db");
}

void login::on_password_returnPressed()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("zz_bms.db");
    QSqlQuery query(db);
    if (db.open()) {
        query.clear();
        query.prepare(QString("select * from user_ where user_name = :user_name and user_pwd = :user_pwd ;"));
        query.bindValue(":user_name", ui->user->text());
        query.bindValue(":user_pwd", ui->password->text());
        query.exec();
        if(query.next()){
            query.exec(QString("CREATE TABLE login_state (login text);"));
            query.clear();
            query.exec(QString("insert into login_state values('1')"));
            query.clear();
            db.close();
            fault *fw = new fault(this);
            fw->show();
            //发送用户类型
        }else {
            QMessageBox::about(this, "登录失败", "账号或密码错误");
        }
    }else {
        QMessageBox::about(this, "错误", "数据库未打开");
    }
    QSqlDatabase::removeDatabase("zz_bms.db");
}
