#include "media.h"
#include "ui_media.h"
#include "qmessagebox.h"
#include "mainwindow.h"
#include "fault.h"
#include "QtDebug"
#include "QDir"
#include "login.h"


media::media(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::media)
{

    ui->setupUi(this);
    setWindowIcon(QIcon(":/icon/zz.ico"));
    Init();
    timeClock = new QTimer(this);
    connect(timeClock,SIGNAL(timeout()),this,SLOT(timeDone()));  //定时更新视频进度条

}

media::~media()
{
    delete ui;
}
bool on_off_slider;

//窗口初始化
void media::Init(){
    //获取播放列表
    //linux
//    QDir dir("/home/alan/Videos/");
    //Windows
    QDir dir("C:/Users/user/Videos/");
    QStringList nameFilters;
    nameFilters << "*.avi" << "*.wav" << "*.mp4";
    playList = dir.entryList(nameFilters, QDir::Files | QDir::NoSymLinks);
    for(int i = 0; i< playList.size();++i)
    {
        ui->listVideo->addItem(playList.at(i));
    }
    //创建进程
    playProcess = new QProcess(this);
    //初始化播放状态
    isPlaying = 0;
    //播放列表连接槽
    QObject::connect(ui->listVideo, SIGNAL(currentTextChanged(const QString &)), SLOT(playVideo(const QString &)));
    QObject::connect(playProcess,SIGNAL(readyRead()),this,SLOT(doProcessReadyRead()));
}

void media::doProcessReadyRead(){
    QString position = QString(playProcess->readAll());
    if(position.contains("ANS_PERCENT_POSITION")){
        QStringList video_data =  position.split("\r\n");
        qDebug()<<video_data;
        video_data.at(0).split("=").at(1);
        QString indexNum = video_data.at(0).split("=").at(1);

        ui->seek->setValue(indexNum.toInt());
        QString now_time = video_data.at(1).split("=").at(1);
        QString last_time = video_data.at(2).split("=").at(1);
        ui->time_labet->setText(now_time+"/"+last_time+"秒");
        on_off_slider = false;
    }
}


void media::timeDone()  //定时槽函数
{
    playProcess->write("get_percent_pos\n");  //获得视频百分比
    playProcess->write("get_time_pos\n");  //获得视频当前时间
    playProcess->write("get_time_length\n");  // 获得视频总时间
}

//关闭按钮点击事件
void media::on_closeBtn_clicked()
{
    if (!(QMessageBox::information(this,tr("请您认真考虑"),tr("退出本程序吗 ?"),tr("退出"),tr("取消")))){
        QApplication* app;
        app->exit(0);
    }
}

//仪表按钮点击事件
void media::on_meterBtn_clicked()
{
    playProcess->close();
    MainWindow *mw = new MainWindow(this);
    mw->show();
}

//故障按钮点击事件
void media::on_faultBtn_clicked()
{
    playProcess->close();
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

}

//播放按钮点击事件
void media::on_playBtn_clicked()
{
    qDebug()<<isPlaying;
    if(isPlaying == 0){ //stop>>Neverplay
        return;
    }else if (isPlaying == 1) { //play>>stop
        cmd = "pause\n";
        timeClock->stop();
        playProcess->write(cmd.toLatin1());
        isPlaying = 2;
    }else if (isPlaying ==2) {//stop>>play
        cmd = "pause\n";
        timeClock->start();
        playProcess->write(cmd.toLatin1());
        isPlaying = 1;
    }
}

//播放视频
void media::playVideo(const QString fileName){
    qDebug()<<fileName;
    playProcess->close();
    //linux_mplayer
//    QString videoPath = "/home/alan/Videos/" + fileName;
//    QString programe = "/usr/bin/mplayer";
    QString videoPath = "C:/Users/user/Videos/" + fileName;
    QString programe = "C:/Mplayer/mplayer.exe";
    QStringList  arguments;
    arguments << videoPath;
    arguments << "-slave";
    arguments << "-quiet";
    arguments << "-wid";
    arguments << QString::number(ui->video->winId());
    playProcess->start(programe,arguments);
    timeClock->start(1000*1);
    isPlaying = 1;
}

//修改音量
void media::on_dial_valueChanged(int value)
{
    if(isPlaying == 1){
        cmd = QString("volume %1 1\n").arg(value);
        playProcess->write(cmd.toLatin1());
    }
}

//进度跳转
void media::on_seek_valueChanged(int value)
{
    if(isPlaying == 1){
        if(on_off_slider){
            cmd = QString("seek %1 1\n").arg(value);
            playProcess->write(cmd.toLatin1());
            timeClock->start();
        }
    }
}

//快退
void media::on_previousBtn_clicked()
{
    plan = plan - 5;
    if(isPlaying == 1){
        cmd = QString("seek %1 1\n").arg(plan);
        playProcess->write(cmd.toLatin1());
    }
}

//快进
void media::on_nextBtn_clicked()
{
    plan = plan + 5;
    if(isPlaying == 1){
        cmd = QString("seek %1 1\n").arg(plan);
        playProcess->write(cmd.toLatin1());
    }
}

void media::on_stopBtn_clicked()
{
    if(isPlaying == 1){
        cmd = QString("stop \n");
        playProcess->write(cmd.toLatin1());
        timeClock->stop();
        ui->seek->setValue(0);

    }
}

void media::on_seek_sliderPressed()
{
    timeClock->stop();
    on_off_slider = true;
}
