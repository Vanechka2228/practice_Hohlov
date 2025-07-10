#include "table.h"
#include "ui_table.h"
#include "library.h"
#include <QString>
#include <QStringList>
#include <QVector>
#include <QRegularExpression>
#include <type_traits>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>

Table::Table(QWidget *parent, int mode)
    : QDialog(parent)
    , ui(new Ui::Table)
    , mode (mode)
{
    ui->setupUi(this);
    switch (mode) {
    case 0:
    {
        ui->tableWidget->setColumnCount(3);
        QStringList headers {"Год","Автор","Название"};
        QFont font("Times New Roman", 13);
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->horizontalHeader()->setFont(font);
        auto h = ui->tableWidget->horizontalHeader();
        for (int i = 0; i < ui->tableWidget->columnCount()-1; ++i)
            h->setSectionResizeMode(i, QHeaderView::ResizeToContents);
        h->setSectionResizeMode(2, QHeaderView::Stretch);
        break;
    }
    case 1:
    {
        ui->tableWidget->setColumnCount(5);
        QStringList headers {"Год","Автор","Название","Кол-во страниц","Тип издания"};
        QFont font("Times New Roman", 13);
        ui->tableWidget->setHorizontalHeaderLabels(headers);
        ui->tableWidget->horizontalHeader()->setFont(font);
        auto h = ui->tableWidget->horizontalHeader();
        for (int i = 0; i < ui->tableWidget->columnCount()-1; ++i)
            h->setSectionResizeMode(i, QHeaderView::ResizeToContents);
        h->setSectionResizeMode(4, QHeaderView::Stretch);
        break;
    }
    }
    ui->pushButton_5->hide();
    ui->textEdit->hide();
    ui->spinBox->hide();
    ui->pushButton_6->hide();
    ui->lineEdit->hide();
    ui->tableWidget_2->hide();
    ui->label->hide();
}

Table::~Table()
{
    delete ui;
}

Library <Book> B1;
Library <Publication> P1;

void Table::on_pushButton_clicked()
{
    ui->label->clear();
    ui->label->hide();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(0);
    ui->tableWidget_2->hide();
    //удаление результатов поиска, если таковые есть на экране
    currentRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(currentRow);
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
    {
        QTableWidgetItem* item = new QTableWidgetItem(QString());
        ui->tableWidget->setItem(currentRow, col, item);
    }
    ui->textEdit->setText("ЗАПОЛНИТЕ НОВУЮ СТРОКУ ТАБЛИЦЫ И НАЖМИТЕ КНОПКУ \"ВЫПОЛНИТЬ ОПЕРАЦИЮ\"");
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->show();
    ui->pushButton_5->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    func=1;
}


void Table::on_pushButton_5_clicked()
{
    switch(func)
    {
    case 1: //добавление
    {
    for (int col=0;col<ui->tableWidget->columnCount();++col)
    {
        if (ui->tableWidget->item(currentRow,col)->text()=="")
        {
            QMessageBox::critical(nullptr,"Ошибка!","Не все поля были заполнены","Повторить ввод");
            return;
        }
    }
    QRegularExpression year_regex("^\\d{1,4}$");
    if (!year_regex.match(ui->tableWidget->item(currentRow,0)->text()).hasMatch())
    {
        QMessageBox::critical(nullptr,"Ошибка!","Год может содержать только от 1 до 4 цифр","Повторить ввод года");
        ui->tableWidget->item(currentRow,0)->setText("");
        return;
    }
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
    {
        ui->tableWidget->item(currentRow,col)->setFlags(ui->tableWidget->item(currentRow,col)->flags()&~Qt::ItemIsEditable);
    }
    switch (mode)
    {
    case 0:
    {
        Book tmp(ui->tableWidget->item(currentRow,0)->text().toInt(),ui->tableWidget->item(currentRow,1)->text(),ui->tableWidget->item(currentRow,2)->text());
        B1.Add(tmp);
        break;
    }
    case 1:
    {
        QRegularExpression pages_regex("^\\d+$");
        if (!pages_regex.match(ui->tableWidget->item(currentRow,3)->text()).hasMatch())
        {
            QMessageBox::critical(nullptr,"Ошибка!","Поле \"кол-во страниц\" может содержать только цифры","Повторить ввод кол-ва страниц");
            ui->tableWidget->item(currentRow,3)->setText("");
            return;
        }
        Publication tmp(ui->tableWidget->item(currentRow,0)->text().toInt(),ui->tableWidget->item(currentRow,1)->text(),ui->tableWidget->item(currentRow,2)->text(),ui->tableWidget->item(currentRow,3)->text().toInt(),ui->tableWidget->item(currentRow,4)->text());
        P1.Add(tmp);
        break;
    }
    }
    break;
    }
    case 2: //удаление
    {
        currentRow=ui->spinBox->value()-1;
        switch (mode)
        {
        case 0:
        {
            B1.Delete(currentRow);
            break;
        }
        case 1:
        {
            P1.Delete(currentRow);
            break;
        }
        }
        ui->tableWidget->removeRow(currentRow);
        ui->spinBox->hide();
        break;
    }
    case 3://редактирование
    {
        for (int col=0;col<ui->tableWidget->columnCount();++col)
        {
            if (ui->tableWidget->item(currentRow,col)->text()=="")
            {
                QMessageBox::critical(nullptr,"Ошибка!","Не все поля были заполнены","Повторить ввод");
                return;
            }
        }
        QRegularExpression year_regex("^\\d{1,4}$");
        if (!year_regex.match(ui->tableWidget->item(currentRow,0)->text()).hasMatch())
        {
            QMessageBox::critical(nullptr,"Ошибка!","Год может содержать только от 1 до 4 цифр","Повторить ввод года");
            ui->tableWidget->item(currentRow,0)->setText("");
            return;
        }
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
        {
            ui->tableWidget->item(currentRow,col)->setFlags(ui->tableWidget->item(currentRow,col)->flags()&~Qt::ItemIsEditable);
        }
        switch (mode)
        {
        case 0:
        {
            Book tmp(ui->tableWidget->item(currentRow,0)->text().toInt(),ui->tableWidget->item(currentRow,1)->text(),ui->tableWidget->item(currentRow,2)->text());
            B1.Replace(currentRow,tmp);
            break;
        }
        case 1:
        {
            QRegularExpression pages_regex("^\\d+$");
            if (!pages_regex.match(ui->tableWidget->item(currentRow,3)->text()).hasMatch())
            {
                QMessageBox::critical(nullptr,"Ошибка!","Поле \"кол-во страниц\" может содержать только цифры","Повторить ввод кол-ва страниц");
                ui->tableWidget->item(currentRow,3)->setText("");
                return;
            }
            Publication tmp(ui->tableWidget->item(currentRow,0)->text().toInt(),ui->tableWidget->item(currentRow,1)->text(),ui->tableWidget->item(currentRow,2)->text(),ui->tableWidget->item(currentRow,3)->text().toInt(),ui->tableWidget->item(currentRow,0)->text());
            P1.Replace(currentRow,tmp);
            break;
        }
        }
        break;
    }
    case 4://поиск
    {
        QString key = ui->lineEdit->text();
        if (key=="")
        {
            QMessageBox::critical(nullptr,"Ошибка!","Ключевое слово не введено","Повторить ввод");
        }
        ui->lineEdit->hide();
        ui->lineEdit->clear();
        switch(mode)
        {
        case 0:
        {
            Library <Book> matches = B1.Find(key);
            if (matches.GetSize()==0)
            {
                QMessageBox::information(nullptr,"Пусто",QString("Совпадений по запросу \"%1\" не найдено").arg(key));
                break;
            }
            else
            {
                ui->tableWidget_2->setColumnCount(3);
                QStringList headers {"Год","Автор","Название"};
                QFont font("Times New Roman", 13);
                ui->tableWidget_2->setHorizontalHeaderLabels(headers);
                ui->tableWidget_2->horizontalHeader()->setFont(font);
                auto h = ui->tableWidget_2->horizontalHeader();
                for (int i = 0; i < ui->tableWidget_2->columnCount()-1; ++i)
                    h->setSectionResizeMode(i, QHeaderView::ResizeToContents);
                h->setSectionResizeMode(2, QHeaderView::Stretch);
                for (int row=0;row<matches.GetSize();++row)
                {
                    ui->tableWidget_2->insertRow(row);
                    for (int col=0;col<3;++col)
                    {
                        QTableWidgetItem *item=new QTableWidgetItem(matches[row].bookGetter()[col]);
                        ui->tableWidget_2->setItem(row,col,item);
                    }
                }
                ui->label->setText(QString("Результаты поиска по запросу \"%1\"").arg(key));
                ui->label->show();
                ui->tableWidget_2->show();
            }
            break;
        }
        case 1:
        {
            Library <Publication> matches = P1.Find(key);
            if (matches.GetSize()==0)
            {
                QMessageBox::information(nullptr,"Пусто",QString("Совпадений по запросу \"%1\" не найдено").arg(key));
                break;
            }
            else
            {
                ui->tableWidget_2->setColumnCount(5);
                QStringList headers {"Год","Автор","Название","Кол-во страниц","Тип издания"};
                QFont font("Times New Roman", 13);
                ui->tableWidget_2->setHorizontalHeaderLabels(headers);
                ui->tableWidget_2->horizontalHeader()->setFont(font);
                auto h = ui->tableWidget_2->horizontalHeader();
                for (int i = 0; i < ui->tableWidget_2->columnCount()-1; ++i)
                    h->setSectionResizeMode(i, QHeaderView::ResizeToContents);
                h->setSectionResizeMode(4, QHeaderView::Stretch);
                for (int row=0;row<matches.GetSize();++row)
                {
                    ui->tableWidget_2->insertRow(row);
                    for (int col=0;col<5;++col)
                    {
                        QTableWidgetItem *item=new QTableWidgetItem(matches[row].pubGetter()[col]);
                        ui->tableWidget_2->setItem(row,col,item);
                    }
                }
                ui->label->setText(QString("Результаты поиска по запросу \"%1\"").arg(key));
                ui->label->show();
                ui->tableWidget_2->show();
            }
            break;
        }
        }
        break;
    }
    }
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_7->setEnabled(true);
    ui->textEdit->clear();
    ui->textEdit->hide();
    ui->pushButton_5->hide();
}


void Table::on_pushButton_2_clicked()
{
    ui->label->clear();
    ui->label->hide();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(0);
    ui->tableWidget_2->hide();
    //удаление результатов поиска, если таковые есть на экране
    if (B1.GetSize()==0 && P1.GetSize()==0)
    {
        QMessageBox::critical(nullptr,"Ошибка!","Невозможно произвести удаление - коллекция пуста");
        return;
    }
    switch (mode) {
    case 0:
    {
        ui->spinBox->setRange(1,B1.GetSize());
        break;
    }
    case 1:
    {
        ui->spinBox->setRange(1,P1.GetSize());
        break;
    }
    }
    ui->spinBox->show();
    ui->textEdit->setText("ВЫБЕРИТЕ НОМЕР ЗАПИСИ, КОТОРУЮ ХОТИТЕ УДАЛИТЬ, И НАЖМИТЕ КНОПКУ \"ВЫПОЛНИТЬ ОПЕРЦАЦИЮ\"");
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->show();
    ui->pushButton_5->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    func=2;
}



void Table::on_pushButton_3_clicked()
{
    ui->label->clear();
    ui->label->hide();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(0);
    ui->tableWidget_2->hide();
    //удаление результатов поиска, если таковые есть на экране
    if (B1.GetSize()==0 && P1.GetSize()==0)
    {
        QMessageBox::critical(nullptr,"Ошибка!","Невозможно произвести редактирование записей - коллекция пуста");
        return;
    }
    switch (mode) {
    case 0:
    {
        ui->spinBox->setRange(1,B1.GetSize());
        break;
    }
    case 1:
    {
        ui->spinBox->setRange(1,P1.GetSize());
        break;
    }
    }
    ui->spinBox->show();
    ui->textEdit->setText("ВЫБЕРИТЕ НОМЕР ЗАПИСИ, КОТОРУЮ ХОТИТЕ ОТРЕДАКТИРОВАТЬ, И НАЖМИТЕ КНОПКУ \"ВЫБРАТЬ ЗАПИСЬ\"");
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    ui->pushButton_6->show();
}


void Table::on_pushButton_6_clicked()
{
    currentRow=ui->spinBox->value()-1;
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col)
        ui->tableWidget->item(currentRow,col)->setFlags(ui->tableWidget->item(currentRow,col)->flags() | Qt::ItemIsEditable);
    ui->textEdit->setText(QString("В ТАБЛИЦЕ ОТРЕДАКТИРУЙТЕ ДАННЫЕ О ВЫБРАННОЙ ВАМИ ЗАПИСИ (ЗАПИСЬ №%1) И НАЖМИТЕ КНОПКУ \"ВЫПОЛНИТЬ ОПЕРАЦИЮ\"").arg(currentRow+1));
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->spinBox->hide();
    ui->pushButton_6->hide();
    ui->pushButton_5->show();
    func=3;
}


void Table::on_pushButton_4_clicked()
{
    ui->label->clear();
    ui->label->hide();
    ui->tableWidget_2->clear();
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(0);
    ui->tableWidget_2->hide();
    //удаление результатов поиска, если таковые есть на экране
    switch(mode)
    {
    case 0:
    {
    ui->textEdit->setText("УКАЖИТЕ КЛЮЧЕВОЕ СЛОВО (имя автора или название книги, достаточно частичного совпадения), И НАЖМИТЕ КНОПКУ \"ВЫПОЛНИТЬ ОПЕРАЦИЮ\"");
        break;
    }
    case 1:
    {
        ui->textEdit->setText("УКАЖИТЕ КЛЮЧЕВОЕ СЛОВО (имя автора,название книги, тип издания, достаточно частичного совпадения), И НАЖМИТЕ КНОПКУ \"ВЫПОЛНИТЬ ОПЕРАЦИЮ\"");
        break;
    }
    }
    ui->textEdit->setAlignment(Qt::AlignCenter);
    ui->textEdit->show();
    ui->lineEdit->show();
    ui->pushButton_5->show();
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_7->setEnabled(false);
    func=4;
}



void Table::on_pushButton_7_clicked()
{
    QFile outputFile("Result.txt");
    if (!outputFile.open(QIODevice::WriteOnly|QIODevice::Truncate|QIODevice::Text))
    {
        QMessageBox::critical(nullptr,"Ошибка!","Ошибка открытия выходного файла для записи");
        return;
    }
    QTextStream output (&outputFile);
    switch (mode)
    {
    case 0:
    {
        output<<B1;
        break;
    }
    case 1:
    {
        output<<P1;
        break;
    }
    }
    outputFile.close();
    close();
}
