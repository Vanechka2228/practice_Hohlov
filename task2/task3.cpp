#include "task3.h"
#include "ui_task3.h"
#include "QMessageBox"
#include <QString>
#include <QVector>

task3::task3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::task3)
{
    ui->setupUi(this);
    ui->textEdit_2->hide();
    ui->textEdit_3->hide();
}

task3::~task3()
{
    delete ui;
}

class Matrix
{
private:
    QVector<QVector<int>> Ma;
    int rows;
    int cols;

public:
    Matrix() : rows(0), cols(0) {}
    Matrix(int M, int N) : rows(M), cols(N), Ma(M, QVector<int>(N)) {}
    Matrix(const Matrix& obj)
    {
        rows = obj.rows;
        cols = obj.cols;
        Ma = obj.Ma;
    }

    Matrix& operator=(const Matrix& obj)
    {
        if (this != &obj)
        {
            rows = obj.rows;
            cols = obj.cols;
            Ma = obj.Ma;
        }
        return *this;
    }

    QVector <int>& operator [](const auto&row_index)
    {
        if (row_index<0 || row_index>=rows)
            throw std::out_of_range ("Индекс вне диапазона");
        return Ma[row_index];
    }

    ~Matrix() {}

    void Gen(int a,int b)
    {
        if (a>b) std::swap (a,b);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                Ma[i][j] = a + rand() % (b - a + 1);
            }
        }
    }

    int Sum(int i)
    {
        int Sum=0;
            for (int j = 0; j < cols; ++j)
                Sum += Ma[i][j];
        return Sum;
    }

    int Min(QVector <int>& numbers)
    {
        numbers.clear();
        int min = Sum(0);
        for (int i = 1; i < rows;++i)
            if (Sum(i) < min) min = Sum(i);
        for (int i = 0; i < rows; i++)
            if (Sum(i) == min)
                numbers.push_back(i);
        return min;
    }
};


void task3::on_pushButton_clicked()
{
    if (ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" || ui->lineEdit->text().toInt()==0 || ui->lineEdit_2->text().toInt()==0)
    {
        QMessageBox::critical(nullptr,"Ошибка!", "Недопустимые размеры матрицы", "Повторить ввод данных");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        return;
    }
    int rows=ui->lineEdit->text().toInt();
    int cols=ui->lineEdit_2->text().toInt();
    Matrix M(rows,cols);
    M.Gen(ui->lineEdit_3->text().toInt(),ui->lineEdit_4->text().toInt());
    QString row;
    for (int i=0;i<rows;++i)
    {
        row="";
        for (int j=0;j<cols;++j)
        row+=QString::number(M[i][j])+"  ";
        ui->textEdit_2->append(row);
    }
    ui->textEdit_2->show();
    QVector <int> numbers;
    int min = M.Min(numbers);
    ui->textEdit_3->setText(QString("Минимальная сумма элементов строки - %1").arg(min));
    for (int i=0;i<numbers.size();++i)
    {
        ui->textEdit_3->append(QString("Минимальную сумму элементов имеет строка под номером %1").arg(numbers[i]+1));
    }
    ui->textEdit_3->show();
}


void task3::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
}

