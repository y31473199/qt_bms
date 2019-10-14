#include "mainwindow.h"
#include <QApplication>
#include "qsplashscreen.h"
#include "QtDebug"
#include <QProcess>
#include <QModbusDataUnit>


int main(int argc, char *argv[])
{
    QString cpu_id = "";
    QProcess p(0);
    p.start("wmic CPU get ProcessorID");    p.waitForStarted();
    p.waitForFinished();
    cpu_id = QString::fromLocal8Bit(p.readAllStandardOutput());
    cpu_id = cpu_id.remove("ProcessorId").trimmed();
//    if(cpu_id == "178BFBFF00810F10"){
        QApplication app(argc, argv);
        QPixmap pixmap(":start/zzicon.png");
        QSplashScreen splash(pixmap);
        splash.show();
        app.processEvents();
        //for(long index = 0; index <= 1000000000; index++);
        MainWindow w;
        w.show();
        splash.finish(&w);
        return app.exec();
//        qDebug()<<"id符合";
//    }
//    cpu_id_myself = 178BFBFF00810F10
//    cpu_id_frist = BFEBFBFF000506C9
}

