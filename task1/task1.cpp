#include "task1.h"
#include "ui_task1.h"
#include <QStringList>
#include <QString>
#include <QMessageBox>

class Number
{
private:
    int d;
    int m;
    int y;
    int dw;

public:
    Number(){}
    Number(int day,int month,int year):d(day),m(month),y(year){}
    ~Number() {}

    int MonthCode()// получение кода месяца
    {
        if (m == 1 || m == 10) return 1;
        else if (m == 2 || m == 3 || m == 11) return 4;
        else if (m == 4 || m == 7) return 0;
        else if (m == 5) return 2;
        else if (m == 6) return 5;
        else if (m == 8) return 3;
        else if (m == 9 || m == 12) return 6;
    }

    bool Visokos()// проверка, вискосный ли год
    {
        return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    }

    int DayOfWeek()
    {
        int km = MonthCode();
        bool c = Visokos();
        if ((m == 1 || m == 2) && c)
            km -= 1;
        int last = y % 100;
        int k = 2 * (3 - (y / 100) % 4);
        int ky = (k + last + last / 4) % 7;
        dw = (d + km + ky) % 7;
        return dw;
    }
};

bool isValidDate(const int& day, const int& month, const int& year)
{
    if (month < 1 || month > 12)
        return false;
    if (day < 1)
        return false;
    int days_in_Month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
    Number temp(day, month, year);
    if (temp.Visokos())
        days_in_Month[1] = 29;
    if (day > days_in_Month[month - 1])
        return false;
    return true;
}
task1::task1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::task1)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    QStringList headers = {"день","месяц","год","день недели"};
    QFont font("Times New Roman", 12);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

task1::~task1()
{
    delete ui;
}


void task1::on_pushButton_clicked()
{
    QString S1=ui->tableWidget->item(0,0)->text();
    QString S2=ui->tableWidget->item(0,1)->text();
    QString S3=ui->tableWidget->item(0,2)->text();
    if (S1=="" || S2=="" || S3=="")
    {
        QMessageBox::critical(nullptr,"Ошибка!","Одно из полей не заполнено","Попробовать ещё раз");
        ui->tableWidget->clearContents();
        return;
    }
    if (!isValidDate(S1.toInt(),S2.toInt(),S3.toInt()))
    {
        QMessageBox::critical(nullptr,"Ошибка!","Введена несуществующая дата","Попробовать ещё раз");
        ui->tableWidget->clearContents();
        return;
    }
    Number M(S1.toInt(),S2.toInt(),S3.toInt());
    int dw=M.DayOfWeek();
    QString day;
    switch (dw)
    {
    case 0: day = "суббота"; break;
    case 1: day = "воскресенье"; break;
    case 2: day = "понедельник"; break;
    case 3: day = "вторник"; break;
    case 4: day = "среда"; break;
    case 5: day = "четверг"; break;
    case 6: day = "пятница"; break;
    }
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(day));
}


void task1::on_pushButton_2_clicked()
{
    ui->tableWidget->clearContents();
}

