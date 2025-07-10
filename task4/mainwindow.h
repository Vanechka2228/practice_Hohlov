#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionConvert_to_binary_1_triggered();

    void on_actionRead_from_binary_1_triggered();

    void on_actionConvert_to_binary_2_triggered();

    void on_actionRead_from_binary_2_triggered();

    void on_actionUnion_triggered();

    void on_actionIntrersection_triggered();

    void on_actionDifference_triggered();

    void on_actionSort_by_numbers_triggered();

    void on_actionSort_by_groupes_and_names_triggered();

    void on_actionSave_current_operation_result_to_Result_txt_triggered();

    void on_actionSort_up_by_grade_triggered();

    void on_actionClose_the_project_triggered();

private:
    Ui::MainWindow *ui;
    QString m_textFileName_1;
    QString m_binFileName_1;
    QString m_textFileName_2;
    QString m_binFileName_2;
};
#endif // MAINWINDOW_H
