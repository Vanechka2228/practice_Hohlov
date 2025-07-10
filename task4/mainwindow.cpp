/*
 Хохлов Иван, 1 курс, 5 группа

Условие задачи: на основе условия задачи лаб26 для консольного приложения сделать GUI-приложение

Создать два бинарных файла с записями следующей структуры:
        struct  Student
        {
            long	num;		// номер зачетки
            char	name[10];	// имя студента
            int	group;		// номер группы
            double	grade;		// средний бал
        };
    1.1. Разработать программу, которая выполняет над заданными файлами алгебраические операции объединения (?), пересечения (?) и разности (-).
Результат выполнения эти операций записывается в третий файл. Имя исходных файлов вводится с консоли,
а имя выходного файла определяется самой программой и выводится на консоль.
Операция над файлами удовлетворяют следующим требованиям:
операция объединения включает в результирующий файл только такие записи, которые находятся хотя бы в одном из двух входных файлах;
операция пересечения включает в результирующий файл только такие записи, которые находятся одновременно в двух входных файлах;
операция разности включает в результирующий файл только такие записи, которые находятся в первом файле и отсутствуют во втором файле;
Запросы на выполнение операций оформить в виде меню.
    1.2. Разработать программу, которая сортирует файл а) по номерам зачеток, б) по номерам групп, а внутри групп по фамилиям студентов. Запросы на сортировку выполнить в виде меню.

Заготовлены два тестовых бинарных файла bin1.bin и bin2.bin со структурами Stud (созданы на основе файлов Stud1.txt и Stud2.txt соотвественно),
но программа позволяет создать свои бинарные файлы на основе текстовых (функция makeBin).
Результаты программа выводит в текстовый файл Result.txt и на экран.
*Кроме указанных в условии, добавлена сортировка студентов по среднему баллу

*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataStream>
#include <QString>
#include <QFile>
#include <QVector>
#include <QTextStream>
#include <QVector>
#include <algorithm>
#include <QMessageBox>
#include <QFileDialog>

struct Student
{
    long num;   // номер зачетки
    QString name;   // имя студента
    int group;  // номер группы
    double grade;   // средний бал

    Student(long num, QString name, int group, double grade): num(num), name(name), group(group), grade(grade) {}
    Student(): num(0), name(""), group(0), grade(0.0) {}

    bool operator==(const Student &other) const
    {
        return (num == other.num) && (name == other.name) && (group == other.group) && (grade == other.grade);
    }

    friend QDataStream& operator<<(QDataStream& out, const Student& stud)
    {
        out << static_cast<qint64>(stud.num);
        out << stud.name << stud.group << stud.grade;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, Student& stud)
    {
        qint64 tempNum;
        in >> tempNum >> stud.name >> stud.group >> stud.grade;
        stud.num = static_cast<long>(tempNum);
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, const Student& stud)
    {
        out << stud.num << " " << stud.name << " " << stud.group << " " << stud.grade;
        return out;
    }

    friend QTextStream& operator>>(QTextStream& in, Student& stud)
    {
        in>>stud.num>>stud.name>>stud.group>>stud.grade;
        return in;
    }

    QString ListFormat ()
    {
        QString stud = QString::number(num)+" "+name+" "+QString::number(group)+" "+QString::number(grade);
        return stud;
    }
};

QVector <Student> Union (const QVector <Student>& Q1, const QVector <Student>& Q2)
{
    QVector <Student> temp = Q1;
    for (const auto &s:Q2)
        if (std::find(temp.begin(),temp.end(),s) == temp.end())
            temp.push_back(s);
    return temp;
}

QVector <Student> Intersection (const QVector <Student>& Q1,const QVector <Student>& Q2)
{
    QVector <Student> temp;
    for (const auto &s:Q1)
        if (std::find(Q2.begin(),Q2.end(),s) != Q2.end())
            temp.push_back(s);
    return temp;
}

QVector <Student> Difference (const QVector <Student>& Q1, const QVector <Student>& Q2)
{
    QVector <Student> temp;
    for (const auto &s:Q1)
        if (std::find(Q2.begin(),Q2.end(),s) == Q2.end())
            temp.push_back(s);
    return temp;
}

template<typename Container, typename Compare>
void Sort(Container &c, Compare cmp)
{
    std::sort(c.begin(), c.end(), cmp);
}


void MakeBin(const QString &textFileName, const QString &binFileName)
{    
    QFile textFile(textFileName);
    if (!textFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка", QString("Не удалось открыть текстовый файл %1").arg(textFileName));
        return;
    }
    QTextStream in(&textFile);
    QFile binFile(binFileName);
    if (!binFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        QMessageBox::critical(nullptr, "Ошибка", QString("Не удалось открыть бинарный файл %1").arg(binFileName));
        return;
    }
    QDataStream out(&binFile);
        QVector<Student> students;
        Student stud;
        while (!in.atEnd())
        {
            in >> stud;
            students.push_back(stud);
        }
        textFile.close();
        for (const auto& stud : students)
        {
            out << stud;
        }
        binFile.close();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    statusBar()->setVisible(true);
    ui->listWidget->hide();
    ui->listWidget_2->hide();
    ui->listWidget_3->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    QMessageBox::information(nullptr,"","Условие задания можно посмотреть в шапке файла mainwindow.cpp");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QVector <Student> Stud1;
QVector <Student> Stud2;
QVector <Student> Result;
bool saved=true;

void MainWindow::on_actionConvert_to_binary_1_triggered()
{
    QString textFileName = QFileDialog::getOpenFileName(this, "Выберите первый текстовый файл", "");
    if (textFileName=="") return;
    m_textFileName_1 = textFileName;
    QString binFileName = QFileDialog::getSaveFileName(this, "Выберите или создайте первый бинарный файл", "");
    if (binFileName=="") return;
    m_binFileName_1 = binFileName;
    MakeBin(m_textFileName_1,m_binFileName_1);
    statusBar()->showMessage(QString("Данные из текстового файла %1 успешно записаны в бинарный %2").arg(m_textFileName_1).arg(m_binFileName_1),4000);
}


void MainWindow::on_actionRead_from_binary_1_triggered()
{
    m_binFileName_1 = QFileDialog::getOpenFileName(this, "Выберите первый бинарный файл", "");
    if (m_binFileName_1=="") return;
    QFile f(m_binFileName_1);
    if (!f.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return;
    }
    QDataStream in(&f);
    Stud1.clear();
    Student s;
    while (!in.atEnd())
    {
        in >> s;
        Stud1.push_back(s);
    }
    f.close();
    ui->listWidget->clear();
    for (auto &s:Stud1)
    {
        ui->listWidget->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget->count(); ++i)
    {
        ui->listWidget->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->label->show();
    ui->listWidget->show();
    ui->listWidget_3->hide();
    ui->label_3->hide();
    ui->label_4->hide();
}


void MainWindow::on_actionConvert_to_binary_2_triggered()
{
    QString textFileName = QFileDialog::getOpenFileName(this, "Выберите второй текстовый файл", "");
    if (textFileName=="") return;
    m_textFileName_2 = textFileName;
    QString binFileName = QFileDialog::getSaveFileName(this, "Выберите или создайте второй бинарный файл", "");
    if (binFileName=="") return;
    m_binFileName_2 = binFileName;
    MakeBin(m_textFileName_2,m_binFileName_2);
    statusBar()->showMessage(QString("Данные из текстового файла %1 успешно записаны в бинарный %2").arg(m_textFileName_2).arg(m_binFileName_2),4000);
}


void MainWindow::on_actionRead_from_binary_2_triggered()
{
    m_binFileName_2 = QFileDialog::getOpenFileName(this, "Выберите первый бинарный файл", "");
    if (m_binFileName_2=="") return;
    QFile f(m_binFileName_2);
    if (!f.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось открыть файл");
        return;
    }
    QDataStream in(&f);
    Stud2.clear();
    Student s;
    while (!in.atEnd())
    {
        in >> s;
        Stud2.push_back(s);
    }
    f.close();
    ui->listWidget_2->clear();
    for (auto &s:Stud2)
    {
        ui->listWidget_2->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget_2->count(); ++i)
    {
        ui->listWidget_2->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->label_2->show();
    ui->listWidget_2->show();
    ui->listWidget_3->hide();
    ui->label_3->hide();
    ui->label_4->hide();
}

void MainWindow::on_actionUnion_triggered()
{
    Result=Union(Stud1,Stud2);
    ui->listWidget_3->clear();
    for (auto &s:Result)
    {
        ui->listWidget_3->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget_3->count(); ++i)
    {
        ui->listWidget_3->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->label_4->hide();
    ui->label_3->setText("Объединение");
    ui->label_3->show();
    ui->listWidget_3->show();
    saved=false;
}


void MainWindow::on_actionIntrersection_triggered()
{
    Result=Intersection(Stud1,Stud2);
    ui->listWidget_3->clear();
    for (auto &s:Result)
    {
        ui->listWidget_3->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget_3->count(); ++i)
    {
        ui->listWidget_3->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->label_4->hide();
    ui->label_3->setText("Пересечение");
    ui->label_3->show();
    ui->listWidget_3->show();
    saved=false;
}


void MainWindow::on_actionDifference_triggered()
{
    Result=Difference(Stud1,Stud2);
    ui->listWidget_3->clear();
    for (auto &s:Result)
    {
        ui->listWidget_3->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget_3->count(); ++i)
    {
        ui->listWidget_3->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    ui->label_4->hide();
    ui->label_3->setText("Разница");
    ui->label_3->show();
    ui->listWidget_3->show();
    saved=false;
}



void MainWindow::on_actionSort_by_numbers_triggered()
{
    Sort(Result,[](const Student&a,const Student&b){return a.num<b.num;});
    ui->listWidget_3->clear();
    for (auto &s:Result)
    {
        ui->listWidget_3->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget_3->count(); ++i)
    {
        ui->listWidget_3->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    saved=false;
    ui->label_4->setText("Сортировка по номерам зачёток");
    ui->label_4->show();
}


void MainWindow::on_actionSort_by_groupes_and_names_triggered()
{
    Sort(Result,[](const Student&a,const Student&b)
    {
        if (a.group == b.group)
            return a.name.compare(b.name) < 0;
        return a.group < b.group;});
    ui->listWidget_3->clear();
    for (auto &s:Result)
    {
        ui->listWidget_3->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget_3->count(); ++i)
    {
        ui->listWidget_3->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    saved=false;
    ui->label_4->setText("Сортировка по группам");
    ui->label_4->show();
}


void MainWindow::on_actionSort_up_by_grade_triggered()
{
    Sort(Result,[](const Student&a,const Student&b)
         {
            if (a.grade == b.grade)
                return a.name.compare(b.name) < 0;
            return a.grade > b.grade;});
    ui->listWidget_3->clear();
    for (auto &s:Result)
    {
        ui->listWidget_3->addItem(s.ListFormat());
    }
    for (int i = 0; i < ui->listWidget_3->count(); ++i)
    {
        ui->listWidget_3->item(i)->setTextAlignment(Qt::AlignCenter);
    }
    saved=false;
    ui->label_4->setText("Сортировка по среднему баллу (по убыванию)");
    ui->label_4->show();
}


void MainWindow::on_actionSave_current_operation_result_to_Result_txt_triggered()
{
    QFile outputFile("Result.txt");
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, "Ошибка!", "Не удалось открыть выходной файл Result.txt");
        return;
    }
    QTextStream out (&outputFile);
    for (const auto&s: Result)
        out<<s<<Qt::endl;
    outputFile.close();
    saved=true;
    statusBar()->showMessage("Текущий результат успешно записан в файл Result.txt",4000);
}



void MainWindow::on_actionClose_the_project_triggered()
{
    if (!saved)
    {
    int ret=QMessageBox::warning(nullptr,"Последние изменения не сохранены в файле","Точно хотите выйти, не сохранив изменения?","Да","Нет");
    if (ret) return;
    }
    close();
}
