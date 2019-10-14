#ifndef SCORE_H
#define SCORE_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class score;
}

class score : public QDialog
{
    Q_OBJECT

public:
    explicit score(QWidget *parent = nullptr);
    ~score();

private slots:
    void on_cancle_clicked();

    void on_clear_score_clicked();

private:
    Ui::score *ui;
    QStandardItemModel *fault_modle;
    QStandardItemModel *fault_score;
};

#endif // SCORE_H
