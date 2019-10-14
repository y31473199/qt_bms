#ifndef MEDIA_H
#define MEDIA_H

#include <QWidget>
#include "QProcess"
#include "QListWidgetItem"
#include "QTimer"

namespace Ui {
class media;
}

class media : public QWidget
{
    Q_OBJECT

public:
    explicit media(QWidget *parent = nullptr);
    ~media();

private slots:
    void on_closeBtn_clicked();

    void on_meterBtn_clicked();

    void on_faultBtn_clicked();

    void on_playBtn_clicked();

    void playVideo(const QString fileName);

    void on_dial_valueChanged(int value);

    void on_seek_valueChanged(int value);

    void on_previousBtn_clicked();

    void on_nextBtn_clicked();

    void on_stopBtn_clicked();

    void timeDone();

    void doProcessReadyRead();

    void on_seek_sliderPressed();

    void onShowAnimationEnd();

private:
    Ui::media *ui;
    QProcess *playProcess;
    int isPlaying;//0 从未播放，1 播放中，2 暂停中，3 停止播放
    void Init(); //页面初始化函数
    QString cmd; //进程命令
    QStringList playList; //播放列表
    int plan = 0; //视频进度
    bool loginState = false;
    QTimer *timeClock;
};

#endif // MEDIA_H
