#include "task2.h"
#include "ui_task2.h"
#include <QString>
#include <QMessageBox>
class Array
{
private:
    QVector<int> arr;
    int size;
public:
    Array() : size(0) {}

    Array(int N) : size(N)
    {
        arr = QVector<int>(size);
        for (int i = 0; i < size; i++)
            arr[i] = 0;
    }

    Array(const Array& Arr)
    {
        size = Arr.size;
        for (int i = 0; i < size; i++)
            arr[i] = Arr.arr[i];
    }

    ~Array() {}

    Array& operator=(const Array& Arr)
    {
        if (this != &Arr)
        {
            size = Arr.size;
            arr = Arr.arr;
        }
        return *this;
    }

    int &operator [](const int& index)
    {
        if (index<0 || index>=size)
            throw std::out_of_range("Индекс вне диапазона");
        return arr[index];
    }

    void Gen(int a, int b) //метод для заполнения массива случайными числами
    {
        if (a>b) std::swap(a,b);
        for (int i = 0; i < size; ++i)
            arr[i] = a + rand() % (b - a + 1);
    }

    void Sort()
    {
        std::sort(arr.begin(),arr.end());
    }

    Array& Intersection(Array& Arr1, Array& Arr2)
    {
        arr.clear();
        size=0;
        int i = 0, j = 0;
        while (i < Arr1.size && j < Arr2.size) // работаем, пока не достигнут конец одного из массивов X или Y
        {
            if (Arr1[i] < Arr2[j])
                i++; // если элемент из X меньше элемента из Y, i увеличивается на 1
            else if (Arr1[i] > Arr2[j])
                j++; // если элемент из X больше элемента из Y, j увеличивается на 1
            else // если элементы равны, то записываем в массив Z один раз, оба индекса для X и Y увеличиваем на 1
            {
                arr.push_back(Arr1[i]);
                i++;
                j++;
                size++;
            }
        }
        return *this;
    }

    int GetSize(){return size;}
};

task2::task2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::task2)
{
    ui->setupUi(this);
    ui->pushButton_2->hide();
    ui->label->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->textEdit_8->hide();
    ui->textEdit_9->hide();
    ui->textEdit_10->hide();
}

task2::~task2()
{
    delete ui;
}


void task2::on_pushButton_clicked()
{
    if (ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" || ui->lineEdit->text().toInt()<1 || ui->lineEdit_2->text().toInt()<1)
    {
    QMessageBox::critical(nullptr,"Ошибка!", "Недопустимые размеры массивов", "Повторить ввод данных");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        return;
    }
    int size1=ui->lineEdit->text().toInt();
    Array arr1(size1);
    int size2=ui->lineEdit_2->text().toInt();
    Array arr2(size2);
    arr1.Gen(ui->lineEdit_3->text().toInt(),ui->lineEdit_4->text().toInt());
    arr2.Gen(ui->lineEdit_5->text().toInt(),ui->lineEdit_6->text().toInt());
    arr1.Sort();
    arr2.Sort();
    QString S1;
    for (int i=0;i<size1;++i)
        S1+=QString::number(arr1[i])+" ";
    ui->label->show();
    ui->textEdit_8->show();
    ui->textEdit_8->setText(S1);
    QString S2;
    for (int i=0;i<size2;++i)
        S2+=QString::number(arr2[i])+" ";
    ui->label_3->show();
    ui->textEdit_9->show();
    ui->textEdit_9->setText(S2);
    Array arr3;
    arr3.Intersection(arr1,arr2);
    ui->label_4->show();
    ui->textEdit_10->show();
    if (arr3.GetSize()==0)
        ui->textEdit_10->setText("Пустое множество");
    else
    {
    QString S3;
    for (int i=0;i<arr3.GetSize();++i)
        S3+=QString::number(arr3[i])+" ";
    ui->textEdit_10->setText(S3);
    }
    ui->pushButton_2->show();
}

void task2::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->textEdit_8->clear();
    ui->textEdit_9->clear();
    ui->textEdit_10->clear();
}
