#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();


private slots:
    void on_submit_clicked();

    void on_mediaBtn_clicked();

    void on_meterBtn_clicked();

    void on_closeBtn_clicked();

    void on_account_clicked();

    void on_password_returnPressed();

private:
    Ui::login *ui;

};

#endif // LOGIN_H
