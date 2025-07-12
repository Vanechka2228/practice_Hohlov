#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(int &rows, int &cols, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , m_rows(rows)
    , m_cols(cols)
{
    ui->setupUi(this);
    ui->spinBox->setValue(m_rows);
    ui->spinBox->setRange(5,50);
    ui->spinBox_2->setValue(m_cols);
    ui->spinBox_2->setRange(5,50);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    m_rows=ui->spinBox->value();
    m_cols=ui->spinBox_2->value();
    accept();
}

