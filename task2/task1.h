#ifndef TASK1_H
#define TASK1_H

#include <QDialog>

namespace Ui {
class task1;
}

class task1 : public QDialog
{
    Q_OBJECT

public:
    explicit task1(QWidget *parent = nullptr);
    ~task1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::task1 *ui;
};

#endif // TASK1_H
