#ifndef SCORE_RECODE_H
#define SCORE_RECODE_H

#include <QDialog>

namespace Ui {
class score_recode;
}

class score_recode : public QDialog
{
    Q_OBJECT

public:
    explicit score_recode(QWidget *parent = nullptr);
    ~score_recode();

private slots:



    void on_gaishupian_clicked(const QModelIndex &index);

    void on_gaoyafanghupian_clicked(const QModelIndex &index);

private:
    Ui::score_recode *ui;
};

#endif // SCORE_RECODE_H
