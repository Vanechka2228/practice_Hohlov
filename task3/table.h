#ifndef TABLE_H
#define TABLE_H
#include <QDialog>


namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent=nullptr,int mode=0);
    ~Table();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::Table *ui;
    int currentRow;
    int mode;
    int func;
};

#endif // TABLE_H
