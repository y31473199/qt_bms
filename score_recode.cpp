#include "score_recode.h"
#include "ui_score_recode.h"
#include "fault.h"
#include <QtDebug>
#include <QUrl>
#include <QDesktopServices>

score_recode::score_recode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::score_recode)
{
    ui->setupUi(this);
    this->setWindowTitle("教学资源");
}

score_recode::~score_recode()
{
    delete ui;
}




void score_recode::on_gaishupian_clicked(const QModelIndex &index)
{
    if(index.row() == 0) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com//animate/ev/xnycs/index.html")));
    if(index.row() == 1) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com//animate/ev/xnyzhyb/index.html")));
    if(index.row() == 2) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com//animate/ev/dlcsgzyl/index.html")));
    if(index.row() == 3) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com//animate/ev/xxcl/index.html")));
    if(index.row() == 4) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/animate/ev/rldcgzyl/index.html")));
    if(index.row() == 5) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/qrcode/ev/6.html")));
    if(index.row() == 6) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/qrcode/ev/7.html")));
    if(index.row() == 7) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/qrcode/ev/8.html")));
    if(index.row() == 8) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/qrcode/ev/9.html")));
    if(index.row() == 9) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/qrcode/ev/10.html")));
}

void score_recode::on_gaoyafanghupian_clicked(const QModelIndex &index)
{
    if(index.row() == 0) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/animate/ev1/wxgjjjcsb/index.html")));
    if(index.row() == 1) QDesktopServices::openUrl(QUrl(QLatin1String("http://edu.885car.com/animate/battery/dldczs/index.html")));
}
