#ifndef TROUBLE_CODE_H
#define TROUBLE_CODE_H

#include <QDialog>
#include <fault.h>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QModelIndex>

namespace Ui {
class trouble_code;
}

class trouble_code : public QDialog
{
    Q_OBJECT

public:
    explicit trouble_code(QWidget *parent = nullptr);
    ~trouble_code();



private slots:

    void on_cancle_clicked();

    void on_clear_fault_clicked();

private:
    Ui::trouble_code *ui;
    QStringListModel *Model;
    QStandardItemModel *fault_modle;
    QStandardItemModel *fault_modle_code;
    void Init();
};

#endif // TROUBLE_CODE_H
